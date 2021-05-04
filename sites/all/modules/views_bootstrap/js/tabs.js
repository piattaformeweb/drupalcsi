(function ($) {
  if(window.location.hash) {
    var hash = window.location.hash.substring(1);
    $('.views-bootstrap-tabs a[href="#' + hash + '"]').tab('show');
  }
})(jQuery);
