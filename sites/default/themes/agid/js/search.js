/**
 * Created by 1884 on 06/04/2017.
 */


// Funzione per motore di riecerca mobile.
(function ($) {

    $("#sb-search form div.nav_search").replaceWith($("#sb-search form div.nav_search").html());
    $("#sb-search form > div").replaceWith($("#sb-search form > div").html());
    $("#sb-search form input[type='text']").removeClass().addClass("sb-search-input");
    $("#sb-search form input[type='submit']").removeClass().addClass("sb-search-submit").attr("tabindex", "-1").val("").after('<span class="sb-icon-search"></span>');

}(jQuery));