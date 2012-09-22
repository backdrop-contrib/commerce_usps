<?php

/**
 * @file
 * Admin functions for Commerce USPS.
 */

/**
 * Form builder function for module settings.
 *
 * @return string
 *   Drupal form for USPS settings
 */
function commerce_usps_settings_form() {
  $form['origin'] = array(
    '#title' => t('Ship from location'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $form['origin']['commerce_usps_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => variable_get('commerce_usps_postal_code', ''),
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Shipment Settings'),
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
    '#title' => t('USPS Connection Settings'),
    '#collapsed' => variable_get('commerce_usps_user', FALSE),
    '#collapsible' => TRUE,
  );
  $form['api']['commerce_usps_connection_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Connection Address'),
    '#default_value' => variable_get('commerce_usps_connection_address', 'http://production.shippingapis.com/ShippingAPI.dll'),
    '#required' => TRUE,
  );
  $form['api']['commerce_usps_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('commerce_usps_user', ''),
    '#description' => t('The user name for your USPS account.'),
    '#required' => TRUE,
  );
  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 40,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save USPS settings'),
  );
  return $form;
}

/**
 * Validate handler: valiates the usps settings form.
 */
function commerce_usps_settings_form_validate($form, $form_state) {
  // Check for a valid postal code
  $postal_code = $form_state['values']['commerce_usps_postal_code'];
  if (!is_numeric($postal_code) || strlen($postal_code) != 5) {
    form_set_error('commerce_usps_postal_code', t('You must enter a 5 digit zip code'));
  }
  // Disallow USPS testing urls.
  $connection_address = $form_state['values']['commerce_usps_connection_address'];
  if (preg_match('/testing/', drupal_strtolower($connection_address))) {
    form_set_error('commerce_usps_connection_address', t('Only production urls will work with this module. Please have USPS exdend production access to your Webtools account by calling or emailing them.'));
  }
}

/**
 * Submit handler: saves the usps settings.
 */
function commerce_usps_settings_form_submit($form, &$form_state) {
  $fields = array(
    'commerce_usps_postal_code',
    'commerce_usps_services',
    'commerce_usps_markup_type',
    'commerce_usps_markup',
    'commerce_usps_connection_address',
    'commerce_usps_user',
  );
  $services = variable_get('commerce_usps_services', NULL);
  foreach ($fields as $key) {
    if (array_key_exists($key, $form_state['values'])) {
      $value = $form_state['values'][$key];
      variable_set($key, $value);
    }
  }
  // If the selected services have changed then rebuild caches.
  if ($services !== $form_state['values']['commerce_usps_services']) {
    commerce_shipping_services_reset();
    entity_defaults_rebuild();
    rules_clear_cache(TRUE);
    menu_rebuild();
  }
  drupal_set_message(t('The USPS configuration options have been saved.'));
}