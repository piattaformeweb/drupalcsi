<?php

/**
 * @file
 * Views integration for the Weight module.
 */

/**
 * Implements hook_field_views_data().
 */
function weight_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $field_name = $field['field_name'];

  foreach ($data as $table_name => $table_data) {
    if (isset($table_data[$field_name])) {
      $selector_field = $table_data[$field_name];
      $title = t('@title Selector', array('@title' => $table_data[$field_name]['title']));
      $selector_field['title'] = $title;
      $selector_field['title short'] = $title;
      $selector_field['field']['handler'] = 'views_handler_weight_selector';
      $selector_field['field']['click sortable'] = FALSE;
      $selector_field['field']['additional fields'][] = 'entity_id';
      $data['field_data_' . $field_name][$field_name . '_selector'] = $selector_field;
    }
  }

  return $data;
}
