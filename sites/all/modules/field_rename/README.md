# CONTENTS OF THIS FILE

* Introduction
* Requirements
* Recommended modules
* Installation
* Configuration
* Maintainers


# INTRODUCTION

The **Field Rename** module allows you to rename a field in the database.

It comes with a submodule named **Field Rename Views**, that allows
you to rename a field in all [**Views**][1].

* For a description of the module, visit the [project page][2].

* To submit bug reports and feature suggestions, or to track changes
  visit the project's [issue tracker][3].

* For documentation, enable [**Advanced Help**][4].


# REQUIREMENTS

This module requires no modules outside of Drupal core.

# RECOMMENDED MODULES

* [**Advanced Help Hint**][5]:  
  Links help text provided by `hook_help` to online help and
  **Advanced Help**.
* [**Advanced Help**][4]:  
  When this module is enabled, display of the project's `README.md`
  will be rendered when you visit
  `help/field_rename/README.md`.
* [**Markdown**][6]:  
  When this module is enabled, display of the project's `README.md`
  will be rendered with the markdown filter.


# INSTALLATION

1. Install as you would normally install a contributed drupal
   module. See: [Installing modules][7] for further information.

2. Enable the **Field Rename** module on the *Modules* list
   page.

3. If you want to rename the fields that re used by views, enable the
   **Field Rename Views** module on the *Modules* list page.

# CONFIGURATION

The module has no menu or modifiable settings. There is no
configuration. When enabled, the module adds a tab on the field list
page that let you rename a single field.

To rename a field, navigate to *Reports » Field list » Rename
fields*. Specify what field to rename, and to what, and press
“Submit”.

If **Field Rename Views** is enabled, a checkbox is added to let you
rename fields used in all views on the system the module is installed.

# MAINTAINERS

Creator: Yonas Yanfa ([fizk][8])  
Current: Gisle Hannemyr ([gisle][9])

Any help with development (patches, reviews, comments) are welcome.

[1]: https://www.drupal.org/project/views
[2]: https://www.drupal.org/project/field_rename
[3]: https://www.drupal.org/project/issues/field_rename
[4]: https://www.drupal.org/project/advanced_help
[5]: https://www.drupal.org/project/advanced_help_hint
[6]: https://www.drupal.org/project/markdown
[7]: https://drupal.org/docs/7/extend/installing-modules
[8]: https://www.drupal.org/u/fizk
[9]: https://www.drupal.org/u/gisle
