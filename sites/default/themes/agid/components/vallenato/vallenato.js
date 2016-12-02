/* Accordion */

jQuery(document).ready(function() {
	//Add Inactive Class To All Accordion Headers
    jQuery('.accordion-header').toggleClass('inactive-header');
	
	// The Accordion Effect
    jQuery('.accordion-header').click(function (e) {
    e.preventDefault();
    
		if(jQuery(this).is('.inactive-header')) {
            jQuery('.active-header').toggleClass('active-header').toggleClass('inactive-header').next().slideToggle("fast").toggleClass('open-content');
            jQuery(this).toggleClass('active-header').toggleClass('inactive-header');
            jQuery(this).next().slideToggle("fast").toggleClass('open-content');
		}
		
		else {
            jQuery(this).toggleClass('active-header').toggleClass('inactive-header');
            jQuery(this).next().slideToggle("fast").toggleClass('open-content');
		}
		
	});
	
	return false;
});




jQuery(document).ready(function() {
	//Add Inactive Class To All Accordion Headers
    jQuery('.accordion-header').toggleClass('inactive-header');
	
	// The Accordion Effect
    jQuery('.accordion-opener').click(function (e) {

    e.preventDefault();
    
		if(jQuery(this).parent().is('.inactive-header')) {
            jQuery('.active-header').toggleClass('active-header').toggleClass('inactive-header').next().slideToggle("fast").toggleClass('open-content');
			jQuery(this).parent().toggleClass('active-header').toggleClass('inactive-header');
			jQuery(this).parent().next().slideToggle("fast").toggleClass('open-content');
		}
		
		else {
			jQuery(this).parent().toggleClass('active-header').toggleClass('inactive-header');
			jQuery(this).parent().next().slideToggle("fast").toggleClass('open-content');
		}
		
	});
	
	return false;
});