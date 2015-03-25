<?php

$view = new view();
$view->name = 'contacts_websites';
$view->description = 'Websites of a civicrm contact';
$view->tag = 'customer info';
$view->base_table = 'civicrm_contact';
$view->human_name = 'Contacts Websites';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '0';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: CiviCRM Website: Website Type */
$handler->display->display_options['fields']['website_type']['id'] = 'website_type';
$handler->display->display_options['fields']['website_type']['table'] = 'civicrm_website';
$handler->display->display_options['fields']['website_type']['field'] = 'website_type';
$handler->display->display_options['fields']['website_type']['label'] = '';
$handler->display->display_options['fields']['website_type']['exclude'] = TRUE;
$handler->display->display_options['fields']['website_type']['element_label_colon'] = FALSE;
/* Field: CiviCRM Website: Website URL */
$handler->display->display_options['fields']['url']['id'] = 'url';
$handler->display->display_options['fields']['url']['table'] = 'civicrm_website';
$handler->display->display_options['fields']['url']['field'] = 'url';
$handler->display->display_options['fields']['url']['label'] = '';
$handler->display->display_options['fields']['url']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['url']['alter']['text'] = '<a href="[url]">[url]</a>';
$handler->display->display_options['fields']['url']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['url']['hide_empty'] = TRUE;
/* Contextual filter: CiviCRM Contacts: Contact ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'access denied';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
$translatables['contacts_websites'] = array(
  t('Master'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('« first'),
  t('‹ previous'),
  t('next ›'),
  t('last »'),
  t('[website_type]: <a href="[url]">[url]</a>'),
  t('All'),
);
