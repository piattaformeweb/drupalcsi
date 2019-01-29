<?php
/**
 * @file
 * Divascookies API.
 *
 * This is currently a stub file that will be used to describe the divascookies
 * implementation API.
 *
 * Date: 01 lug 2015 18:19:52
 * File: divascookies.api.php
 * Author: stefano.
 */

/**
 * Implements hook_divascookies_script_stop().
 *
 * It returns an array with keys:
 *
 *   - 'regex': the regular expression with delimiters and the 'i' (case
 *     insensitive) PCRE modifier recommended. The whole regex must be enclosed
 *     by "()";
 *   - 'type': one of the list below.
 *
 *   The meaning of type value depend from the html tags to block:
 *
 *   - 'externalscript', to block like
 *     <script type="text/javascript" src="myscript.js"></script>
 *
 *   - 'inlinescript', to block some code inline like
 *     <script>... some code .... </script>
 *
 *   - 'externalattr', to block any <iframe> or any <img /> or <input /> that
 *     contains a src attribute and loads content from an external source that
 *     potentially installs cookies (i.e. YouTube videos or Paypal donate
 *     buttons)
 *
 *   Read the Divas Cookies doc in the index.html inside the libs to know how
 *   to write the regex.
 *
 * SC 01 lug 2015 18:20:20 stefano.
 */
function myscript_divascookies_script_stop() {
  $file = 'myscript.js';

  // Finds the filename of the aggregated contents of the js files.
  //
  // SC 15 lug 2015 01:14:57 stefano.
  //
  $map = variable_get('drupal_js_cache_files', array());

  $path = drupal_get_path('module', 'myscript') . '/' . $file;

  $key = hash('sha256', serialize(array(
    $path
  )));

  if (array_key_exists($key, $map)) {
    $foo_file = preg_replace(array(
      '@^.+/js/(.+)$@i',
      '@\.@'
    ), array(
      '$1',
      '\.'
    ), $map[$key]);
  }
  else {
    $foo_file = 'myscript\.js';
  }

  $foo = array('regex' => '@(<script.+src\s*=.+'.$foo_file.'.+</script>)@i', 'type' => 'externalscript');

  return $foo;
}
