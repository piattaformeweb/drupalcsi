<?php

/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapMediaPluginStyle extends views_plugin_style {

  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['image_field'] = array('default' => NULL);
    $options['heading_field'] = array('default' => NULL);
    $options['image_class'] = array('default' => 'media-left');
    return $options;
  }

  /**
   * Form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    if (isset($form['grouping'])) {
      $options = array();
      foreach (element_children($form['grouping']) as $key => $value) {
        if (!empty($form['grouping'][$key]['field']['#options']) && is_array($form['grouping'][$key]['field']['#options'])) {
          $options = array_merge($options, $form['grouping'][$key]['field']['#options']);
        }
      }

      $form['help'] = array(
        '#markup' => t('The Bootstrap media object displays content with an image item lead with heading and text (<a href="!docs">see documentation</a>).', ['!docs' => 'https://www.drupal.org/docs/7/modules/views-bootstrap/media-object']),
        '#weight' => -99,
      );

      $form['image_field'] = array(
        '#type' => 'select',
        '#title' => t('Image field'),
        '#options' => $options,
        '#default_value' => $this->options['image_field'],
        '#description' => t('Select the field that will be used as the image. Exclude this field from display to prevent duplication.'),
      );

      $form['heading_field'] = array(
        '#type' => 'select',
        '#title' => t('Heading field'),
        '#options' => $options,
        '#default_value' => $this->options['heading_field'],
        '#description' => t('Select the field that will be used as the heading. Exclude this field from display to prevent duplication.'),
      );

      $form['body_field'] = array(
        '#title' => t('Body field'),
        '#markup' => t('All fields that are not excluded from display will be shown as the body.'),
      );

      $form['image_class'] = array(
        '#type' => 'radios',
        '#title' => t('Image Alignment'),
        '#options' => [
          'media-left' => t('Left'),
          'media-right' => t('Right'),
        ],
        '#default_value' => $this->options['image_class'],
        '#description' => t('Align the media object image left or right.'),
      );

    }
  }

}
