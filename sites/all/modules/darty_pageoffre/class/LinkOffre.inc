<?php

class LinkOffre {

    private $bold = false;
    private $underline = false;
    private $size = 12;
    private $color = '#000000';
    private $bgColor = 'transparent';
    private $url = '';
    private $text = '';
    private $target = '';

    function __construct($objLink) {
        $link_wrapper = entity_metadata_wrapper('field_collection_item', $objLink);
        $this->bold = $link_wrapper->field_link_gras->value();
        $this->underline = $link_wrapper->field_link_souligne->value();
        $this->size = $link_wrapper->field_link_size->value();
        $this->color = $link_wrapper->field_link_color_font->value();
        $this->bgColor = $link_wrapper->field_link_color_bg->value();

        $link_field = $objLink->field_link_lien;
        if (isset($link_field[LANGUAGE_NONE][0]['url']) && !empty($link_field[LANGUAGE_NONE][0]['url'])) {
            $this->url = $link_field[LANGUAGE_NONE][0]['url'];
            $this->text = $link_field[LANGUAGE_NONE][0]['title'];
            if (isset($link_field[LANGUAGE_NONE][0]['attributes']['target']) && !empty($link_field[LANGUAGE_NONE][0]['attributes']['target'])) {
                $this->target = $link_field[LANGUAGE_NONE][0]['attributes']['target'];
            }
        }
    }

    function hasLink() {
        return (!empty($this->url)) ? true : false;
    }

    function isBold() {
        return $this->bold;
    }

    function isUnderline() {
        return $this->underline;
    }

    function hasColor() {
        return (isset($this->color['rgb']) && !empty($this->color['rgb'])) ? true : false;
    }

    function getColor() {
        return $this->color['rgb'];
    }

    function hasBgColor() {
        return (isset($this->bgColor['rgb']) && !empty($this->bgColor['rgb'])) ? true : false;
    }

    function getBgColor() {
        return $this->bgColor['rgb'];
    }

    function getSize() {
        return $this->size;
    }

    function getText() {
        return $this->text;
    }

    function getUrl() {
        return $this->url;
    }

    function hasTarget() {
        return (!empty($this->target) && $this->target == '_blank') ? true : false;
    }

    private function getStyleCss() {
        $style = '';
        if ($this->isBold()) {
            $style .= 'font-weight : bold; ';
        }
        if ($this->isUnderline()) {
            $style .= 'text-decoration : underline; ';
        }
        $style .= 'font-size: ' . $this->size . 'px; ';
        if ($this->hasColor()) {
            $style .= 'color: ' . $this->getColor() . '; ';
        }
        if ($this->hasBgColor()) {
            $style .= 'background-color: ' . $this->getBgColor() . '; ';
        }
        return 'style="' . $style . '"';
    }

    function getFullLink() {
        if ($this->hasLink()) {
            $target = ($this->hasTarget()) ? 'target="_blank"' : '';
            return '<a href="' . $this->url . '" title="' . $this->text . '" ' . $target . ' ' . $this->getStyleCss() . '>' . $this->text . '</a>';
        }
        return '';
    }

}
