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