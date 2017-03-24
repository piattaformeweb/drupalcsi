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
 * AGID SUB-THEME OVERRIDE
 *
 */

?>
<div class="body_wrapper fp_body_wrapper push_container clearfix" id="page_top">

	<header class="header_container">
      
        <div class="main_nav_container fp_main_nav_container container-fullwidth menu_top main_nav_container_small">
          
			<div class="burger_wrapper">
				<div class="burger_container">
					<a class="toggle-menu menu-left push-body" href="#">
						<span class="bar"></span>
						<span class="bar"></span>
						<span class="bar"></span>
					</a>
				</div><!-- /burger_container -->
			</div><!-- /burger_wrapper -->
          
			<!-- Menu -->
			<nav class="cbp-spmenu cbp-spmenu-vertical cbp-spmenu-left">
				<div class="cbp-menu-wrapper clearfix">
				<?php print render($main_menu); ?>
				<!-- /navgoco -->
				</div>
			</nav><!-- /nav cbp-spmenu -->
			<!-- End Menu -->
          
			<div class="top_nav clearfix">
				<div class="container-fluid">       
					<div class="row">           
						<div class="logo_container col-lg-9 col-lg-offset-1 col-md-9 col-md-offset-1 col-xs-8 col-xs-offset-2">
						<?php if ($page['top_header']) :?>
						<?php print render($page['top_header']); ?>
						<?php endif; ?>
						</div><!-- /logo_container col-lg-9 col-lg-offset-1 col-md-9 col-md-offset-1 col-xs-8 col-xs-offset-2 -->

						<div class="col-lg-2 col-md-2 col-xs-2 button-spid-container">
						<?php if ($page['top_header_right']) :?>
						<?php print render($page['top_header_right']); ?>
						<?php endif; ?>
						</div><!-- /col-lg-2 col-md-2 col-xs-2 button-spid-container -->
					</div><!-- /row --> 
				</div><!-- /container -->
			</div><!-- /top_nav -->

			
			<div class="main_nav clearfix">     
				<div class="container-fluid">       
					<div class="row">
						<!--div class="col-md-8 col-sm-9 col-xs-12"-->
							<div class="logo_container clearfix col-lg-9 col-lg-offset-1 col-md-8 col-md-offset-1 col-sm-7 col-sm-offset-2 col-xs-7 col-xs-offset-2">
							
								<div class="logo_wrapper clearfix">
								<?php if ($logo):?>
									<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"> <img src="<?php print $logo; ?>" class="logo" alt="<?php print t('Home'); ?>" /> </a>
								<?php endif; ?>
								</div>
								
								<div class="logo_text clearfix">
								<?php if ($site_name && $is_front): ?>
									<h1 id="site-name">
										<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
									</h1>
								<?php elseif ($site_name && !$is_front) : ?>
									<p id="site-name" class="h1">
										<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
									</p>
								<?php endif; ?>
								</div>
					
								<?php if ($page['header']) :?>
								<?php print render($page['header']); ?>
								<?php endif; ?> 

					
							</div><!-- /logo_container -->
							<div id="sb-search" class="sb-search">
								<form>
									<input class="sb-search-input" placeholder="Cerca" type="text" value="" name="search" id="search" tabindex="-1">
									<input class="sb-search-submit" type="submit" value="" tabindex="-1">
									<span class="sb-icon-search"></span>
								</form>
							</div>
						<!--</div> /col-md-8 -->
                
						<div class="col-lg-3 col-md-3 col-sm-3 hidden-xs">

							<?php if ($page['navigation']) :?>
							<?php print render($page['navigation']); ?>
							<?php endif; ?>

						</div><!-- /col-md-4 -->        
					</div><!-- /row --> 
				</div><!-- /container -->
			</div><!-- /main_nav -->

	
			<?php if ((null !== menu_navigation_links('menu-sezioni-principali')) && is_array(menu_navigation_links('menu-sezioni-principali'))): ?>
			<div class="sub_nav clearfix">
				<?php
				$menu_links = menu_navigation_links('menu-sezioni-principali');
				print theme('links__menu_sezioni_principali', array('links' => $menu_links, 'attributes' => array('class' => array(''), ), 'heading' => array('text' => t('Top menu'), 'level' => 'h2', 'class' => array('sr-only'), ), ));
				?>
			</div><!-- /sub_nav -->  
			<?php endif; ?>
		</div><!-- /main_nav_container -->
      
	</header><!-- /header_container -->

	<?php if (isset($page_intro_markup) && $page_intro_markup !== ""): ?>
		<?php print $page_intro_markup; ?>
	<?php endif; ?>
	
	<?php if (!empty($page['banner'])): ?>
	<div id="banner" class="container-fullwidth">
		<div class="section section_white section_first clearfix">
			<?php print render($page['banner']); ?>
		</div>
	</div>
	<?php endif; ?>

	<?php if ($is_front === FALSE) : ?>
	<div id="main" class="main_container">

		<div class="section section_white section_first clearfix">
			<div class=" <?php print $container_class; ?>">
				<div class="row">
					<?php if (!empty($page['sidebar_first'])): ?>
					<aside class="col-lg-4 col-lg-offset-2 col-md-4 col-md-offset-1 col-sm-4 col-xs-12" role="complementary">
						<?php print render($page['sidebar_first']); ?>
					</aside>  <!-- /#sidebar-first -->
					<?php endif; ?>

					<section class="<?php print $content_column_class; ?>">
						<?php if (!empty($page['highlighted'])) : ?>
						<div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
						<?php endif; ?>
						<?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
						<a id="main-content"></a>
						<?php print render($title_prefix); ?>
						<?php if (!empty($title) && !$is_front): ?>
						<h1 class="page-header"><?php print $title; ?></h1>
						<?php endif; ?>
						<?php print render($title_suffix); ?>
						<?php print $messages; ?>
						<?php if (!empty($tabs)): ?>
						<?php print render($tabs); ?>
						<?php endif; ?>
						<?php if (!empty($page['help'])): ?>
						<?php print render($page['help']); ?>
						<?php endif; ?>
						<?php if (!empty($action_links)): ?>
						<ul class="action-links"><?php print render($action_links); ?></ul>
						<?php endif; ?>
						<!-- #content -->
						<?php if (!drupal_is_front_page()) : ?>
						<?php print render($page['content']); ?>
						<?php endif; ?>
						  
						<!-- /#content -->
					</section>

					<?php if (!empty($page['sidebar_second'])) : ?>
					<!-- #sidebar-second -->
					<aside class="col-lg-4 col-lg-offset-2 col-md-4 col-md-offset-1 col-sm-4 col-xs-12 sidebar" role="complementary">
						<?php print render($page['sidebar_second']); ?>
					</aside>
					<!-- /#sidebar-second -->
					<?php endif; ?>
					
				</div><!-- /row -->
			</div><!-- /container -->
		</div><!-- /section -->
      
	</div><!-- /#main -->
	<?php endif; ?>
	  
	<!-- #gallery_first -->
	<?php if (!empty($page['gallery_first'])) : ?>
    <div class="section section_grey clearfix">
		<div id="gallery-first" class="<?php print $container_class; ?>">
			<div class="row">
				<div class="col-lg-12">
				<?php print render($page['gallery_first']); ?>
				</div>
			</div>
		</div>
	</div>
	<?php endif; ?>
	<!-- /#gallery_first -->
	
	<!-- #gallery_second -->
	<?php if (!empty($page['gallery_second'])) : ?>
    <div class="section section_white clearfix">
		<div id="gallery-second" class="<?php print $container_class; ?>">
			<div class="row">
				<div class="col-lg-12">
				<?php print render($page['gallery_second']); ?>
				</div>
			</div>
		</div>
	</div>
	<?php endif; ?>
	<!-- /#gallery_second -->
	
	<!-- #gallery_third -->
	<?php if (!empty($page['gallery_third'])) : ?>
    <div class="section section_grey clearfix">
		<div id="gallery-third" class="<?php print $container_class; ?>">
			<div class="row">
				<div class="col-lg-12">
				<?php print render($page['gallery_third']); ?>
				</div>
			</div>
		</div>
	</div>
	<?php endif; ?>
	<!-- /#gallery_third -->
	
	<!-- #gallery_fourth -->
	<?php if (!empty($page['gallery_fourth'])) : ?>
    <div class="section section_white clearfix">
		<div id="gallery-fourth" class="<?php print $container_class; ?>">
			<div class="row">
				<div class="col-lg-12">
				<?php print render($page['gallery_fourth']); ?>
				</div>
			</div>
		</div>
	</div>
	<?php endif; ?>
	<!-- /#gallery_fourth -->

	<!-- #gallery_fifth -->
	<?php if (!empty($page['gallery_fifth'])) : ?>
    <div class="section section_blue clearfix">
		<div id="gallery-fifth" class="<?php print $container_class; ?>">
			<div class="row">
				<div class="col-lg-12">
				<?php print render($page['gallery_fifth']); ?>
				</div>
			</div>
		</div>
	</div>
	<?php endif; ?>
	<!-- /#gallery_fourth -->
	  
	<?php if($is_front) : ?>

	<div class="section section_blue_light clearfix" id="survey">
		<div class="container">
			<div class="row">
				<div class="col-md-12">
					<div class="icon_survey clearfix">
						<a href="<?php print $base_path; ?>webform/questionario" title="Compila il questionario">
						<img src="<?php print $base_path.drupal_get_path('theme', 'agid'); ?>/img/icon_survey.svg">
						<p>Valuta questo sito rispondi al questionario</p>
						</a>
					</div>
				</div><!-- /col-md-12 -->
			</div><!-- /row -->
		</div><!-- /container -->
	</div>
	
	<?php endif; ?>
	
	<div class="section section_grey_darker clearfix">
        <footer id="footer" class="footer_container fp_footer_container <?php print $container_class; ?>">
			<div class="row">
				<div class="col-md-12">
					<div class="logo_container clearfix">
						<?php if ($logo):?>
						<div class="logo_wrapper clearfix">
							<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"> <img src="<?php print $logo; ?>" class="logo" alt="<?php print t('Home'); ?>" /> </a>
						</div>
						<?php endif; ?>

						<?php if ($site_name):?>
						<div class="logo_text clearfix">
							<h2 class="h1"><span><?php print $site_name; ?></span></h2>
						</div>
						<?php endif; ?>
					</div><!-- /logo_container -->
				</div><!-- /col-md-12 -->
			</div><!-- /row -->

			
			<?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third'] || $page['footer_fourth']):?>
			<div class="row base">
				<?php if ($page['footer_first']):?>
				<div id="footer-first" class="<?php print $footer_grid_class; ?>">
					<div class="footer-area">
					<?php print render($page['footer_first']); ?>
					</div>
				</div>
				<?php endif; ?>      

				<?php if ($page['footer_second']) : ?>      
				<div id="footer-second" class="<?php print $footer_grid_class; ?>">
					<div class="footer-area">
					<?php print render($page['footer_second']); ?>
					</div>
				</div>
				<?php endif; ?>

				<?php if ($page['footer_third']) : ?>
				<div id="footer-third" class="<?php print $footer_grid_class; ?>">
					<div class="footer-area">
					<?php print render($page['footer_third']); ?>
					</div>
				</div>
				<?php endif; ?>

				<?php if ($page['footer_fourth']) : ?>
				<div id="footer-fourth" class="<?php print $footer_grid_class; ?>">
					<div class="footer-area">
					<?php print render($page['footer_fourth']); ?>
					</div>
				</div>
				<?php endif; ?>
			</div>
			<?php endif; ?>
		
		
			<?php if (!empty($page['footer'])) : ?>
			<div class="row">
				<?php print render($page['footer']); ?>
			</div>
			<?php endif; ?>     

        </footer><!-- /footer_container -->

	</div><!-- /section -->
      
	<a class="scrollto_top" href="#page_top"><span class="icon icon-icon-top" aria-hidden="true"></span></a>


</div><!-- /push_container -->    
    
<div class="push-body-mask"></div>