<?php

class BlocOffre {

    private $id = 0;
    private $srcImage = '';
    private $altImage = '';
    private $urlImage = '';
    private $targetImage = '';
    private $contenu = '';
    private $type = '';
    private $colorBg = '';
    private $links = array();
    private $node = false;

    function __construct($obj_blocoffre) {
        $this->node = $obj_blocoffre;
        $this->id = $obj_blocoffre->nid;
    }

    function initialise() {
        $wrapper = entity_metadata_wrapper('node', $this->node);

        $this->contenu = $wrapper->field_bloc_contenu->value();
        $this->type = $this->node->type;
        $colorBg = $wrapper->field_bloc_color_bg->value();
        $this->colorBg = $colorBg['rgb'];

        $imageObj = $wrapper->field_bloc_image->value();
        if (isset($imageObj)) {
            $obj_atom = scald_atom_load($imageObj->sid);
            if (isset($obj_atom) && isset($obj_atom->scald_thumbnail[LANGUAGE_NONE][0])) {
                $this->srcImage = file_create_url_relative($obj_atom->scald_thumbnail[LANGUAGE_NONE][0]['uri']);
                $this->altImage = $obj_atom->scald_thumbnail[LANGUAGE_NONE][0]['alt'];
            }
        }

        $link_image = $this->node->field_bloc_image_lien;
        if (isset($link_image[LANGUAGE_NONE][0]['display_url']) && !empty($link_image[LANGUAGE_NONE][0]['display_url'])) {
            $this->urlImage = $link_image[LANGUAGE_NONE][0]['display_url'];
            if (isset($link_image[LANGUAGE_NONE][0]['attributes']['target']) && !empty($link_image[LANGUAGE_NONE][0]['attributes']['target'])) {
                $this->targetImage = $link_image[LANGUAGE_NONE][0]['attributes']['target'];
            }
        }

        $links = $wrapper->field_bloc_liens->value();
        foreach ($links as $link) {
            if (isset($link->field_link_lien) && !empty($link->field_link_lien)) {
                $this->links[] = new LinkOffre($link);
            }
        }
    }

    function getLinks() {
        return $this->links;
    }

    function hasColorBg() {
        return (!empty($this->colorBg)) ? true : false;
    }

    function getColorBg() {
        return $this->colorBg;
    }

    function getType() {
        return ($this->type == 'bloc_video') ? 'video' : 'image';
    }

    function hasContenu() {
        return (isset($this->contenu['value']) && !empty($this->contenu['value'])) ? true : false;
    }

    function getContenu() {
        if (isset($this->contenu['value'])) {
            return $this->contenu['value'];
        }
        return '';
    }

    function getId() {
        return $this->id;
    }

    function hasImage() {
        return (!empty($this->srcImage)) ? true : false;
    }

    function getSrcImage() {
        return $this->srcImage;
    }

    function getAltImage() {
        return $this->altImage;
    }

    function hasTargetLinkImageBlank() {
        return (!empty($this->targetImage) && $this->targetImage == '_blank') ? true : false;
    }

    function hasLinkImage() {
        return (!empty($this->urlImage)) ? true : false;
    }

    function getUrlImage() {
        return $this->urlImage;
    }

    function getTargetImage() {
        return $this->targetImage;
    }

    function renderBloc() {
        $node_view = node_view($this->node, 'teaser');
        $rendered_node = drupal_render($node_view);
        return $rendered_node;
    }

    function getParentUrl() {
        $result = db_query('select entity_id from field_revision_field_blocs_item where field_blocs_item_target_id=:nid', array(':nid' => $this->node->nid));
        $nid = $result->fetchColumn();
        if (isset($nid) && !empty($nid)) {
            return 'node/' . $nid;
        }
        return '<front>';
    }

}
