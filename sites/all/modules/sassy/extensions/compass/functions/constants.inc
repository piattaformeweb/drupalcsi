<?php

function sassy_compass__is_position($position) {
	if (is_object($position)) {
		$position = $position->value;
	}
	return new SassBoolean(in_array($position, array('top', 'left', 'bottom', 'right')));
}

function sassy_compass__is_position_list($position) {
	$list = array();
	foreach (func_get_args() as $pos) {
		$list = array_merge($list, sassy_compass__list($pos, ' '));
	}
	foreach ($list as $el) {
		if (!in_array($el, array('top', 'left', 'bottom', 'right'))) {
			return new SassBoolean(FALSE);
		}
	}
	return new SassBoolean(TRUE);
}

# returns the opposite position of a side or corner.
function sassy_compass__opposite_position($position) {
	$list = sassy_compass__list($position, ' ');
	foreach ($list as $key=>$val) {
		switch ($val) {
			case 'top':
				$val = 'bottom';
				break;
			case 'bottom':
				$val = 'top';
				break;
			case 'left':
				$val = 'right';
				break;
			case 'right':
				$val = 'left';
				break;
		}
		$list[$key] = $val;
	}
	return implode(' ', $list);
}

