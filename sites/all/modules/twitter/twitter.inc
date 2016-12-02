<?php
/**
 * @file
 * Twitter API functions
 */

module_load_include('php', 'oauth_common', 'lib/OAuth');
require_once('twitter.lib.php');

/**
 * Connect to the Twitter API.
 *
 * @param object $twitter_account
 *   An authenticated twitter_account object to be used to authenticate against
 *   Twitter.
 * @param bool $access_global
 *   Whether or not to load the global accounts too.
 * @param bool $force
 *   Loads accounts regardless of other access limits. Should be used with care
 *   and only for limited scenarios that do would not pose a security risk.
 *
 * @return
 *   A Twitter object ready to be used to query the Twitter API or FALSE.
 */
function twitter_connect($twitter_account = NULL, $access_global = FALSE, $force = FALSE) {
  if (empty($twitter_account)) {
    // Load all authenticated accounts, passing in the same access requirements.
    $accounts = twitter_load_authenticated_accounts(NULL, $access_global, $force);

    // If no accounts were found, there's a problem.
    if (empty($accounts)) {
      watchdog('twitter', 'There are no authenticated Twitter accounts to use for API connections.');
    }

    // Grab the first authenticated account.
    else {
      $twitter_account = reset($accounts);
    }
  }

  if (!empty($twitter_account)) {
    $auth = $twitter_account->get_auth();
    if (isset($auth['oauth_token']) && isset($auth['oauth_token_secret'])) {
      return new Twitter(
        variable_get('twitter_consumer_key', ''),
        variable_get('twitter_consumer_secret', ''),
        $auth['oauth_token'],
        $auth['oauth_token_secret']
      );
    }
  }

  return FALSE;
}

/**
 * Loads a Twitter account by its screen_name.
 *
 * @param string $screen_name
 *   A Twitter account name.
 * @return
 *   A TwitterAccount object or FALSE.
 */
function twitter_account_load($screen_name) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'twitter_account')
    ->propertyCondition('screen_name', $screen_name);
  $result = $query->execute();

  $ids = !empty($result['twitter_account']) ? array_keys($result['twitter_account']) : array();
  if (count($ids)) {
    return entity_load_single('twitter_account', array_pop($ids));
  }
  else {
    return FALSE;
  }
}

/**
 * Loads all Twitter accounts added by a Drupal user.
 *
 * This excludes Twitter accounts added automatically when,
 * for example, pulling mentions of an account from the Twitter API.
 *
 * @return array
 *   A list of TwitterAccount objects.
 */
function twitter_load_accounts() {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'twitter_account')
    ->propertyCondition('uid', 0, '<>')
    ->propertyOrderBy('screen_name');
  $result = $query->execute();

  $ids = !empty($result['twitter_account']) ? array_keys($result['twitter_account']) : array();
  if (count($ids)) {
    return entity_load('twitter_account', $ids);
  }
  else {
    return array();
  }
}

/**
 * Bare list of all account names, keyed by Twitter ID.
 *
 * @return array
 *   A list of TwitterUser objects.
 */
function twitter_load_account_names() {
  $accounts = array();
  foreach (twitter_load_accounts() as $account) {
    $accounts[$account->id] = check_plain($account->name);
  }
  return $accounts;
}

/**
 * Returns a list of authenticated global or user-specific Twitter accounts.
 *
 * @param int $uid
 *   Optional Drupal user ID to limit the results against.
 * @param bool $access_global
 *   Whether or not to load the global accounts too.
 * @param bool $force
 *   Loads accounts regardless of other access limits. Should be used with care
 *   and only for limited scenarios that do would not pose a security risk.
 *
 * @return array
 *   List of TwitterUser objects. Will always include global accounts, will
 *   optionally include accounts from a specific user.
 */
function twitter_load_authenticated_accounts($uid = NULL, $access_global = TRUE, $force = FALSE) {
  $auth_accounts = array();

  // Load every Twitter account, check to see if each one is suitable.
  foreach (twitter_load_accounts() as $index => $twitter_account) {
    // Only include authenticated accounts.
    if ($twitter_account->is_auth()) {
      // Only include either global accounts or, if a $uid was passed in,
      // accounts that are owned by the requested user.
      if ($force
        || ($access_global && $twitter_account->is_global)
        || (isset($uid) && $uid == $twitter_account->uid)) {
        $auth_accounts[] = $twitter_account;
      }
    }
  }

  return $auth_accounts;
}

/**
 * Saves a TwitterStatus object to {twitter}
 */
function twitter_status_save($status) {
  // RT's get special handling.
  if (!empty($status->retweeted_status)) {
    $text = 'RT @' . $status->retweeted_status->user->screen_name . ': ' . $status->retweeted_status->text;
  }
  else {
    $text = $status->text;
  }

  $twitter_status = new TwitterStatus();
  $twitter_status->twitter_id = $status->id;
  $twitter_status->screen_name = $status->user->screen_name;
  $twitter_status->created_time = strtotime($status->created_at);
  $twitter_status->text = $text;
  $twitter_status->source = $status->source;
  $twitter_status->in_reply_to_status_id = ($status->in_reply_to_status_id > 0) ? (string) $status->in_reply_to_status_id : NULL;
  $twitter_status->in_reply_to_user_id = $status->in_reply_to_user_id;
  $twitter_status->in_reply_to_screen_name = $status->in_reply_to_screen_name;
  $twitter_status->truncated = (int) $status->truncated;
  $twitter_status->is_new = entity_load_single('twitter_status', $twitter_status->twitter_id) ? FALSE : TRUE;
  entity_save('twitter_status', $twitter_status);

  // Let other modules know that a status has been saved.
  module_invoke_all('twitter_status_save', $status);
}

/**
 * Post a message to twitter
 *
 * @param $twitter_account
 *   object with a Twitter account.
 * @param $status
 *   string message to publish.
 * @return
 *   array response from Twitter API.
 */
function twitter_set_status($twitter_account, $status) {
  $twitter = twitter_connect($twitter_account);
  if (empty($twitter)) {
    return FALSE;
  }

  return $twitter->statuses_update($status);
}

/**
 * Retrieve an embedded Tweet.
 *
 * @param int $tweet_id
 *   Status ID of the tweet.
 *
 * @return array
 *   Response from Twitter API.
 */
function twitter_statuses_oembed($tweet_id) {
  // Need to request any global account, though preferably a global account.
  $twitter = twitter_connect(NULL, TRUE, TRUE);
  if (empty($twitter)) {
    watchdog('twitter', 'Unable to load an authenticated Twitter account to embed a tweet.');
    return FALSE;
  }

  $params = array(
    'hide_media' => !variable_get('twitter_media', FALSE),
    'hide_thread' => !variable_get('twitter_conversation', FALSE),
    'align' => variable_get('twitter_align', 'none'),
  );
  return $twitter->statuses_oembed($tweet_id, $params);
}

/**
 * Fetches a user's timeline.
 */
function twitter_fetch_user_timeline($id) {
  $twitter_account = entity_load_single('twitter_account', $id);
  $since = db_query("SELECT MAX(twitter_id)
    FROM {twitter}
    WHERE screen_name = :screen_name",
    array(':screen_name' => $twitter_account->screen_name))
    ->fetchField();

  // Connect to the Twitter's API. If the account is authenticated, use that
  // account, otherwise grab the first authenticated account.
  if ($twitter_account->is_auth()) {
    $twitter = twitter_connect($twitter_account);
  }
  else {
    // Use the first authenticated account or global to download tweets.
    $twitter = twitter_connect(NULL, TRUE, TRUE);
  }

  // That should have worked, but there might have been a problem.
  if (empty($twitter)) {
    watchdog('twitter', 'Unable to authenticate to download tweets for the %name account.', array('%name' => $twitter_account->screen_name));
    return FALSE;
  }

  // Fetch tweets.
  $params = array();
  if (!empty($since)) {
    $params['since_id'] = $since;
  }

  // Trigger hook_twitter_prefetch_timeline().
  // Doing it this way so that the hook may adjust the parameters.
  $hook = 'twitter_prefetch_timeline';
  foreach (module_implements($hook) as $module) {
    $function = $module . '_' . $hook;
    if (function_exists($function)) {
      $function($account, $params);
    }
  }

  // Load the timeline.
  $statuses = $twitter->user_timeline($id, $params);

  // Trigger hook_twitter_statuses_alter().
  drupal_alter('twitter_statuses', $statuses, $twitter_account);

  // Save each tweet.
  if (count($statuses) > 0) {
    watchdog('twitter', 'Downloaded %count tweets for the %name account.', array('%count' => count($statuses), '%name' => $twitter_account->screen_name));

    foreach ($statuses as $status) {
      twitter_status_save($status);
    }
  }

  // Trigger hook_twitter_insert_statuses().
  module_invoke_all('twitter_insert_statuses', $statuses, $twitter_account);

  // Update Twitter account data.
  if (count($statuses) > 0) {
    twitter_account_save($statuses[0]->user);
  }
}

/**
 * Retweet a tweet.
 */
function twitter_retweet($twitter_account, $tweet_id) {
  module_load_include('lib.php', 'twitter');

  $twitter = twitter_connect($twitter_account);
  $twitter->retweet($tweet_id, $twitter_account);
}

/**
 * Fetches user's mentions of an authenticated account.
 */
function twitter_fetch_mentions_timeline($id) {
  $twitter_account = entity_load_single('twitter_account', $id);

  // Connect to Twitter's API using the authenticated account to fetch mentions.
  $twitter = twitter_connect($twitter_account);
  if (empty($twitter)) {
    watchdog('twitter', 'Unable to authenticate to download mentions for the %name account.', array('%name' => $account->screen_name));
    return FALSE;
  }

  $params = array();
  $statuses = $twitter->mentions_timeline($params);
  foreach ($statuses as $twitter_status) {
    twitter_account_save($twitter_status->user);
    twitter_status_save($twitter_status);
  }
}

/**
 * Pulls tweets from the database.
 *
 * @param string $screen_name
 *   Optionally provide a screen_name to filter.
 */
function twitter_tweets($screen_name = NULL) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'twitter_status');
  if (isset($screen_name)) {
    $query->entityCondition('screen_name', $screen_name);
  }
  $result = $query->execute();
  $ids = !empty($result['twitter_status']) ? array_keys($result['twitter_status']) : array();
  $twitter_statuses = entity_load('twitter_status', $ids);

  return $twitter_statuses;
}

/**
 * Saves a twitter account.
 *
 * @param object $twitter_account
 *   A TwitterAccount instance.
 */
function twitter_account_save($twitter_account) {
  $twitter_account_db = entity_load_single('twitter_account', $twitter_account->twitter_uid);
  // Check whether this account exists and load its defaults prior to save.
  $twitter_account->is_new = $twitter_account_db ? FALSE : TRUE;
  if ($twitter_account_db) {
    $twitter_account = (object) array_merge((array) $twitter_account_db, (array) $twitter_account);
  }
  entity_save('twitter_account', $twitter_account);
}

/**
 * Delete a twitter account and its statuses.
 *
 * @param $twitter_uid
 *   An integer with the Twitter UID.
 */
function twitter_account_delete($twitter_uid) {
  $account = entity_load_single('twitter_account', $twitter_uid);

  // Delete from {twitter_account}.
  entity_delete('twitter_account', $twitter_uid);

  // Delete from {twitter}.
  $twitter_statuses = twitter_tweets($account->screen_name);
  entity_delete_multiple('twitter_status', array_keys($twitter_statuses));

  // Delete from {authmap}.
  $query = db_delete('authmap');
  $query->condition('authname', $twitter_uid);
  $query->condition('module', 'twitter');
  $query->execute();
}

/**
 * Obtain an account screen name from its Twitter UID.
 *
 * @param int $twitter_uid
 *   The Twitter user account ID.
 *
 * @return string
 *   The corresponding Twitter screen name.
 */
function twitter_screen_name_from_uid($twitter_uid) {
  return db_select('twitter_account', 'ta')
    ->fields('ta', array('screen_name'))
    ->condition('twitter_uid', $twitter_uid)
    // Only want the first occurrence of this screen name.
    ->range(0, 1)
    ->execute()
    ->fetchField();
}
