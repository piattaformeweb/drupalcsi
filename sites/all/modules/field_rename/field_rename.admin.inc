<?php

function field_rename_admin() {
    $form = array();
    $form['current_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Current field machine name'),
        '#description' => t('Eg. "field_my_image"'),
        '#required' => TRUE,
    );
    $form['new_field'] = array(
        '#type' => 'textfield',
        '#title' => t('New field machine name'),
        '#description' => t('Eg. "field_my_image_new"'),
        '#required' => TRUE,
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#weight' => 10,
        '#value' => t('Submit'),
    );

    return $form;
}

function field_rename_admin_validate(&$form, &$form_state) {
    $current_field = field_read_field($form_state['values']['current_field']);
    if (empty($current_field)) {
        form_set_error('current_field', 'Field does not exist.');
    }
    else if ($form_state['values']['current_field'] == $form_state['values']['new_field']) {
        form_set_error('new_field', 'New field name should be different.');
    } else {
        $new_field_len = strlen($form_state['values']['new_field']);
        if ($new_field_len > 30) {
            form_set_error('new_field', 'New field name must not exceed 30 character.');
        }
    }
}

function field_rename_admin_submit(&$form, &$form_state) {
    $fields = array(
        $form_state['values']['current_field'] => $form_state['values']['new_field'],
    );

    try {
        $modules = field_rename_get_plugins();

        // Allow other modules to alter the list of plugins
        drupal_alter('field_rename_plugin', $modules, $form, $form_state);

        // Make fields an object so it is passed by reference
        $fields = (object)$fields;
        // Execute three stages of renaming
        $phases = array('pre_execute', 'execute', 'post_execute');
        foreach ($phases as $phase) {
            foreach ($modules as $module_name => $module) {
                if ($module['api'] != 1) {
                    $name = isset($module['name']) ? $module['name'] : $module_name;
                    drupal_set_message('Unsupported plugin ' . $name . ': not using API version 1.');
                    continue;
                }
                $hook = 'field_rename_' . $phase;
                module_invoke($module_name, $hook, $fields);
            }
        }
    } catch (Exception $e) {
        drupal_set_message($e->getMessage(), 'error');
        return;
    }

    drupal_flush_all_caches();
    drupal_set_message('Flushed all Drupal caches.');
}
