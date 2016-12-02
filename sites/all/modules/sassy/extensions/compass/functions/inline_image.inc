<?php

function sassy_compass__inline_image($file, $mime = NULL) {
	if ($path = sassy_compass__url($file, true, false)) {
		$info = getimagesize($path);
		$mime = $info['mime'];
		$data = base64_encode(file_get_contents($path));
		# todo - do not return encoded if file size > 32kb
		return new SassString("url('data:$mime;base64,$data')");
	}
	return new SassString('');
}

function sassy_compass__inline_font_files($file) {
	$args = func_get_args();
	$files = array();
	$mimes = array(
		'otf' => 'font.opentype',
		'ttf' => 'font.truetype',
		'woff' => 'font.woff',
		'off' => 'font.openfont',
	);

	while (count($args)) {
		$path = sassy_compass__resolve_path(array_shift($args));
		$data = base64_encode(file_get_contents($path));
		$format = array_shift($args);

		$ext = array_pop(explode('.', $file));
		if (isset($mimes[$ext])) {
			$mime = $mimes[$ext];
		}
		else {
			continue;
		}

		$files[] = "url('data:$mime;base64,$data') format('$format')";
	}

	return new SassString(implode(', ', $files));
}
