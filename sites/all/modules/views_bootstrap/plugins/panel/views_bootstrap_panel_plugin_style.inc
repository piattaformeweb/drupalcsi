<?php

/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapPanelPluginStyle extends views_plugin_style {

  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['heading_field'] = array('default' => NULL);
    $options['title'] = array('default' => FALSE);
    $options['title_tag'] = array('default' => 'h3');
    $options['label_field'] = array('default' => NULL);
    $options['footer_field'] = array('default' => NULL);
    $options['context'] = array('default' => 'default');
    return $options;
  }

  /**
   * Options form.
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
        '#markup' => t('The Bootstrap panels displays content in a box with optional header and footer elements (<a href="!docs">see documentation</a>).', ['!docs' => 'https://www.drupal.org/docs/7/modules/views-bootstrap/panels']),
        '#weight' => -99,
      );

      $form['heading_field'] = array(
        '#type' => 'select',
        '#title' => t('Heading field'),
        '#options' => $options,
        '#default_value' => $this->options['heading_field'],
        '#description' => t('Select the field that will be used as the heading.'),
        '#id' => 'heading-field',
      );

      $field_labels = $this->display->handler->get_field_labels(TRUE);
      $form['title'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use panel-title class'),
        '#default_value' => $this->options['title'],
        '#states' => array(
          'invisible' => array(
            ':input#heading-field' => array('value' => ''),
          ),
        ),
        '#id' => 'title-checkbox',
      );
      $t_options = array(
        'h1' => t('h1'),
        'h2' => t('h2'),
        'h3' => t('h3'),
        'h4' => t('h4'),
        'h5' => t('h5'),
        'h6' => t('h6'),
        'div' => t('div'),
      );
      $form['title_tag'] = array(
        '#type' => 'select',
        '#title' => t('Title tag'),
        '#options' => $t_options,
        '#default_value' => $this->options['title_tag'],
        '#description' => t('Select the tag to use around the title.'),
        '#states' => array(
          'visible' => array(
            ':input#title-checkbox' => array('checked' => TRUE),
          ),
        ),
      );
      $form['label_field'] = array(
        '#type' => 'select',
        '#title' => t('Label field'),
        '#options' => $options,
        '#required' => FALSE,
        '#default_value' => $this->options['label_field'],
        '#description' => t('Select the field that will be used as the label.'),
        '#states' => array(
          'invisible' => array(
            ':input#heading-field' => array('value' => ''),
          ),
        ),
      );
      $form['footer_field'] = array(
        '#type' => 'select',
        '#title' => t('Footer field'),
        '#options' => $options,
        '#default_value' => $this->options['footer_field'],
        '#description' => t('Select the field that will be used as the footer.'),
      );

      $c_options = array(
        'default' => t('Default'),
        'primary' => t('Primary'),
        'success' => t('Success'),
        'info' => t('Info'),
        'warning' => t('Warning'),
        'danger' => t('Danger'),
      );
      $form['context'] = array(
        '#type' => 'select',
        '#title' => t('Contextual class'),
        '#options' => $c_options,
        '#default_value' => $this->options['context'],
        '#description' => t('<a href="!docs">see Bootstrap documentation</a>', ['!docs' => 'https://getbootstrap.com/docs/3.4/components/#panels-alternatives']),
      );
    }
  }

}
