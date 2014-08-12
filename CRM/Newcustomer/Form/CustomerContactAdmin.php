<?php

require_once 'CRM/Core/Form.php';

/**
 * Form controller class
 *
 * @see http://wiki.civicrm.org/confluence/display/CRMDOC43/QuickForm+Reference
 */
class CRM_Newcustomer_Form_CustomerContactAdmin extends CRM_Core_Form {
  function buildQuickForm() {
    CRM_Utils_System::setTitle(ts('Settings for customer contact'));
    
    // add form elements
    $this->add(
      'select', // field type
      'drupal_role', // field name
      'Drupal role for new customer contact', // field label
      $this->getDrupalRolesOptions(), // list of options
      true // is required
    );
    
    $this->add(
      'select', // field type
      'relationship_type', // field name
      'Grant drupal role on creation of relation', // field label
      $this->getRelationshipTypes(), // list of options
      true, // is required
      array('multiple' => true)
    );
    
    $this->addButtons(array(
      array(
        'type' => 'submit',
        'name' => ts('Submit'),
        'isDefault' => TRUE,
      ),
    ));

    // export form elements
    $this->assign('elementNames', $this->getRenderableElementNames());
    parent::buildQuickForm();
  }
  
  function setDefaultValues() {
    parent::setDefaultValues();
    
    $config = CRM_Newcustomer_Config::singleton();
    $values['drupal_role'] = $config->getDrupalRole();
    $values['relationship_type'] = $config->getRelationshipTypes();

    return $values;
  }

  function postProcess() {
    $values = $this->exportValues();    
    
    CRM_Core_BAO_Setting::setItem($values['drupal_role'], 'nl.pum.newcustomer', 'new_customer_role_id');
    CRM_Core_BAO_Setting::setItem(serialize($values['relationship_type']), 'nl.pum.newcustomer', 'new_customer_relationship_types');
    
    CRM_Core_Session::setStatus(ts('Saved customer contact settings'), ts('Customer contact settings'), 'success');
        
    parent::postProcess();
  }

  function getDrupalRolesOptions() {    
    $options = array(
      '' => ts('- select -')
    );
    
    $config = CRM_Expertapplication_Config::singleton();
    $roles = $config->getDrupalRoles();
    foreach($roles as $rid => $role) {
      $options[$rid] = $role;
    }
    return $options;
  }
  
  function getRelationshipTypes() {
    $dao = new CRM_Contact_BAO_RelationshipType();
    $dao->is_active = 1;
    $dao->find(FALSE);
    while($dao->fetch()) {
      $options['a_'.$dao->id] = $dao->label_a_b;
      $options['b_'.$dao->id] = $dao->label_b_a;
    }
    asort($options);
    return $options;
  }

  /**
   * Get the fields/elements defined in this form.
   *
   * @return array (string)
   */
  function getRenderableElementNames() {
    // The _elements list includes some items which should not be
    // auto-rendered in the loop -- such as "qfKey" and "buttons".  These
    // items don't have labels.  We'll identify renderable by filtering on
    // the 'label'.
    $elementNames = array();
    foreach ($this->_elements as $element) {
      $label = $element->getLabel();
      if (!empty($label)) {
        $elementNames[] = $element->getName();
      }
    }
    return $elementNames;
  }
}
