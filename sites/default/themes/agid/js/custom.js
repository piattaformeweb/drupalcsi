/**
 * Cityweb – CMS per siti web istituzionali dei comuni italiani
 * Copyright (C)  2016 CSI-Piemonte - C.so Unione Sovietica 216, 10134, Turin, Italy.– piattaformeweb@csi.it
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by  the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see http://www.gnu.org/licenses/
 */

// We define a function that takes one parameter named $.
(function ($) {

	$(".cbp-spmenu li a.preventclick").attr("href","#");
	$(".image-popup").magnificPopup({
		type:"image",
		removalDelay: 300,
		mainClass: "mfp-fade",
		gallery: {
			enabled: true, // set to true to enable gallery
		}
	});
	
	$(".region-content .block-menu-block ul.menu").addClass("grid");
	$(".region-content .block-menu-block ul.menu li").addClass("grid-sizer col-md-3 col-sm-6 col-xs-12");
	$("div#edit-basic").addClass("nav_search");
	$(".views-submit-button button.btn-info").removeClass("btn-info").addClass("btn-primary");
	
 $('.carousel_gallery').owlCarousel({
    nav: true,
    navText: ["o","b"],
    items: 3,
    dots: false,
    loop: false,
    margin: 0,
    responsive: {
      0: {
      items: 1
      },
      768: {
      items: 2
      },
      992: {
      items: 3
      }
    }
  });
	
// Here we immediately call the function with jQuery as the parameter.
}(jQuery));