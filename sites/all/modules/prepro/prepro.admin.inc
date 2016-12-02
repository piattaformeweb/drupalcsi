<?php

/**
 * @file
 * Prepro admin section.
 */

/**
 * Callback for Prepro settings page.
 *
 * Compiles a table of filetype-specific settings
 * and any preprocessor-specific settings available.
 */
function prepro_admin_form($form, &$form_state, $buttons = TRUE) {
  $compilers = prepro_get_compilers();
  $cachers = prepro_get_cachers();
  $settings = prepro_get_settings();
  // Keep track of chosen preprocs for deciding whether a fieldset
  // is open by default.
  // $rows = array();
  $selected = array();

  foreach ($cachers as $key => $cacher) {
    $cache_options[$cacher['module'] . '/' . $key] = $cacher['title'] . ': ' . $cacher['description'];
  }

  $form['prepro'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );
  $form['prepro']['filetypes'] = array(
    '#type' => 'container',
    '#theme' => 'prepro_admin_form_filetypes',
  );
  foreach ($compilers as $format => $processors) {
    $proc_list = array();
    foreach ($processors as $key => $proc) {
      $proc_list[$proc['module'] . '/' . $key] = $proc['label'];
    }
    $settings['filetypes'] += array($format => array());
    $settings['filetypes'][$format] += array(
      'compile_handler' => current(array_keys($proc_list)),
      'cache_handler' => '',
      'cache_path' => 'public://prepro/',
    );
    $selected[] = $settings['filetypes'][$format]['compile_handler'];

    $form['prepro']['filetypes'][$format] = array(
      '#type' => 'fieldset',
      '#title' => $format,
    );
    $form['prepro']['filetypes'][$format]['compile_handler'] = array(
      '#type' => 'select',
      '#title' => t('Pre-processor'),
      '#options' => $proc_list,
      '#default_value' => $settings['filetypes'][$format]['compile_handler'],
    );
    $form['prepro']['filetypes'][$format]['cache_handler'] = array(
      '#type' => 'select',
      '#title' => t('Caching'),
      '#options' => $cache_options,
      '#default_value' => $settings['filetypes'][$format]['cache_handler'],
    );
    $form['prepro']['filetypes'][$format]['cache_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Cache Location'),
      '#default_value' => rtrim($settings['filetypes'][$format]['cache_path'], '/'),
    );
  }

  $form['prepro']['additional'] = array(
    '#type' => 'container',
  );
  foreach (module_implements('preprocessor_settings_form') as $module) {
    $procs = module_invoke($module, 'preprocessor_info');
    foreach ($procs as $proc => $info) {
      // Use the "retrieve" and "prepare" funcs to get the form and allow the
      // usual form handler functions.
      $form_id = $module . '_preprocessor_settings_form';
      $settings['additional'] += array($proc => array());
      $temp_state = array(
        'prepro' => array(
          'local' => $settings['additional'][$proc],
          'global' => $settings,
          'processor' => $proc,
        ),
      ) + form_state_defaults();
      $result = drupal_retrieve_form($form_id, $temp_state);
      // If we didn't get the form, remove the compiler
      // from the "selected" list.
      if (!$result) {
        foreach ($selected as $i => $v) {
          if ($v == $proc) {
            unset($selected[$i]);
          }
        }
        // Change the label a wee bit.
        $info['label'] .= ' (no settings)';
        $result = array();
      }

      // Add the result to the page.
      $form['prepro']['additional'][$module] = array(
        '#type' => 'fieldset',
        '#title' => filter_xss($info['label']),
        '#collapsible' => TRUE,
        '#collapsed' => !in_array($proc, $selected),
      );
      $form['prepro']['additional'][$module] += $result;
    }
  }

  $form['prepro']['show_warnings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the "files are being recompiled on every page load" warning?'),
    '#description' => t('This warning is there for a reason - compilation can be a heavy process and will cause slowdown on production servers.'),
    '#default_value' => $settings['show_warnings'],
  );

  if ($buttons) {
    $form['buttons'] = array(
      'submit' => array(
        '#type' => 'submit',
        '#value' => 'Save settings',
        '#submit' => array('prepro_admin_form_save'),
      ),
      'clear_cache' => array(
        '#type' => 'submit',
        '#value' => 'Clear prepro cache',
        '#submit' => array('prepro_admin_form_cc'),
      ),
    );
  }

  return $form;
}

/**
 * Submit handler for "Save" on the prepro admin form.
 */
function prepro_admin_form_save($form, &$form_state) {
  $settings = $form_state['values']['prepro'];
  // Make sure that we can write to all the cache locations.
  foreach ($settings['filetypes'] as $ext => $type) {
    if (!file_prepare_directory($type['cache_path'], FILE_MODIFY_PERMISSIONS ^ FILE_CREATE_DIRECTORY)) {
      drupal_set_message(t('The cache location for :ext files (:dir) can either not be created or is not writable.', array(':ext' => $ext, ':dir' => $type['cache_path'])), 'warning');
    }
  }
  variable_set('prepro', $settings);
  drupal_set_message(t('Prepro settings have been saved'));
  prepro_admin_form_cc($form, $form_state);
}

/**
 * Submit handler for clearing the cache from the prepro admin form.
 */
function prepro_admin_form_cc($form, &$form_state) {
  cache_clear_all('prepro:map', 'cache_prepro');
  drupal_set_message(t('The Prepro cache has been cleared'));
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function prepro_form_system_performance_settings_alter(&$form) {
  $form['clear_cache']['prepro_clear'] = array(
    '#type' => 'submit',
    '#value' => 'Clear prepro cache',
    '#submit' => array('prepro_admin_form_cc'),
  );
}

/**
 * Theme callback for Prepro admin form filetypes.
 */
function theme_prepro_admin_form_filetypes($variables) {
  $form = $variables['form'];
  $rows = array();

  foreach (element_children($form) as $format) {
    $row = array();

    $row[] = '.' . $format;
    $fields = array('compile_handler', 'cache_handler', 'cache_path');
    foreach ($fields as $field) {
      unset($form[$format][$field]['#title']);
      $row[] = render($form[$format][$field]);
    }

    $rows[] = $row;
  }

  return theme('table', array(
    'header' => array(
      t('Format'),
      t('Pre-processor'),
      t('Caching'),
      t('Cache Location'),
    ),
    'rows' => $rows,
    'empty' => t('There are no modules offering to preprocess JS/CSS files'),
  ));
}
