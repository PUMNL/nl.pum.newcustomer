<?php

class CRM_Newcustomer_Config {
  
  static $_singleton;
  
  private $auth_for_relationship;
  
  private $representative_relationship;
  
  private function __construct() {
    $this->auth_for_relationship = civicrm_api3('RelationshipType', 'getsingle', array('name_a_b' => 'Has authorised'));
    $this->representative_relationship = civicrm_api3('RelationshipType', 'getsingle', array('name_a_b' => 'Representative'));
  }
  
  public static function singleton() {
    if (!self::$_singleton) {
      self::$_singleton = new CRM_Newcustomer_Config();
    }
    return self::$_singleton;
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
