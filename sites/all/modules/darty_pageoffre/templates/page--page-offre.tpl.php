<div id="page-wrapper">
    <div id="page">
        <div id="header">
            <?php print render($page['header']); ?>
        </div>
        <?php print $messages; ?>
        <div id="content" class="offre">
            <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
            <div id="contenu-wrapper">
                <?php print render($page['content']); ?>
            </div>
        </div>
    </div>
</div>
<div id="footer">
    <?php print render($page['footer']); ?>
</div>