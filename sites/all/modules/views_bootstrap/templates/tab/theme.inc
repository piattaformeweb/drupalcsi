<?php

/**
 * @file
 * Preprocessors and helper functions for tab theming.
 */

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_tab_plugin_style(&$vars) {
  $view = &$vars['view'];
  $tab_field = $vars['options']['tab_field'];

  $vars['tab_type'] = $vars['options']['tab_type'];
  $vars['tab_position'] = $vars['options']['tab_position'];
  $vars['tab_fade'] = $vars['options']['tab_fade'];

  // Get tabs.
  if (isset($view->field[$tab_field])) {
    foreach (array_keys($vars['rows']) as $key) {
      $vars['tabs'][$key] = filter_xss($view->style_plugin->get_field($key, $tab_field), array(
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

  $keys = array_keys($vars['rows']);
  $vars['first_key'] = reset($keys);
  drupal_add_js(drupal_get_path('module', 'views_bootstrap') . '/js/tabs.js');
  drupal_add_css(drupal_get_path('module', 'views_bootstrap') . '/css/tabs.css');
}
