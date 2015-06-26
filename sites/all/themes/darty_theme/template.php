<?php
/**
 * Implementation of template_preprocess_html
 */
function darty_theme_preprocess_html(&$variables) {
    //Add a specific html template to the list for each node type.
    //Usefull for the newsletter in order to have a simple HTML with only the content
    if ($node = menu_get_object()) {
        $variables ['theme_hook_suggestions'] [] = 'html__' . $node->type;
    }

}

/**
 * Implementation of template_preprocess_page
 */
function darty_theme_preprocess_page(&$variables) {
   
    //Add a specific page template to the list for each node type.
    //Usefull for the newsletter in order to have a simple HTML with only the content
    if ($node = menu_get_object()) {
        $variables ['theme_hook_suggestions'] [] = 'page__' . $node->type;
    }
}

function darty_theme_sdl_editor_legend($variables) {
    return "";
}