<?php
// http://compass-style.org/reference/compass/helpers/font-files/#font-files
function sassy_compass__font_files() {
  $font_types = array(
    'woff' => 'woff',
    'otf' => 'opentype',
    'opentype' => 'opentype',
    'ttf' => 'truetype',
    'truetype' => 'truetype',
    'svg' => 'svg',
    'eot' => 'embedded-opentype',
  );

  $args = func_get_args();
  foreach ($args as $k=>$v) {
    if (is_object($v)) {
      $args[$k] = $v->value;
    }
  }

  $output = array();
  while (count($args)) {
    $url = array_shift($args);

    preg_match('/\.([a-z-]+).*$/i', $url, $type);
    $type = $type[1];

    if (!isset($font_types[$type])) {
      throw new SassException('Could not determine the font type for ' . $url);
    }

    $output[] = "font_url($url) format({$font_types[$type]})";
  }

  return new SassString(implode(', ', $output));
}
