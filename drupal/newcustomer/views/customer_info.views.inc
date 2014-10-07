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
$handler->display->display_options['fields']['fieldset']['id'] = 'fieldset';
$handler->display->display_options['fields']['fieldset']['table'] = 'views';
$handler->display->display_options['fields']['fieldset']['field'] = 'fieldset';
$handler->display->display_options['fields']['fieldset']['label'] = 'General info';
$handler->display->display_options['fields']['fieldset']['children'] = array(
  0 => 'display_name',
  1 => 'email',
  2 => 'phone',
  3 => 'fieldset_1',
  4 => 'fieldset_2',
);
$handler->display->display_options['fields']['fieldset']['fieldset']['type'] = 'div';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['label'] = '';
$handler->display->display_options['fields']['display_name']['element_type'] = 'h1';
$handler->display->display_options['fields']['display_name']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Email: Email Address */
$handler->display->display_options['fields']['email']['id'] = 'email';
$handler->display->display_options['fields']['email']['table'] = 'civicrm_email';
$handler->display->display_options['fields']['email']['field'] = 'email';
$handler->display->display_options['fields']['email']['location_type'] = '0';
$handler->display->display_options['fields']['email']['location_op'] = '0';
$handler->display->display_options['fields']['email']['is_primary'] = 0;
/* Field: CiviCRM Phone Details: Phone Number */
$handler->display->display_options['fields']['phone']['id'] = 'phone';
$handler->display->display_options['fields']['phone']['table'] = 'civicrm_phone';
$handler->display->display_options['fields']['phone']['field'] = 'phone';
$handler->display->display_options['fields']['phone']['location_type'] = '0';
$handler->display->display_options['fields']['phone']['location_op'] = '0';
$handler->display->display_options['fields']['phone']['is_primary'] = 0;
$handler->display->display_options['fields']['phone']['phone_type'] = '0';
/* Field: Global: View */
$handler->display->display_options['fields']['view_2']['id'] = 'view_2';
$handler->display->display_options['fields']['view_2']['table'] = 'views';
$handler->display->display_options['fields']['view_2']['field'] = 'view';
$handler->display->display_options['fields']['view_2']['label'] = '';
$handler->display->display_options['fields']['view_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view_2']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['view_2']['view'] = 'contacts_websites';
$handler->display->display_options['fields']['view_2']['arguments'] = '!1';
/* Field: Global: Fieldset */
$handler->display->display_options['fields']['fieldset_1']['id'] = 'fieldset_1';
$handler->display->display_options['fields']['fieldset_1']['table'] = 'views';
$handler->display->display_options['fields']['fieldset_1']['field'] = 'fieldset';
$handler->display->display_options['fields']['fieldset_1']['label'] = 'Primary address';
$handler->display->display_options['fields']['fieldset_1']['children'] = array(
  0 => 'street_address',
  1 => 'city',
  2 => 'postal_code',
  3 => 'state_province',
  4 => 'country',
);
/* Field: CiviCRM Address: Full Street Address */
$handler->display->display_options['fields']['street_address']['id'] = 'street_address';
$handler->display->display_options['fields']['street_address']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['street_address']['field'] = 'street_address';
$handler->display->display_options['fields']['street_address']['label'] = '';
$handler->display->display_options['fields']['street_address']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['street_address']['location_type'] = '0';
$handler->display->display_options['fields']['street_address']['location_op'] = '0';
$handler->display->display_options['fields']['street_address']['is_primary'] = 1;
$handler->display->display_options['fields']['street_address']['is_billing'] = 0;
/* Field: CiviCRM Address: City / Suburb */
$handler->display->display_options['fields']['city']['id'] = 'city';
$handler->display->display_options['fields']['city']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['city']['field'] = 'city';
$handler->display->display_options['fields']['city']['label'] = '';
$handler->display->display_options['fields']['city']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['city']['location_type'] = '0';
$handler->display->display_options['fields']['city']['location_op'] = '0';
$handler->display->display_options['fields']['city']['is_primary'] = 1;
$handler->display->display_options['fields']['city']['is_billing'] = 0;
/* Field: CiviCRM Address: ZIP / Postal Code */
$handler->display->display_options['fields']['postal_code']['id'] = 'postal_code';
$handler->display->display_options['fields']['postal_code']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['postal_code']['field'] = 'postal_code';
$handler->display->display_options['fields']['postal_code']['label'] = '';
$handler->display->display_options['fields']['postal_code']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['postal_code']['location_type'] = '0';
$handler->display->display_options['fields']['postal_code']['location_op'] = '0';
$handler->display->display_options['fields']['postal_code']['is_primary'] = 1;
$handler->display->display_options['fields']['postal_code']['is_billing'] = 0;
/* Field: CiviCRM Address: State / Province */
$handler->display->display_options['fields']['state_province']['id'] = 'state_province';
$handler->display->display_options['fields']['state_province']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['state_province']['field'] = 'state_province';
$handler->display->display_options['fields']['state_province']['label'] = '';
$handler->display->display_options['fields']['state_province']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['state_province']['location_type'] = '0';
$handler->display->display_options['fields']['state_province']['location_op'] = '0';
$handler->display->display_options['fields']['state_province']['is_primary'] = 1;
$handler->display->display_options['fields']['state_province']['is_billing'] = 0;
$handler->display->display_options['fields']['state_province']['prov_display'] = '2';
/* Field: CiviCRM Address: Country */
$handler->display->display_options['fields']['country']['id'] = 'country';
$handler->display->display_options['fields']['country']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['country']['field'] = 'country';
$handler->display->display_options['fields']['country']['label'] = '';
$handler->display->display_options['fields']['country']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['country']['location_type'] = '0';
$handler->display->display_options['fields']['country']['location_op'] = '0';
$handler->display->display_options['fields']['country']['is_primary'] = 1;
$handler->display->display_options['fields']['country']['is_billing'] = 0;
/* Field: Global: Fieldset */
$handler->display->display_options['fields']['fieldset_2']['id'] = 'fieldset_2';
$handler->display->display_options['fields']['fieldset_2']['table'] = 'views';
$handler->display->display_options['fields']['fieldset_2']['field'] = 'fieldset';
$handler->display->display_options['fields']['fieldset_2']['label'] = 'Postal address';
$handler->display->display_options['fields']['fieldset_2']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['fieldset_2']['children'] = array(
  0 => 'street_address_1',
  1 => 'city_1',
  2 => 'postal_code_1',
  3 => 'state_province_1',
  4 => 'country_1',
);
/* Field: CiviCRM Address: Full Street Address */
$handler->display->display_options['fields']['street_address_1']['id'] = 'street_address_1';
$handler->display->display_options['fields']['street_address_1']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['street_address_1']['field'] = 'street_address';
$handler->display->display_options['fields']['street_address_1']['label'] = '';
$handler->display->display_options['fields']['street_address_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['street_address_1']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['street_address_1']['location_type'] = $postal_loc_type_id;
$handler->display->display_options['fields']['street_address_1']['location_op'] = '0';
$handler->display->display_options['fields']['street_address_1']['is_primary'] = 0;
$handler->display->display_options['fields']['street_address_1']['is_billing'] = 0;
/* Field: CiviCRM Address: City / Suburb */
$handler->display->display_options['fields']['city_1']['id'] = 'city_1';
$handler->display->display_options['fields']['city_1']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['city_1']['field'] = 'city';
$handler->display->display_options['fields']['city_1']['label'] = '';
$handler->display->display_options['fields']['city_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['city_1']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['city_1']['location_type'] = $postal_loc_type_id;
$handler->display->display_options['fields']['city_1']['location_op'] = '0';
$handler->display->display_options['fields']['city_1']['is_primary'] = 0;
$handler->display->display_options['fields']['city_1']['is_billing'] = 0;
/* Field: CiviCRM Address: ZIP / Postal Code */
$handler->display->display_options['fields']['postal_code_1']['id'] = 'postal_code_1';
$handler->display->display_options['fields']['postal_code_1']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['postal_code_1']['field'] = 'postal_code';
$handler->display->display_options['fields']['postal_code_1']['label'] = '';
$handler->display->display_options['fields']['postal_code_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['postal_code_1']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['postal_code_1']['location_type'] = $postal_loc_type_id;
$handler->display->display_options['fields']['postal_code_1']['location_op'] = '0';
$handler->display->display_options['fields']['postal_code_1']['is_primary'] = 0;
$handler->display->display_options['fields']['postal_code_1']['is_billing'] = 0;
/* Field: CiviCRM Address: State / Province */
$handler->display->display_options['fields']['state_province_1']['id'] = 'state_province_1';
$handler->display->display_options['fields']['state_province_1']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['state_province_1']['field'] = 'state_province';
$handler->display->display_options['fields']['state_province_1']['label'] = '';
$handler->display->display_options['fields']['state_province_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['state_province_1']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['state_province_1']['location_type'] = $postal_loc_type_id;
$handler->display->display_options['fields']['state_province_1']['location_op'] = '0';
$handler->display->display_options['fields']['state_province_1']['is_primary'] = 0;
$handler->display->display_options['fields']['state_province_1']['is_billing'] = 0;
$handler->display->display_options['fields']['state_province_1']['prov_display'] = '2';
/* Field: CiviCRM Address: Country */
$handler->display->display_options['fields']['country_1']['id'] = 'country_1';
$handler->display->display_options['fields']['country_1']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['country_1']['field'] = 'country';
$handler->display->display_options['fields']['country_1']['label'] = '';
$handler->display->display_options['fields']['country_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['country_1']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['country_1']['location_type'] = $postal_loc_type_id;
$handler->display->display_options['fields']['country_1']['location_op'] = '0';
$handler->display->display_options['fields']['country_1']['is_primary'] = 0;
$handler->display->display_options['fields']['country_1']['is_billing'] = 0;
$handler->display->display_options['fields']['country_1']['country_display'] = '2';
/* Field: Global: Fieldset */
$handler->display->display_options['fields']['fieldset_3']['id'] = 'fieldset_3';
$handler->display->display_options['fields']['fieldset_3']['table'] = 'views';
$handler->display->display_options['fields']['fieldset_3']['field'] = 'fieldset';
$handler->display->display_options['fields']['fieldset_3']['label'] = 'Main product/services';
$handler->display->display_options['fields']['fieldset_3']['children'] = array(
  0 => 'what_is_the_operational_model_of_513',
  1 => 'products_and_or_services_offered_86',
  2 => 'where_and_how_are_the_products_o_89',
);
/* Field: CiviCRM Custom: Customer Data: What is the operational model of the organisation */
$handler->display->display_options['fields']['what_is_the_operational_model_of_513']['id'] = 'what_is_the_operational_model_of_513';
$handler->display->display_options['fields']['what_is_the_operational_model_of_513']['table'] = $customer_data['table_name'];
$handler->display->display_options['fields']['what_is_the_operational_model_of_513']['field'] = $model;
$handler->display->display_options['fields']['what_is_the_operational_model_of_513']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Products and/or Services offered */
$handler->display->display_options['fields']['products_and_or_services_offered_86']['id'] = 'products_and_or_services_offered_86';
$handler->display->display_options['fields']['products_and_or_services_offered_86']['table'] = $customer_data['table_name'];
$handler->display->display_options['fields']['products_and_or_services_offered_86']['field'] = $services;
$handler->display->display_options['fields']['products_and_or_services_offered_86']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Where and how are the products or services sold */
$handler->display->display_options['fields']['where_and_how_are_the_products_o_89']['id'] = 'where_and_how_are_the_products_o_89';
$handler->display->display_options['fields']['where_and_how_are_the_products_o_89']['table'] = $customer_data['table_name'];
$handler->display->display_options['fields']['where_and_how_are_the_products_o_89']['field'] = $when_where_sold;
$handler->display->display_options['fields']['where_and_how_are_the_products_o_89']['element_label_type'] = 'p';
/* Field: Global: Fieldset */
$handler->display->display_options['fields']['fieldset_4']['id'] = 'fieldset_4';
$handler->display->display_options['fields']['fieldset_4']['table'] = 'views';
$handler->display->display_options['fields']['fieldset_4']['field'] = 'fieldset';
$handler->display->display_options['fields']['fieldset_4']['label'] = 'Business Support available for your company';
$handler->display->display_options['fields']['fieldset_4']['children'] = array(
  0 => 'is_your_company_aware_of_any_bus_514',
  1 => 'has_your_company_ever_worked_wit_515',
  2 => 'does_your_company_actively_make__516',
  3 => 'is_your_company_member_of_any_of_517',
);
/* Field: CiviCRM Custom: Customer Data: Is your company aware of any business support provided by the following type of organisations?  (check box if yes) */
$handler->display->display_options['fields']['is_your_company_aware_of_any_bus_514']['id'] = 'is_your_company_aware_of_any_bus_514';
$handler->display->display_options['fields']['is_your_company_aware_of_any_bus_514']['table'] = $customer_data['table_name'];
$handler->display->display_options['fields']['is_your_company_aware_of_any_bus_514']['field'] = $aware;
$handler->display->display_options['fields']['is_your_company_aware_of_any_bus_514']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Has your company ever worked with any of these organisations?  (check box if yes) */
$handler->display->display_options['fields']['has_your_company_ever_worked_wit_515']['id'] = 'has_your_company_ever_worked_wit_515';
$handler->display->display_options['fields']['has_your_company_ever_worked_wit_515']['table'] = $customer_data['table_name'];
$handler->display->display_options['fields']['has_your_company_ever_worked_wit_515']['field'] = $worked_with;
$handler->display->display_options['fields']['has_your_company_ever_worked_wit_515']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Does your company actively make use of the business support provided by these organisations? (check box if yes) */
$handler->display->display_options['fields']['does_your_company_actively_make__516']['id'] = 'does_your_company_actively_make__516';
$handler->display->display_options['fields']['does_your_company_actively_make__516']['table'] = $customer_data['table_name'];
$handler->display->display_options['fields']['does_your_company_actively_make__516']['field'] = $activily_make;
$handler->display->display_options['fields']['does_your_company_actively_make__516']['element_label_type'] = 'p';
/* Field: CiviCRM Custom: Customer Data: Is your company member of any of the above mentrioned type of support organisation for which membership is not voluntary? */
$handler->display->display_options['fields']['is_your_company_member_of_any_of_517']['id'] = 'is_your_company_member_of_any_of_517';
$handler->display->display_options['fields']['is_your_company_member_of_any_of_517']['table'] = $customer_data['table_name'];
$handler->display->display_options['fields']['is_your_company_member_of_any_of_517']['field'] = $member_of;
$handler->display->display_options['fields']['is_your_company_member_of_any_of_517']['element_label_type'] = 'p';


/* Field: Global: View */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['label'] = 'Authorised contacts';
$handler->display->display_options['fields']['view']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view']['view'] = 'authorised_contacts_for_customer';
$handler->display->display_options['fields']['view']['arguments'] = '!1';
/* Field: Global: View */
$handler->display->display_options['fields']['view_1']['id'] = 'view_1';
$handler->display->display_options['fields']['view_1']['table'] = 'views';
$handler->display->display_options['fields']['view_1']['field'] = 'view';
$handler->display->display_options['fields']['view_1']['label'] = 'Representative';
$handler->display->display_options['fields']['view_1']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view_1']['view'] = 'representatives_for_customer';
$handler->display->display_options['fields']['view_1']['arguments'] = '!1';
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
$handler1->display->display_options['path'] = 'customer';

/* Display: Customer for customer */
$handler2 = $view->new_display('page', 'Customer for customer', 'page_1');
$handler2->display->display_options['defaults']['access'] = FALSE;
$handler2->display->display_options['access']['type'] = 'role';
$handler2->display->display_options['access']['role'] = newcustomer_get_role_ids(array('Customer', 'Customer (contact)'));
$handler2->display->display_options['defaults']['fields'] = FALSE;
$handler2->display->display_options['fields'] = $handler->display->display_options['fields'];
/* Field: Global: Custom text */
$handler2->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler2->display->display_options['fields']['nothing']['table'] = 'views';
$handler2->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler2->display->display_options['fields']['nothing']['label'] = '';
$handler2->display->display_options['fields']['nothing']['alter']['text'] = 'Edit organisation profile';
$handler2->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler2->display->display_options['fields']['nothing']['alter']['path'] = 'customer/profile/?cid1=[id]';
$handler2->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler2->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;

$handler2->display->display_options['path'] = 'customer';
