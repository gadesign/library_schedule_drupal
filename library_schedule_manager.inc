<?php
/*
 * Interface for managing entries and exception
 */

function library_schedule_manager () {
    drupal_add_css(drupal_get_path('module','library_schedule') . '/css/manager.css');
    $entries = library_schedule_get_entries();
    $exceptions = library_schedule_get_exceptions();
    $groups = library_schedule_get_groups();
    
    //krumo($exceptions);
    $html = '<h2 class="table-heading">Entries</h2>';
    $html .= '<div class="add-new"><a href="' . base_path() . 
            'node/add/library-hours-entry?destination=admin/config/library_schedule/manager">Add New Entry</a></div>';
    $html .= '<table class="manager-table">' .
            '<thead>' .
            '<tr><th>Term</th><th>Date Range</th><th>Group</th><th>Operations</th></tr>' .
            '</thead>';
            foreach ($entries as $tax => $group) {
                foreach ($group as $entry) {
                $name = $entry['node']->title;
                $date_range = $entry['node']->lhe_start_date['und'][0]['safe_value'] . ' - ' .
                        $entry['node']->lhe_end_date['und'][0]['safe_value'];
                $edit_link = '<a href="' . base_path() . 'node/' .$entry['node']->nid . '/edit?destination=admin/config/library_schedule/manager">Edit</a>';
                $delete_link = '<a href="' . base_path() . 'node/' .$entry['node']->nid . '/delete?destination=admin/config/library_schedule/manager">Remove</a>';
                $html .= '<tr><td>' . $name . '</td><td>' . $date_range . '</td><td>' . $tax . 
                        '</td><td>' . $edit_link . ' | ' . $delete_link . '</tr>';
            }
            }
            $html .= '</table>';
                
    $html .= '<h2 class="table-heading">Exceptions</h2>';
    $html .= '<div class="add-new"><a href="' . base_path() . 
            'node/add/library-hours-exception?destination=admin/config/library_schedule/manager">Add New Exception</a></div>';
    $html .= '<table class="manager-table">' .
            '<thead>' .
            '<tr><th>Exception</th><th>Date Range</th><th>Group</th><th>Operations</th></tr>' .
            '</thead>';
    $html .= '<tbody>';
            foreach ($exceptions as $tax => $group) {
                foreach ($group as $entry) {
                $name = $entry['node']->title;
                $date_range = $entry['node']->lhe_exception_start_date['und'][0]['safe_value'] . ' - ' .
                        $entry['node']->lhe_exception_end_date['und'][0]['safe_value'];
                $edit_link = '<a href="' . base_path() . 'node/' .$entry['node']->nid . '/edit?destination=admin/config/library_schedule/manager">Edit</a>';
                $delete_link = '<a href="' . base_path() . 'node/' .$entry['node']->nid . '/delete?destination=admin/config/library_schedule/manager">Remove</a>';
                $html .= '<tr><td>' . $name . '</td><td>' . $date_range . '</td><td>' . $tax . 
                        '</td><td>' . $edit_link . ' | ' . $delete_link . '</tr>';
            }
            }
    $html .= '</tbody>';
            $html .= '</table>';
            
    return $html;
}