<div 
  class="type-<?php print $blocOffre->getType();?> bloc-<?php print $blocOffre->getId(); ?> contextual-links-region"
  style="background-color:<?php print ($blocOffre->hasColorBg())?$blocOffre->getColorBg():'transparent';?>"
  >
  <?php print render($title_suffix); ?>
  <div class="image-wrapper">
    <?php if ($blocOffre->hasLinkImage()) { ?>
      <a href="<?php print $blocOffre->getUrlImage(); ?>" 
         title="<?php print $blocOffre->getAltImage(); ?>"
         <?php if ($blocOffre->hasTargetLinkImageBlank()) { ?>target="_blank"<?php } ?>
         >
         <?php } ?>
      <img src="<?php print $blocOffre->getSrcImage(); ?>" border="0" alt="<?php print $blocOffre->getAltImage(); ?>"/>
      <?php if ($blocOffre->hasLinkImage()) { ?></a><?php } ?>
  </div>
  <div class="contenu-wrapper link<?php print count($blocOffre->getLinks());?>">
    <div class="contenu">
      <div class="texte"><?php print $blocOffre->getContenu();?></div>
    </div>
    <?php if (count($blocOffre->getLinks()) > 0){?>
    <div class="links">
      <?php foreach($blocOffre->getLinks() as $link){
        print '<div class="link">'.$link->getFullLink().'</div>';
      }?>
    </div>
    <?php }?>
  </div>
  <div class="clear"></div>
</div>