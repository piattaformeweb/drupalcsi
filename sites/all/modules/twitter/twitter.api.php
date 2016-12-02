<?php

/**
 * @file
 * Describe hooks provided by Twitter module.
 */

/**
 * Loads Twitter accounts for a user.
 *
 * @param $account
 *   stdClass object containing a user account.
 * @return
 *   array of stdClass objects with the associated Twitter accounts.
 * @see twitter_twitter_accounts()
 */
function hook_twitter_accounts($account) {}

/**
 * Notifies of a saved tweet.
 *
 * @param $status
 *   stdClass containing information about the status message.
 * @see https://dev.twitter.com/docs/platform-objects/tweets for details about the contents of $status.
 */
function hook_twitter_status_save($status) {}

/**
 * Alter the twitter user settings page.
 *
 * @param array $output
 *   A render array containing the user settings data.
 */
function hook_twitter_user_settings_alter(&$output) {}

/**
 * Notifies that the module is about to update a user timeline.
 *
 * @param $account
 *   User account object.
 * @param array $params
 *   Any arguments that are going to be passed to the Twitter API. May already
 *   include the 'since' argument.
 *
 * @see twitter_fetch_user_timeline()
 */
function hook_twitter_prefetch_timeline($account, $params) {
  watchdog('mymodule', 'About to fetch the tweets for %screenname.', array('%screenname' => $account->screen_name));
}

/**
 * Allow the system to modify tweets that are about to be saved.
 *
 * @param array $statuses
 *   The statuses to be saved.
 * @param object $account
 *   User account object.
 *
 * @see twitter_fetch_user_timeline()
 */
function hook_twitter_statuses_alter(&$statues, $account) {
  watchdog('mymodule', 'About to insert %count tweets for %screenname.', array('%count' => count($statuses), '%screenname' => $account->screen_name));
}

/**
 * Allow the system to react after tweets are saved.
 *
 * @param array $statuses
 *   The statuses that were saved.
 * @param object $account
 *   User account object.
 *
 * @see twitter_fetch_user_timeline()
 */
function hook_twitter_insert_statuses($statues, $account) {
  watchdog('mymodule', '%count tweets were imported for %screenname.', array('%count' => count($statuses), '%screenname' => $account->screen_name));
}
