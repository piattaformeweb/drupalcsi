<?php

/**
 * @file
 * Preprocessors and helper functions for panel theming.
 */

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_panel_plugin_style(&$vars) {
  $view = &$vars['view'];

  $heading_field = $vars['options']['heading_field'];
  $footer_field = $vars['options']['footer_field'];
  $label_field = isset($vars['options']['label_field']) ? $vars['options']['label_field'] : NULL;

  $vars['context'] = $vars['options']['context'];
  $vars['title_flag'] = $vars['options']['title'];
  $vars['title_tag'] = $vars['options']['title_tag'];

  $vars['headers'] = $vars['labels'] = $vars['footers'] = array();

  // Get headers.
  if (isset($view->field[$heading_field])) {
    foreach (array_keys($vars['rows']) as $key) {
      $vars['headers'][$key] = $view->style_plugin->get_field($key, $heading_field);
    }
  }

  // Get labels.
  if (isset($view->field[$label_field])) {
    foreach (array_keys($vars['rows']) as $key) {
      $vars['labels'][$key] = $view->style_plugin->get_field($key, $label_field);
    }
  }

  // Get footers.
  if (isset($view->field[$footer_field])) {
    foreach (array_keys($vars['rows']) as $key) {
      $vars['footers'][$key] = $view->style_plugin->get_field($key, $footer_field);
    }
  }

}
