<?php

/**
 * @file
 * Template to display Bootstrap Carousels.
 */
if (!empty($title)): ?>
  <h3><?php print $title ?></h3>
<?php endif ?>

<div id="views-bootstrap-carousel-<?php print $id ?>" class="<?php print $classes ?>" <?php print $attributes ?>>
  <?php if ($indicators): ?>
    <!-- Carousel indicators -->
    <ol class="carousel-indicators">
      <?php foreach ($rows as $key => $value): ?>
        <li data-target="#views-bootstrap-carousel-<?php print $id ?>" data-slide-to="<?php print $key ?>" class="<?php if ($key == $first_key) {print 'active';
       } ?>"></li>
      <?php endforeach ?>
    </ol>
  <?php endif ?>

  <!-- Carousel items -->
  <div class="carousel-inner" role="listbox">
    <?php foreach ($rows as $key => $row): ?>
      <div class="item <?php if ($key == $first_key) {print 'active';
     } ?>">
        <?php print $row ?>
      </div>
    <?php endforeach ?>
  </div>

  <?php if ($navigation): ?>
    <!-- Carousel navigation -->
    <a class="carousel-control left" href="#views-bootstrap-carousel-<?php print $id ?>" role="button" data-slide="prev">
      <span class="icon-prev"></span>
      <span class="sr-only">Previous</span>
    </a>
    <a class="carousel-control right" href="#views-bootstrap-carousel-<?php print $id ?>" role="button" data-slide="next">
      <span class="icon-next"></span>
      <span class="sr-only">Next</span>
    </a>
  <?php endif ?>
</div>
