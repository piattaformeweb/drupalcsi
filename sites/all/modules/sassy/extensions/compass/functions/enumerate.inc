<?php
/**
 * Enumerate all options within a set. Deprecated in favor of @for, @extend
 * @example enumerate('.foo', 1, 3) => ".foo-1, .foo-2, .foo-3"
 */
function sassy_compass__enumerate($prefix, $from, $to, $sep = NULL) {
	$output = array();

	foreach (array('prefix', 'from', 'to', 'sep') as $var) {
		if (is_object($$var)) {
			$$var = $$var->value;
		}
	}

	if ($sep === NULL) {
		$sep = '-';
	}

	for ($i = $from; $i <= $to; $i++) {
		$output[] = $prefix . $sep. $i;
	}

	return new SassString(implode(', ', $output));
}