<?php
/**
 * CMS Drupal 7 per i siti web dei Comuni
 * Copyright (C)  2016 CSI-Piemonte - C.so Unione Sovietica 216, 10134, Turin, Italy.– piattaformeweb@csi.it
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by  the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see http://www.gnu.org/licenses/
 */

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup templates
 */
?>

<?php if ($teaser) : ?>
<div class="box_text box_text_small">
	<div class="box_text_container">
<?php endif; // end $teaser?>

 		
<article id="node-<?php print $node->nid; ?>" class="row <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

<?php
  if ($node->field_facebook){ $facebook = $node->field_facebook['und'][0]['url']; }
  if ($node->field_twitter){ $twitter = $node->field_twitter['und'][0]['url']; }
  if ($node->field_linkedin){ $linkedin = $node->field_linkedin['und'][0]['url']; }
  if ($node->field_email){ $email = $node->field_email['und'][0]['email']; }
  if ($node->field_telefono){ $telefono = $node->field_telefono['und'][0]['value']; }
?>

<?php if ($page) : ?>

  <aside class="article-side col-md-4">

  <?php if ($photo = render($content['field_photo'])) : ?>
    <?php print render($photo); ?>
  <?php endif; ?>
        
	<div class="box_tools field clearfix">
	
	<?php if (render($content['field_facebook'])) : ?>
		<a href="<?php print $facebook; ?>" target="_blank"><span class="fa fa-facebook"></span></a>
	<?php endif; ?>
	
	<?php if (render($content['field_twitter'])) : ?>
		<a href="<?php print $twitter; ?>" target="_blank"><span class="fa fa-twitter"></span></a>
	<?php endif; ?>
	
	<?php if (render($content['field_linkedin'])) : ?>
		<a href="<?php print $linkedin; ?>" target="_blank"><span class="fa fa-linkedin"></span></a>
	<?php endif; ?>
	
	</div>

  </aside>

  <div class="article-main col-md-8">

    <?php if (render($content['tile_field'])) : ?>
    <header>
      <?php print render($content['tile_field']); ?>
    </header>
    <?php endif; ?>


    <?php
      // Hide comments, tags, and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_tags']);
      hide($content['field_twitter']);
      hide($content['field_facebook']);
      hide($content['field_linkedin']);
      print render($content);
    ?>
    <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php print render($content['field_tags']); ?>
      <?php print render($content['links']); ?>
    </footer>
    <?php endif; ?>
    <?php print render($content['comments']); ?>
  </div>

<?php endif; // end $page?>

<?php if ($teaser) : ?>



    <?php if (!empty($title_prefix) || !empty($title_suffix) || $display_submitted): ?>

	<header> 
	  <?php print render($title_prefix); ?>
	  <?php if (!empty($title)): ?>
	  <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
	  <?php endif; ?>
	  <?php print render($title_suffix); ?>
	</header>

    <?php endif; ?>

	<?php if (!empty($content['field_email'])) { print render($content['field_email']); } ?>
	<?php if (!empty($content['field_telefono'])) { print render($content['field_telefono']); } ?>

	<div class="box_tools field clearfix">
	
	<?php if (render($content['field_facebook'])) : ?>
		<a href="<?php print $facebook; ?>" target="_blank"><span class="fa fa-facebook"></span></a>
	<?php endif; ?>
	
	<?php if (render($content['field_twitter'])) : ?>
		<a href="<?php print $twitter; ?>" target="_blank"><span class="fa fa-twitter"></span></a>
	<?php endif; ?>
	
	<?php if (render($content['field_linkedin'])) : ?>
		<a href="<?php print $linkedin; ?>" target="_blank"><span class="fa fa-linkedin"></span></a>
	<?php endif; ?>
	
	</div>
	
    <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
		<footer>
		<?php print render($content['field_tags']); ?>
		<?php // print render($content['links']); ?>
		</footer>
    <?php endif; ?>
    <?php print render($content['comments']); ?>


<?php endif; // end $teaser?>

</article>

<?php if ($teaser) : ?>
	</div>
</div>
<?php endif; // end $teaser?>