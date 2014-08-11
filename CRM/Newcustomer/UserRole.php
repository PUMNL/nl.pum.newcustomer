<?php

class CRM_Newcustomer_UserRole {
  
  protected $contact_ids;
  
  public function __construct($relationship_bao) {
     $config = CRM_Newcustomer_Config::singleton();
     foreach($config->getRelationshipTypes() as $type_id) {
       if ('a_'.$relationship_bao->relationship_type_id == $type_id) {
         $this->contact_ids[] = $relationship_bao->contact_id_a;
       } elseif ('b_'.$relationship_bao->relationship_type_id == $type_id) {
         $this->contact_ids[] = $relationship_bao->contact_id_b;
       }
     }
  }
  
  public function process() {
    if (!count($this->contact_ids)) {
      return;
    }
    
    $config = CRM_Newcustomer_Config::singleton();
    if (!$config->getDrupalRole()) {
      CRM_Core_Session::setStatus('No user account created becasue an invalid role is set up', 'No user account created', 'error');
      return;
    }
    foreach($this->contact_ids as $cid) {
      //check if this user exist in drupal
      $drupal_uid = $this->createDrupalUser($cid);
      if ($drupal_uid) {
        //assign role to drupal user
        $this->assignRoleToUser($drupal_uid, $config->getDrupalRole());
        //set the message
        try {
          $contact = civicrm_api3('Contact', 'getsingle', array('id' => $cid));
          CRM_Core_Session::setStatus('User account created for '.$contact['display_name'], 'User account created', 'success');
        } catch (Exception $e) {
          CRM_Core_Session::setStatus('User account created', 'User account created', 'success');
        }
      }
    }
  }
  
  protected function assignRoleToUser($uid, $role_id) {
    $user = user_load($uid);
    if (isset($user->roles[$role_id])) {
      return;
    }
    
    $roles = user_roles(TRUE);
    $role_name = $roles[$role_id];
    $user_roles = $user->roles;
    $user_roles[$role_id] = $role_name;
    user_save($user, array('roles' => $user_roles));
  }
  
  protected function createDrupalUser($contact_id) {
    $drupal_uid = $this->getDurpalUserId($contact_id);
    if ($drupal_uid !== false) {
      return $drupal_uid;
    }
    
    //create user in drupal
    //user the form api to create the user
    $form_state = form_state_defaults();
    try {
      $contact = civicrm_api3('Contact', 'getsingle', array('id' => $contact_id));
    } catch (Exception $e) {
      CRM_Core_Session::setStatus('No user account created because contact could not be found', 'No user account created', 'error');
    }
    
    try {
     $email = civicrm_api3('Email', 'getsingle', array('contact_id' => $contact_id, 'is_primary' => '1'));   
    } catch (Exception $ex) {
       CRM_Core_Session::setStatus('No user account created because contact does not have an e-mail address', 'No user account created', 'error');
    }
    
    $name = $email['email'];
    
    $form_state['input'] = array(
      'name' => $name,
      'mail' => $email['email'],
      'op' => 'Create new account',
      'notify' => true,
    );
    
    $pass = $this->randomPassword();
    $form_state['input']['pass'] = array('pass1'=>$pass,'pass2'=>$pass);
    
    $form_state['rebuild'] = FALSE;
    $form_state['programmed'] = TRUE;
    $form_state['complete form'] = FALSE;
    $form_state['method'] = 'post';
    $form_state['build_info']['args'] = array();
    /*
    * if we want to submit this form more than once in a process (e.g. create more than one user)
    * we must force it to validate each time for this form. Otherwise it will not validate
    * subsequent submissions and the manner in which the password is passed in will be invalid
    * */
    $form_state['must_validate'] = TRUE;
    $config = CRM_Core_Config::singleton();

    // we also need to redirect b......
    $config->inCiviCRM = TRUE;

    $form = drupal_retrieve_form('user_register_form', $form_state);
    $form_state['process_input'] = 1;
    $form_state['submitted'] = 1;
    $form['#array_parents'] = array();
    $form['#tree'] = FALSE;
    drupal_process_form('user_register_form', $form, $form_state);

    $config->inCiviCRM = FALSE;

    if (form_get_errors()) {
      CRM_Core_Session::setStatus('No user account created', 'No user account created', 'error');
      return FALSE;
    }
    $drupal_uid = $form_state['user']->uid;
    
    $ufmatch             = new CRM_Core_DAO_UFMatch();
    $ufmatch->domain_id  = CRM_Core_Config::domainID();
    $ufmatch->uf_id      = $drupal_uid;
    $ufmatch->contact_id = $contact_id;
    $ufmatch->uf_name    = $name;

    if (!$ufmatch->find(TRUE)) {
      $ufmatch->save();
    }
    
    return $drupal_uid;
  }
  
  protected function getDurpalUserId($contact_id) {
    try {
      $domain_id = CRM_Core_Config::domainID();
      $uf = civicrm_api3('UFMatch', 'getsingle', array('contact_id' => $contact_id, 'domain_id' => $domain_id));
      return $uf['uf_id'];
    } catch (Exception $e) {
      //do nothing
    }
    return false;
  }
  
  protected function randomPassword() {
    //from http://stackoverflow.com/a/6101969
    $alphabet = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ0123456789";
    $pass = array(); //remember to declare $pass as an array
    $alphaLength = strlen($alphabet) - 1; //put the length -1 in cache
    for ($i = 0; $i < 8; $i++) {
        $n = rand(0, $alphaLength);
        $pass[] = $alphabet[$n];
    }
    return implode($pass); //turn the array into a string
  }
  
  
}

