<?php

/**
 * @file
 * Preprocessors and helper functions for dropdown theming.
 */

/**
 * Implementation of template preprocess for the view.
 */
function template_preprocess_views_bootstrap_dropdown_plugin_style(&$vars) {
  $view = &$vars['view'];

  $wrapper_class = explode(' ', $vars['options']['wrapper_class']);
  $wrapper_class[] = 'dropdown';
  $wrapper_class = array_map('drupal_clean_css_identifier', $wrapper_class);
  $vars['wrapper_class'] = implode(' ', $wrapper_class);

  $vars['wrapper_prefix'] = '<div id="views-bootstrap-dropdown-' . $vars['id'] . '" class="' . implode(' ', $wrapper_class) . '">';
  $vars['wrapper_suffix'] = '</div>';

  $vars['button_text'] = filter_xss_admin($vars['options']['button_text']);
  $vars['button_class'] = filter_xss_admin($vars['options']['button_class']);

  $class = explode(' ', $vars['options']['class']);
  $class[] = "dropdown-menu";
  $class = array_map('drupal_clean_css_identifier', $class);
  $vars['class'] = implode(' ', $class);

  $vars['list_type_prefix'] = '<ul class="' . implode(' ', $class) . '" role="menu" aria-labelledby="' . $id . '-dropdown">';
  $vars['list_type_suffix'] = '</ul>';

  // Inject additional dropdown aria attributes into the individual rows to
  // make them behave as menu items.
  // The most common case should be one linked field, but there seems
  // no reason why the whole rendered row can't be here if that's what you want.
  foreach ($vars['rows'] as $id => $row) {
    $vars['rows'][$id] = array();
    $vars['rows'][$id]['content'] = $row;

    // Using role=presentation here is supposed to diminish the screen readers
    // treatment of list items as "List Items". Being a menu item is sufficient.
    // tabindex -1 means that all these links will not waylay keyboard
    // navigation (until the user deliberately opens that list).
    $attributes = array(
      'role' => 'menuitem presentation',
      'tabindex' => -1,
    );
    if ($row_class = $vars['view']->style_plugin->get_row_class($id)) {
      $attributes['class'] = $row_class;
    }
    $vars['rows'][$id]['attributes'] = drupal_attributes($attributes);
  }
}
