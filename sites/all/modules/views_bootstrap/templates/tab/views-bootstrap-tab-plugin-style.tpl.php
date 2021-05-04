<?php

/**
 * @file
 * Template to display Bootstrap tabs.
 */
if (!empty($title)): ?>
  <h3><?php print $title ?></h3>
<?php endif ?>
<?php
  $wrapper_classes = ' views-bootstrap-tabs';
  $option_classes = 'nav nav-' . $tab_type;
  if ($tab_position == 'justified' || $tab_position == 'stacked') {
    $option_classes .= ' nav-' . $tab_position;
  }
  elseif ($tab_position != 'basic') {
    $wrapper_classes = ' tabs-' . $tab_position;
  }
?>

<div id="views-bootstrap-tab-<?php print $id ?>" class="<?php print $classes; print $wrapper_classes; ?>">
  <?php if ($tab_position != 'below'): ?>
  <ul class="<?php print $option_classes ?>" role="tablist">
    <?php foreach ($tabs as $key => $tab): ?>
     <li class="<?php if ($key == $first_key) {print 'active';
    } ?>" role="presentation">
       <a href="#tab-<?php print "{$id}-{$key}" ?>" aria-controls="tab-<?php print "{$id}-{$key}" ?>" role="tab" data-toggle="tab"><?php print $tab ?></a>
     </li>
    <?php endforeach ?>
  </ul>
  <?php endif ?>
  <div class="tab-content">
    <?php foreach ($rows as $key => $row): ?>
      <?php
      $tab_classes = $tab_fade ? ' fade' : '';
      if ($key == $first_key) {
        $tab_classes = ' active';
        if ($tab_fade) {
         $tab_classes .= ' in';
        }
      }
      ?>
      <div role="tabpanel" class="tab-pane<?php print $tab_classes ?>" id="tab-<?php print "{$id}-{$key}" ?>">
        <?php print $row ?>
      </div>
    <?php endforeach ?>
  </div>
  <?php if ($tab_position == 'below'): ?>
    <ul class="<?php print $option_classes ?>" role="tablist">
      <?php foreach ($tabs as $key => $tab): ?>
        <li class="<?php if ($key == $first_key) {print 'active';
       } ?>" role="presentation">
          <a href="#tab-<?php print "{$id}-{$key}" ?>" aria-controls="tab-<?php print "{$id}-{$key}" ?>" role="tab" data-toggle="tab"><?php print $tab ?></a>
        </li>
      <?php endforeach ?>
    </ul>
  <?php endif ?>
</div>
