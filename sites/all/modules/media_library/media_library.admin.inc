<?php

/**
 * @file
 * Media Library administration and module settings UI.
 */

/**
 * Form callback for Media Library settings.
 */
function media_library_settings_form($form, &$form_state) {
  $form['media_library_file_add_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add files to the media library by default'),
    '#default_value' => variable_get('media_library_file_add_default', FALSE),
    '#description' => t('Users may choose to include files added through the <a href="@url">file uploaded wizard</a> in the media library. Enable this setting to opt newly added files into the media library by default.', array('@url' => url('file/add'))),
  );

  return system_settings_form($form);
}
