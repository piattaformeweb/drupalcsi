/*!
 * jPushMenu.js
 * 1.1.1
 */

(function($) {
    $.fn.jPushMenu = function(customOptions) {
        var o = $.extend({}, $.fn.jPushMenu.defaultOptions, customOptions);

        $('body').addClass(o.pushBodyClass);

        // Add class to toggler
        $(this).addClass('jPushMenuBtn');

        $(this).click(function(e) {
            e.stopPropagation();

            var target     = '',
            push_direction = '';

            // Determine menu and push direction
            if ($(this).is('.' + o.showLeftClass)) {
                target         = '.cbp-spmenu-left';
                push_direction = 'toright';
            }
            else if ($(this).is('.' + o.showRightClass)) {
                target         = '.cbp-spmenu-right';
                push_direction = 'toleft';
            }
            else if ($(this).is('.' + o.showTopClass)) {
                target = '.cbp-spmenu-top';
            }
            else if ($(this).is('.' + o.showBottomClass)) {
                target = '.cbp-spmenu-bottom';
            }

            if (target == '') {
                return;
            }

            $(this).toggleClass(o.activeClass);
            $(target).toggleClass(o.menuOpenClass);

            if ($(this).is('.' + o.pushBodyClass) && push_direction != '') {
                $('body').toggleClass(o.pushBodyClass + '-' + push_direction);
            }

            // Disable all other buttons
            $('.jPushMenuBtn').not($(this)).toggleClass('disabled');

            return;
        });
        
        
        // AGGIUNTA SOLO PER ON FOCUS
        $('.navgoco a').on('focus',function() {            

            var target     = '',
            push_direction = '';

            // Determine menu and push direction
            if ($('.jPushMenuBtn').is('.' + o.showLeftClass)) {
                target         = '.cbp-spmenu-left';
                push_direction = 'toright';
            }
            else if ($('.jPushMenuBtn').is('.' + o.showRightClass)) {
                target         = '.cbp-spmenu-right';
                push_direction = 'toleft';
            }
            else if ($('.jPushMenuBtn').is('.' + o.showTopClass)) {
                target = '.cbp-spmenu-top';
            }
            else if ($('.jPushMenuBtn').is('.' + o.showBottomClass)) {
                target = '.cbp-spmenu-bottom';
            }

            if (target == '') {
                return;
            }

            $('.jPushMenuBtn').addClass(o.activeClass);
            $(target).addClass(o.menuOpenClass);

            if ($('.jPushMenuBtn').is('.' + o.pushBodyClass) && push_direction != '') {
                $('body').addClass(o.pushBodyClass + '-' + push_direction);
            }

            // Disable all other buttons
            $('.jPushMenuBtn').not($('.jPushMenuBtn')).toggleClass('disabled');

            return;
        });
        // END AGGIUNTA SOLO PER ON FOCUS


        var jPushMenu = {
            close: function (o) {
                $('.jPushMenuBtn,body,.cbp-spmenu')
                    .removeClass('disabled ' + o.activeClass + ' ' + o.menuOpenClass + ' ' + o.pushBodyClass + '-toleft ' + o.pushBodyClass + '-toright');
                $('.navgoco a').attr('tabindex','-1'); // AGGIUNTA RIMUOVE TABINDEX DA NAVGOCO
                $( '.push_container' ).css('position','relative');
                $( '.toggle-menu' ).blur();
            }
        }

        // Close menu on clicking outside menu
        if (o.closeOnClickOutside) {
             $(document).click(function() {
                jPushMenu.close(o);
             });
         }

        // Close menu on clicking menu link
        if (o.closeOnClickLink) {
            $('.cbp-spmenu a').on('click',function() {
                if ( $(this).hasClass('preventclick') ) return;
                jPushMenu.close(o);
            });
        }
        
        // Close menu on clicking menu link
        if (o.closeOnFocus) {
            $('.logo_wrapper a').on('focus',function() {
                jPushMenu.close(o);
            });
        }
        
    };

   /*
    * In case you want to customize class name,
    * do not directly edit here, use function parameter when call jPushMenu.
    */
    $.fn.jPushMenu.defaultOptions = {
        pushBodyClass      : 'push-body',
        showLeftClass      : 'menu-left',
        showRightClass     : 'menu-right',
        showTopClass       : 'menu-top',
        showBottomClass    : 'menu-bottom',
        activeClass        : 'menu-active',
        menuOpenClass      : 'menu-open',
        closeOnClickOutside: true,
        closeOnClickLink   : true,
        closeOnFocus       : true
    };
})(jQuery);