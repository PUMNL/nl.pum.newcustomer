<?php

require_once 'newcustomer.civix.php';

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
