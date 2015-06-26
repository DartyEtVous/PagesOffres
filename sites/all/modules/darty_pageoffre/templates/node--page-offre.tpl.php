<div id="header_mobile"><div onClick="window.open('http://www.darty.com','_self'); return false;" class="header_mobile_logo"></div></div>
<div id="offre-wrapper" class="type-<?php print $pageOffre->getType(); ?><?php print ($pageOffre->hasDecalage()) ? ' decal' : ' nondecal'; ?>">
    <?php if ($pageOffre->hasBanniere()) { ?>
        <div id="banniere">
            <?php if ($pageOffre->hasLinkBanniere()) { ?>
                <a href="<?php print $pageOffre->getUrlBanniere(); ?>" 
                   title="<?php print $pageOffre->getAltBanniere(); ?>"
                   <?php if ($pageOffre->hasTargetLinkBanniereBlank()) { ?>target="_blank"<?php } ?>
                   >
                   <?php } ?>
                <img src="<?php print $pageOffre->getSrcBanniere(); ?>" border="0" alt="<?php print $pageOffre->getAltBanniere(); ?>"/>
                <?php if ($pageOffre->hasLinkBanniere()) { ?></a><?php } ?>
        </div>
    <?php } ?>
    <?php if ($pageOffre->hasIntroduction()) { ?>
        <div id="introduction"><?php print $pageOffre->getIntroduction(); ?></div>
    <?php } ?>
    <div id="blocs-offre">
        <?php
        $blocs = $pageOffre->getBlocs();
        $i = 0;
        foreach ($blocs as $bloc) {
            ?>
            <div class="bloc-offre <?php print ($i++ % 2) ? 'odd' : 'even'; ?>"><?php print $bloc->renderBloc(); ?></div>
        <?php } ?>
        <div class="clear"></div>
    </div>
</div>