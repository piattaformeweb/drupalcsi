<?php

/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapDropdownPluginStyle extends views_plugin_style {

  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['class'] = array('default' => NULL);
    $options['wrapper_class'] = array('default' => NULL);
    $options['button_text'] = array('default' => 'Select');
    $options['button_class'] = array('default' => 'btn-default');
    return $options;
  }

  /**
   * Options form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['help'] = array(
      '#markup' => t('The Bootstrap dropdown style displays a list of links in a drop-down menu format (<a href="!docs">see Bootstrap documentation</a>).', ['!docs' => 'https://www.drupal.org/docs/7/modules/views-bootstrap/dropdown']),
      '#weight' => -99,
    );

    $form['wrapper_class'] = array(
      '#title' => t('Wrapper class'),
      '#description' => t('The class to provide on the wrapper, outside the list.'),
      '#type' => 'textfield',
      '#size' => '30',
      '#default_value' => $this->options['wrapper_class'],
    );

    $form['button_text'] = array(
      '#title' => t('Button text'),
      '#description' => t('Text label for the button that is the drop-down toggle.'),
      '#type' => 'textfield',
      '#default_value' => $this->options['button_text'],
    );

    $form['button_class'] = array(
      '#title' => t('Button class'),
      '#description' => t('Classes for the button that is the dropdown toggle.'),
      '#type' => 'select',
      '#options' => array(
        'btn-default' => t('Default'),
        'btn-primary' => t('Primary'),
        'btn-success' => t('Success'),
        'btn-info' => t('Info'),
        'btn-warning' => t('Warning'),
        'btn-danger' => t('Danger'),
      ),
      '#default_value' => $this->options['button_class'],
    );

    $form['class'] = array(
      '#title' => t('List class'),
      '#description' => t('The class to provide on the list element itself.'),
      '#type' => 'textfield',
      '#size' => '30',
      '#default_value' => $this->options['class'],
    );
  }

}
