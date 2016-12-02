/* Gallery */

(function($){

    var bgcolor, blocknum, blocktitle, border, core, container, content, dest, 
        evitacontent, evitanext, evitaprev, extraCss, figliall, framewidth, frameheight, 
        infinigall, items, keyNavigationDisabled, margine, numeratio, overlayColor, overlay, 
        prima, title, thisgall, thenext, theprev, type, 
        finH, sonH, nextok, prevok;
        

    var blockshare, description, share;
    var baseurl = window.static_files ? static_files : '';

    $.fn.extend({
        
        venobox: function(options) {

          
          var defaults = {
              framewidth: '',
              frameheight: '',
              border: '0',
              bgcolor: '#fff',
              titleattr: 'title',
              numeratio: false,
              infinigall: false,
              overlayclose: true
          };

          var option = $.extend(defaults, options);

            return this.each(function() {
                  var obj = $(this);

                  
                  if(obj.data('venobox')) {
                    return true;
                  }

                  obj.addClass('vbox-item');
                  obj.data('framewidth', option.framewidth);
                  obj.data('frameheight', option.frameheight);
                  obj.data('border', option.border);
                  obj.data('bgcolor', option.bgcolor);
                  obj.data('numeratio', option.numeratio);
                  obj.data('infinigall', option.infinigall);
                  obj.data('overlayclose', option.overlayclose);
                  obj.data('venobox', true);

                  obj.click(function(e){
                    e.stopPropagation();
                    e.preventDefault();
                    obj = $(this);
                    overlayColor = obj.data('overlay');
                    framewidth = obj.data('framewidth');
                    frameheight = obj.data('frameheight');
                    border = obj.data('border');
                    bgcolor = obj.data('bgcolor');
                    nextok = false;
                    prevok = false;
                    keyNavigationDisabled = false;
                    dest = obj.attr('href');
                    extraCss = obj.data( 'css' ) || "";

                    $('body').addClass('vbox-open');
                    core = '<div class="vbox-overlay ' + extraCss + '" style="background:'+ overlayColor +'"><a href="#" class="first-vbox-tabindex" style="position:absolute; z-index:-1; left:-9999px;" tabindex="1" aria-hidden="true">#</a>' +
          						'<div class="vbox-cc">' +
          						'<img src="' +baseurl+ 'img/cc_by_white.svg" alt="creative commons"><img src="' +baseurl+ 'img/cc_nc_white.svg" alt="creative commons">' +
          						'<img src="' +baseurl+ 'img/cc_sa_white.svg" alt="creative commons">' +
          						'<span class="vbox-cc-text"> Immagini messe a disposizione con <a href="https://creativecommons.org/licenses/by-nc-sa/3.0/it/" title="Diritti" class="vbox-cc-text link" tabindex="2">licenza CC-BY-NC-SA 3.0 IT</a></span>' +
          						'</div>' +
          						'<div class="vbox-container">' +
          						'<div class="vbox-content"></div>' +
          						'<div class="vbox-inner-container">' +
          						'<div class="vbox-title"></div>' +
          						'<div class="vbox-description" style="display:none;"></div>' +
          						'</div><div class="vbox-num">0/0</div>' +
          						'<div class="vbox-text-close">Per chiudere la foto si può utilizzare anche il tasto "ESC" della tastiera</div>' +
          						'<a class="vbox-close" href="#" tabindex="3"></a>' +
          						'<a class="vbox-next" href="#" tabindex="4"></a>' +
          						'<a class="vbox-prev" href="#" tabindex="5"></a>' +
          
          						'<div class="vbox-share share_buttons social-content clearfix" style="display:none;">' +
          						'<a href="#" class="share_buttons_trigger social-trigger" tabindex="6"><span aria-hidden="true" class="icon icon-sharethis"></span></a>' +
          						'<span>Condividi</span>' +
          						'<div class="share_buttons_container clearfix">' +
          						'<a href="#" class="vbox-share-facebook" tabindex="7"><span aria-hidden="true" class="icon icon-facebook"></span></a>' +
          						'<a href="#" class="vbox-share-twitter" tabindex="8"><span aria-hidden="true" class="icon icon-twitter"></span></a>' +
          						'<a href="#" class="vbox-share-googleplus" tabindex="9"><span aria-hidden="true" class="icon icon-google-plus"></span></a>' +
          						'<a class="hidden-lg hidden-md vbox-share-whatsapp" href="#" tabindex="10"><span class="icon icon-whatsapp" aria-hidden="true"></span></a><a href="#" class="last-vbox-tabindex" style="position:absolute; z-index:-1; left:-9999px;" tabindex="11" aria-hidden="true" onfocus="setFirstFocus();">#</a>' +
          						'</div>' +
          						'</div></div>';

                    $('body').append(core);
                    $(".first-vbox-tabindex").focus();
                    

                    overlay = $('.vbox-overlay');
                    container = $('.vbox-container');
                    content = $('.vbox-content');
                    blocknum = $('.vbox-num');
                    blocktitle = $('.vbox-title');
                    blockdescription = $('.vbox-description');
                    blockshare = $('.vbox-share');
                    
                    $('.vbox-share .vbox-share-facebook').click( function(event)
                    {
                      event.preventDefault( );
                      
                      if ( !share )
                        return;
                      
                      window.open( '//www.facebook.com/sharer/sharer.php?u=' + encodeURIComponent(share) );
                    });
                    
                    $('.vbox-share .vbox-share-twitter').click( function(event)
                    {
                      event.preventDefault( );
                      
                      if ( !share )
                        return;
                      
                      window.open( '//twitter.com/home?status=' + encodeURIComponent(share) );
                    });
                    
                    $('.vbox-share .vbox-share-googleplus').click( function(event)
                    {
                      event.preventDefault( );
                      
                      if ( !share )
                        return;
                      
                      window.open( '//plus.google.com/share?url=' + encodeURIComponent(share) );
                    });
                    
                    
                    $('.vbox-share .vbox-share-whatsapp').click( function(event)
        					  {
        						  event.preventDefault( );
        
        						  if ( !share )
        							  return;
        							  
        						  document.location.href ='whatsapp://send?text=' + description + ' ' + share ;
        					  });
                    

                    //$(blocktitle).wrap('<div class="vbox-inner-container"></div>');

                    content.html('');
                    content.css('opacity', '0');

                    checknav();

                    

                    // fade in overlay
                    overlay.animate({opacity:1}, 250, function(){
    
                      if(obj.data('type') == 'iframe'){
                        loadIframe();
                      }else if (obj.data('type') == 'inline'){
                        loadInline();
                      }else if (obj.data('type') == 'ajax'){
                        loadAjax();
                      }else if (obj.data('type') == 'vimeo'){
                        loadVimeo();
                      }else if (obj.data('type') == 'youtube'){
                        loadYoutube();
                      } else {
                        content.html('<img src="'+dest+'">');
                        preloadFirst();
                      }
                    });

                    /* -------- CHECK NEXT / PREV -------- */
                    function checknav(){

                      thisgall = obj.data('gall');
                      numeratio = obj.data('numeratio');
                      infinigall = obj.data('infinigall');

                      items = $('.vbox-item[data-gall="' + thisgall + '"]');
                      
                      
                      /* -------- vbox-next vbox-prev remove if only 1 item -------- */                 
                      // if (items.length <= 1){
          						// 	jQuery('.vbox-next').remove();
          						//	jQuery('.vbox-prev').remove();
          						// }	
          						/* -------- end vbox-next vbox-prev remove if only 1 item -------- */
          						

                      if(items.length > 0 && numeratio === true){
                        blocknum.html(items.index(obj)+1 + ' / ' + items.length);
                        blocknum.show();
                      }else{
                        blocknum.hide();
                      }

                      thenext = items.eq( items.index(obj) + 1 );
                      theprev = items.eq( items.index(obj) - 1 );

                      if(obj.attr(option.titleattr)){
                        title = obj.attr(option.titleattr);
                        blocktitle.show();
                      }else{
                        title = '';
                        blocktitle.hide();
                        
                      }
                      

                      description = obj.data('description') ? obj.data('description') : null;
                      share       = obj.data('share') ? obj.data('share') : null;
                    
                    
                      

                      if (items.length > 0 && infinigall === true) {

                        nextok = true;
                        prevok = true;

                        if(thenext.length < 1 ){
                          thenext = items.eq(0);
                        }
                        if(items.index(obj) < 1 ){
                          theprev = items.eq( items.index(items.length) );
                        }

                      } else {

                        if(thenext.length > 0 ){
                          $('.vbox-next').css('display', 'block');
                          nextok = true;
                        }else{
                          $('.vbox-next').css('display', 'none');
                          nextok = false;
                        }
                        if(items.index(obj) > 0 ){
                          $('.vbox-prev').css('display', 'block');
                          prevok = true;
                        }else{
                          $('.vbox-prev').css('display', 'none');
                          prevok = false;
                        }
                      }
                    }
                    
                     /* -------- NAVIGATION CODE -------- */
                    var gallnav = {
                      
                      prev: function() {

                        if (keyNavigationDisabled) {
                          return;
                        } else {
                          keyNavigationDisabled = true;
                        }

                        overlayColor = theprev.data('overlay');

                        framewidth = theprev.data('framewidth');
                        frameheight = theprev.data('frameheight');
                        border = theprev.data('border');
                        bgcolor = theprev.data('bgcolor');

                        dest = theprev.attr('href');

                        if(theprev.attr(option.titleattr)){
                          title = theprev.attr(option.titleattr);
                        }else{
                          title = '';
                        }


                        description = theprev.data('description') ? theprev.data('description') : null;
                        share       = theprev.data('share') ? theprev.data('share') : null;
                    
                        
                        
                        
                        
                        

                        if (overlayColor === undefined ) {
                          overlayColor = "";
                        }

                        content.animate({ opacity:0}, 500, function(){
                          
                          overlay.css('background',overlayColor);

                          if (theprev.data('type') == 'iframe') {
                            loadIframe();
                          } else if (theprev.data('type') == 'inline'){
                            loadInline();
                          } else if (theprev.data('type') == 'ajax'){
                            loadAjax();
                          } else if (theprev.data('type') == 'youtube'){
                            loadYoutube();
                          } else if (theprev.data('type') == 'vimeo'){
                            loadVimeo();
                          }else{
                            content.html('<img src="'+dest+'">');
                            preloadFirst();
                          }
                          obj = theprev;
                          checknav();
                          keyNavigationDisabled = false;
                        });

                      },

                      next: function() {
                        
                        if (keyNavigationDisabled) {
                          return;
                        } else {
                          keyNavigationDisabled = true;
                        }

                        overlayColor = thenext.data('overlay');

                        framewidth = thenext.data('framewidth');
                        frameheight = thenext.data('frameheight');
                        border = thenext.data('border');
                        bgcolor = thenext.data('bgcolor');
                        dest = thenext.attr('href');

                        if(thenext.attr(option.titleattr)){
                          title = thenext.attr(option.titleattr);
                        }else{
                          title = '';
                        }
                        

                        description = thenext.data('description') ? thenext.data('description') : null;
                        share       = thenext.data('share') ? thenext.data('share') : null;
                        
                        

                        if (overlayColor === undefined ) {
                          overlayColor = "";
                        }

                        content.animate({ opacity:0}, 500, function(){
                          
                          overlay.css('background',overlayColor);

                          if (thenext.data('type') == 'iframe') {
                            loadIframe();
                          } else if (thenext.data('type') == 'inline'){
                            loadInline();
                          } else if (thenext.data('type') == 'ajax'){
                            loadAjax();
                          } else if (thenext.data('type') == 'youtube'){
                            loadYoutube();
                          } else if (thenext.data('type') == 'vimeo'){
                            loadVimeo();
                          }else{
                            content.html('<img src="'+dest+'">');
                            preloadFirst();
                          }
                          obj = thenext;
                          checknav();
                          keyNavigationDisabled = false;
                        });

                      }

                    };
                    
                    
                    

                    /* -------- NAVIGATE WITH ARROW KEYS -------- */
                    $('body').keydown(function(e) {

                      if(e.keyCode == 37 && prevok == true) { // left
                        gallnav.prev();
                      }

                      if(e.keyCode == 39 && nextok == true) { // right
                        gallnav.next();
                      }

                    });

                    /* -------- PREVGALL -------- */
                    $('.vbox-prev').click(function(e){
	                    e.preventDefault();
                      gallnav.prev();
                    });
                    
                    
                    
                    /* -------- NEXTGALL -------- */
                    $('.vbox-next').click(function(e){
	                    e.preventDefault();
                      gallnav.next();
                    });
                    
                    
                    /* SOCIAL TRIGGER */
                    
                    $('.social-trigger').click(function(e) {
                      e.preventDefault();
                      $(this).parent('.social-content').toggleClass('active');
                    });
                    
                    
                    /* -------- ESCAPE HANDLER -------- */
                    function escapeHandler(e) {
                      if(e.keyCode === 27) {
                        closeVbox();
                      }
                    }

                    /* -------- CLOSE VBOX -------- */

                    function closeVbox(){
                      
                      $('body').removeClass('vbox-open');
                      $('body').unbind('keydown', escapeHandler);

                        overlay.animate({opacity:0}, 500, function(){
                          overlay.remove();
                          keyNavigationDisabled = false;
                          obj.focus();
                        });
                    }

                    /* -------- CLOSE CLICK -------- */
                    var closeclickclass = '.vbox-close';
                    if(!obj.data('overlayclose')){
                        closeclickclass = '.vbox-close';    // close only on X
                    }

                    $(closeclickclass).click(function(e){
	                    e.preventDefault();
                      evitacontent = '.figlio';
                      evitaprev = '.vbox-prev';
                      evitanext = '.vbox-next';
                      figliall = '.figlio *';
                      if(!$(e.target).is(evitacontent) && !$(e.target).is(evitanext) && !$(e.target).is(evitaprev)&& !$(e.target).is(figliall)){
                        closeVbox();
                      }
                    });
                    $('body').keydown(escapeHandler);
                    return false;
                  });
            });
        }
    });

    /* -------- LOAD AJAX -------- */
    function loadAjax(){
      $.ajax({
      url: dest,
      cache: false
      }).done(function( msg ) {
          content.html('<div class="vbox-inline">'+ msg +'</div>');
          updateoverlay(true);

      }).fail(function() {
          content.html('<div class="vbox-inline"><p>Error retrieving contents, please retry</div>');
          updateoverlay(true);
      })
    }

    /* -------- LOAD IFRAME -------- */
    function loadIframe(){
      content.html('<iframe class="venoframe" src="'+dest+'"></iframe>');
    //  $('.venoframe').load(function(){ // valid only for iFrames in same domain
      updateoverlay();
    //  });
    }

    /* -------- LOAD VIMEO -------- */
    function loadVimeo(){
      var pezzi = dest.split('/');
      var videoid = pezzi[pezzi.length-1];
      content.html('<iframe class="venoframe" src="//player.vimeo.com/video/'+videoid+'"></iframe>');
      updateoverlay();
    }

    /* -------- LOAD YOUTUBE -------- */
    function loadYoutube(){
      var pezzi = dest.split('/');
      var videoid = pezzi[pezzi.length-1];
      content.html('<iframe class="venoframe" allowfullscreen src="//www.youtube.com/embed/'+videoid+'"></iframe>');
      updateoverlay();
    }

    /* -------- LOAD INLINE -------- */
    function loadInline(){
      content.html('<div class="vbox-inline">'+$(dest).html()+'</div>');
      updateoverlay();
    }

    /* -------- PRELOAD IMAGE -------- */
    function preloadFirst(){
        prima = $('.vbox-content').find('img');
        prima.one('load', function() {
          updateoverlay();
        }).each(function() {
          if(this.complete) $(this).load();
        });
    }

    /* -------- CENTER ON LOAD -------- */
    function updateoverlay(){

      blocktitle.html(title);
      


      if ( description )
      {
        blockdescription
          .html( description )
          .fadeIn( );
      }
      
      else
        blockdescription.fadeOut( );
      
      

      if ( share )
        blockshare.fadeIn( );
      else
        blockshare.fadeOut( );
      
      
      
      
      content.find(">:first-child").addClass('figlio');
      $('.figlio').css('width', framewidth).css('height', frameheight).css('padding', border).css('background', bgcolor);

      
      content.animate({
        'opacity': '1'
      },'slow');
    }

    

})(jQuery);