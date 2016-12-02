<?php

function sassy_compass__image_width($file) {
  if ($info = sassy_compass__image_info($file)) {
    return new SassNumber($info[0] . 'px');
  }
  return new SassNumber('0px');
}

function sassy_compass__image_height($file) {
  if ($info = sassy_compass__image_info($file)) {
    return new SassNumber($info[1] . 'px');
  }
  return new SassNumber('0px');  
}

function sassy_compass__image_info($file) {
  if ($path = sassy_compass__resolve_path($file)) {
    if ($info = getimagesize($path)) {
      return $info;
    }
  }
  return false; 
}