<?php

class CRM_Newcustomer_Form_Report_MyNewCustomerReport extends CRM_Report_Form {

  protected $_summary = NULL;
  protected $_emailField = FALSE;
  protected $_localRepField = FALSE;
  protected $_customGroupExtends = array('Contact');
  public $_drilldownReport = array('contact/detail' => 'Link to Detail Report');

  function __construct() {

    $contact_type = CRM_Contact_BAO_ContactType::getSelectElements(FALSE, TRUE, '_');

    $this->_columns = array(
      'civicrm_contact' =>
      array(
        'dao' => 'CRM_Contact_DAO_Contact',
        'fields' =>
        array(
          'display_name' =>
          array('title' => ts('Contact'),
            'name' => 'display_name',
            'required' => TRUE,
          ),
          'id' =>
          array(
            'no_display' => TRUE,
            'required' => TRUE,
          ),
        ),
        'grouping' => 'conact_fields',
      ),
      'civicrm_contact_local_rep' =>
      array(
        'dao' => 'CRM_Contact_DAO_Contact',
        'alias' => 'local_rep',
        'fields' =>
        array(
          'display_name_lcal_rep' =>
          array('title' => ts('Local rep'),
            'name' => 'display_name',
            'default' => TRUE,
          ),
        ),
        'grouping' => 'local_rep',
      ),
      'civicrm_email' =>
      array(
        'dao' => 'CRM_Core_DAO_Email',
        'fields' =>
        array(
          'email' =>
          array('title' => ts('Email of Contact'),
            'name' => 'email',
          ),
        ),
        'grouping' => 'conact_fields',
      ),
      'civicrm_relationship_local_rep' =>
      array(
        'dao' => 'CRM_Contact_DAO_Relationship',
        'alias' => 'local_rep_relation',
      ),
      'civicrm_relationship' =>
      array(
        'dao' => 'CRM_Contact_DAO_Relationship',
      ),
      'civicrm_address' =>
      array(
        'dao' => 'CRM_Core_DAO_Address',
        'fields' =>
        array(
          'street_address' => array(
            'title' => ts('Address')
          ),
          'postcal_code' => array(
            'title' => ts('Postal code')
          ),
          'city' => array(
            'title' => ts('City')
          ),
          'county_id' => array(
            'title' => ts('County'),
          ),
          'state_province_id' => array(
            'title' => ts('State or Province'),
          ),
          'country_id' =>
          array(
            'title' => ts('Country'),
          ),
        ),
        'grouping' => 'contact_fields',
      ),
    );

    $this->_tagFilter = TRUE;
    parent::__construct();
  }

  function preProcess() {
    parent::preProcess();
  }

  function select() {
    $select = $this->_columnHeaders = array();
    foreach ($this->_columns as $tableName => $table) {
      if (array_key_exists('fields', $table)) {
        foreach ($table['fields'] as $fieldName => $field) {
          if (CRM_Utils_Array::value('required', $field) ||
              CRM_Utils_Array::value($fieldName, $this->_params['fields'])
          ) {

            if ($fieldName == 'email') {
              $this->_emailField = TRUE;
            }
            if ($fieldName == 'display_name_lcal_rep') {
              $this->_localRepField = TRUE;
              $select[] = "{$this->_aliases['civicrm_contact_local_rep']}.id as local_rep_id";
              $this->_columnHeaders["local_rep_id"] = array(
                'type' => 'int',
                'no_display' => true,
              );
            }
            $select[] = "{$field['dbAlias']} as {$tableName}_{$fieldName}";
            $this->_columnHeaders["{$tableName}_{$fieldName}"]['type'] = CRM_Utils_Array::value('type', $field);
            $this->_columnHeaders["{$tableName}_{$fieldName}"]['title'] = CRM_Utils_Array::value('title', $field);
          }
        }
      }
    }

    $this->_select = "SELECT " . implode(', ', $select) . " ";
  }

  function from() {
    $contact_side = 'contact_id_a';
    if ($this->_params['user_side_value'] == 2) {
      $contact_side = 'contact_id_b';
    }
    $this->_from = "
        FROM civicrm_contact {$this->_aliases['civicrm_contact']}
             {$this->_aclFrom} ";

    $this->_from .= "
            INNER  JOIN civicrm_address {$this->_aliases['civicrm_address']}
                         ON ( {$this->_aliases['civicrm_address']}.contact_id =
                               {$this->_aliases['civicrm_contact']}.id AND
                               {$this->_aliases['civicrm_address']}.is_primary = 1 ) ";
    
    
    $pumCountry = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'pumCountry'));
    $pumCountryField = civicrm_api3('CustomField', 'getsingle', array('custom_group_id' => $pumCountry['id'], 'name' => 'civicrm_country_id'));
                               
    $this->_from .= " INNER JOIN {$pumCountry['table_name']} country_contact
                        ON (country_contact.{$pumCountryField['column_name']} = {$this->_aliases['civicrm_address']}.country_id)";
    
    $cc_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Country Coordinator is', 'return' => 'id'));
    $currentUserContactId = $this->getCurrentUsersContactId();
    $this->_from .= " INNER JOIN civicrm_relationship cc_relationship
                      ON (cc_relationship.relationship_type_id = {$cc_rel_type_id}
                      AND cc_relationship.is_active = 1
                      AND (cc_relationship.start_date IS NULL OR cc_relationship.start_date <= CURDATE())
                      AND (cc_relationship.end_date IS NULL OR cc_relationship.end_date >= CURDATE())
                      AND cc_relationship.contact_id_a = country_contact.entity_id
                      AND cc_relationship.contact_id_b = '{$currentUserContactId}')";
    
    // include Email Field
    if ($this->_emailField) {
      $this->_from .= "
             LEFT JOIN civicrm_email {$this->_aliases['civicrm_email']}
                       ON ( {$this->_aliases['civicrm_contact']}.id =
                            {$this->_aliases['civicrm_email']}.contact_id AND
                            {$this->_aliases['civicrm_email']}.is_primary = 1 )";
    }

    if ($this->_localRepField) {
      $local_rep_relation_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Representative', 'return' => 'id'));
      $this->_from .= " LEFT JOIN civicrm_relationship {$this->_aliases['civicrm_relationship_local_rep']} ON (
        {$this->_aliases['civicrm_relationship_local_rep']}.relationship_type_id = '{$local_rep_relation_type_id}'
                AND {$this->_aliases['civicrm_relationship_local_rep']}.contact_id_a = {$this->_aliases['civicrm_contact']}.id
                AND (
                  {$this->_aliases['civicrm_relationship_local_rep']}.is_active = '1' 
                  AND ({$this->_aliases['civicrm_relationship_local_rep']}.start_date IS NULL OR {$this->_aliases['civicrm_relationship_local_rep']}.start_date <= NOW()) 
                  AND ({$this->_aliases['civicrm_relationship_local_rep']}.end_date IS NULL OR {$this->_aliases['civicrm_relationship_local_rep']}.end_date >= NOW())
               )
      )";
      $this->_from .= " LEFT JOIN civicrm_contact {$this->_aliases['civicrm_contact_local_rep']} ON (
        {$this->_aliases['civicrm_relationship_local_rep']}.contact_id_b = {$this->_aliases['civicrm_contact_local_rep']}.id
          )";
    }
  }

  function getCurrentUsersContactId() {
    $uf_id = CRM_Utils_System::getLoggedInUfID();
    $domain_id = CRM_Core_Config::domainID();
    $cid = civicrm_api3('UFMatch', 'getvalue', array('domain_id' => $domain_id, 'uf_id' => $uf_id, 'return' => 'contact_id'));
    return $cid;
  }

  function where() {

    $whereClauses = $havingClauses = array();
    foreach ($this->_columns as $tableName => $table) {
      if (array_key_exists('filters', $table)) {
        foreach ($table['filters'] as $fieldName => $field) {

          $clause = NULL;
          if (CRM_Utils_Array::value('type', $field) & CRM_Utils_Type::T_DATE) {
            $relative = CRM_Utils_Array::value("{$fieldName}_relative", $this->_params);
            $from = CRM_Utils_Array::value("{$fieldName}_from", $this->_params);
            $to = CRM_Utils_Array::value("{$fieldName}_to", $this->_params);

            $clause = $this->dateClause($field['name'], $relative, $from, $to, $field['type']);
          } else {
            $op = CRM_Utils_Array::value("{$fieldName}_op", $this->_params);
            if ($op) {
                $clause = $this->whereClause($field, $op, CRM_Utils_Array::value("{$fieldName}_value", $this->_params), CRM_Utils_Array::value("{$fieldName}_min", $this->_params), CRM_Utils_Array::value("{$fieldName}_max", $this->_params));
            }
          }

          if (!empty($clause)) {
            if (CRM_Utils_Array::value('having', $field)) {
              $havingClauses[] = $clause;
            } else {
              $whereClauses[] = $clause;
            }
          }
        }
      }
    }

    if (empty($whereClauses)) {
      $this->_where = 'WHERE ( 1 ) ';
      $this->_having = '';
    } else {
      $this->_where = 'WHERE ' . implode(' AND ', $whereClauses);
    }

    if ($this->_aclWhere) {
      $this->_where .= " AND {$this->_aclWhere} ";
    }

    if (!empty($havingClauses)) {
      // use this clause to construct group by clause.
      $this->_having = 'HAVING ' . implode(' AND ', $havingClauses);
    }
  }

  function statistics(&$rows) {
    $statistics = parent::statistics($rows);

    $isStatusFilter = FALSE;
    $relStatus = NULL;
    if (CRM_Utils_Array::value('is_active_value', $this->_params) == '1') {
      $relStatus = 'Is equal to Active';
    } elseif (CRM_Utils_Array::value('is_active_value', $this->_params) == '0') {
      $relStatus = 'Is equal to Inactive';
    }
    if (CRM_Utils_Array::value('filters', $statistics)) {
      foreach ($statistics['filters'] as $id => $value) {
        //for displaying relationship type filter
        if ($value['title'] == 'Relationship') {
          $relTypes = CRM_Core_PseudoConstant::relationshipType();
          $statistics['filters'][$id]['value'] = 'Is equal to ' . $relTypes[$this->_params['relationship_type_id_value']]['label_' . $this->relationType];
        }

        //for displaying relationship status
        if ($value['title'] == 'Relationship Status') {
          $isStatusFilter = TRUE;
          $statistics['filters'][$id]['value'] = $relStatus;
        }
      }
    }
    //for displaying relationship status
    if (!$isStatusFilter && $relStatus) {
      $statistics['filters'][] = array(
        'title' => 'Relationship Status',
        'value' => $relStatus,
      );
    }
    return $statistics;
  }

  function groupBy() {
    $this->_groupBy = " ";
    $groupBy = array();

    if (!empty($groupBy)) {
      $this->_groupBy = " GROUP BY  " . implode(', ', $groupBy) . " ,  {$this->_aliases['civicrm_contact']}.id ";
    } else {
      $this->_groupBy = " GROUP BY {$this->_aliases['civicrm_contact']}.id ";
    }
  }

  function orderBy() {
    $this->_orderBy = " ORDER BY {$this->_aliases['civicrm_contact']}.sort_name";
  }

  function postProcess() {
    $this->beginPostProcess();

    $this->relationType = NULL;
    $relType = array();
    if (CRM_Utils_Array::value('relationship_type_id_value', $this->_params)) {
      $relType = explode('_', $this->_params['relationship_type_id_value']);

      $this->relationType = $relType[1] . '_' . $relType[2];
      $this->_params['relationship_type_id_value'] = intval($relType[0]);
    }

    $this->buildACLClause(array($this->_aliases['civicrm_contact']));
    $sql = $this->buildQuery();
    
    $rows = array();
    $this->buildRows($sql, $rows);

    $this->formatDisplay($rows);
    $this->doTemplateAssignment($rows);

    if (!empty($relType)) {
      // store its old value, CRM-5837
      $this->_params['relationship_type_id_value'] = implode('_', $relType);
    }
    $this->endPostProcess($rows);
  }

  function alterDisplay(&$rows) {
    // custom code to alter rows
    $entryFound = FALSE;

    foreach ($rows as $rowNum => $row) {

      // handle country
      if (array_key_exists('civicrm_address_country_id', $row)) {
        if ($value = $row['civicrm_address_country_id']) {
          $rows[$rowNum]['civicrm_address_country_id'] = CRM_Core_PseudoConstant::country($value, FALSE);
        }
        $entryFound = TRUE;
      }
      
      if (array_key_exists('civicrm_address_county_id', $row)) {
        if ($value = $row['civicrm_address_county_id']) {
          $rows[$rowNum]['civicrm_address_countr_id'] = CRM_Core_PseudoConstant::county($value, FALSE);
        }
        $entryFound = TRUE;
      }

      if (array_key_exists('civicrm_address_state_province_id', $row)) {
        if ($value = $row['civicrm_address_state_province_id']) {
          $rows[$rowNum]['civicrm_address_state_province_id'] = CRM_Core_PseudoConstant::stateProvince($value, FALSE);
        }
        $entryFound = TRUE;
      }

      if (array_key_exists('civicrm_contact_display_name', $row) &&
          array_key_exists('civicrm_contact_id', $row)
      ) {
        $url = CRM_Utils_System::url('civicrm/contact/view', 'reset=1&cid=' . $row['civicrm_contact_id']);
        $rows[$rowNum]['civicrm_contact_display_name_link'] = $url;
        $rows[$rowNum]['civicrm_contact_display_name_hover'] = ts("View Contact details for this contact.");
        $entryFound = TRUE;
      }

      if (array_key_exists('civicrm_contact_local_rep_display_name_lcal_rep', $row) &&
          array_key_exists('local_rep_id', $row)
      ) {
        $url = CRM_Utils_System::url('civicrm/contact/view', 'reset=1&cid=' . $row['local_rep_id']);
        $rows[$rowNum]['civicrm_contact_local_rep_display_name_lcal_rep_link'] = $url;
        $rows[$rowNum]['civicrm_contact_local_rep_display_name_lcal_rep_hover'] = ts("View Contact details for this contact.");
        $entryFound = TRUE;
      }

      // skip looking further in rows, if first row itself doesn't
      // have the column we need
      if (!$entryFound) {
        break;
      }
    }
  }

}
