<?php

require_once 'newcustomer.civix.php';

/**
 * Implementation of hook_civicrm_aclWhereClause
 * 
 * Check if the current user is customer contact and retreive for every customer 
 * 
 * @param type $type
 * @param type $tables
 * @param type $whereTables
 * @param type $contactID
 * @param type $where
 */
function newcustomer_civicrm_aclWhereClause($type, &$tables, &$whereTables, &$contactID, &$where) {
  //select all customers for this contact
  $config = CRM_Newcustomer_Config::singleton();
  $auth_contact_rel_type_id = $config->getAuthorizedContactRelationshipTypeId();
  $representative_rel_type_id = $config->getRepresepentativeRelationshipTypeId();
  $relationship_types = array();
  
  if ($auth_contact_rel_type_id !== false) {
    $relationship_types[] = $auth_contact_rel_type_id;
  }
  if ($representative_rel_type_id !== false) {
    $relationship_types[] = $representative_rel_type_id;
  }
  
  if ($contactID > 0 && count($relationship_types) > 0) {
    //user is logged in
    //access to its customers when contact is a local rep
    //or access to its customers when contact is an authorised for
    $auth_rel_table_name = 'customer_relationship';
  
    $tables[$auth_rel_table_name] = $whereTables[$auth_rel_table_name] = "LEFT JOIN `civicrm_relationship` `{$auth_rel_table_name}` ON contact_a.id = {$auth_rel_table_name}.contact_id_a AND {$auth_rel_table_name}.relationship_type_id IN (" . implode(",", $relationship_types) . ") AND `{$auth_rel_table_name}`.`is_active` = '1' AND (`{$auth_rel_table_name}`.`start_date` <= CURDATE() OR `{$auth_rel_table_name}`.`start_date` IS NULL) AND (`{$auth_rel_table_name}`.`end_date` >= CURDATE() OR `{$auth_rel_table_name}`.`end_date` IS NULL)";
    $where .= " ({$auth_rel_table_name}.contact_id_b = '" . $contactID . "')";
  
    return true;
  } else if ($contactID === 0 && $representative_rel_type_id) {
    //make sure the anonymous user can fetch a list of represntatives. This is needed
    //when a new customer register itself, the new customer has to select which 
    //local representative they want. This hook is called for anonymous users when contactId = 0
    $rep_rel_table_name = 'customer_relationship';
  
    $tables[$rep_rel_table_name] = $whereTables[$rep_rel_table_name] = "LEFT JOIN `civicrm_relationship` `{$rep_rel_table_name}` ON contact_a.id = {$rep_rel_table_name}.contact_id_a AND {$rep_rel_table_name}.relationship_type_id IN = '".$representative_rel_type_id."' AND `{$rep_rel_table_name}`.`is_active` = '1' AND (`{$rep_rel_table_name}`.`start_date` <= CURDATE() OR `{$rep_rel_table_name}`.`start_date` IS NULL) AND (`{$rep_rel_table_name}`.`end_date` >= CURDATE() OR `{$rep_rel_table_name}`.`end_date` IS NULL)";
    $where .= ""; //empty where clause
    return true;
  }
  
  return false;;
}

/**
 * Create a drupal user account as soon as a customer contact relation is created
 * 
 */
function newcustomer_civicrm_post($op, $objectName, $objectId, &$objectRef) {
  if ($objectName == 'Relationship' && ($op == 'edit' || $op == 'create')) {
    //create drupal user account    
    $user_account = new CRM_Newcustomer_UserRole($objectRef);
    //process checks if this is a valid relationship type
    $user_account->process();
  }
}

/**
 * Implementation of hook_civicrm_navigationMenu
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_navigationMenu
 */
function newcustomer_civicrm_navigationMenu(&$params) {
  $item = array(
    "name" => ts('Customer contact settings'),
    "url" => "civicrm/admin/customercontact",
    "permission" => "administer CiviCRM",
  );
  _newcustomer_civix_insert_navigation_menu($params, "Administer/System Settings", $item);
}

/**
 * Implementation of hook_civicrm_config
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_config
 */
function newcustomer_civicrm_config(&$config) {
  _newcustomer_civix_civicrm_config($config);
}

/**
 * Implementation of hook_civicrm_xmlMenu
 *
 * @param $files array(string)
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_xmlMenu
 */
function newcustomer_civicrm_xmlMenu(&$files) {
  _newcustomer_civix_civicrm_xmlMenu($files);
}

/**
 * Implementation of hook_civicrm_install
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_install
 */
function newcustomer_civicrm_install() {
  return _newcustomer_civix_civicrm_install();
}

/**
 * Implementation of hook_civicrm_uninstall
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_uninstall
 */
function newcustomer_civicrm_uninstall() {
  return _newcustomer_civix_civicrm_uninstall();
}

/**
 * Implementation of hook_civicrm_enable
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_enable
 */
function newcustomer_civicrm_enable() {
  return _newcustomer_civix_civicrm_enable();
}

/**
 * Implementation of hook_civicrm_disable
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_disable
 */
function newcustomer_civicrm_disable() {
  return _newcustomer_civix_civicrm_disable();
}

/**
 * Implementation of hook_civicrm_upgrade
 *
 * @param $op string, the type of operation being performed; 'check' or 'enqueue'
 * @param $queue CRM_Queue_Queue, (for 'enqueue') the modifiable list of pending up upgrade tasks
 *
 * @return mixed  based on op. for 'check', returns array(boolean) (TRUE if upgrades are pending)
 *                for 'enqueue', returns void
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_upgrade
 */
function newcustomer_civicrm_upgrade($op, CRM_Queue_Queue $queue = NULL) {
  return _newcustomer_civix_civicrm_upgrade($op, $queue);
}

/**
 * Implementation of hook_civicrm_managed
 *
 * Generate a list of entities to create/deactivate/delete when this module
 * is installed, disabled, uninstalled.
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_managed
 */
function newcustomer_civicrm_managed(&$entities) {
  return _newcustomer_civix_civicrm_managed($entities);
}

/**
 * Implementation of hook_civicrm_caseTypes
 *
 * Generate a list of case-types
 *
 * Note: This hook only runs in CiviCRM 4.4+.
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_caseTypes
 */
function newcustomer_civicrm_caseTypes(&$caseTypes) {
  _newcustomer_civix_civicrm_caseTypes($caseTypes);
}

/**
 * Implementation of hook_civicrm_alterSettingsFolders
 *
 * @link http://wiki.civicrm.org/confluence/display/CRMDOC/hook_civicrm_alterSettingsFolders
 */
function newcustomer_civicrm_alterSettingsFolders(&$metaDataFolders = NULL) {
  _newcustomer_civix_civicrm_alterSettingsFolders($metaDataFolders);
}
