<?php

# not sure what should happen with these

function sassy_compass__stylesheet_url($path, $only_path = FALSE) {
	return sassy_compass__url($path, $only_path);
}

function sassy_compass__font_url($path, $only_path = FALSE) {
	return sassy_compass__url($path, $only_path);
}

function sassy_compass__image_url($path, $only_path = FALSE) {
	return sassy_compass__url($path, $only_path);
}

function sassy_compass__url($path, $only_path = FALSE, $web_path = TRUE) {
	$opath = $path;
	if (!$path = SassFile::get_file($path, SassParser::$instance, false)) {
		throw new Exception('File not found: ' . $opath);
	}

	$path = $path[0];
	if ($web_path) {
		$webroot = realpath($_SERVER['DOCUMENT_ROOT']);
		$path = str_replace($webroot, '', $path);
	}

	if ($only_path) {
		return new SassString($path);
	}
	return new SassString("url('$path')");
}
