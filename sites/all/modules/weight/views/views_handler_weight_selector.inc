<?php

class views_handler_weight_selector extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);

    $this->options['weight_selector'] = TRUE;
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['weight_range'] = array(
      'default' => 20,
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['weight_range'] = array(
      '#type' => 'textfield',
      '#title' => t('Range'),
      '#description' => t('The range of weights available to select. For
        example, a range of 20 will allow you to select a weight between -20
        and 20.'),
      '#default_value' => $this->options['weight_range'],
      '#size' => 5,
    );
  }

  function render($values) {
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  function views_form(&$form, &$form_state) {
    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );

    $options = _weight_get_options($this->options['weight_range']);
    $entity_type = $this->view->base_table;
    $entity_key = $this->view->base_field;

    // At this point, the query has already been run, so we can access the results
    foreach ($this->view->result as $row_index => $row) {
      $entity = entity_load($entity_type, array($row->{$entity_key}));

      $form[$this->options['id']][$row_index]['weight'] = array(
        '#type' => 'select',
        '#options' =>  $options,
        '#default_value' => $this->get_value($row),
        '#attributes' => array('class' => array('weight-selector')),
        '#access' => user_access('assign node weight'),
      );

      $form[$this->options['id']][$row_index]['entity'] = array(
        '#type' => 'value',
        '#value' => $entity,
      );
    }

    $form['entity_type'] = array(
      '#type' => 'value',
      '#value' => $entity_type,
    );

    $form['views_field'] = array(
      '#type' => 'value',
      '#value' => $this->field,
    );

    $form['#action'] = request_uri();
  }

  function views_form_submit($form, &$form_state) {
    $values = $form_state['values'];
    $field_name = str_replace('_selector', '' , $values['views_field']);

    foreach ($values[$values['views_field']] as $value) {
      $entity = array_pop($value['entity']);
      $lang = field_language($values['entity_type'], $entity, $field_name);
      $entity->{$field_name}[$lang][0]['value'] = $value['weight'];
      entity_save($values['entity_type'], $entity);
    }
  }
}
