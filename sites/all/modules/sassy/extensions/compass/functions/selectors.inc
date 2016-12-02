<?php

// http://compass-style.org/reference/compass/helpers/selectors/#nest
function sassy_compass__nest() {
	$args = func_get_args();
	$output = explode(',', array_pop($args));

	for ($i = count($args) - 1; $i >= 0; $i--) {
		$current = explode(',', $args[$i]);
		$size = count($output);
		foreach ($current as $selector) {
			for ($j = 0; $j < $size; $j++) {
				$output[] = trim($selector) . " " . trim($output[$j]);
			}
		}
		$output = array_slice($output, $size);
	}

	return new SassString(implode(', ', $output));
}

function sassy_compass__append_selector($initial, $new) {
	$list = explode(',', $initial);
	foreach ($list as $k => $selector) {
		$list[$k] = trim($selector) . $new;
	}
	return new SassString(implode(', ', $list));
}

function sassy_compass__headers($from = false, $to = false) {
	if (is_object($from))
		$from = $from->value;
	if (is_object($to))
		$to = $to->value;

	if (!$from || !is_numeric($from))
		$from = 1;
	if (!$to || !is_numeric($to))
		$to = 6;
	
	$from = (int) $from;
	$to = (int) $to;

	$output = array();
	for ($i = $from; $i <= $to; $i++) {
		$output[] = 'h' . $i;
	}
	return new SassString(implode(', ', $output));
}