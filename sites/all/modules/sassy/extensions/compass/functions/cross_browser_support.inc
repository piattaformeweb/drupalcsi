<?php

# Check if any of the arguments passed require a vendor prefix.
function sassy_compass__prefixed($prefix, $list) {
  $list = sassy_compass__list($list);
  $prefix = trim(preg_replace('/[^a-z]/', '', strtolower($prefix)));

  # thanks http://www.quirksmode.org/css/contents.html
  $reqs = array(
    'pie' => array(
      'border-radius', 'box-shadow', 'border-image', 'background', 'linear-gradient',
    ),
    'webkit' => array(
      'background-clip', 'background-origin', 'border-radius', 'box-shadow', 'box-sizing', 'columns',
      'gradient', 'linear-gradient', 'text-stroke'
    ),
    'moz' => array(
      'background-size', 'border-radius', 'box-shadow', 'box-sizing', 'columns', 'gradient', 'linear-gradient'
    ),
    'o' => array(
      'background-origin', 'text-overflow'
    ),
  );
  foreach ($list as $item) {
    $aspect = trim(current(explode('(', $item)));
    if (isset($reqs[$prefix]) && in_array($aspect, $reqs[$prefix])) {
      return new SassBoolean(TRUE);
    }
  }
  return new SassBoolean(FALSE);
}

function sassy_compass___webkit($input) {
  return sassy_compass__prefix('webkit', $input);
}
function sassy_compass___moz($input) {
  return sassy_compass__prefix('moz', $input);
}
function sassy_compass___o($input) {
  return sassy_compass__prefix('o', $input);
}
function sassy_compass___ms($input) {
  return sassy_compass__prefix('ms', $input);
}
function sassy_compass___svg($input) {
  return sassy_compass__prefix('ms', $input);
}
function sassy_compass___pie($input) {
  return sassy_compass__prefix('ms', $input);
}
function sassy_compass___css2($input) {
  return sassy_compass__prefix('ms', $input);
}
function sassy_compass___owg($input) {
  return sassy_compass__prefix('ms', $input);
}
function sassy_compass__prefix($vendor, $input) {
  if (is_object($vendor)) {
    $vendor = $vendor->value;
  }

  $list = sassy_compass__list($input, ',');
  $output = '';
  foreach($list as $key=>$value) {
    $list[$key] = '-' . $vendor . '-' . $value;
  }
  return new SassString(implode(', ', $list));
}