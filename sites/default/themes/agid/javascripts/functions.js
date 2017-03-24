/**
 * CMS Drupal 7 per i siti web dei Comuni
 * Copyright (C)  2016 CSI-Piemonte - C.so Unione Sovietica 216, 10134, Turin, Italy.– piattaformeweb@csi.it
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by  the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see http://www.gnu.org/licenses/
 */

/* Scripts Functions */

// Avoid `console` errors in browsers that lack a console.
(function() {
    var method;
    var noop = function () {};
    var methods = [
        'assert', 'clear', 'count', 'debug', 'dir', 'dirxml', 'error',
        'exception', 'group', 'groupCollapsed', 'groupEnd', 'info', 'log',
        'markTimeline', 'profile', 'profileEnd', 'table', 'time', 'timeEnd',
        'timeStamp', 'trace', 'warn'
    ];
    var length = methods.length;
    var console = (window.console = window.console || {});

    while (length--) {
        method = methods[length];

        // Only stub undefined methods.
        if (!console[method]) {
            console[method] = noop;
        }
    }
}());


/* Modernizr Image SVG Fallback PNG */

if(!Modernizr.svg) {
    $('img[src*="svg"]').attr('src', function() {
        return $(this).attr('src').replace('.svg', '.png');
    });
}

/* End Modernizr Image SVG Fallback PNG */


/* Toggle Target */

$(document).ready(function() {
    $('.toggle-trigger').click(function(e) {
        e.preventDefault();
        $(this).next('.toggle-content').slideToggle(200);
    });
});

/* End Toggle Target */


/* Toggle Datepicker */

$(document).ready(function() {
    $('.toggle-datepicker').click(function(e) {
        e.preventDefault();
        $(this).toggleClass('active');
        $('.section_datepicker').slideToggle(200);
    });
});

/* End Toggle Datepicker */


/* Reveal */

$(document).ready(function() {
    $('.reveal-trigger').click(function(e) {
        e.preventDefault();
        $(this).parent('.reveal-content').toggleClass('active');
    });
});

/* End Reveal */



/* Mobile Tap Open Link */

$(document).ready(function() {
    $(document).on('tap', '.share_button', function(e) {
        e.stopPropagation();
        e.preventDefault();
        window.open( $(this).attr('href') );
        return false;
    });
});

/* End Mobile Tap Open Link */


/* Share Trigger */

$(document).ready(function() {
    $(document).on('click touchstart', '.share-reveal-trigger', function(e) {
        e.preventDefault();
        $(this).parent('.share-reveal-content').toggleClass('active');
        $('.share_buttons_wrapper').toggleClass('active');
        $('.share-more-trigger').removeClass('hide');
        $('.share_more_container').removeClass('active');
        $('.share_buttons_scroller').toggleClass('noscroll');
    });
});

/* End Share Trigger */

/* Share More Trigger */

$(document).ready(function() {    
    $(document).on('click touchstart', '.share-more-trigger', function(e) {
        e.preventDefault();
        $('.share_more_container').toggleClass('active');
        $('.share-more-trigger').addClass('hide');
    });
});

/* End Share More Trigger */

/* Share More Container Close */

$(document).ready(function() {
    $(document).on('click touchstart', '.share_more_container_close', function(e) {
        e.preventDefault();
        $('.share_more_container').removeClass('active');
        $('.share-more-trigger').removeClass('hide');
    });
});

/* End Share More Container Close */




/* Sticky */

$(window).scroll(function() {    
  var scroll = $(window).scrollTop();

  if (scroll > 120) {
    $(".main_nav_container").addClass("menu_sticky");
  }
  else {
    $(".main_nav_container").removeClass("menu_sticky");
  }
});

$(function() {
  $('.main_nav_container').addClass('menu_top');
});

$(window).scroll(function() {    
  var top_offset = $(window).scrollTop();

  if (top_offset <= 120) {
    $(".main_nav_container").addClass("menu_top");
  }
  else {
    $(".main_nav_container").removeClass("menu_top");
  }
});

/* End Sticky */


/* Keyboard linking */

$(".sub_nav a").keydown(function(e) {
  if(e.keyCode==39){
    $(this).parent().next().find('a').focus();
  }
  if(e.keyCode==37){
    $(this).parent().prev().find('a').focus();
  }
});


$(".navgoco a").keydown(function(e) {
  if(e.keyCode==40){
    $(this).parent().next().find('a').focus();
  }
  if(e.keyCode==38){
    $(this).parent().prev().find('a').focus();
  }
});

/* End Keyboard linking */


/********** CALLBACKS JS **********/


/* jPush Menu */

jQuery(document).ready(function($) {
  $('.toggle-menu').jPushMenu();
  $( ".toggle-menu" ).click(function( event ) {
    event.preventDefault();
    var winHeight = $(window).height();
    if ($(this).hasClass('menu-active')) {
      $( '.push_container' ).css({
        'position':'fixed',
        'width':'100%'
      });
    } else {
      $( '.push_container' ).css({
        'position':'relative',
        'width':'auto'
      });
    }
  });
});

jQuery(document).ready(function($) {
  $('.toggle-menu-related').jPushMenu();
  $( ".toggle-menu-related" ).click(function( event ) {
    event.preventDefault();
    var winHeight = $(window).height();
    $('.mobile-header-menu ul').css('height', winHeight-162);
    if ($(this).hasClass('menu-active')) {
      $( '.push_container' ).css({
        'position':'fixed',
        'width':'100%'
      });
    } else {
      $( '.push_container' ).css({
        'position':'relative',
        'width':'auto'
      });
    }
  });
});

// $(document).keyup(function(e) {
//   Bind the key esc to the toggle menu funcion
//   if (e.which == 77) { 
//     $('.toggle-menu').click();
//     $('.toggle-menu').focus(); 
//   }
// });

/* End jPush Menu */


/* ScrollTo */

$(function() {
  $('.scrollto_top').bind('click',function(event){
    var $anchor = $(this);
      $('html, body').stop().animate({
        scrollTop: $($anchor.attr('href')).offset().top
      }, 1000,'easeInOutExpo');
    event.preventDefault();
  });
});

$(window).scroll(function() {    
    var scroll = $(window).scrollTop();

    if (scroll >= 200) {
        $(".scrollto_top").addClass("show");
    } else {
        $(".scrollto_top").removeClass("show");
    }
});

/* End ScrollTo */


/* Navgoco */

$(document).ready(function() {
	// Initialize navgoco with default options
	
	$(".navgoco").navgoco({
		caretHtml: '',
		accordion: true,
		openClass: 'open',
		
		slide: {
			duration: 400,
			easing: 'swing'
		},
		onClickAfter: function(submenu) {
			$('.navgoco').find('li').removeClass('active');
			var li =  $(this).parent();
			var lis = li.parents('li');
			li.addClass('active');
			lis.addClass('active');
		},
	});
});

/* End Navgoco */



/* Navgoco Change Tabindex on Toggle Menu */

$('.toggle-menu').click(function() {
  if ($('.navgoco a').attr('tabindex','-1')) {
    $('.navgoco a').attr('tabindex','0');
  }
});

/* End Navgoco Change Tabindex on Toggle Menu */




/* Carousel 2 */

jQuery(document).ready(function($) {
  
  $('.carousel_base').owlCarousel({
    nav: true,
    navText: ["o","b"],
    items: 3,
    dots: false,
    loop: false,
    margin: 16,
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
  
  
  $('.carousel_album').owlCarousel({
    nav: true,
    navText: ["s","t"],
    items: 1,
    dots: true,
    loop: false,
    margin: 0,
    mouseDrag: false,
    responsive: {
      0: {
      items: 1
      },
      768: {
      items: 1
      },
      992: {
      items: 1
      }
    }
  });
  
  $(document).ready(function() {
    $('.carousel_album .item a').click(function(e) {
        e.preventDefault();
    });
  });
  
   
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
  
  
  agendadays = $(".carousel_agenda_days");
  agendaevents = $(".carousel_agenda_events");

  agendadays.on('change.owl.carousel', function(event) {
    if (event.namespace && event.property.name === 'position') {
      var target = event.relatedTarget.relative(event.property.value, true);
      agendaevents.owlCarousel('to', target, 500, true);
    }
  })
  
  agendadays.owlCarousel({
    nav: true,
    navText: ["s","t"],
    center: false,
    items: 3,
    loop: false,
    dots: false,
    margin: 0,
    responsive: {
      0: {
      items: 1
      },
      768: {
      items: 1
      },
      992: {
      items: 3
      }
    }
  });
  
  agendaevents.owlCarousel({
    nav: false,
    mouseDrag: false,
    touchDrag: false,
    pullDrag: false,
    center: false,
    items: 3,
    loop: false,
    dots: false,
    margin: 0,
    responsive: {
      0: {
      items: 1
      },
      768: {
      items: 1
      },
      992: {
      items: 3
      }
    }
  });
  
   
  $('.carousel_calendar_days').owlCarousel({
    nav: true,
    navText: ["s","t"],
    center: true,
    items: 13,
    loop: false,
    dots: false,
    margin: 0,
    startPosition: 6,
    responsive: {
      0: {
      items: 3,
      },
      768: {
      items: 7
      },
      992: {
      items: 13
      }
    }
  });
  
  $('.carousel_calendar_days').on('click', '.date_day', function (e) {
    e.preventDefault();
    
		var tab_id = $(this).attr('data-tab');
		
		$('.section_calendar_simple_events').removeClass('section_calendar_simple_events_hidden');

		$('.date_day').removeClass('current');
		$('.events_tab').removeClass('current');
		$('.events_tab a').attr('tabindex','-1');


		$(this).addClass('current');
		$("#"+tab_id).addClass('current');
		$("#"+tab_id+ " a").attr('tabindex','0');

	})

});

/* End Carousel 2 */



/* Match Height */

$(function() {
    $('.match_height').matchHeight();
});

$(window).resize(function(){
    $('.match_height').matchHeight();
});

$(function() {
    $('.calendar_simple_event').matchHeight();
});

$(window).resize(function(){
    $('.calendar_simple_event').matchHeight();
});

$(function() {
    $('.box_visual_data').matchHeight();
});

$(window).resize(function(){
    $('.box_visual_data').matchHeight();
});

$(function() {
    $('.carousel_agenda_events .item').matchHeight();
});

$(window).resize(function(){
    $('.carousel_agenda_events .item').matchHeight();
});

$(function() {
    $('.section_archive_list .box_text').matchHeight();
});

$(window).resize(function(){
    $('.section_archive_list .box_text').matchHeight();
});

/* End Match Height */



/* Packery */


$(document).ready(function(){

    var cnt = $("img").length;
    $("img").one("load", function() {
        cnt--;
        
        if (cnt === 0)
        {
            $(".grid").packery({
               itemSelector: '.grid-item',
            });
        }

    }).each(function() {
      if(this.complete) $(this).load();
    });

});


$(document).ready(function(){

    var cnt = $("img").length;
    $("img").one("load", function() {
        cnt--;
        
        if (cnt === 0)
        {
            $(".grid-album").packery({
               itemSelector: '.album-item',
            });
        }

    }).each(function() {
      if(this.complete) $(this).load();
    });

});


/* End Packery */




/* Venobox */

$(document).ready(function(){

    $('.lightbox-foto').venobox({
        framewidth: '',        // default: ''
        frameheight: '',       // default: ''
        border: '0px',             // default: '0'
        bgcolor: '#000000',         // default: '#fff'
        titleattr: 'data-title',    // default: 'title'
        numeratio: true,            // default: false
        infinigall: true            // default: false
    });
    
});

/* Funzione per rendere circolare all'interno del lightbox la navigazione tramite Tab */
function setFirstFocus() {
	$(".last-vbox-tabindex").blur();
	$(".vbox-cc-text.link").focus();
}

/* End Venobox */



/* Skiplink */

jQuery(document).ready(function($) {

  $('.skiplink a').on({
    'focus' : function() {
       $('.skiplink').addClass('focused');
     },
     'blur' : function() {
       $('.skiplink').removeClass('focused');
     }
  });

});  

/* End Skiplink */


/* Qtip */

$('.tooltip').each(function() {
  
    $(this).qtip({
        show: {
          solo: true,
          event: 'click mouseover'
        },
          
        hide: {       
          event: 'unfocus',
        },
        
        content: {
            title: {
              text: $(this).attr('title'),
              button: 'Close'
            },
            text: $(this).next('span.tooltip-content')
        },


        position: {
            my: 'bottom center',
            at: 'top center',
            target: 'mouse',
            container: true, // Defaults to $(document.body)
            viewport: $('.main_container'), // Requires Viewport plugin
            adjust: {
                x: 0, y: 0, // Minor x/y adjustments
                mouse: false, // Follow mouse when using target:'mouse'
                resize: true, // Reposition on resize by default
                method: 'shift none' // Requires Viewport plugin
            },
            effect: function(api, pos, viewport) {
                $(this).animate(pos, {
                    duration: 200,
                    queue: false
                });
            }
        },

        
        style: {
            classes: 'qtip-light qtip-shadow qtip-zindex', // No additional classes added to .qtip element
            widget: false, // Not a jQuery UI widget
            width: false, // No set width
            height: false, // No set height
            tip: { // Requires Tips plugin
                corner: true, // Use position.my by default
                mimic: false, // Don't mimic a particular corner
                width: 30, 
                height: 15,
                border: true, // Detect border from tooltip style
                offset: 0 // Do not apply an offset from corner
            }
        }
        
    });
});

/* End Qtip */


/* FitVids */

  $(".embedded-video").fitVids();

/* End FitVids */










var myScroll;

    $(document).ready(function(){
        myScroll = new IScroll('.share_buttons_wrapper', { scrollX: true, scrollY: false, mouseWheel: true, tap: true });

        $('.share_more_container_close').on('click, tap', function() {
            myScroll.scrollTo(0, 0);
        });

        $('.share-reveal-trigger').on('click, tap', function() {
            myScroll.scrollTo(0, 0);
        });

        $('.share-more-trigger').on('click, tap', function() {
            myScroll.scrollTo(0, 0);
        });

    });

 jQuery( document ).ready(function() {

        
        
        positionDocument();

        jQuery(window).scroll(function(){
        	positionDocument();


    });

function positionDocument() {

	if ($('.carousel_album').length) {



				var docHeight = $(document).height();
        var albumHeight = $('.carousel_album').height();
        var headerHeight = 64;
        var owlNavPrev = $('.owl-nav .owl-prev');
        var owlNavNext = $('.owl-nav .owl-next');
        var albumPosition = $('.carousel_album').offset();
        var albumTop = albumPosition.top;
        var albumBottom = albumHeight + albumTop;

        var posNext = owlNavNext.offset();
        var posPrev = owlNavPrev.offset();
        var leftNext = posNext.left;
        var leftPrev = posPrev.left;


        $(window).on('resize', function() {
            var posNext = owlNavNext.offset();
            var posPrev = owlNavPrev.offset();
            var leftNext = posNext.left;
            var leftPrev = posPrev.left;
    
        });


	          var winScroll = jQuery(window).scrollTop() + 120;
            var toPx = 210;
            
            if(winScroll > albumTop && winScroll < albumBottom) {

                owlNavPrev.css('position', 'fixed');
                owlNavNext.css('position', 'fixed');
                owlNavNext.css({'top': toPx + 'px', 'left': leftNext, 'right':'auto'});
                owlNavPrev.css({'top': toPx + 'px', 'left': leftPrev, 'right':'auto'});

            } else if (winScroll > albumTop && winScroll > albumBottom) {

                owlNavPrev.css('position', 'fixed');
                owlNavNext.css('position', 'fixed');
                owlNavNext.css({'top': albumBottom + 'px', 'right': 'auto', 'left': leftNext});
                owlNavPrev.css({'top': albumBottom + 'px', 'left': leftPrev, 'right': 'auto'});

            } else {

                owlNavPrev.css('position', 'absolute');
                owlNavNext.css('position', 'absolute');
                owlNavNext.css({'top': '40px', 'right': '-180px', 'left': 'auto'});
                owlNavPrev.css({'top': '40px', 'left': '-180px', 'right': 'auto'});
            }

    }
        
}

});