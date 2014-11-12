    <div class="todays-hours-container">
        
        <div class="todays-hours">
            <p><?php print date('l F jS, Y'); ?></p>
            <?php if($library_open) : ?>
            <p>The library is currently open.</p>
            <p>The library will close at <?php print $close_time; ?>.</p>
            <?php endif;?>

            <?php if(!$library_open && $closed_for_exception != TRUE) : ?>
            <p>The library is closed.</p>
            <?php endif; ?>

            <?php if(!$library_open && $closed_for_exception) : ?>
            <p>The library is closed to due to <?php print $exception_name; ?>
            <?php endif; ?>
            
        </div>
        <div class="vector-clock"></div>
    </div>
