<?php
/**
 * @file
 * Cookies manager for EU/Italian Cookies Law.
 *
 * Date: 18/giu/2015 17:57:12
 * File: divascookies.admin.inc
 * Author: stefano.
 */

/**
 * Implements element validate form.
 *
 * SC 23/giu/2015 11:08:25 stefano.
 */
function divascookies_settings_text_validate($element, &$form_state) {
  if (trim(check_plain($element['value'])) == '') {
    form_set_error($element['name'], t('You must put some text into @name (not HTML).', array(
      '@name' => $element['title']
    )));
  }
}

/**
 * Implements element validate form.
 *
 * SC 23/giu/2015 11:08:25 stefano.
 */
function divascookies_settings_url_validate($element, &$form_state) {
  $value = check_plain($element['value']);
  if (!valid_url($value) && !(!$element['required'] && trim($value) == '')) {
    form_set_error($element['name'], t('You must put a valid URL into @name.', array(
      '@name' => $element['title']
    )));
  }
}

/**
 * Implements element validate form.
 *
 * SC 23/giu/2015 11:08:25 stefano.
 */
function divascookies_settings_integer_positive_validate($element, &$form_state) {
  $value = $element['value'];
  if ($value !== '' && (!is_numeric($value) || intval($value) != $value || $value <= 0)) {
    form_set_error($element['name'], t('@name must be a positive integer.', array('@name' => $element['title'])));
  }
}
