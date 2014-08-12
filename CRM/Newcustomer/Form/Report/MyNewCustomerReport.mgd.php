<?php
// This file declares a managed database record of type "ReportTemplate".
// The record will be automatically inserted, updated, or deleted from the
// database as appropriate. For more details, see "hook_civicrm_managed" at:
// http://wiki.civicrm.org/confluence/display/CRMDOC42/Hook+Reference
return array (
  0 => 
  array (
    'name' => 'CRM_Newcustomer_Form_Report_MyNewCustomerReport',
    'entity' => 'ReportTemplate',
    'params' => 
    array (
      'version' => 3,
      'label' => 'My new customers',
      'description' => 'Report to show contacts with which the user has a relation with',
      'class_name' => 'CRM_Newcustomer_Form_Report_MyNewCustomerReport',
      'report_url' => 'nl.pum.newcustomer/mynewcustomerreport',
      'component' => '',
    ),
  ),
);