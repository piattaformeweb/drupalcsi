<?php
/**
 * @file
 * Cookies manager for EU/Italian Cookies Law.
 *
 * Instantiate Divas Cookies:
 * bannerText : "This website uses cookies in order to improve your web
 * experience. ", // text for the Divas Cookies banner
 * cookiePolicyLink : "yourprivacy.html", // link to the extended cookie policy
 * cookiePolicyLinkText : "More info", // text for the link to the extended
 * cookie policy
 * thirdPartyPolicyWidget : "", // if set to "iubenda" tries to use the Iubenda
 * widget
 * acceptButtonText : "OK", // text for the close button
 * acceptButtonSrc : "", // source for the close button image
 * openEffect : "slideDown", // opening effect for Divas Cookies banner ["fade",
 * "slideUp", "slideDown", "slideLeft", "slideRight"]
 * openEffectDuration : 600, // duration of the opening effect (msec)
 * openEffectEasing : "swing", // easing for the opening effect
 * closeEffect : "slideUp", // closing effect for Divas Cookies banner ["fade",
 * "slideUp", "slideDown", "slideLeft", "slideRight"]
 * closeEffectDuration : 600, // duration of the closing effect (msec)
 * closeEffectEasing : "swing", // easing for the closing effect
 * debugMode : false, // if true, the options are checked and warnings are shown
 * saveUserPreferences : true, // if true, sets a cookie after the Divas Cookies
 * is closed the first time and never shows it again
 * cookieDuration : 30, // number of days after which the Divas Cookie technical
 * cookie will expire (default 365 days)
 * blockScripts : true, // set this to true if you blocked scripts by wrapping
 * them with if($.DivasCookies.optedIn()){**script to be blocked**} or with the
 * add class + change type in <script> tag (default false)
 * pageReload : true, // if true reloads the actual page after opt-in to show
 * the previuosly inline blocked scripts (default false)
 * acceptOnScroll : true, // if true sets the Divas Cookie technical cookie on
 * page scroll for cookies agreement (default false)
 * acceptOnClick : false, // if true sets the Divas Cookie technical cookie on
 * click on any in the page except that on Divas Cookies banner for cookies
 * agreement (default false)
 * excludePolicyPage : false // if true excludes the cookie policy page from
 * acceptOnScroll and acceptOnClick (default false)
 *
 * The parameters "saveUserPreferences" and "blockScripts" must be set to true
 * (see options configuration above).
 * Moreover, if you want the page to be reloaded immediately after the user has
 * accepted the cookies (so that the previously inline blocked scripts are
 * immediately executed), set also the "pageReload" parameter to true (see
 * options configuration above).
 *
 * Date: 22/giu/2015 22:30:54
 * File: divascookies.variable.inc
 * Author: stefano
 */

/**
 * Implements hook_variable_info().
 *
 * SC 22/giu/2015 23:11:47 stefano.
 */
function divascookies_variable_info($options) {
  $options_effect = array(
    "fade" => t('Fade'),
    "slideUp" => t('Slide up'),
    "slideDown" => t('Slide down'),
    "slideLeft" => t('Slide left'),
    "slideRight" => t('Slide right')
  );
  $options_enable = array(
    'false' => t('false'),
    'true' => t('true')
  );

  // List of css files from library.
  //
  // SC 29 giu 2015 11:33:31 stefano.
  //
  $options_css = _divascookie_get_css();

  $variables['divascookies_bannerText'] = array(
    // 'name' isn't really necessary, as it will get populated from the key of
    // this array above.
    // 'name' => '',
    'type' => 'string',
    'title' => t('Banner text'),
    'description' => t('Text for the Divas Cookies banner.'),
    'default' => t('This website uses cookies in order to improve your web experience.', array(), $options),
    'required' => TRUE,
    'localize' => TRUE,
    'element' => array(
      '#type' => 'textarea',
      '#size' => 60,
      '#weight' => 0
    ),
    'validate callback' => 'divascookies_settings_text_validate',
    'group' => 'divascookies'
  );

  $variables['divascookies_cookiePolicyLink'] = array(
    'type' => 'string',
    'title' => t('Cookie policy link'),
    'description' => t('Link to the extended cookie policy.'),
    'default' => '',
    'required' => TRUE,
    'localize' => TRUE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 60,
      '#weight' => 1
    ),
    'validate callback' => 'divascookies_settings_url_validate',
    'group' => 'divascookies'
  );
  $variables['divascookies_cookiePolicyLinkText'] = array(
    'type' => 'string',
    'title' => t('Cookie policy link text'),
    'description' => t('Text for the link to the extended cookie policy.'),
    'default' => t('More info'),
    'required' => TRUE,
    'localize' => TRUE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 60,
      '#weight' => 2
    ),
    'validate callback' => 'divascookies_settings_text_validate',
    'group' => 'divascookies'
  );
  $variables['divascookies_thirdPartyPolicyWidget'] = array(
    'type' => 'string',
    'title' => t('Third party policy widget'),
    'description' => t('If set to "iubenda" tries to use the Iubenda widget.'),
    'default' => '',
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 60,
      '#weight' => 3
    ),
    // 'validate callback' => 'divascookies_settings_text_validate',
    'group' => 'divascookies'
  );
  $variables['divascookies_acceptButtonText'] = array(
    'type' => 'string',
    'title' => t('Accept button text'),
    'description' => t('Text for the close button.'),
    'default' => t('OK'),
    'required' => TRUE,
    'localize' => TRUE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 60,
      '#weight' => 4
    ),
    'validate callback' => 'divascookies_settings_text_validate',
    'group' => 'divascookies'
  );
  $variables['divascookies_acceptButtonSrc'] = array(
    'type' => 'string',
    'title' => t('Accept button src'),
    'description' => t('Source for the close button image.'),
    'default' => '',
    'required' => FALSE,
    'localize' => TRUE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 60,
      '#weight' => 5
    ),
    'validate callback' => 'divascookies_settings_url_validate',
    'group' => 'divascookies'
  );

  $variables['divascookies_openEffect'] = array(
    'type' => 'select',
    'title' => t('Open effect'),
    'description' => t('Opening effect for Divas Cookies banner.'),
    'default' => 'slideDown',
    'options' => $options_effect,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'select',
      '#size' => 6,
      '#weight' => 6
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_openEffectDuration'] = array(
    'type' => 'number',
    'title' => t('Open effect duration'),
    'description' => t('Duration of the opening effect (msec).'),
    'default' => 600,
    'required' => TRUE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 3,
      '#weight' => 7
    ),
    'validate callback' => 'divascookies_settings_integer_positive_validate',
    'group' => 'divascookies'
  );

  // $variables['divascookies_openEffectEasing'] = array(
  // '#type' => 'textfield',
  // '#size' => 30,
  // '#title' => t('openEffectEasing'),
  // '#description' => t('Easing for the opening effect.'),
  // '#default' => check_plain(variable_get('divascookies_openEffectEasing',
  // 'swing')),
  // '#required' => TRUE,
  // '#weight' =>8);

  $variables['divascookies_closeEffect'] = array(
    'type' => 'select',
    'title' => t('Close effect'),
    'description' => t('Closing effect for Divas Cookies banner.'),
    'default' => 'slideUp',
    'options' => $options_effect,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'select',
      '#size' => 6,
      '#weight' => 9
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_closeEffectDuration'] = array(
    'type' => 'number',
    'title' => t('Close effect duration'),
    'description' => t('Duration of the closing effect (msec).'),
    'default' => 600,
    'required' => TRUE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 3,
      '#weight' => 10
    ),
    'validate callback' => 'divascookies_settings_integer_positive_validate',
    'group' => 'divascookies'
  );

  // $variables['divascookies_closeEffectEasing'] = array(
  // '#type' => 'textfield',
  // '#size' => 30,
  // '#title' => t('Close effect easing'),
  // '#description' => t('Easing for the closing effect.'),
  // '#default' => check_plain(variable_get('divascookies_closeEffectEasing',
  // 'swing')),
  // '#required' => FALSE,
  // '#weight' => 11);

  $variables['divascookies_saveUserPreferences'] = array(
    'type' => 'select',
    'title' => t('Save user preferences'),
    'description' => t('If true, sets a cookie after the Divas Cookies is closed the first time and never shows it again.'),
    'default' => 'true',
    'options' => $options_enable,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'radios',
      // '#size' => 30,
      '#weight' => 13
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_cookieDuration'] = array(
    'type' => 'number',
    'title' => t('Cookie duration'),
    'description' => t('Number of days after which the Divas Cookie technical cookie will expire.'),
    'default' => 30,
    'required' => TRUE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'textfield',
      '#size' => 3,
      '#weight' => 14
    ),
    'validate callback' => 'divascookies_settings_integer_positive_validate',
    'group' => 'divascookies'
  );

  $variables['divascookies_blockScripts'] = array(
    'type' => 'select',
    'title' => t('Block scripts'),
    'description' => check_plain(t('Set this to true if you blocked scripts by wrapping them with if($.DivasCookies.optedIn()){**script to be blocked**} or with the add class + change type in <script> tag.')),
    'default' => 'true',
    'options' => $options_enable,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'radios',
      // '#size' => 30,
      '#weight' => 15
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_pageReload'] = array(
    'type' => 'select',
    'title' => t('Page reload'),
    'description' => t('If true reloads the actual page after opt-in to show the previuosly inline blocked scripts.'),
    'default' => 'true',
    'options' => $options_enable,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'radios',
      // '#size' => 30,
      '#weight' => 16
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_acceptOnScroll'] = array(
    'type' => 'select',
    'title' => t('Accept on scroll'),
    'description' => t('If true sets the Divas Cookie technical cookie on page scroll for cookies agreement.'),
    'default' => 'false',
    'options' => $options_enable,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'radios',
      // '#size' => 30,
      '#weight' => 17
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_acceptOnClick'] = array(
    'type' => 'select',
    'title' => t('Accept on click'),
    'description' => t('If true sets the Divas Cookie technical cookie on click on any  in the page except that on Divas Cookies banner for cookies agreement.'),
    'default' => 'true',
    'options' => $options_enable,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'radios',
      // '#size' => 30,
      '#weight' => 18
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_excludePolicyPage'] = array(
    'type' => 'select',
    'title' => t('Exclude policy page'),
    'description' => t('If true excludes the cookie policy page from Accept on scroll and Accept on click.'),
    'default' => 'false',
    'options' => $options_enable,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'radios',
      // '#size' => 30,
      '#weight' => 19
    ),
    'group' => 'divascookies'
  );

  $variables['divascookies_css'] = array(
    'type' => 'select',
    'title' => t('CSS file'),
    'description' => t('If you need personalizations, add these CSS rules in your theme and change them.'),
    'default' => 'divascookies_style_dark_bottom.css',
    'options' => $options_css,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'select',
      // '#size' => 30,
      '#weight' => 20
    ),
    'group' => 'divascookies'
  );
  $variables['divascookies_debugMode'] = array(
    'type' => 'select',
    'title' => t('Debug mode'),
    'description' => t('If true, the options are checked and warnings are shown.'),
    'default' => 'false',
    'options' => $options_enable,
    'required' => FALSE,
    'localize' => FALSE,
    'element' => array(
      '#type' => 'radios',
      // '#size' => 30,
      '#weight' => 21
    ),
    'group' => 'divascookies'
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 *
 * SC 22/giu/2015 23:12:25 stefano.
 */
function divascookies_variable_group_info() {
  $groups['divascookies'] = array(
    'title' => t('Divas Cookies settings'),
    'access' => 'divascookies admin settings',
    'path' => 'admin/config/system/divascookies'
  );
  return $groups;
}
