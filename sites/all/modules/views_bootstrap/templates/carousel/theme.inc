<?php

/**
 * @file
 * Preprocessors and helper functions for carousel theming.
 */

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_carousel_plugin_style(&$vars) {

  if ($vars['options']['items_per_slide'] > 1) {
    $rows = array();

    foreach ($vars['rows'] as $key => $row) {
      $mod = $key % (int) $vars['options']['items_per_slide'];
      if ($mod == 0) {
        $rows[] = $row;
      }
      else {
        $rows[(count($rows) - 1)] .= $row;
      }
    }

    $vars['rows'] = $rows;
  }

  $vars['classes_array'][] = 'carousel slide';

  $vars['attributes_array'] = array(
    'data-ride' => 'carousel',
    'data-interval' => $vars['options']['interval'] ? (int) $vars['options']['interval'] : 'false',
    'data-pause' => $vars['options']['pause'] ? 'hover' : 'false',
    'data-wrap' => (bool) $vars['options']['wrap'] ? 'true' : 'false',
  );
  if (count($vars['rows']) > 1) {
    $vars['navigation'] = (bool) $vars['options']['navigation'];
    $vars['indicators'] = (bool) $vars['options']['indicators'];
  }
  else {
    $vars['navigation'] = FALSE;
    $vars['indicators'] = FALSE;
  }
  $keys = array_keys($vars['rows']);
  $vars['first_key'] = reset($keys);
}

/**
 * Implementation of template preprocess for the view fields.
 */
function template_preprocess_views_bootstrap_carousel_plugin_rows(&$vars) {
  $view = &$vars['view'];
  // Clone value because get_field will unset it.
  $row_index = $view->row_index;

  foreach ($vars['options'] as $id => $field) {
    if (isset($view->field[$field])) {
      $vars[$id] = $view->style_plugin->get_field($row_index, $field);
    }
  }
}
