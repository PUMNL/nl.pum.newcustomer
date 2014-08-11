<?php

class CRM_Newcustomer_Config {
  
  private static $_singleton;
  
  private $relationship_types;
  
  private $drupal_role = false;
  
  private function __construct() {
    $this->relationship_types = unserialize(CRM_Core_BAO_Setting::getItem('nl.pum.newcustomer', 'new_customer_relationship_types'));
    if (!is_array($this->relationship_types)) {
      $this->relationship_types = array();
    }
    
    $rid = CRM_Core_BAO_Setting::getItem('nl.pum.newcustomer', 'new_customer_role_id');
    $roles = $this->getDrupalRoles();
    if (isset($roles[$rid])) {
      $this->drupal_role = $rid;
    }
  }
  
  public static function singleton() {
    if (!self::$_singleton) {
      self::$_singleton = new CRM_Newcustomer_Config();
    }
    return self::$_singleton;
  }
  
  public function getRelationshipTypes() {
    return $this->relationship_types;
  }
  
  public function getDrupalRole() {
    return $this->drupal_role;
  }
  
  public function getDrupalRoles() {
    $roles = array();
    if (function_exists('user_roles')) {
      $roles = user_roles(true);
    }
    return $roles;
  }
  
}

