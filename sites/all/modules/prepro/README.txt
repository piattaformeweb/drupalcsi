INTRODUCTION
------------
This module currently does the following:

 * Picks all files from the drupal stylesheets/javascript list and offers
   to preprocess them (based on filetype) to registered preprocessors
   (such as Sassy or Coffeescript-PHP).
 * Caches the files on production servers, with the option to recompile
   on mtime change.
 * Wraps the settings stuff neatly into one page.
 * Makes it easy to move between multiple compilers if required
   (eg Sassy and a Ruby parser link for SASS/SCSS).

IMPLEMENTING MODULES
--------------------
* Sassy: SASS/SCSS => CSS
* Coffeescript-PHP: Coffeescript => Javascript

INSTALLATION
------------
* Install as you would normally install a contributed drupal module. See:
  https://drupal.org/documentation/install/modules-themes/modules-7
  for further information.
