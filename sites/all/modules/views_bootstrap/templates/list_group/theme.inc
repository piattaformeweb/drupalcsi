<?php

/**
 * @file
 * Preprocessors and helper functions for list group theming.
 */

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_list_group_plugin_style(&$vars) {
  $view = $vars['view'];
  $link_field = $vars['options']['link_field'];

  $vars['linked_items'] = !empty($link_field);
  $vars['panels'] = isset($vars['options']['panels']) ? $vars['options']['panels'] : FALSE;
  foreach (array_keys($vars['rows']) as $key) {
    $vars['link_fields'][$key] = $view->style_plugin->get_field($key, $link_field);
  }
}
