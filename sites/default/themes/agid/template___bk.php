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
/*
	// Caricamento libreria Google Maps...
	if (theme_get_setting('google_map_enabled', 'agid') || theme_get_setting('google_map_event_enabled', 'agid')) {

		// Get variables from theme.info file
		$google_map_latitude = theme_get_setting('google_map_latitude','agid');
		$google_map_longitude = theme_get_setting('google_map_longitude','agid');
		$google_map_zoom = (int) theme_get_setting('google_map_zoom','agid');
		$google_map_canvas = theme_get_setting('google_map_canvas','agid');
		$google_map_event_zoom = (int) theme_get_setting('google_map_event_zoom','agid');
		$google_map_event_canvas = theme_get_setting('google_map_event_canvas','agid');

		// Pass variables to JS
		drupal_add_js(array('agid' => array('google_map_latitude' => $google_map_latitude)), 'setting');
		drupal_add_js(array('agid' => array('google_map_longitude' => $google_map_longitude)), 'setting');
		drupal_add_js(array('agid' => array('google_map_zoom' => $google_map_zoom)), 'setting');
		drupal_add_js(array('agid' => array('google_map_canvas' => $google_map_canvas)), 'setting');
		drupal_add_js(array('agid' => array('google_map_event_zoom' => $google_map_event_zoom)), 'setting');
		drupal_add_js(array('agid' => array('google_map_event_canvas' => $google_map_event_canvas)), 'setting');

		drupal_add_js('https://maps.googleapis.com/maps/api/js?v=3.exp', array(
			'type' => 'external',
			'group' => JS_THEME,
			'scope' => 'header'
		));

	}
*/
	// Caricamento script del tema...
	drupal_add_js(drupal_get_path('theme', 'agid') . '/js/scripts-min.js', array(
		'type' => 'file',
		'group' => JS_THEME,
		'scope' => 'footer',
		'weight' => 40
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

/*
    // Add script to use gallery effect over images...
	drupal_add_js('
	    (function ($) {
	        $(window).load(function() {
				$(".image-popup").magnificPopup({
	    			type:"image",
	    			removalDelay: 300,
	    			mainClass: "mfp-fade",
	    			gallery: {
	    		      enabled: true, // set to true to enable gallery
	    			}
				});
	        });
	    }(jQuery));', array('type' => 'inline', 'scope' => 'footer', 'weight' => 4)
	);

	// Add script to show map in page
	if (theme_get_setting('google_map_enabled', 'agid')) {

		drupal_add_js('
			(function ($) { 

				if ($("#"+Drupal.settings.agid[\'google_map_canvas\']+"").length > 0) {

					var map;
					var myLatlng;
					var myZoom;
					var marker;

					myLatlng = new google.maps.LatLng(Drupal.settings.agid[\'google_map_latitude\'], Drupal.settings.agid[\'google_map_longitude\']);
					myZoom = Drupal.settings.agid[\'google_map_zoom\'];
					
					function initialize() {
					
						var mapOptions = {
							zoom: myZoom,
							mapTypeId: google.maps.MapTypeId.ROADMAP,
							center: myLatlng,
							scrollwheel: false,
							streetViewControl: true,
							streetViewControlOptions: {
								position: google.maps.ControlPosition.LEFT_CENTER
							},
							zoomControl: true,
							zoomControlOptions: {
								position: google.maps.ControlPosition.LEFT_CENTER
							}
						};
						
						map = new google.maps.Map(document.getElementById(Drupal.settings.agid[\'google_map_canvas\']),mapOptions);
						
						marker = new google.maps.Marker({
							map:map,
							draggable:true,
							position: myLatlng
						});
						
						google.maps.event.addDomListener(window, "resize", function() {
							map.setCenter(myLatlng);
						});
				
					}
				
					google.maps.event.addDomListener(window, "load", initialize);
					
				}
		
			}(jQuery));',
			array(
				'type' => 'inline',
				'scope' => 'footer',
				'weight' => 1
			)
		);

	}
*/
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

		// Reset node $title var to match different layout
		if ($node->type == "scheda_personale") {
			drupal_set_title('');
		}	    

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
	            $banner_image_markup = "<div class=\"container-fullwidth ".$banner_class."\"><div class=\"image_container clearfix\" style=\"background-image: url(".$image.");\"></div>";
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

	if (theme_get_setting('social_share_on') === 1) {

		$social_btn = '<div class="share_buttons reveal-content clearfix"><div class="share_buttons_container clearfix">';
		
		if (theme_get_setting('social_share_facebook') === 1) {
			$social_btn .= '<a href="#" title="" tabindex="-1"><span class="icon icon-facebook" aria-hidden="true"></span></a>';
		}
		
		/*
		<a href="#" title="" tabindex="-1"><span class="icon icon-twitter" aria-hidden="true"></span></a>
		<a href="#" title="" tabindex="-1"><span class="icon icon-google-plus" aria-hidden="true"></span></a>
		<a href="#" title="" tabindex="-1"><span class="icon icon-youtube" aria-hidden="true"></span></a>
		<a href="#" title="" tabindex="-1"><span class="icon icon-flickr" aria-hidden="true"></span></a>
		<a href="#" title="" tabindex="-1"><span class="icon icon-slideshare" aria-hidden="true"></span></a>
		<a class="hidden-lg hidden-md" href="#" title="" tabindex="-1"><span class="icon icon-whatsapp" aria-hidden="true"></span></a>

		$soci
		</div><!-- /share_buttons_container -->
		<span>Condividi</span>
		<a href="#" title="" class="share_buttons_trigger reveal-trigger" tabindex="-1"><span class="icon icon-sharethis" aria-hidden="true"></span></a>
		</div>
*/

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

	$node = $variables['elements']['#node'];
/*
	if (($node->type == 'evento' || $node->type == 'struttura_organizzativa') && $node->field_indirizzo) {

		$node = $variables['elements']['#node'];
		// Add script to show map in page
		if (theme_get_setting('google_map_event_enabled', 'agid')) {

			$google_map_event_latitude = $node->field_indirizzo['und'][0]['latitude'];
			$google_map_event_longitude = $node->field_indirizzo['und'][0]['longitude'];

			drupal_add_js(array('agid' => array('google_map_event_latitude' => $google_map_event_latitude)), 'setting');
			drupal_add_js(array('agid' => array('google_map_event_longitude' => $google_map_event_longitude)), 'setting');

			drupal_add_js('

				(function ($) { 

					if ($("#"+Drupal.settings.agid[\'google_map_event_canvas\']+"").length > 0) {
						console.log("#"+Drupal.settings.agid[\'google_map_event_canvas\']+"");
						var map;
						var myLatlng;
						var myZoom;
						var marker;

						myLatlng = new google.maps.LatLng(Drupal.settings.agid[\'google_map_event_latitude\'], Drupal.settings.agid[\'google_map_event_longitude\']);
						myZoom = Drupal.settings.agid[\'google_map_event_zoom\'];
						
						function initialize() {
						
							var mapOptions = {
								zoom: myZoom,
								mapTypeId: google.maps.MapTypeId.ROADMAP,
								mapTypeControl: false,
								streetViewControl: false,
								center: myLatlng,
								scrollwheel: false
							};
							
							map = new google.maps.Map(document.getElementById(Drupal.settings.agid[\'google_map_event_canvas\']),mapOptions);
							
							marker = new google.maps.Marker({
								map:map,
								position: myLatlng
							});
							
							
							google.maps.event.addListener(marker, "click", function() {
								// Insert onclick behaviour...
							});
							
							google.maps.event.addDomListener(window, "resize", function() {
								map.setCenter(myLatlng);
							});
					
						}
					
						google.maps.event.addDomListener(window, "load", initialize);
						
					}
				
				}(jQuery));',
				array(
					'type' => 'inline',
					'scope' => 'footer',
					'weight' => 1
				)
			);

		}

	}
*/
}


/**
 * Other theme hooks...
 */


function agid_menu_tree__main_menu(&$vars) {
	// To add CSS class to the main menu ul
	return '<ul class="navgoco">' . $vars['tree'] . '</ul>';
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