<?php

/**
 * @file
 * Preprocessors and helper functions for accordion theming.
 */

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_accordion_plugin_style(&$vars) {
  $view = &$vars['view'];
  $title_field = $vars['options']['title_field'];
  $vars['behavior'] = $vars['options']['behavior'];
  $label_field = isset($vars['options']['label_field']) ? $vars['options']['label_field'] : NULL;
  $vars['classes_array'][] = 'panel-group';

  // Get titles.
  if (isset($view->field[$title_field])) {
    foreach (array_keys($vars['rows']) as $key) {
      $vars['titles'][$key] = filter_xss($view->style_plugin->get_field($key, $title_field), array(
        'img',
        'br',
        'h2',
        'h3',
        'h4',
        'h5',
        'h6',
        'span',
        'strong',
        'em',
        'i',
        'small',
      ));
    }
  }
  if (isset($view->field[$label_field])) {
    foreach (array_keys($vars['rows']) as $key) {
      $vars['labels'][$key] = $view->style_plugin->get_field($key, $label_field);
    }
  }
}
