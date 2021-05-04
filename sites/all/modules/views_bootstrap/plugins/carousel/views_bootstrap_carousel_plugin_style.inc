<?php

/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapCarouselPluginStyle extends views_plugin_style {

  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['interval'] = array('default' => 5000);
    $options['navigation'] = array('default' => TRUE);
    $options['indicators'] = array('default' => TRUE);
    $options['wrap'] = array('default' => TRUE);
    $options['pause'] = array('default' => FALSE);
    $options['items_per_slide'] = array('default' => 1);
    return $options;
  }

  /**
   * Form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['help'] = array(
      '#markup' => t('The Bootstrap carousel displays content as a slideshow (<a href="!docs">see documentation</a>).', ['!docs' => 'https://www.drupal.org/docs/7/modules/views-bootstrap/carousel']),
      '#weight' => -99,
    );

    $form['interval'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' => t('Interval'),
      '#description' => t('The amount of time to delay between automatically cycling an item. If false, carousel will not automatically cycle.'),
      '#default_value' => $this->options['interval'],
    );

    $form['navigation'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show navigation'),
      '#default_value' => $this->options['navigation'],
    );

    $form['indicators'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show indicators'),
      '#default_value' => $this->options['indicators'],
    );

    $form['wrap'] = array(
      '#type' => 'checkbox',
      '#title' => t('Wrap'),
      '#description' => t('Restarts the carousel after the last slide, rather than having a hard stop.'),
      '#default_value' => $this->options['wrap'],
    );

    $form['pause'] = array(
      '#type' => 'checkbox',
      '#title' => t('Pause on hover'),
      '#description' => t('Pauses the cycling of the carousel on mouseenter and resumes the cycling of the carousel on mouseleave.'),
      '#default_value' => $this->options['pause'],
    );

    $form['items_per_slide'] = array(
      '#type' => 'textfield',
      '#title' => t('Item per slide'),
      '#description' => t('How many items shown per slide.'),
      '#default_value' => $this->options['items_per_slide'],
    );
  }

}
