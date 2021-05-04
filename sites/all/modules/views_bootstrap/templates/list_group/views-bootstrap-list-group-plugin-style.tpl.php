<?php

/**
 * @file
 * views-bootstrap-list-group-plugin-style.tpl.php
 *
 * Default simple view template to display Bootstrap List Group.
 *
 * @ingroup views_templates
 */
?>
<?php print $panels ? '<div class="panel panel-default">' : '' ?>
<?php if (!empty($title)): ?>
  <?php print $panels ? '<div class="panel-heading">' : '' ?>
  <h3><?php print $title ?></h3>
  <?php print $panels ? '</div>' : '' ?>
<?php endif ?>

<<?php print $linked_items ? 'div' : 'ul'?> id="views-bootstrap-list-group-<?php print $id ?>" class="list-group <?php print $classes ?>">
  <?php foreach ($rows as $key => $row): ?>
    <?php if ($linked_items): ?>
      <?php print l($row, $link_fields[$key], array(
        'html' => TRUE,
        'attributes' => array(
          'class' => 'list-group-item',
        ),
      )) ?>
    <?php else: ?>
      <li class="list-group-item">
        <?php print $row ?>
      </li>
    <?php endif ?>
  <?php endforeach ?>
</<?php print $linked_items ? 'div' : 'ul'?>>
<?php print $panels ? '</div>' : '' ?>
