<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function agid_form_system_theme_settings_alter(&$form, &$form_state) {


  $form['agid_color_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Color settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['agid_color_settings']['tabs'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['agid_color_settings']['tabs']['gallery_first'] = array(
    '#type' => 'fieldset',
    '#title' => t('First gallery'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['agid_color_settings']['tabs']['gallery_first']['color'] = array(
    '#type'          => 'radios',
    '#title'         => t('Choose color'),
    '#options'       => array(
      'section_white'         =>t('White'),
      'section_gray'          =>t('Gray'),
      'section_gray_darker'   =>t('Gray darker'),
      'section_blue'          =>t('Blue'),
      ),
    '#default_value' => theme_get_setting('color_gallery_first'),
  );

  $form['agid_color_settings']['tabs']['gallery_second'] = array(
    '#type' => 'fieldset',
    '#title' => t('Second gallery'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['agid_color_settings']['tabs']['gallery_second']['color'] = array(
    '#type'          => 'radios',
    '#title'         => t('Choose color'),
    '#options'       => array(
      'section_white'         =>t('White'),
      'section_gray'          =>t('Gray'),
      'section_gray_darker'   =>t('Gray darker'),
      'section_blue'          =>t('Blue'),
      ),
    '#default_value' => theme_get_setting('color_gallery_second'),
  );

  $form['agid_color_settings']['tabs']['gallery_third'] = array(
    '#type' => 'fieldset',
    '#title' => t('Third gallery'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['agid_color_settings']['tabs']['gallery_third']['color'] = array(
    '#type'          => 'radios',
    '#title'         => t('Choose color'),
    '#options'       => array(
      'section_white'         =>t('White'),
      'section_gray'          =>t('Gray'),
      'section_gray_darker'   =>t('Gray darker'),
      'section_blue'          =>t('Blue'),
      ),
    '#default_value' => theme_get_setting('color_gallery_third'),
  );

    $form['agid_color_settings']['tabs']['gallery_fourth'] = array(
        '#type' => 'fieldset',
        '#title' => t('Fourth gallery'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['agid_color_settings']['tabs']['gallery_fourth']['color'] = array(
        '#type'          => 'radios',
        '#title'         => t('Choose color'),
        '#options'       => array(
            'section_white'         =>t('White'),
            'section_gray'          =>t('Gray'),
            'section_gray_darker'   =>t('Gray darker'),
            'section_blue'          =>t('Blue'),
        ),
        '#default_value' => theme_get_setting('color_gallery_fourth'),
    );

    $form['agid_color_settings']['tabs']['gallery_fifth'] = array(
        '#type' => 'fieldset',
        '#title' => t('Fifth gallery'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['agid_color_settings']['tabs']['gallery_fifth']['color'] = array(
        '#type'          => 'radios',
        '#title'         => t('Choose color'),
        '#options'       => array(
            'section_white'         =>t('White'),
            'section_gray'          =>t('Gray'),
            'section_gray_darker'   =>t('Gray darker'),
            'section_blue'          =>t('Blue'),
        ),
        '#default_value' => theme_get_setting('color_gallery_fifth'),
    );

}