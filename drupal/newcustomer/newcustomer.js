(function($) {

    Drupal.behaviors.newcustomer = {
        attach: function(context, settings) {
            // AJAX GET STARTED FORM

            $("select.newcustomer-country-source").change(function() {
                var nid = $('select.newcustomer-country-source option:selected').attr('value');

                // Provide temporary message until results received
                if ($("select.newcustomer-country-coordinator")) {
                    $("select.newcustomer-country-coordinator").html('<option value selected="selected">Retrieving country coordinators, please wait...</option>');

                    // Get the programs for this location
                    $.get('/newcustomer/prefill/country-coordinator/' + nid, null, newcustomer_updateCountryCoordinators);
                }
                if ($("select.newcustomer-local-rep")) {
                    $("select.newcustomer-local-rep").html('<option value selected="selected">Retrieving local reps, please wait...</option>');

                    // Get the programs for this location
                    $.get('/newcustomer/prefill/local-rep/' + nid, null, newcustomer_updateLocalReps);
                }

                return false;
            });
            // END AJAX GET STARTED FORM
        }
    };


    var newcustomer_updateCountryCoordinators = function(response) {
        $("select.newcustomer-country-coordinator").html(response.html_output);
    }
    
    var newcustomer_updateLocalReps = function(response) {
        $("select.newcustomer-local-rep").html(response.html_output);
    }

})(jQuery);
