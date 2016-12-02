<?php

function sassy_compass__elements_of_type($type) {
  if (is_object($type)) {
    $type = $type->value;
  }
  $type = strtolower(trim($type));

  $types = array(
    'block' => 'address article aside blockquote center dir div dd details dl dt fieldset'
             . 'figcaption figure form footer frameset h1 h2 h3 h4 h5 h6 hr header hgroup'
             . 'isindex menu nav noframes noscript ol p pre section summary ul',
    'inline'=> 'a abbr acronym audio b basefont bdo big br canvas cite code command'
             . 'datalist dfn em embed font i img input keygen kbd label mark meter output'
             . 'progress q rp rt ruby s samp select small span strike strong sub'
             . 'sup textarea time tt u var video wbr',
    'table' => 'table',
    'list-item' => 'li',
    'table-row-group' => 'tbody',
    'table-header-group' => 'thead',
    'table-footer-group' => 'tfoot',
    'table-row' => 'tr',
    'table-cell' => 'th td',
    'html5-block' => 'article aside deatils figcaption figure footer header hgroup menu nav section summary',
    'html5-inline' => 'audio canvas command datalist embed keygen mark meter output progress rp rt ruby time video wbr',
    'html5' => 'article aside audio canvas command datalist details embed figcaption figure footer header hgroup keygen mark menu meter nav output progress rp rt ruby section summary time video wbr',
  );

  if (isset($types[$type])) {
    return new SassString(str_replace(' ', ',', $types[$type]));
  }
  throw new SassException('Elements-of-type does not support the type ' . $type);
}
