<?php

function sassy_preprocessor_settings_form($form, $form_state) {
  extract($form_state['prepro']);
  $local += array(
    'debug' => FALSE,
    'watchdog' => FALSE,
    'errors' => 'watchdog',
    'style' => 'nested',
  );

  $form['watchdog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pass @warn and @debug to Watchdog'),
    '#description' => t('Should the compiler pass results of @warn and @debug directives in the parsed files to the Drupal Watchdog system.'),
    '#default_value' => $local['watchdog'],
  );
  $form['debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include debug information in output'),
    '#description' => t('Should the compiler include debugging text, ' . l('usable by Firebug', 'https://github.com/is-already-taken/firecompass') . ' for enhanced debugging.'),
    '#default_value' => $local['debug'],
  );
  $form['errors'] = array(
    '#type' => 'select',
    '#title' => 'Error reporting method',
    '#description' => t('How should the compiler record/display errors from processing?'),
    '#options' => array(
      'silent' => 'Silent: the file will fail to compile but no errors are shown anywhere.',
      'watchdog' => 'Watchdog: errors are recorded by the Watchdog to be viewed by an administrator.',
      'output' => 'Show on page: errors and a stacktrace are shown on the page in compatible browsers.',
    ),
    '#default_value' => $local['errors'],
  );
  $form['style'] = array(
    '#type' => 'select',
    '#title' => 'Output style',
    '#description' => t('What style of output should Sassy use.'),
    '#options' => array(
      'nested' => 'Nested: Each property+selector takes up 1 line, selector indentation reflects nesting depth.',
      'expanded' => 'Expanded: Each property+selector takes up 1 line, no selector indentation.',
      'compact' => 'Compact: Each selector takes up 1 line with properties on the same line. No indentation.',
      'compressed' => 'Compressed: Almost no whitespace, designed to be as space-efficient as possible.',
    ),
    '#default_value' => $local['style'],
  );
  return $form;
}
