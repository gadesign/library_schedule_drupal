<?php
/**
 * Form for Library Schedule settings.
 */
function library_schedule_settings_form($form, &$form_state) {
    $form['library_schedule_settings']= array(
        '#type' => 'fieldset',
        '#title' => t('Settings'),
        '#description' => t('Adjust settings for Library Schedule module.'),
    );
    
    $form['library_schedule_settings']['library_schedule_default_hours']= array(
        '#type' => 'fieldset',
        '#title' => t('Default Hours'),
        '#description' => t('Enter a valid time or Closed for both fields.'),
    );
    
     $form['library_schedule_settings']['library_schedule_default_hours']['library_schedule_default_open'] = array(
        '#type' => 'textfield',
        '#title' => t('Opening Time'),
        '#default_value' => variable_get('library_schedule_default_open', '7:30am'),
        '#description' => t("Enter a valid opening time or Closed."),
        '#required' => TRUE,
    );
    
    $form['library_schedule_settings']['library_schedule_default_hours']['library_schedule_default_close'] = array(
        '#type' => 'textfield',
        '#title' => t('Closing Time'),
        '#default_value' => variable_get('library_schedule_default_close', '10:00pm'),
        '#description' => t("Enter a valid opening time or Closed."),
        '#required' => TRUE,
    );
    
    return(system_settings_form($form));
}

/**
 * Implements hook_validate().
 */
function library_schedule_settings_form_validate($form, &$form_state) {
    //Validate default hours
    $open_delta = 'library_schedule_default_open';
    $close_delta = 'library_schedule_default_close';
     if ((strtolower($form_state['values'][$open_delta]) != 'closed')&&
       (strtotime($form_state['values'][$open_delta]) == FALSE)) {
        form_set_error($open_delta, t('Please enter a valid time of day or "Closed"'));
    }
    
    if ((strtolower($form_state['values'][$close_delta]) != 'closed')&&
       (strtotime($form_state['values'][$close_delta]) == FALSE)) {
        form_set_error($close_delta, t('Please enter a valid time of day or "Closed"'));
    }
    // OPening time can be no later than closing time or closed.
    if ((strtotime($form_state['values'][$open_delta])) >=
       (strtotime($form_state['values'][$close_delta]))) {
        if(strtolower($form_state['values'][$open_delta])!= 'closed' &&
            strtolower($form_state['values'][$close_delta])!= 'closed') {
            form_set_error($open_delta, t('The opening time must be sooner than the closing time.'));
        }
       }
    
    if ((strtolower($form_state['values'][$open_delta]) == 'closed')xor
        (strtolower($form_state['values'][$close_delta]) == 'closed')) {
        if (strtolower($form_state['values'][$open_delta]) == 'closed') {
        form_set_error($open_delta, t('Both fields must be set to "Closed" or a valid time.'));
        } else {
            form_set_error($close_delta, t('Both fields must be set to "Closed" or a valid time.'));
        }
    }
}