DESCRIPTION
-----------

This is the porting to Drupal of Divas Cookies jquery script by Coding Diva

Divas Cookies is:

"EU Cookie Law Policy Banner for jQuery, WordPress and Prestashop.

The quickest and most elegant solution to add a banner compliant with EU Cookie 
Policy. Block scripts with simple helpers. Easily and fully customizable to get 
the look & feel of any website.

The only EU Cookie Policy banner plugin natively ready for translations!"

Full features in http://www.codingdivas.net/divascookies/index.php

REQUIREMENTS
------------

 * Jquery Update
 * Variable
 * Variable translation
 * Libraries API

INSTALLATION
------------

 1. INSTALL THE EXTERNAL LIBRARY

    - Download the library from 
      http://www.codingdivas.net/divascookies/index.php#downloads
    
    - Extract the files
      
      If the file you downloaded is an archive, i.e. its file extension is .zip 
      or .tar.gz, you will need to extract it first.
      
      After extracting the file, you should see multiple files or a single 
      folder with the library's name.

    - Upload the library
      
      First you need to check if there is a libraries directory in one of three 
      suitable spots. These are:
        
        * sites/all/libraries/divascookies directory or
        * profiles/[yourprofilename]/libraries/divascookies or
        * sites/example.com/libraries/divascookies if you have a multi-site 
          installation
          
      If not, create one. Upload the library directory/files into the directory 
      you have just created.

 2. CREATE DIRECTORY

    Create a new directory "divascookies" in the sites/all/modules directory 
    and place the entire contents of this divascookies folder in it.

 3. ENABLE THE MODULE

    Enable the module on the Modules admin page.

 4. ACCESS PERMISSION

    Grant the access at the Access control page:
      People > Permissions.

 5. CONFIGURE DIVAS COOKIES
 
    

CONFIGURATION
-------------

 1. MULTILINGUAL SETTINGS
 
    Go to admin/config/regional/i18n/variable and under "Divas Cookies settings" 
    select every viariables if you need multilingual.
    
 2. DIVAS COOKIES
 
    Go to admin/config/system/divascookies to fill the form for your needs.
    
 3. COOKIES FILTER
 
    To block scripts to disable the third party cookies (AddThis, Google 
    Analytics, etc) simply you  can enable the extras modules or you build your 
    own using the divascookies API.
