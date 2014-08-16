<?php

class CRM_Newcustomer_Config {
  
  private static $_singleton;
  
  private $relationship_types;
  
  private $drupal_role = false;
  
  private $auth_for_relationship;
  
  private $representative_relationship;
  
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
    
    $this->auth_for_relationship = civicrm_api3('RelationshipType', 'getsingle', array('name_a_b' => 'Has authorised'));
    $this->representative_relationship = civicrm_api3('RelationshipType', 'getsingle', array('name_a_b' => 'Representative'));
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
  
  public function getAuthorizedContactRelationshipTypeId() {
    if (isset($this->auth_for_relationship['id'])) {
      return $this->auth_for_relationship['id'];
    }
    return false;
  }
  
  public function getRepresepentativeRelationshipTypeId() {
    if (isset($this->representative_relationship['id'])) {
      return $this->representative_relationship['id'];
    }
    return false;
  }
  
}

