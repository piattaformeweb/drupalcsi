/**
 * Attach handlers to toggle the twitter message field and inform the number
 * of characters remaining to achieve the max length
 */
(function ($) {
  Drupal.behaviors.twitter_post = {
    attach: function (context, settings) {
      $(".twitter-post-message", context).keyup(function() {
        var charsLeft = (140 - $(this).val().length);
        var descDiv = $(this).next();
        var character = "<strong>1</strong> character remaining";
        var characters = "<strong>@count</strong> characters remaining";
        $(descDiv).html(Drupal.formatPlural(charsLeft, character, characters));
        if (charsLeft < 0) {
          $(descDiv).css('color', 'red');
        } else {
          $(descDiv).css('color', '');
        }
      });
    }
  };
}(jQuery));
