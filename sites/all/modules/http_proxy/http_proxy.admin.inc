<?php

/**
 * @file
 * Administrative page callbacks for the http proxy module.
 */

/**
 * Form callback: builds the form for configuring proxy settings.
 *
 * @param array $form
 *   An associative array containing the structure of the form.
 * @param array $form_state
 *   An associative array containing the current state of the form.
 *
 * @return array
 *   An array representing the form definition.
 *
 * @ingroup forms
 * @see http_proxy_configuration_submit()
 */
function http_proxy_configuration($form, &$form_state) {
  $form['proxy_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Server'),
    '#default_value' => variable_get('proxy_server', ''),
    '#description' => t('The IP address or hostname of the proxy server.'),
  );
  $form['proxy_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Port'),
    '#default_value' => variable_get('proxy_port', 8080),
    '#element_validate' => array('element_validate_integer_positive'),
    '#description' => t('The port number used by the proxy server for client connections.'),
  );
  $form['proxy_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('proxy_username', ''),
    '#description' => t('A username used for proxy authentication.'),
  );
  $form['proxy_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#default_value' => variable_get('proxy_password', ''),
    '#description' => t('A password used for proxy authentication.'),
  );
  $form['proxy_user_agent'] = array(
    '#type' => 'textfield',
    '#title' => t('User agent'),
    '#default_value' => variable_get('proxy_user_agent', ''),
    '#description' => t('A string which can be used by the proxy server to identify connection requests.'),
  );
  $form['proxy_exceptions'] = array(
    '#type' => 'textarea',
    '#title' => t('Exceptions'),
    '#default_value' => implode("\n", variable_get('proxy_exceptions', array('localhost', '127.0.0.1'))),
    '#description' => t('Specify exceptions using either IP addresses or hostnames. Enter one exception per line. Exceptions will be accessed directly, not via proxy.'),
  );

  $form['#submit'][] = 'http_proxy_configuration_submit';

  return system_settings_form($form);
}

/**
 * Submit handler for http_proxy_configuration().
 */
function http_proxy_configuration_submit($form, &$form_state) {
  $form_state['values']['proxy_exceptions'] = explode("\n", trim($form_state['values']['proxy_exceptions']));
}
