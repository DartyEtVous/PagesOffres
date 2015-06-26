<?php

/**
 * Classe permettant de regrouper les infos et les méthodes d'une page offre (à partir de l'objet fournit par drupal)
 */
class Pageoffre {

    private $srcBanniere = "";
    private $altBanniere = "";
    private $urlBanniere = "";
    private $targetBanniere = "";
    private $srcBg = "";
    private $colorBg = "#FFFFFF";
    private $bool_decalage = 0;
    private $srcHabillage = "";
    private $type = 1;
    private $introduction = "";
    private $meta_desc = "";
    private $blocs = array();
    private $node = false;

    function __construct($obj_pageoffre) {
        $this->node = $obj_pageoffre;
    }

    function initialise() {
        $wrapper = entity_metadata_wrapper('node', $this->node);

        $this->type = $wrapper->field_pageoffre_type->value();
        $this->introduction = $wrapper->field_pageoffre_introduction->value();
        $this->meta_desc = $wrapper->field_pageoffre_meta->value();

        //bannière
        $imageObj = $wrapper->field_pageoffre_image_banniere->value();
        if (isset($imageObj)) {
            $obj_atom = scald_atom_load($imageObj->sid);
            if (isset($obj_atom) && isset($obj_atom->scald_thumbnail[LANGUAGE_NONE][0])) {
                $this->srcBanniere = file_create_url_relative($obj_atom->scald_thumbnail[LANGUAGE_NONE][0]['uri']);
                $this->altBanniere = $obj_atom->scald_thumbnail[LANGUAGE_NONE][0]['alt'];
            }
        }
        $link_banniere = $this->node->field_pageoffre_lien_banniere;
        if (isset($link_banniere[LANGUAGE_NONE][0]['display_url']) && !empty($link_banniere[LANGUAGE_NONE][0]['display_url'])) {
            $this->urlBanniere = $link_banniere[LANGUAGE_NONE][0]['display_url'];
            if (isset($link_banniere[LANGUAGE_NONE][0]['attributes']['target']) && !empty($link_banniere[LANGUAGE_NONE][0]['attributes']['target'])) {
                $this->targetBanniere = $link_banniere[LANGUAGE_NONE][0]['attributes']['target'];
            }
        }

        //background
        $colorBg = $wrapper->field_pageoffre_color_background->value();
        $this->colorBg = $colorBg['rgb'];

        $imageBgObj = $wrapper->field_pageoffre_image_background->value();
        if (isset($imageBgObj)) {
            $obj_bg_atom = scald_atom_load($imageBgObj->sid);
            if (isset($obj_bg_atom) && isset($obj_bg_atom->scald_thumbnail[LANGUAGE_NONE][0])) {
                $this->srcBg = file_create_url_relative($obj_bg_atom->scald_thumbnail[LANGUAGE_NONE][0]['uri']);
            }
        }
        $this->bool_decalage = $wrapper->field_pageoffre_decalage_bg->value();


        //habillage
        $imageHabillageObj = $wrapper->field_pageoffre_image_habillage->value();
        if (isset($imageHabillageObj)) {
            $obj_habillage_atom = scald_atom_load($imageHabillageObj->sid);
            if (isset($obj_habillage_atom) && isset($obj_habillage_atom->scald_thumbnail[LANGUAGE_NONE][0])) {
                $this->srcHabillage = file_create_url_relative($obj_habillage_atom->scald_thumbnail[LANGUAGE_NONE][0]['uri']);
            }
        }

        //blocs
        $blocs = $wrapper->field_blocs_item->value();
        foreach ($blocs as $bloc) {
            if ($bloc->status == 1) {
                $this->blocs[] = new BlocOffre($bloc);
            }
        }
    }

    function hasDecalage() {
        return ($this->bool_decalage) ? true : false;
    }

    function getMetaDesc() {
        return $this->meta_desc;
    }

    function hasIntroduction() {
        return (isset($this->introduction['value']) && !empty($this->introduction['value'])) ? true : false;
    }

    function getIntroduction() {
        if (isset($this->introduction['value'])) {
            return $this->introduction['value'];
        }
        return '';
    }

    function getType() {
        return $this->type;
    }

    function hasLinkBanniere() {
        return (!empty($this->urlBanniere)) ? true : false;
    }

    function hasTargetLinkBanniereBlank() {
        return (!empty($this->targetBanniere) && $this->targetBanniere == '_blank') ? true : false;
    }

    function getUrlBanniere() {
        return $this->urlBanniere;
    }

    function getTargetBanniere() {
        return $this->targetBanniere;
    }

    function hasBanniere() {
        return (!empty($this->srcBanniere)) ? true : false;
    }

    function getSrcBanniere() {
        return $this->srcBanniere;
    }

    function getAltBanniere() {
        return $this->altBanniere;
    }

    function hasBg() {
        return (!empty($this->srcBg)) ? true : false;
    }

    function getSrcBg() {
        return $this->srcBg;
    }

    function getSrcHabillage() {
        return $this->srcHabillage;
    }

    function hasHabillage() {
        return (!empty($this->srcHabillage)) ? true : false;
    }

    function getBlocs() {
        return $this->blocs;
    }

    function prepareCss() {
        if ($this->hasBg()) {
            $output = "#content #offre-wrapper { background: url('" . $this->srcBg . "') no-repeat " . $this->colorBg . "; } ";
        } else {
            $output = "#content #offre-wrapper{ background-color: " . $this->colorBg . "; } ";
        }
        if ($this->hasHabillage()) {
            $output .= "html body{ background-image: url('" . $this->srcHabillage . "') !important; } ";
        }
        $output .= '@media only screen and (max-width: 767px) {
                #header_mobile { display: block; background: #ffffff url(http://www.darty.com/res3/informations/img/top_banner.jpg) top right no-repeat; height: 129px; }
                #header_mobile .header_mobile_logo { background: url(http://www.darty.com/res3/informations/img/logo_darty.png) 10px 25px no-repeat; height: 129px; }
                }';
       
        return $output;
    }

}
