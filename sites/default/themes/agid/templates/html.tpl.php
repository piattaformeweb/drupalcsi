<?php
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or
 *   'rtl'.
 * - $html_attributes:  String of attributes for the html element. It can be
 *   manipulated through the variable $html_attributes_array from preprocess
 *   functions.
 * - $html_attributes_array: An array of attribute values for the HTML element.
 *   It is flattened into a string within the variable $html_attributes.
 * - $body_attributes:  String of attributes for the BODY element. It can be
 *   manipulated through the variable $body_attributes_array from preprocess
 *   functions.
 * - $body_attributes_array: An array of attribute values for the BODY element.
 *   It is flattened into a string within the variable $body_attributes.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see bootstrap_preprocess_html()
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 *
 * @ingroup templates
 */
?><!DOCTYPE html>
<!--[if lt IE 7]><html class="no-js lt-ie9 lt-ie8 lt-ie7"><![endif]-->
<!--[if IE 7]><html class="no-js lt-ie9 lt-ie8"><![endif]-->
<!--[if IE 8]><html class="no-js lt-ie9"><![endif]-->
<!--[if gt IE 8]><!--><html class="no-js"><!--<![endif]-->
<html<?php print $html_attributes;?><?php print $rdf_namespaces;?>>
<head>
	<link rel="profile" href="<?php print $grddl_profile; ?>" />
	<meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
	<?php print $head; ?>
	<title><?php print $head_title; ?></title>
	<?php print $styles; ?>
	
<!-- HTML5 element support for IE6-8 -->
<!--[if lt IE 9]>

	<link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web" />
	<link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:200italic" /> 	
	<link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:300italic" />
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:400italic" /> 
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:600italic" /> 	
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:700italic" /> 	
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:200" /> 	
	<link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:300" />
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:400" /> 
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:600" /> 	
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:700" /> 
    <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Titillium+Web:900" />

	<link rel="stylesheet" href="<?php echo base_path().path_to_theme(); ?>/css/main.css" type="text/css">
	<link rel="stylesheet" href="<?php echo base_path().path_to_theme(); ?>/css/ie8.css" type="text/css">

	<script src="<?php echo base_path().path_to_theme(); ?>/js/vendor/htmll5shiv.js"></script>
	<script src="<?php echo base_path().path_to_theme(); ?>/js/vendor/respond.min.js"></script>
	
<![endif]-->	
	
	
	<?php print $scripts; ?>
</head>
<body<?php print $body_attributes; ?>>
	<p id="skip-link">
		<a href="#main" class="element_invisible element_focusable">Vai al Contenuto</a>
		<a href="#footer" class="element_invisible element_focusable">Raggiungi il pi&egrave; di pagina</a>
	</p>

	<?php print $page_top; ?>
	<?php print $page; ?>
	<?php print $page_bottom; ?>

</body>
</html>
