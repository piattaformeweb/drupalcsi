<?php

function sassy_compass__blank($object) {
	if (is_object($object)) {
		$object =  $object->value;
	}
	$result = false;
	if (is_bool($object)) {
		$result = !$object;
	}
	if (is_string($object)) {
		$result = (strlen(trim($object, ' ,')) === 0);
	}

	return new SassBoolean($result);
}

function sassy_compass__compact() {
  $sep = ', ';

  $args = func_get_args();
  $list = array();

  // remove blank entries
  // append non-blank entries to list
  foreach ($args as $k=>$v) {
    if (is_object($v)) {
      $string = (isset($v->value) ? $v->value : FALSE);
    }
    else {
      $string = (string) $v;
    }
    if (empty($string) || $string == 'false') {
      unset($args[$k]);
      continue;
    }
    $list[] = $string;
  }
  return new SassString(implode($sep, $list));
}

function sassy_compass___compass_nth() {
	$args = func_get_args();
	$place = array_pop($args);
	$list = array();
	foreach ($args as $arg) {
		$list = array_merge($list, sassy_compass__list($arg));
	}

	if ($place == 'first') {
		$place = 0;
	}
	if ($place == 'last') {
		$place = count($list) - 1;
	}

	if (isset($list[$place])) {
		return current(SassScriptLexer::$instance->lex($list[$place], new SassContext()));
	}
	return new SassBoolean(false);
}

function sassy_compass___compass_list() {
	$args = func_get_args();
	$list = array();
	foreach ($args as $arg) {
		$list = array_merge($list, sassy_compass__list($arg));
	}
	return new SassString(implode(', ', $list));
}

function sassy_compass___compass_space_list() {
	$args = func_get_args();
	$list = sassy_compass__list($args, ',');
	return new SassString(implode(' ', $list));
}

function sassy_compass___compass_list_size() {
	$args = func_get_args();
	$list = sassy_compass__list($args, ',');
	return new SassNumber(count($list));
}

function sassy_compass___compass_list_slice($list, $start, $end) {
	$args = func_get_args();
	$end = array_pop($args);
	$start = array_pop($args);
	$list = sassy_compass__list($args, ',');
	return implode(',', array_slice($list, $start, $end));
}

function sassy_compass__first_value_of() {
	$args = array();
	$args[] = 'first';
	return call_user_func_array('sassy_compass___compass_nth', $args);
}

function sassy_compass__list($list, $seperator = ',') {
  if (is_object($list)) {
    $list = $list->value;
  }
  if (is_array($list)) {
  	$newlist = array();
  	foreach ($list as $listlet) {
  		$newlist = array_merge($newlist, sassy_compass__list($listlet, $seperator));
  	}
  	$list = implode(', ', $newlist);
  }

  $out = array();
  $size = 0;
  $braces = 0;
  $stack = '';
  for($i = 0; $i < strlen($list); $i++) {
    $char = substr($list, $i, 1);
    switch ($char) {
      case '(':
        $braces++;
        $stack .= $char;
        break;
      case ')':
        $braces--;
        $stack .= $char;
        break;
      case $seperator:
        if ($braces === 0) {
          $out[] = $stack;
          $stack = '';
          $size++;
          break;
        }

      default:
        $stack .= $char;
    }
  }
  $out[] = $stack;
  return $out;
}