<?php

$new_customer_tag_id = civicrm_api3('Tag', 'getvalue', array('return' => 'id', 'name' => 'New customer'));
$local_rep_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Representative', 'return' => 'id'));

$view = new view();
$view->name = 'lr_s_new_customers';
$view->description = '';
$view->tag = 'new customer';
$view->base_table = 'civicrm_contact';
$view->human_name = 'LR\'s new customers';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'New customers';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  6 => '6',
);
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
/* Relationship: Local rep relationship */
$handler->display->display_options['relationships']['relationship_id_a']['id'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_a']['field'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['ui_name'] = 'Local rep relationship';
$handler->display->display_options['relationships']['relationship_id_a']['label'] = 'Local rep relationship';
$handler->display->display_options['relationships']['relationship_id_a']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_a']['relationship_type'] = $local_rep_rel_type_id;
/* Relationship: CiviCRM Relationships: Contact ID A */
$handler->display->display_options['relationships']['contact_id_a_']['id'] = 'contact_id_a_';
$handler->display->display_options['relationships']['contact_id_a_']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_a_']['field'] = 'contact_id_a_';
$handler->display->display_options['relationships']['contact_id_a_']['relationship'] = 'relationship_id_a';
$handler->display->display_options['relationships']['contact_id_a_']['label'] = 'customer';
$handler->display->display_options['relationships']['contact_id_a_']['required'] = TRUE;
/* Relationship: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['relationships']['contact_id_b_']['id'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_b_']['field'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['relationship'] = 'relationship_id_a';
$handler->display->display_options['relationships']['contact_id_b_']['label'] = 'Local rep';
$handler->display->display_options['relationships']['contact_id_b_']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['relationship'] = 'contact_id_b_';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['display_name']['label'] = 'Customer';
$handler->display->display_options['fields']['display_name']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 1;
/* Field: CiviCRM Address: City / Suburb */
$handler->display->display_options['fields']['city']['id'] = 'city';
$handler->display->display_options['fields']['city']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['city']['field'] = 'city';
$handler->display->display_options['fields']['city']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['city']['label'] = 'City';
$handler->display->display_options['fields']['city']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['city']['location_type'] = '0';
$handler->display->display_options['fields']['city']['location_op'] = '0';
$handler->display->display_options['fields']['city']['is_primary'] = 1;
$handler->display->display_options['fields']['city']['is_billing'] = 0;
/* Field: CiviCRM Address: State / Province */
$handler->display->display_options['fields']['state_province']['id'] = 'state_province';
$handler->display->display_options['fields']['state_province']['table'] = 'civicrm_address';
$handler->display->display_options['fields']['state_province']['field'] = 'state_province';
$handler->display->display_options['fields']['state_province']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['state_province']['location_type'] = '0';
$handler->display->display_options['fields']['state_province']['location_op'] = '0';
$handler->display->display_options['fields']['state_province']['is_primary'] = 1;
$handler->display->display_options['fields']['state_province']['is_billing'] = 0;
$handler->display->display_options['fields']['state_province']['prov_display'] = '2';
/* Field: CiviCRM Phone Details: Phone Number */
$handler->display->display_options['fields']['phone']['id'] = 'phone';
$handler->display->display_options['fields']['phone']['table'] = 'civicrm_phone';
$handler->display->display_options['fields']['phone']['field'] = 'phone';
$handler->display->display_options['fields']['phone']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['phone']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['phone']['location_type'] = '0';
$handler->display->display_options['fields']['phone']['location_op'] = '0';
$handler->display->display_options['fields']['phone']['is_primary'] = 0;
$handler->display->display_options['fields']['phone']['phone_type'] = '0';
/* Field: CiviCRM Email: Email Address */
$handler->display->display_options['fields']['email']['id'] = 'email';
$handler->display->display_options['fields']['email']['table'] = 'civicrm_email';
$handler->display->display_options['fields']['email']['field'] = 'email';
$handler->display->display_options['fields']['email']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['email']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['email']['location_type'] = '0';
$handler->display->display_options['fields']['email']['location_op'] = '0';
$handler->display->display_options['fields']['email']['is_primary'] = 0;
/* Filter criterion: CiviCRM Tags: Name */
$handler->display->display_options['filters']['name']['id'] = 'name';
$handler->display->display_options['filters']['name']['table'] = 'civicrm_tag';
$handler->display->display_options['filters']['name']['field'] = 'name';
$handler->display->display_options['filters']['name']['relationship'] = 'contact_id_a_';
$handler->display->display_options['filters']['name']['value'] = array(
  $new_customer_tag_id => $new_customer_tag_id,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'lr-s-new-customers';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'New customers';
$handler->display->display_options['menu']['weight'] = '-50';
$handler->display->display_options['menu']['name'] = 'menu-webforms';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

$views[$view->name] = $view;