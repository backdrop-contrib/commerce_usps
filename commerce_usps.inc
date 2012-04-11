<?php
/**
 * @file
 * Admin functions for Commerce Shipping USPS.
 */

/**
 * Form builder function for module settings.
 */
function commerce_usps_settings() {
  $form['origin'] = array(
    '#title' => 'Ship from location',
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['origin']['commerce_usps_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => variable_get('commerce_usps_name', ''),
  );
  $form['origin']['commerce_usps_owner'] = array(
    '#type' => 'textfield',
    '#title' => t('Owner'),
    '#default_value' => variable_get('commerce_usps_owner', ''),
  );
  $form['origin']['commerce_usps_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#default_value' => variable_get('commerce_usps_email', ''),
  );
  $form['origin']['commerce_usps_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => variable_get('commerce_usps_phone', ''),
  );
  $form['origin']['commerce_usps_fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#default_value' => variable_get('commerce_usps_fax', ''),
  );
  $form['origin']['commerce_usps_street1'] = array(
    '#type' => 'textfield',
    '#title' => t('Street #1'),
    '#default_value' => variable_get('commerce_usps_street1', ''),
  );
  $form['origin']['commerce_usps_street2'] = array(
    '#type' => 'textfield',
    '#title' => t('Street #2'),
    '#default_value' => variable_get('commerce_usps_street2', ''),
  );
  $form['origin']['commerce_usps_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => variable_get('commerce_usps_city', ''),
  );
  $form['origin']['commerce_usps_zone'] = array(
    '#type' => 'textfield',
    '#title' => t('State/Province'),
    '#default_value' => variable_get('commerce_usps_zone', ''),
  );
  $form['origin']['commerce_usps_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => variable_get('commerce_usps_postal_code', ''),
  );
  $form['origin']['commerce_usps_country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#default_value' => variable_get('commerce_usps_country', 'US'),
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Shipment Settings',
    '#collapsible' => TRUE,
  );
  $form['settings']['commerce_usps_services'] = array(
    '#type' => 'checkboxes',
    '#title' => t('USPS Services'),
    '#description' => t('Select the USPS services that are available to customers.'),
    '#default_value' => variable_get('commerce_usps_services', array()),
    '#options' => commerce_usps_service_list(),
  );
  $form['settings']['commerce_usps_markup_type'] = array(
    '#type' => 'select',
    '#title' => t('Markup type'),
    '#default_value' => variable_get('commerce_usps_markup_type', 'percentage'),
    '#options' => array(
      'percentage' => t('Percentage (%)'),
      'amount' => t('Amount ($)'),
    ),
  );
  $form['settings']['commerce_usps_markup'] = array(
    '#type' => 'textfield',
    '#title' => t('Shipping rate markup'),
    '#default_value' => variable_get('commerce_usps_markup', '0'),
    '#description' => t('Markup shipping rate quote by a percentage or an amount.'),
  );
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => 'USPS Connection Settings',
  );
  $form['api']['commerce_usps_connection_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Connection Address'),
    '#default_value' => variable_get('commerce_usps_connection_address', 'http://production.shippingapis.com/ShippingAPI.dll'),
  );
  $form['api']['commerce_usps_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('commerce_usps_user', ''),
    '#description' => t('The user name for your USPS account.'),
  );

  return system_settings_form($form);
}