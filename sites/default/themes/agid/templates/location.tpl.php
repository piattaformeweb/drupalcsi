<?php
/**
 * CMS Drupal 7 per i siti web dei Comuni
 * Copyright (C)  2016 CSI-Piemonte - C.so Unione Sovietica 216, 10134, Turin, Italy.– piattaformeweb@csi.it
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by  the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program.  If not, see http://www.gnu.org/licenses/
 */

/**
 * @file
 * Template for displaying single location.
 */
?>
<div class="location vcard" itemscope itemtype="http://schema.org/PostalAddress">
  <div class="adr">
    <?php if (!empty($name)): ?>
      <span class="fn" itemprop="name"><strong><?php print $name; ?></strong></span>
    <?php endif; ?>
    <?php if (!empty($street) || !empty($additional)): ?>
      <div class="street-address">
        <span itemprop="streetAddress"><?php print $street; ?></span>
        <?php if (!empty($additional)): ?>
          <span class="additional" itemprop="streetAddress">
            <?php print ' ' . $additional; ?>
          </span>
        <?php endif; ?>
	&mdash;
    <?php if (!empty($postal_code)): ?>
      <span class="postal-code" itemprop="postalCode"><?php print $postal_code; ?></span>
    <?php endif; ?>
    <?php if (!empty($city)): ?>
      <span class="locality" itemprop="addressLocality">
      <?php print $city; ?>
      </span>
      <?php if (!empty($province)) : ?>
        <?php print ', '; ?>
      <?php endif; ?>
    <?php endif; ?>
    <?php if (!empty($province)): ?>
      <span class="region" itemprop="addressRegion"><?php print $province_print; ?></span>
    <?php endif; ?>
		
		
      </div>
    <?php endif; ?>

    <?php if (!empty($country_name)): ?>
      <div class="country-name" itemprop="addressCountry"><?php print $country_name; ?></div>
    <?php endif; ?>
    <?php if (!empty($email)): ?>
      <div class="email">
        <abbr class="type" title="email"><?php print t("Email address"); ?>:</abbr>
        <span><a href="mailto:<?php print $email; ?>" itemprop="email"><?php print $email; ?></a></span>
      </div>
    <?php endif; ?>
    <?php if (!empty($phone)): ?>
      <div class="tel">
        <abbr class="type" title="voice"><?php print t("Phone"); ?>:</abbr>
        <span class="value" itemprop="telephone"><?php print $phone; ?></span>
      </div>
    <?php endif; ?>
    <?php if (!empty($fax)): ?>
      <div class="tel">
        <abbr class="type" title="fax"><?php print t("Fax"); ?>:</abbr>
        <span itemprop="faxNumber"><?php print $fax; ?></span>
      </div>
    <?php endif; ?>
    <?php
    // "Geo" microformat, see http://microformats.org/wiki/geo.
    ?>
    <?php if (isset($latitude) && isset($longitude)): ?>
      <?php
      // Assume that 0, 0 is invalid.
      ?>
      <?php if ($latitude != 0 || $longitude != 0): ?>
        <span class="geo"><abbr class="latitude" title="<?php print $latitude; ?>"><?php print $latitude_dms; ?></abbr>, <abbr
            class="longitude" title="<?php print $longitude; ?>"><?php print $longitude_dms; ?></abbr></span>
      <?php endif; ?>
    <?php endif; ?>
  </div>
  <?php if (!empty($map_link)): ?>
    <div class="map-link">
      <?php // print $map_link; ?>
    </div>
  <?php endif; ?>
</div>
<?php if (!empty($province_name) || (!empty($country))): ?>
  <div class="location-hidden">
        <?php if (!empty($province_name)): ?><?php print $province_name; ?><?php endif; ?>
        <?php if (!empty($country)): ?><?php print strtoupper($country); ?><?php endif; ?>
      </div>
<?php endif; ?>
