/**
 * @file
 * Javascript behaviors for the Book module.
 */(function(a){Drupal.behaviors.bookFieldsetSummaries={attach:function(b){a("fieldset.book-outline-form",b).drupalSetSummary(function(b){var c=a(".form-item-book-bid select"),d=c.val();return d==="0"?Drupal.t("Not in book"):d==="new"?Drupal.t("New book"):Drupal.checkPlain(c.find(":selected").text())})}}})(jQuery);