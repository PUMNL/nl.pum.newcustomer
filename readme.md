# nl.pum.newcustomer

This module provides functionality for the new customer process at PUM.

The following functionality is provided:
- Autofilling of country coordinator and local rep based on the country in a webform
- Creation of a drupal user account as soon as a relationship is created
- Civi report template for Country Coordinators to see their new customers
- Drupal view for local reps and country coordinator to see their new customers
- Drupal view with customer info
- Permission check for 'has authorised' contacts only allowing contacts he/she is authorised for
- Permission check for 'representatives' only allowing contacts he/she is a representative for

To enable the functionality you have to enable the *drupal* module and the *civicrm* extension

# Configuration of the autofill

The country, country coordinator and the local rep all should be select fields on the webform.

To enable the auto fill you have to add a class on the country field with the following value:
- **newcustomer-country-source**

To autofill for country coordinator you have to add a class on this field with the following value:
- **newcustomer-country-coordinator**

To autofill for local rep you have to add a class on this field with the following value:
- **newcustomer-local-rep**

# Configuration of the customer account user creation

You have to link a relationship type to a user role. You can set this up at Administration --> System Settings --> Customer Contact Settings