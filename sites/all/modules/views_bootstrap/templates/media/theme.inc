<?php

/**
 * @file
 * Preprocessors and helper functions for panel theming.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_views_bootstrap_media_plugin_style(&$vars) {
  $view = &$vars['view'];

  $image_field = $vars['options']['image_field'];
  $heading_field = $vars['options']['heading_field'];
  $vars['image_class'] = $vars['options']['image_class'];

  foreach ($vars['rows'] as $id => $row) {
    $vars['rows'][$id] = array();
    $vars['rows'][$id]['image'] = isset($view->field[$image_field]) ? $view->style_plugin->get_field($id, $image_field) : NULL;
    $vars['rows'][$id]['heading'] = isset($view->field[$heading_field]) ? $view->style_plugin->get_field($id, $heading_field) : NULL;
    $vars['rows'][$id]['body'] = $row;
  }
}
