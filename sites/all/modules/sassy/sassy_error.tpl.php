<?php
$error = str_replace(array('"', "\n"), array("'", '\A'), $error->getMessage());
?>
body::before {
  display: block;
  padding: 5px;
  white-space: pre;
  font-family: monospace;
  font-size: 8pt;
  line-height: 17px;
  overflow: hidden;
  content: "<?php print $error; ?>";
}
