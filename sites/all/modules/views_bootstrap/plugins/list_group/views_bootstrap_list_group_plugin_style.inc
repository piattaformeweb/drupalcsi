<?php

/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapListGroupPluginStyle extends views_plugin_style {

  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['link_field'] = array('default' => NULL);

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
        '#markup' => t('The Bootstrap list group displays content in an unordered list with list group classes (<a href="!docs">see documentation</a>).', ['!docs' => 'https://www.drupal.org/docs/7/modules/views-bootstrap/list-group']),
        '#weight' => -99,
      );

      $form['panels'] = array(
        '#type' => 'checkbox',
        '#title' => t('Set group field in panel heading'),
        '#default_value' => $this->options['panels'],
        '#states' => array(
          'invisible' => array(
            ':input[name="style_options[grouping][0][field]"]' => ['value' => ''],
          ),
        ),
        '#weight' => 0,
      );

      $form['link_field'] = array(
        '#type' => 'select',
        '#title' => t('Link field'),
        '#options' => $options,
        '#default_value' => $this->options['link_field'],
        '#description' => t('Select the field that will be used as the link.'),
      );
    }
  }

}
