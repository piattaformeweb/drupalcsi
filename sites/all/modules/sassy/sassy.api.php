<?php

/**
 * @file
 * Hooks provided by the Sassy module.
 */


/**
 * Allows provision of additional functions for use inside the parser.
 * Return structure should be an optionally-keyed array where each item
 * has:
 *	@param name : the function name as it will appear in the SASS file.
 *  @param callback : the function to be executed when it is encountered.
 * The callback should return either a PHP or SASS primitive.
 * The callback recieves only those arguments that are passed. In order
 * to get additional information about the parser, use the static
 * parameter $instance of the SassParser class.
 */
function hook_sassy_functions() {
	return array(
		array(
			'name' => 'theme_setting', // function name
			'callback' => 'sassy_get_theme_setting', // (not actually defined)
		),
		array(
			'name' => 'variable', // function name
			'callback' => 'variable_get', // Drupal callback. Probably unsafe.
		),
	);
}

/**
 * Allows definition of shorthand filepaths under a single namespace.
 *
 * @param NAMESPACE : the first segment of the filepath. For example, when
 * 		  requesting "theme/foo", the hook is hook_sassy_resolve_path_theme.
 *        The namespaces is lowercased and all non alphanumeric characters
 *        are replaced with underscores. `S0me Path` => 's0me_path'.
 *
 * @param $filename : the filename being requested for transformation. Any
 *        restrictions on this outside of those inherent in SASS are left up
 *        to the implementor.
 *
 * @return a filepath or array of filepathds relative to the Drupal basepath.
 */
function hook_sassy_resolve_path_NAMESPACE($filename) {
	return array('one.sass', 'two.scss', 'three.css');
}

/**
 * Example implementation of a "theme" namespace which can handle the following:
 *   theme/path/to/file - paths within the currently enabled theme.
 *   theme/THEMENAME/path/to/file - paths within the named theme.
 */
function hook_sass_resolve_path_theme($filename, $syntax) {
	$parts = explode('/', $filename, 2);

	if (!$path = drupal_get_path('theme', array_shift($parts))) {
		$path = drupal_get_path('theme', $GLOBALS['theme_key']);
	}
	array_unshift($parts, $path);
	$file = implode('/', $parts);

	foreach (array('', '.scss', '.sass') as $ext) {
		if (file_exists($file . $ext)) {
			return $file . $ext;
		}
	}
	return FALSE;
}
