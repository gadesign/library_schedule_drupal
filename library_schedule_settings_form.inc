<?php
/**
 * Form for library hours settings.
 */
function library_hours_settings_form($form) {
    
    $form['library_hours_default_hours']= array(
        '#type' => 'fieldset',
        '#title' => t('Default Hours'),
        '#description' => t('Enter a valid time or Closed for both fields.'),
    );
    
    $form['library_hours_default_hours']['library_hours_default_open'] = array(
        '#type' => 'textfield',
        '#title' => t('Opening Time'),
        '#default_value' => variable_get('library_hours_default_open', '7:30am'),
        '#description' => t("Enter a valid opening time or Closed."),
        '#required' => TRUE,
    );
    
    $form['library_hours_default_hours']['library_hours_default_close'] = array(
        '#type' => 'textfield',
        '#title' => t('Closing Time'),
        '#default_value' => variable_get('library_hours_default_close', '10:00pm'),
        '#description' => t("Enter a valid opening time or Closed."),
        '#required' => TRUE,
    );
    
    $vocab = taxonomy_vocabulary_machine_name_load('lh_group');
    $terms = taxonomy_term_load_multiple(array(), array('vid' => $vocab->vid));
    usort($terms,"library_hours_sort_terms");
    $form['library_hours_sortable_list']['#tree'] = true;
    foreach ($terms as $term) {
        $form['library_hours_sortable_list'][$term->tid] = array(
            'group' => array(
                '#markup' => check_plain($term->name),
            ),
            'weight' => array(
                '#type' => 'weight',
                '#title' => t('Order'),
                '#default_value' => $term->weight,
                '#delta' => 10,
                '#title_display' => 'invisible',
            ),
        );
    }
    
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' =>'submit', 
        '#value' => t('Save Changes'),
        );
    return $form;
}

function library_hours_sort_terms($a,$b) {
    if($a->weight == $b->weight){
        return 0;
    }
    return ($a->weight < $b->weight) ? -1 : 1;
}
function theme_library_hours_settings_form($variables) {
    $form = $variables['form'];
    $rows = array();
    foreach (element_children($form['library_hours_sortable_list']) as $termID) {
        $form['library_hours_sortable_list'][$termID]['weight']['#attributes']['class'] = array('group-item-weight');
        $rows[] = array(
            'data' => array(
                drupal_render($form['library_hours_sortable_list'][$termID]['group']),
                drupal_render($form['library_hours_sortable_list'][$termID]['weight']),
            ),
            'class' => array('draggable'),
        );
    }
    $header = array(t('Tab Group'),t('Weight'));
    $table_id = 'tab-group-table';
    $output = theme('table', array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => array('id' => $table_id),
    ));
    $output .= drupal_render_children($form);
    drupal_add_tabledrag($table_id, 'order', 'sibling', 'group-item-weight');
    return $output;
}
/**
 * Implements hook_validate().
 */
function library_hours_settings_form_validate($form, &$form_state) {
    //Validate default hours
    $open_delta = 'library_hours_default_open';
    $close_delta = 'library_hours_default_close';
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

function library_hours_settings_form_submit(&$form_state) {
    $vocab = taxonomy_vocabulary_machine_name_load('lh_group');
    $terms = taxonomy_term_load_multiple(array(), array('vid' => $vocab->vid));
    
    foreach($terms as $term) {
        $term->weight = $form_state['library_hours_sortable_list'][$term->tid]['weight']['#value'];
        taxonomy_term_save($term);
    }
    
    
    $open_time = $form_state['library_hours_settings']['library_hours_default_hours']['library_hours_default_open']['#value'];
    $close_time = $form_state['library_hours_settings']['library_hours_default_hours']['library_hours_default_close']['#value'];
    variable_set('library_hours_default_open', $open_time);
    variable_set('library_hours_default_close', $close_time);
}