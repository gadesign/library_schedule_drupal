jQuery(document).ready(function($){
  $( "#sortable-groups" ).sortable({
      update: function () {
          //alert(window.location.pathname);
          var sortablePath = window.location.pathname + "/sortable.php";
          $.ajax({
              url: sortablePath,
              data: $('ul#sortable-groups').sortable('serialize'),
              success: function(r) {
                  console.log(r);
              }
          });     
      }
  });
});
