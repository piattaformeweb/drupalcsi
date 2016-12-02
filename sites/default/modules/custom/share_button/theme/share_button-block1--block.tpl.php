<?php
// Shortcuts for items...
$u = $items['share_page'];
$t = $items['share_title'];
?>
<div class="share_buttons reveal-content clearfix">
	<div class="share_buttons_container clearfix">

	<?php if (isset($items['opt_facebook']) && $items['opt_facebook'] == 1) : ?>
		<a href="https://www.facebook.com/sharer/sharer.php?u=<?php print $u; ?>&t=<?php print $t; ?>" title="" tabindex="-1" title="Condividi via Facebook" target="_blank"><span class="icon icon-facebook" aria-hidden="true"></span></a>
	<?php endif; ?>

	<?php if (isset($items['opt_twitter']) && $items['opt_twitter'] == 1) : ?>
		<a href="http://twitter.com/share?text=<?php print $t; ?>&url=<?php print $u; ?>" title="" tabindex="-1" target="_blank" title="Condividi via Twitter"><span class="icon icon-twitter" aria-hidden="true"></span></a>
	<?php endif; ?>

	<?php if (isset($items['opt_googleplus']) && $items['opt_googleplus'] == 1) : ?>
		<a href="https://plus.google.com/share?url=<?php print $u; ?>" title="" tabindex="-1" target="_blank" title="Condividi via Google Plus"><span class="icon icon-google-plus" aria-hidden="true"></span></a>
	<?php endif; ?>

	</div><!-- /share_buttons_container -->
	<span><?php print t("Share"); ?></span>
	<a href="#" title="" class="share_buttons_trigger reveal-trigger" tabindex="-1"><span class="icon icon-sharethis" aria-hidden="true"></span></a>
</div><!-- /share_buttons -->