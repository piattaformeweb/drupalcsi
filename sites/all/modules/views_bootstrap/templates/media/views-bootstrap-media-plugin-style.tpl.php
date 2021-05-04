<?php

/**
 * @file
 * Default simple view template to display Bootstrap media object.
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title ?></h3>
<?php endif ?>

<div id="views-bootstrap-media-<?php print $id ?>" class="<?php print $classes ?>">
  <div class="media-list">
    <?php foreach ($rows as $key => $row): ?>
      <div class="media">
        <?php if ($row['image'] && $image_class == 'media-left'): ?>
          <div class="media-left pull-left">
            <?php print $row['image'] ?>
          </div>
        <?php endif ?>
        <?php if ($row['image'] && $image_class == 'media-right'): ?>
          <div class="media-right pull-right">
            <?php print $row['image'] ?>
          </div>
        <?php endif ?>

        <div class="media-body">
          <?php if ($row['heading']): ?>
            <h3 class="media-heading">
              <?php print $row['heading'] ?>
            </h3>
          <?php endif ?>

          <?php print $row['body'] ?>
        </div>
      </div>
    <?php endforeach ?>
  </div>
</div>
