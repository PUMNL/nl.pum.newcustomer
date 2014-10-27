<?php

$customer_data = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Customers_Data'));
$model = civicrm_api3('CustomField', 'getvalue', array('name' => 'What_is_the_operational_model_of_the_organisation', 'return' => 'column_name', 'custom_group_id' => $customer_data['id']));
$services = civicrm_api3('CustomField', 'getvalue', array('name' => 'Products_and_or_Services_offered', 'return' => 'column_name', 'custom_group_id' => $customer_data['id']));
$when_where_sold = civicrm_api3('CustomField', 'getvalue', array('name' => 'Where_and_how_are_the_products_of_services_sold', 'return' => 'column_name', 'custom_group_id' => $customer_data['id']));

$aware = civicrm_api3('CustomField', 'getvalue', array('name' => 'Is_your_company_aware_of_any_business_support_provided_by_the_fo', 'return' => 'column_name', 'custom_group_id' => $customer_data['id']));
$worked_with = civicrm_api3('CustomField', 'getvalue', array('name' => 'Has_your_company_ever_worked_with_any_of_these_organisations_che', 'return' => 'column_name', 'custom_group_id' => $customer_data['id']));
$activily_make = civicrm_api3('CustomField', 'getvalue', array('name' => 'Does_your_company_actively_make_use_of_the_business_support_prov', 'return' => 'column_name', 'custom_group_id' => $customer_data['id']));
$member_of = civicrm_api3('CustomField', 'getvalue', array('name' => 'Is_your_company_member_of_any_of_the_above_mentrioned_type_of_su', 'return' => 'column_name', 'custom_group_id' => $customer_data['id']));

$postal_loc_type_id = civicrm_api3('LocationType', 'getvalue', array('return' => 'id', 'name' => 'Postaladdress'));

$view = new view();
$view->name = 'customer_info';
$view->description = 'This view is used to show customer info in drupal. ';
$view->tag = 'newcustomer';
$view->base_table = 'civicrm_contact';
$view->human_name = 'Customer info';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Customer';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = newcustomer_get_role_ids(array( 'Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '1';
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['style_options']['columns'] = '1';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: Global: Fieldset */
$fields['fieldset']['id'] = 'fieldset';
$fields['fieldset']['table'] = 'views';
$fields['fieldset']['field'] = 'fieldset';
$fields['fieldset']['label'] = 'General info';
$fields['fieldset']['children'] = array(
  0 => 'display_name',
  1 => 'edit_link_1',
  2 => 'email',
  3 => 'phone',
  4 => 'view_2',
  5 => 'fieldset_1',
  6 => 'fieldset_2',
);
$fields['fieldset']['fieldset']['type'] = 'div';
/* Field: CiviCRM Contacts: Contact ID */
$fields['id']['id'] = 'id';
$fields['id']['table'] = 'civicrm_contact';
$fields['id']['field'] = 'id';
$fields['id']['label'] = '';
$fields['id']['exclude'] = TRUE;
$fields['id']['element_label_colon'] = FALSE;
$fields['id']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$fields['display_name']['id'] = 'display_name';
$fields['display_name']['table'] = 'civicrm_contact';
$fields['display_name']['field'] = 'display_name';
$fields['display_name']['label'] = '';
$fields['display_name']['element_type'] = 'h1';
$fields['display_name']['element_label_colon'] = FALSE;
$fields['display_name']['link_to_civicrm_contact'] = 0;
/* Field: Global: Custom text */
$fields['edit_link_1']['id'] = 'edit_link_1';
$fields['edit_link_1']['table'] = 'views';
$fields['edit_link_1']['field'] = 'nothing';
$fields['edit_link_1']['label'] = '';
$fields['edit_link_1']['alter']['text'] = 'Edit organisation profile';
$fields['edit_link_1']['alter']['make_link'] = TRUE;
$fields['edit_link_1']['alter']['path'] = 'customer/profile/?cid1=[id]';
$fields['edit_link_1']['alter']['absolute'] = TRUE;
$fields['edit_link_1']['element_label_colon'] = FALSE;
/* Field: CiviCRM Email: Email Address */
$fields['email']['id'] = 'email';
$fields['email']['table'] = 'civicrm_email';
$fields['email']['field'] = 'email';
$fields['email']['location_type'] = '0';
$fields['email']['location_op'] = '0';
$fields['email']['is_primary'] = 0;
/* Field: CiviCRM Phone Details: Phone Number */
$fields['phone']['id'] = 'phone';
$fields['phone']['table'] = 'civicrm_phone';
$fields['phone']['field'] = 'phone';
$fields['phone']['location_type'] = '0';
$fields['phone']['location_op'] = '0';
$fields['phone']['is_primary'] = 0;
$fields['phone']['phone_type'] = '0';
/* Field: Global: View */
$fields['view_2']['id'] = 'view_2';
$fields['view_2']['table'] = 'views';
$fields['view_2']['field'] = 'view';
$fields['view_2']['label'] = '';
$fields['view_2']['element_label_colon'] = FALSE;
$fields['view_2']['hide_empty'] = TRUE;
$fields['view_2']['view'] = 'contacts_websites';
$fields['view_2']['arguments'] = '!1';
/* Field: Global: Fieldset */
$fields['fieldset_1']['id'] = 'fieldset_1';
$fields['fieldset_1']['table'] = 'views';
$fields['fieldset_1']['field'] = 'fieldset';
$fields['fieldset_1']['label'] = 'Primary address';
$fields['fieldset_1']['children'] = array(
  0 => 'street_address',
  1 => 'city',
  2 => 'postal_code',
  3 => 'state_province',
  4 => 'country',
);
/* Field: CiviCRM Address: Full Street Address */
$fields['street_address']['id'] = 'street_address';
$fields['street_address']['table'] = 'civicrm_address';
$fields['street_address']['field'] = 'street_address';
$fields['street_address']['label'] = '';
$fields['street_address']['element_label_colon'] = FALSE;
$fields['street_address']['location_type'] = '0';
$fields['street_address']['location_op'] = '0';
$fields['street_address']['is_primary'] = 1;
$fields['street_address']['is_billing'] = 0;
/* Field: CiviCRM Address: City / Suburb */
$fields['city']['id'] = 'city';
$fields['city']['table'] = 'civicrm_address';
$fields['city']['field'] = 'city';
$fields['city']['label'] = '';
$fields['city']['element_label_colon'] = FALSE;
$fields['city']['location_type'] = '0';
$fields['city']['location_op'] = '0';
$fields['city']['is_primary'] = 1;
$fields['city']['is_billing'] = 0;
/* Field: CiviCRM Address: ZIP / Postal Code */
$fields['postal_code']['id'] = 'postal_code';
$fields['postal_code']['table'] = 'civicrm_address';
$fields['postal_code']['field'] = 'postal_code';
$fields['postal_code']['label'] = '';
$fields['postal_code']['element_label_colon'] = FALSE;
$fields['postal_code']['location_type'] = '0';
$fields['postal_code']['location_op'] = '0';
$fields['postal_code']['is_primary'] = 1;
$fields['postal_code']['is_billing'] = 0;
/* Field: CiviCRM Address: State / Province */
$fields['state_province']['id'] = 'state_province';
$fields['state_province']['table'] = 'civicrm_address';
$fields['state_province']['field'] = 'state_province';
$fields['state_province']['label'] = '';
$fields['state_province']['element_label_colon'] = FALSE;
$fields['state_province']['location_type'] = '0';
$fields['state_province']['location_op'] = '0';
$fields['state_province']['is_primary'] = 1;
$fields['state_province']['is_billing'] = 0;
$fields['state_province']['prov_display'] = '2';
/* Field: CiviCRM Address: Country */
$fields['country']['id'] = 'country';
$fields['country']['table'] = 'civicrm_address';
$fields['country']['field'] = 'country';
$fields['country']['label'] = '';
$fields['country']['element_label_colon'] = FALSE;
$fields['country']['location_type'] = '0';
$fields['country']['location_op'] = '0';
$fields['country']['is_primary'] = 1;
$fields['country']['is_billing'] = 0;
/* Field: Global: Fieldset */
$fields['fieldset_2']['id'] = 'fieldset_2';
$fields['fieldset_2']['table'] = 'views';
$fields['fieldset_2']['field'] = 'fieldset';
$fields['fieldset_2']['label'] = 'Postal address';
$fields['fieldset_2']['hide_empty'] = TRUE;
$fields['fieldset_2']['children'] = array(
  0 => 'street_address_1',
  1 => 'city_1',
  2 => 'postal_code_1',
  3 => 'state_province_1',
  4 => 'country_1',
);
/* Field: CiviCRM Address: Full Street Address */
$fields['street_address_1']['id'] = 'street_address_1';
$fields['street_address_1']['table'] = 'civicrm_address';
$fields['street_address_1']['field'] = 'street_address';
$fields['street_address_1']['label'] = '';
$fields['street_address_1']['element_label_colon'] = FALSE;
$fields['street_address_1']['hide_empty'] = TRUE;
$fields['street_address_1']['location_type'] = $postal_loc_type_id;
$fields['street_address_1']['location_op'] = '0';
$fields['street_address_1']['is_primary'] = 0;
$fields['street_address_1']['is_billing'] = 0;
/* Field: CiviCRM Address: City / Suburb */
$fields['city_1']['id'] = 'city_1';
$fields['city_1']['table'] = 'civicrm_address';
$fields['city_1']['field'] = 'city';
$fields['city_1']['label'] = '';
$fields['city_1']['element_label_colon'] = FALSE;
$fields['city_1']['hide_empty'] = TRUE;
$fields['city_1']['location_type'] = $postal_loc_type_id;
$fields['city_1']['location_op'] = '0';
$fields['city_1']['is_primary'] = 0;
$fields['city_1']['is_billing'] = 0;
/* Field: CiviCRM Address: ZIP / Postal Code */
$fields['postal_code_1']['id'] = 'postal_code_1';
$fields['postal_code_1']['table'] = 'civicrm_address';
$fields['postal_code_1']['field'] = 'postal_code';
$fields['postal_code_1']['label'] = '';
$fields['postal_code_1']['element_label_colon'] = FALSE;
$fields['postal_code_1']['hide_empty'] = TRUE;
$fields['postal_code_1']['location_type'] = $postal_loc_type_id;
$fields['postal_code_1']['location_op'] = '0';
$fields['postal_code_1']['is_primary'] = 0;
$fields['postal_code_1']['is_billing'] = 0;
/* Field: CiviCRM Address: State / Province */
$fields['state_province_1']['id'] = 'state_province_1';
$fields['state_province_1']['table'] = 'civicrm_address';
$fields['state_province_1']['field'] = 'state_province';
$fields['state_province_1']['label'] = '';
$fields['state_province_1']['element_label_colon'] = FALSE;
$fields['state_province_1']['hide_empty'] = TRUE;
$fields['state_province_1']['location_type'] = $postal_loc_type_id;
$fields['state_province_1']['location_op'] = '0';
$fields['state_province_1']['is_primary'] = 0;
$fields['state_province_1']['is_billing'] = 0;
$fields['state_province_1']['prov_display'] = '2';
/* Field: CiviCRM Address: Country */
$fields['country_1']['id'] = 'country_1';
$fields['country_1']['table'] = 'civicrm_address';
$fields['country_1']['field'] = 'country';
$fields['country_1']['label'] = '';
$fields['country_1']['element_label_colon'] = FALSE;
$fields['country_1']['hide_empty'] = TRUE;
$fields['country_1']['location_type'] = $postal_loc_type_id;
$fields['country_1']['location_op'] = '0';
$fields['country_1']['is_primary'] = 0;
$fields['country_1']['is_billing'] = 0;
$fields['country_1']['country_display'] = '2';
/* Field: Global: Fieldset */
$fields['fieldset_3']['id'] = 'fieldset_3';
$fields['fieldset_3']['table'] = 'views';
$fields['fieldset_3']['field'] = 'fieldset';
$fields['fieldset_3']['label'] = 'Main product/services';
$fields['fieldset_3']['children'] = array(
  0 => 'what_is_the_operational_model_of_513',
  1 => 'products_and_or_services_offered_86',
  2 => 'where_and_how_are_the_products_o_89',
);
/* Field: CiviCRM Custom: Customer Data: What is the operational model of the organisation */
$fields['what_is_the_operational_model_of_513']['id'] = 'what_is_the_operational_model_of_513';
$fields['what_is_the_operational_model_of_513']['table'] = $customer_data['table_name'];
$fields['what_is_the_operational_model_of_513']['field'] = $model;
$fields['what_is_the_operational_model_of_513']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Products and/or Services offered */
$fields['products_and_or_services_offered_86']['id'] = 'products_and_or_services_offered_86';
$fields['products_and_or_services_offered_86']['table'] = $customer_data['table_name'];
$fields['products_and_or_services_offered_86']['field'] = $services;
$fields['products_and_or_services_offered_86']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Where and how are the products or services sold */
$fields['where_and_how_are_the_products_o_89']['id'] = 'where_and_how_are_the_products_o_89';
$fields['where_and_how_are_the_products_o_89']['table'] = $customer_data['table_name'];
$fields['where_and_how_are_the_products_o_89']['field'] = $when_where_sold;
$fields['where_and_how_are_the_products_o_89']['element_label_type'] = 'p';
/* Field: Global: Fieldset */
$fields['fieldset_4']['id'] = 'fieldset_4';
$fields['fieldset_4']['table'] = 'views';
$fields['fieldset_4']['field'] = 'fieldset';
$fields['fieldset_4']['label'] = 'Business Support available for your company';
$fields['fieldset_4']['children'] = array(
  0 => 'is_your_company_aware_of_any_bus_514',
  1 => 'has_your_company_ever_worked_wit_515',
  2 => 'does_your_company_actively_make__516',
  3 => 'is_your_company_member_of_any_of_517',
);
/* Field: CiviCRM Custom: Customer Data: Is your company aware of any business support provided by the following type of organisations?  (check box if yes) */
$fields['is_your_company_aware_of_any_bus_514']['id'] = 'is_your_company_aware_of_any_bus_514';
$fields['is_your_company_aware_of_any_bus_514']['table'] = $customer_data['table_name'];
$fields['is_your_company_aware_of_any_bus_514']['field'] = $aware;
$fields['is_your_company_aware_of_any_bus_514']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Has your company ever worked with any of these organisations?  (check box if yes) */
$fields['has_your_company_ever_worked_wit_515']['id'] = 'has_your_company_ever_worked_wit_515';
$fields['has_your_company_ever_worked_wit_515']['table'] = $customer_data['table_name'];
$fields['has_your_company_ever_worked_wit_515']['field'] = $worked_with;
$fields['has_your_company_ever_worked_wit_515']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Does your company actively make use of the business support provided by these organisations? (check box if yes) */
$fields['does_your_company_actively_make__516']['id'] = 'does_your_company_actively_make__516';
$fields['does_your_company_actively_make__516']['table'] = $customer_data['table_name'];
$fields['does_your_company_actively_make__516']['field'] = $activily_make;
$fields['does_your_company_actively_make__516']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Is your company member of any of the above mentrioned type of support organisation for which membership is not voluntary? */
$fields['is_your_company_member_of_any_of_517']['id'] = 'is_your_company_member_of_any_of_517';
$fields['is_your_company_member_of_any_of_517']['table'] = $customer_data['table_name'];
$fields['is_your_company_member_of_any_of_517']['field'] = $member_of;
$fields['is_your_company_member_of_any_of_517']['element_label_type'] = 'p';


/* Field: Global: View */
$fields['view']['id'] = 'view';
$fields['view']['table'] = 'views';
$fields['view']['field'] = 'view';
$fields['view']['label'] = 'Authorised contacts';
$fields['view']['element_label_type'] = 'h2';
$fields['view']['element_label_colon'] = FALSE;
$fields['view']['view'] = 'authorised_contacts_for_customer';
$fields['view']['arguments'] = '!1';
/* Field: Global: View */
$fields['view_1']['id'] = 'view_1';
$fields['view_1']['table'] = 'views';
$fields['view_1']['field'] = 'view';
$fields['view_1']['label'] = 'Representative';
$fields['view_1']['element_label_type'] = 'h2';
$fields['view_1']['element_label_colon'] = FALSE;
$fields['view_1']['view'] = 'representatives_for_customer';
$fields['view_1']['arguments'] = '!1';
/* Field: Global: Custom text */
$fields['edit_link_2']['id'] = 'edit_link_2';
$fields['edit_link_2']['table'] = 'views';
$fields['edit_link_2']['field'] = 'nothing';
$fields['edit_link_2']['label'] = '';
$fields['edit_link_2']['alter']['text'] = 'Edit organisation profile';
$fields['edit_link_2']['alter']['make_link'] = TRUE;
$fields['edit_link_2']['alter']['path'] = 'customer/profile/?cid1=[id]';
$fields['edit_link_2']['alter']['absolute'] = TRUE;
$fields['edit_link_2']['element_label_colon'] = FALSE;

/* Contextual filter: CiviCRM Contacts: Contact ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
/* Filter criterion: CiviCRM Contacts: Contact Sub Type */
$handler->display->display_options['filters']['contact_sub_type']['id'] = 'contact_sub_type';
$handler->display->display_options['filters']['contact_sub_type']['table'] = 'civicrm_contact';
$handler->display->display_options['filters']['contact_sub_type']['field'] = 'contact_sub_type';
$handler->display->display_options['filters']['contact_sub_type']['value'] = array(
  'Customer' => 'Customer',
);

/* Display: Customer */
$handler1 = $view->new_display('page', 'Customer', 'page');
$handler1->display->display_options['fields'] = $fields;
unset($handler1->display->display_options['fields']['edit_link_1']);
unset($handler1->display->display_options['fields']['edit_link_2']);
$handler1->display->display_options['path'] = 'customer';

/* Display: Customer for customer */
$handler2 = $view->new_display('page', 'Customer for customer', 'page_1');
$handler2->display->display_options['defaults']['access'] = FALSE;
$handler2->display->display_options['access']['type'] = 'role';
$handler2->display->display_options['access']['role'] = newcustomer_get_role_ids(array('Customer', 'Customer (contact)'));
$handler2->display->display_options['defaults']['fields'] = FALSE;
$handler2->display->display_options['fields'] = $fields;

$handler2->display->display_options['path'] = 'customer';
