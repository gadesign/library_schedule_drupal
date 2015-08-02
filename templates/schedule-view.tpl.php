<div id="tabs">
<ul>
<?php foreach ($groups as $group) : ?>
<li><a href="#<?php print $group['name']; ?>">
    <?php print $group['name']; ?>
    <br><span class="group-date">
        <?php print $group['date']['start_date']; ?> - <?php print $group['date']['end_date']; ?>
    </span>
    </a></li>
<?php endforeach; ?>
</ul>
<?php foreach ($groups as $group) : ?>
<div id="<?php print $group['name']; ?>">
<?php foreach ($group['entries'] as $node) : ?>
<div class="schedule-item">
<div class="schedule-item-content <?php print $node->title; ?>">
        <h1><?php print $node->title; ?></h1>
        <span class="entry-date-range">
        <?php print $node->lhe_start_date['und'][0]['value']; ?> - 
        <?php print $node->lhe_end_date['und'][0]['value']; ?> 
        </span>
 
        <table class="library-hours-table">
            <thead>
                <tr>
                    <th>Day</th>
                    <th>Hours</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td class="day">Monday</td>
                    <?php if (strtolower($node->lhe_monday_hours_open['und'][0]['value']) != 'closed') : ?>
                    <td class="hours"><?php print $node->lhe_monday_hours_open['und'][0]['value']; ?> - 
                    <?php print $node->lhe_monday_hours_close['und'][0]['value']; ?></td>
                    <?php endif; ?>
                    <?php if (strtolower($node->lhe_monday_hours_open['und'][0]['value']) == 'closed') : ?>
                    <td class="hours">Closed</td>
                    <?php endif; ?>
                </tr>
                <tr>
                    <td class="day">Tuesday</td>
                    <?php if (strtolower($node->lhe_tuesday_hours_open['und'][0]['value']) != 'closed') : ?>
                    <td class="hours"><?php print $node->lhe_tuesday_hours_open['und'][0]['value']; ?> - 
                    <?php print $node->lhe_tuesday_hours_close['und'][0]['value']; ?></td>
                    <?php endif; ?>
                    <?php if (strtolower($node->lhe_tuesday_hours_open['und'][0]['value']) == 'closed') : ?>
                    <td class="hours">Closed</td>
                    <?php endif; ?>
                </tr>
                <tr>
                    <td class="day">Wednesday</td>
                    <?php if (strtolower($node->lhe_wednesday_hours_open['und'][0]['value']) != 'closed') : ?>
                    <td class="hours"><?php print $node->lhe_wednesday_hours_open['und'][0]['value']; ?> - 
                    <?php print $node->lhe_wednesday_hours_close['und'][0]['value']; ?></td>
                    <?php endif; ?>
                    <?php if (strtolower($node->lhe_wednesday_hours_open['und'][0]['value']) == 'closed') : ?>
                    <td class="hours">Closed</td>
                    <?php endif; ?>
                </tr>
                <tr>
                    <td class="day">Thursday</td>
                    <?php if (strtolower($node->lhe_thursday_hours_open['und'][0]['value']) != 'closed') : ?>
                    <td class="hours"><?php print $node->lhe_thursday_hours_open['und'][0]['value']; ?> - 
                    <?php print $node->lhe_thursday_hours_close['und'][0]['value']; ?></td>
                    <?php endif; ?>
                    <?php if (strtolower($node->lhe_thursday_hours_open['und'][0]['value']) == 'closed') : ?>
                    <td class="hours">Closed</td>
                    <?php endif; ?>
                </tr>
                <tr>
                    <td class="day">Friday</td>
                    <?php if (strtolower($node->lhe_friday_hours_open['und'][0]['value']) != 'closed') : ?>
                    <td class="hours"><?php print $node->lhe_friday_hours_open['und'][0]['value']; ?> - 
                    <?php print $node->lhe_friday_hours_close['und'][0]['value']; ?></td>
                    <?php endif; ?>
                    <?php if (strtolower($node->lhe_friday_hours_open['und'][0]['value']) == 'closed') : ?>
                    <td class="hours">Closed</td>
                    <?php endif; ?>
                </tr>
                <tr>
                    <td class="day">Saturday</td>
                    <?php if (strtolower($node->lhe_saturday_hours_open['und'][0]['value']) != 'closed') : ?>
                    <td class="hours"><?php print $node->lhe_saturday_hours_open['und'][0]['value']; ?> - 
                    <?php print $node->lhe_saturday_hours_close['und'][0]['value']; ?></td>
                    <?php endif; ?>
                    <?php if (strtolower($node->lhe_saturday_hours_open['und'][0]['value']) == 'closed') : ?>
                    <td class="hours">Closed</td>
                    <?php endif; ?>
                </tr>
                <tr>
                    <td class="day">Sunday</td>
                    <?php if (strtolower($node->lhe_sunday_hours_open['und'][0]['value']) != 'closed') : ?>
                    <td class="hours"><?php print $node->lhe_sunday_hours_open['und'][0]['value']; ?> - 
                    <?php print $node->lhe_sunday_hours_close['und'][0]['value']; ?></td>
                    <?php endif; ?>
                    <?php if (strtolower($node->lhe_sunday_hours_open['und'][0]['value']) == 'closed') : ?>
                    <td class="hours">Closed</td>
                    <?php endif; ?>
                </tr>
            </tbody>
        </table>
    </div>
</div> <!--    End of Schedule Item-->

<?php endforeach; ?>
<?php if (isset($group['exceptions'])) : ?>
<div class="exception-container">
<div class="exceptions">
<h1>Exceptions</h1>

<?php foreach ($group['exceptions'] as $node) : ?>
        <p><?php print $node->lhe_exception_start_date['und'][0]['value']; ?> to  
        <?php print $node->lhe_exception_end_date['und'][0]['value']; ?> - Closed for <?php print $node->title; ?></p>
<?php endforeach; ?>
</div>
</div><!--    End of exception-container-->
<?php endif; ?>
</div>
<?php endforeach; ?>
</div>