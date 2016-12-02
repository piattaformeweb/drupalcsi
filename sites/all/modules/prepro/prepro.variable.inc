<?php
/**
 * Variable module integration.
 */

/**
 * Implements hook_variable_info().
 */
function prepro_variable_info($options) {
  $variable = array();

  $variable['prepro'] = array(
    'title' => t('Preprocessors'),
    'type' => 'prepro_settings',
    'access' => 'administer site configuration',
  );

  return $variable;
}

/**
 * Implements hook_variable_type_info().
 */
function prepro_variable_type_info() {
  $type = array();

  $type['prepro_settings'] = array(
    'title' => t('Prepro settings'),
    'element callback' => 'prepro_variable_element_prepro_settings',
  );

  return $type;
}

/**
 * Element callback for Prepro settings variable type.
 */
function prepro_variable_element_prepro_settings($variable, $options = array()) {
  $form = $form_state = array();

  module_load_include('inc', 'prepro', 'prepro.admin');
  $form = prepro_admin_form($form, $form_state, FALSE);

  return $form['prepro'];
}
