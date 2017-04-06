<?php
/**
 * @file
 * The primary PHP file for this theme.
 */

 
function agid_preprocess_html(&$variables) {

	// Caricamento font Titillium...
	drupal_add_css('https://fonts.googleapis.com/css?family=Titillium+Web:400,200,200italic,300,300italic,400italic,600,600italic,700,700italic,900', array(
		'type' => 'external',
		'scope' => 'header'
	));

	// Caricamento script del motore di ricerca mobile...
    drupal_add_js(drupal_get_path('theme', 'agid') . '/js/search.js', array(
        'type' => 'file',
        'group' => JS_THEME,
        'scope' => 'footer',
        'weight' => 35
    ));

	// Caricamento script del tema...
	drupal_add_js(drupal_get_path('theme', 'agid') . '/js/scripts-min.js', array(
		'type' => 'file',
		'group' => JS_THEME,
		'scope' => 'footer',
		'weight' => 40
	));

	drupal_add_css(libraries_get_path('magnific-popup') . '/dist/magnific-popup.css', array(
		'type' => 'file',
		'group' => CSS_THEME,
		'every_page' => TRUE,
		'media' => 'all'
	));

	// Caricamento js della libreria Magic Popup...
	drupal_add_js(libraries_get_path('magnific-popup') . '/dist/jquery.magnific-popup.min.js', array(
		'type' => 'file',
		'group' => JS_THEME,
		'scope' => 'footer',
		'weight' => 45
	));
	
	// Caricamento script custom del tema...
	drupal_add_js(drupal_get_path('theme', 'agid') . '/js/custom.js', array(
		'type' => 'file',
		'group' => JS_THEME,
		'scope' => 'footer',
		'weight' => 50
	));
}


/**
 * Pre-processes variables for the "page" theme hook.
 *
 * See template for list of available variables.
 *
 * @see page.tpl.php
 *
 * @ingroup theme_preprocess
 */
function agid_preprocess_page(&$variables) {

	// Add information about the number of sidebars.
	if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
		$variables['content_column_class'] = "col-sm-4";
	}
	elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
		$variables['content_column_class'] = "col-lg-6 col-md-7 col-sm-8 col-xs-12";
	}
	else {
		$variables['content_column_class'] = "col-sm-12";
	}

	if (bootstrap_setting('fluid_container') == 1) {
		$variables['container_class'] = "container-fluid";
	}
	else {
		$variables['container_class'] = "container";
	}

	// Primary nav.
	$variables['primary_nav'] = FALSE;
	if ($variables['main_menu']) {
		// Build links.
		$variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
		// Provide default theme wrapper function.
		$variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
	}

	// Secondary nav.
	$variables['secondary_nav'] = FALSE;
	if ($variables['secondary_menu']) {
		// Build links.
		$variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
		// Provide default theme wrapper function.
		$variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
	}

  	$variables['navbar_classes_array'] = array('navbar');

	if (bootstrap_setting('navbar_position') !== '') {
		$variables['navbar_classes_array'][] = 'navbar-' . bootstrap_setting('navbar_position');
	}
	elseif (bootstrap_setting('fluid_container') == 1) {
		$variables['navbar_classes_array'][] = 'container-fluid';
	}
	else {
		$variables['navbar_classes_array'][] = 'container';
	}
	if (bootstrap_setting('navbar_inverse')) {
		$variables['navbar_classes_array'][] = 'navbar-inverse';
	}
	else {
		$variables['navbar_classes_array'][] = 'navbar-default';
	}

  
    // Main menu alter to display sublinks...
    $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    $variables['main_menu'] =  $main_menu_tree;


	// Variables settings...
	
	$footer_first = $variables['page']['footer_first'];
	$footer_second = $variables['page']['footer_second'];
	$footer_third = $variables['page']['footer_third'];
	$footer_fourth = $variables['page']['footer_fourth'];
	
	$variables['top_header_grid_class'] = 'col-md-8 col-md-offset-2 col-xs-8 col-xs-offset-2';
	$variables['top_header_right_grid_class'] = 'col-md-2 col-xs-2';


	// Alter breadcrumbs classes to remove preventclick
	$breadcrumb_full = theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb()));
	$badcrumbs = array("preventclick");
	$breadcrumb = str_replace($badcrumbs, "", $breadcrumb_full);


	// Set classes of footer columns...
	if ($footer_first && $footer_second && $footer_third && $footer_fourth) { 
		$variables['footer_grid_class'] = 'col-md-3 col-sm-6';
	} elseif ((!$footer_first && $footer_second && $footer_third && $footer_fourth) || ($footer_first && !$footer_second && $footer_third && $footer_fourth) 
	|| ($footer_first && $footer_second && !$footer_third && $footer_fourth) || ($footer_first && $footer_second && $footer_third && !$footer_fourth)) { 
		$variables['footer_grid_class'] = 'col-md-4 col-sm-4';
	} elseif ((!$footer_first && !$footer_second && $footer_third && $footer_fourth) || (!$footer_first && $footer_second && !$footer_third && $footer_fourth) 
	|| (!$footer_first && $footer_second && $footer_third && !$footer_fourth) || ($footer_first && !$footer_second && !$footer_third && $footer_fourth)
	|| ($footer_first && !$footer_second && $footer_third && !$footer_fourth) || ($footer_first && $footer_second && !$footer_third && !$footer_fourth)) {
		$variables['footer_grid_class'] = 'col-md-6';		
	} else { 
		$variables['footer_grid_class'] = 'col-md-12';
	}

	
	/**
	 * Generate page intro markup and remove title
	 */

	if (arg(0) == "node" && is_numeric(arg(1))) {
	    
	    $nid = arg(1);
	    $node = node_load($nid);
	    $lang= "und";
	    $banner_class = "";
	    $variables['page_intro_markup'] = "";

	    if (empty($node->field_teaser_image) || (!isset($node->field_internal_banner) || $node->field_internal_banner[$lang][0]["value"] == "0")) { 
		    $banner_class = "no-internal-banner-image";
		} else {
		    $banner_class = "with-internal-banner-image ";
	    }

	    if ( (!empty($node->field_teaser_image) && (isset($node->field_internal_banner) && $node->field_internal_banner[$lang][0]["value"] == "1"))) {

	        if (!empty($node->field_teaser_image) && (isset($node->field_internal_banner) && $node->field_internal_banner[$lang][0]["value"] == "1")) {
	            $image = image_style_url("slideshow", $node->field_teaser_image[$lang][0]["uri"]);
	            $image_alt = $node->field_teaser_image[$lang][0]["alt"];
	            $image_title = $node->field_teaser_image[$lang][0]["title"]; 
	            $banner_image_markup = "<div class=\"image_container clearfix\" style=\"background-image: url(".$image.");\"></div>";
	            //$banner_image_markup = "<div class=\"section section_white section_full_screen clearfix ".$banner_class."\"><div class=\"image_container clearfix\" style=\"background-image: url(".$image.");\"></div></div>";
	        } else {
	            $banner_image_markup = "";
	        }

	        $variables['page_intro_markup'] = "<div class=\"section section_white section_full_screen clearfix\">".$banner_image_markup."</div>";
	    
	    } else {
	    	$variables['page_intro_markup'] = "";
	    }

	} else {
    	$variables['page_intro_markup'] = "";
	}


  
}


/**
 * Processes variables for the "page" theme hook.
 *
 * See template for list of available variables.
 *
 * @see page.tpl.php
 *
 * @ingroup theme_process
 */
function agid_process_page(&$variables) {
  $variables['navbar_classes'] = implode(' ', $variables['navbar_classes_array']);
}


/**
 * Pre-processes variables for the "node" theme hook.
 *
 * See template for list of available variables.
 *
 * @see node.tpl.php
 *
 * @ingroup theme_preprocess
 */

function agid_preprocess_node(&$variables) {

	$node		= $variables['elements']['#node'];
	$view_mode	= $variables['elements']['#view_mode'];
	//$types		= array("evento", "struttura_organizzativa", "");
	$type		= $node->type;
	
	if (($type == "articolo") && ($view_mode == "teaser") && empty($node->field_image)) {
		$variables['classes_array'][] = 'node-teaser-noimg';
	}
	

}


/**
 * Other theme hooks...
 */

/*
function agid_menu_tree__main_menu(&$vars) {
	// To add CSS class to the main menu ul
	return '<ul class="menu navgoco">' . $vars['tree'] . '</ul>';
}
*/

function agid_menu_tree(&$variables) {
  return '<ul class="menu">' . $variables['tree'] . '</ul>';
}

function agid_form_alter(&$form, &$form_state, $form_id) {
	
	if ($form_id == 'search_block_form') {
		$form['search_block_form']['#title'] = t('Search');
		$form['search_block_form']['#size'] = NULL;
		$form['search_block_form']['#title_display'] = 'invisible';
		$form_default = t('Enter terms then hit Search...');
		$form['search_block_form']['#default_value'] = $form_default;
		$form['actions']['submit']['#attributes']['value'][] = '';
		$form['actions']['submit']['#attributes']['class'][] = '';
		$form['search_block_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = '{$form_default}';}", 'onfocus' => "if (this.value == '{$form_default}') {this.value = '';}" );
	}
	

}

function agid_bootstrap_search_form_wrapper($variables) {
  //$output = '<div class="input-group">';
  $output = $variables['element']['#children'];
 // $output .= '<span class="input-group-btn">';
 // $output .= '<button type="submit" class="btn btn-primary">' . _bootstrap_icon('search', t('Search')) . '</button>';
  $output .= '<input type="submit" value="h" />'; // aggiunto...
  //$output .= '</span>';
  //$output .= '</div>';
  return $output;
}


