<?php

/**
 * @file magnific_popup/includes/magnific_popup.formatters.inc
 *
 * Formatters for Magnific Popup.
 */

/**
 * Implements hook_field_formatter_info().
 */
function magnific_popup_field_formatter_info() {
  $gallery_options = _magnific_popup_gallery_options();

  return array(
    'magnific_popup_file_field_formatter' => array(
      'label' => t('Magnific Popup'),
      'field types' => array('file', 'image'),
      'settings'  => array(
        'gallery_style' => key($gallery_options),
        'thumbnail_field' => array(),
        'thumbnail_style' => array(),
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function magnific_popup_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  // Get all possible thumbnail fields.
  $all_fields = !empty($form['#fields'])? $form['#fields'] : array();
  $field_bundle = !empty($form['#bundle'])? $form['#bundle'] : '';
  $thumbnail_field_options = _magnific_popup_thumbnail_field_options($all_fields, $field_bundle);
  
  // Get all possible image styles.
  $image_style_options = _magnific_popup_image_style_options();

  // Gallery Mode is TRUE when this field supports multiple items.
  $gallery_available = $field['cardinality'] !== 1;
  $gallery_options = _magnific_popup_gallery_options();
  
  $element = array();
  $element['gallery_available'] = array(
    '#type' => 'markup',
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );
  $element['gallery_available']['#markup'] = $gallery_available ?
    t('This field configuration <strong>supports multiple items</strong> and can display itself as a gallery of items!') :
    t('This field configuration <strong>does not support multiple items</strong> and cannot display itself as a gallery of items.');
  $element['gallery_style'] = array(
    '#type' => 'select',
    '#title' => t('Gallery Type'),
    '#options' => $gallery_options,
    '#disabled' => !$gallery_available,
    '#default_value' => $settings['gallery_style'],
    '#description' => t('Choose how this gallery displays its triggering element(s).'),
  );
  $thumbnail_field = empty($settings['thumbnail_field']) ? $field['field_name'] : $settings['thumbnail_field'];
  $element['thumbnail_field'] = array(
    '#type' => 'select',
    '#title' => t('Image Thumbnail Field'),
    '#options' => $thumbnail_field_options,
    '#disabled' => empty($thumbnail_field_options),
    '#default_value' => $thumbnail_field,
    '#description' => t('Select field to be used as thumbnail (by default use the same field for popup as for thumbnail).'),
  );
  $thumbnail_style = empty($settings['thumbnail_style']) ? 'magnific_popup_thumbnail' : $settings['thumbnail_style'];
  $element['thumbnail_style'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnail Style'),
    '#options' => $image_style_options,
    '#disabled' => empty($image_style_options),
    '#default_value' => $thumbnail_style,
    '#description' => t('Select the image style used to display the thumbnail.'),
  );
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function magnific_popup_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $gallery_options = _magnific_popup_gallery_options();
  $summary = t('Gallery Type: @gallery_type', array('@gallery_type' => $gallery_options[$settings['gallery_style']]));
  return $summary;
}

/**
 * Implements hook_field_formatter_prepare_view().
 */
function magnific_popup_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
  // Items are some kind of entity reference, be it via image or file type.
  // Load the corresponding items into a common format for our formatter_view().
  $static = &drupal_static(__FUNCTION__, array('loaded_items' => array(), 'thumbnail_schemes' => NULL));
  $loaded_items = &$static['loaded_items'];
  $thumbnail_schemes = &$static['thumbnail_schemes'];
  if (!isset($thumbnail_schemes)) {
    $thumbnail_schemes = module_invoke_all('magnific_popup_thumbnail_schemes');
  }
  // Iterate through $items looking for valid gallery items. Refactor them into
  // a consistent format for magnific_popup_field_formatter_view().
  $wrappers = array();
  foreach ($entities as $entity_id => $entity) {
    foreach ($items[$entity_id] as $delta => &$item) {
      // Fail-safe check to not load items 
      if (empty($item['uri'])) {
        continue;
      }
      // Check if we've already parsed this fid, and build it if not.
      if (!isset($loaded_items[$item['fid']])) {
        $loaded_items[$item['fid']] = FALSE;
        $scheme = file_uri_scheme($item['uri']);
        // Attempt to re-use, or load from scratch, a wrapper for this scheme.
        if (empty($wrappers[$scheme])) {
          // Create a new wrapper.
          $wrappers[$scheme] = file_stream_wrapper_get_instance_by_uri($item['uri']);
        }
        else {
          // Attempt to re-use an existing wrapper.
          $wrappers[$scheme]->setUri($item['uri']);
        }
        // Check that the resource was accessible.
        if ($wrappers[$scheme] && $wrappers[$scheme]->url_stat($item['uri'], STREAM_URL_STAT_QUIET) !== FALSE) {
          $wrapper = $wrappers[$scheme];
          $classes = array();
          // Determine the file's info and store it.
          $thumbnail_path = $wrapper->getUri();
          $thumbnail_style = '';
          // Determine if the URL is an external URL.
          $is_external_url = FALSE;
          // MediaYouTubeStreamWrapper implements getLocalThumbnailPath() to
          // find the thumbnail path.
          if (method_exists($wrapper,'getLocalThumbnailPath')) {
            $thumbnail_path = $wrapper->getLocalThumbnailPath();
            $is_external_url = TRUE;
          }
          else if (!empty($displays[$entity_id]) && !empty($displays[$entity_id]['settings'])) {
            $current_display = $displays[$entity_id]['settings'];
            $thumbnail_field_name = !empty($current_display['thumbnail_field']) ? $current_display['thumbnail_field'] : '';
            // Check for thumbnail overrides (where a different field is used
            // to derive thumbnails).
            if (!empty($thumbnail_field_name) && $thumbnail_field_name !== $field['field_name'] && !empty($entities[$entity_id])) {
              $thumbnail_field_item = field_get_items($entity_type, $entities[$entity_id], $thumbnail_field_name, NULL);
              // Only override the thumbnail if we have an actual thumbnail to
              // use instead (the field override may be empty!).
              if (!empty($thumbnail_field_item[$delta]['uri'])) {
                $thumbnail_path = $thumbnail_field_item[$delta]['uri'];
              }
            }
            $thumbnail_style = (!empty($current_display['thumbnail_style'])) ? $current_display['thumbnail_style'] : '';
            $classes[] = 'mfp-custom-thumbnail';
            // If a thumbnail was not provided, use the default thumbnail.
            if (file_uri_scheme($thumbnail_path) === 'oembed' && function_exists('oembed_get_data')) {
              // Get oembed data.
              $oembed_data = oembed_get_data($wrapper->getExternalUrl());
              if (!empty($oembed_data) && !empty($oembed_data['thumbnail_url'])) {
                $is_external_url = TRUE;
                $thumbnail_path = '//' . file_uri_target($oembed_data['thumbnail_url']);
              }
            }
          }
          // Try the standard method to get a thumbnail.
          else {
            if ($uri = $wrapper->getUri()) {
              $thumbnail_path = $uri;
            }
          }
          // Default $thumbnail_path based on the $scheme.
          if (empty($thumbnail_style)) {
            $thumbnail_style = 'magnific_popup_thumbnail';
            if (!empty($thumbnail_schemes[$scheme])) {
              $thumbnail_style = $thumbnail_schemes[$scheme];
            }
          }
          // Do not request image style URLs for externally-derived thumbs.
          if (!$is_external_url) {
            $thumbnail_path = image_style_url($thumbnail_style, $thumbnail_path);
          }
          // Get the title if it exists, or fallback to the filename.
          $title = !empty($item['title']) ? $item['title'] : $item['filename'];
          // Get the alt if it exists, or fallback to the title.
          $alt = !empty($item['alt']) ? $item['alt'] : $title;
          // Build the finished gallery item.
          $gallery_item = array(
            'title' => $title,
            'alt' => $alt,
            'thumbnail_path' => $thumbnail_path,
            'target_uri' => $wrapper->getExternalUrl(),
            'classes' => $classes,
          ) + $item;
          $loaded_items[$item['fid']] = $gallery_item;
        }
      }
      // Replace $item with the parsed version of info for this fid.
      $item = $loaded_items[$item['fid']];
      // Check if this item was unloadable and if so remove it from the list.
      if (empty($item)) {
        unset($items[$entity_id][$delta]);
      }
    }
    // Remove the pointer.
    if (isset($item)) {
      unset($item);
    }
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function magnific_popup_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  if (!_magnific_popup_check_status()) {
    return FALSE;
  }
  $element = array();
  // Create the main container.
  $settings = $display['settings'];
  $popup_gallery = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(),
    ),
  );
  // Determine if/what the allowed trigger item is (which will get a thumbnail).
  $trigger_item = key($items);
  if ($settings['gallery_style'] == 'random_item') {
    $trigger_item = array_rand($items);
  }
  // Figure out the base-class for the gallery/nogallery, which is generally
  // something like 'mfp-nogallery-image' or 'mfp-gallery-iframe'.
  $gallery_base_class = $settings['gallery_style'] == 'no_gallery' ?
    'mfp-nogallery' : 'mfp-gallery';
  if ($field['type'] == 'image') {
    $gallery_base_class .= '-image';
  }
  else {
    $gallery_base_class .= '-iframe';
  }
  $popup_gallery['#attributes']['class'][] = $gallery_base_class;
  // Add each item to our container.
  foreach ($items as $delta => $item) {
    $popup_gallery['item-' . $delta] = array(
      '#theme' => 'link',
      '#text' => '',
      '#path' => $item['target_uri'],
      '#options' => array(
        'attributes' => array('class' => $item['classes'], 'style' => array()),
        'html' => TRUE,
      ),
    );
    $popup_gallery['item-' . $delta]['#options']['attributes']['class'][] = 'mfp-item';
    // This item has a thumbnail image if:
    //  - the Gallery Type is "all items" (because all items have thumbs), or
    //  - the Gallery Type is "no gallery", or
    //  - the Gallery Type is "first item" and this $delta is the first item, or
    //  - the Gallery Type is "random item" and this $delta is the random item.
    if ($settings['gallery_style'] == 'all_items' || $settings['gallery_style'] == 'no_gallery' || $delta == $trigger_item) {
      $image = array(
        // Try to use a "figure" theme implementation if it exists, or fall back
        // to "image".
        '#theme' => array('figure', 'image'),
        '#path' => $item['thumbnail_path'],
        '#alt' => $item['alt'],
        '#title' => $item['title'],
        '#attributes' => array(
          'class' => array('mfp-thumbnail'),
        ),
      );
      $popup_gallery['item-' . $delta]['#text'] = render($image);
    }
    else {
      // Normally the title comes from img.mfp-thumbnail's title attribute.
      // Since this a.mfp-item will not have a thumbnail image, add the title to
      // a special span.mfp-title's title attribute.
      $popup_gallery['item-' . $delta]['#text'] = t('<span class="mfp-title" title="@title">&nbsp;</span>', array('@title' => $item['title']));
      // Hide the a.mfp-item (and any span.mfp-title).
      $popup_gallery['item-' . $delta]['#options']['attributes']['style'][] = 'display: none;';
    }
  }
  if (count($items)) {
    $element[0] = $popup_gallery;
  }
  return $element;
}

function _magnific_popup_gallery_options() {
  return array(
    'all_items' => t('Gallery: All Items Displayed'),
    'first_item' => t('Gallery: First Item Displayed'),
    'random_item' => t('Gallery: Random Item Displayed'),
    'no_gallery' => t('No Gallery: Display Each Item Separately'),
  );
}


function _magnific_popup_thumbnail_field_options($all_fields, $field_bundle) {
  $file_fields = array();
  if (!empty($all_fields)) {
    foreach ($all_fields as $field_name) {
      $field_info = field_info_field($field_name);
      if($field_info['type'] == 'file' || $field_info['type'] == 'image') {
        $file_field = field_info_instance('node', $field_name, $field_bundle);
        if (!empty($file_field['label']) && !empty($file_field['field_name'])) {
          $file_fields[$file_field['field_name']] = $file_field['label'];
        }
      }
    }
  }

  return $file_fields;
}

function _magnific_popup_image_style_options($all_fields, $field_bundle) {
  $image_styles = array();
  $all_styles = image_styles();

  foreach($all_styles as $style) {
    if (!empty($style['name']) && !empty($style['label'])) {
      $image_styles[$style['name']] = $style['label'];
    }
  }

  return $image_styles;
}
