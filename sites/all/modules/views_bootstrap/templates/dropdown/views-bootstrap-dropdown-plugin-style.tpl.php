<?php

/**
 * @file
 * Render a view containing a list of rows as a drop-down.
 */
?>
<?php print $wrapper_prefix; ?>
  <button class="dropdown-toggle btn <?php print $button_class; ?>" type="button" id="<?php print $id; ?>-dropdown" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
    <?php print $button_text; ?> <span class="caret"></span>
  </button>
  <?php print $list_type_prefix; ?>
<?php foreach ($rows as $key => $row): ?>
    <li <?php print $row['attributes']; ?>><?php print strip_tags($row['content'], '<a><img>'); ?></li>
<?php endforeach ?>
  <?php print $list_type_suffix; ?>
<?php print $wrapper_suffix; ?>
