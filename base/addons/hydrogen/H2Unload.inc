$ifi %bb2%==yes $if     EXIST '../addons/Hydrogen/H2STOVOL_START.gdx' $execute_unload '../../addons/Hydrogen/H2STOVOL_START.gdx',H2STOVOL_START;
$ifi %bb2%==yes $if not EXIST '../addons/Hydrogen/H2STOVOL_START.gdx' $execute_unload '../../base/addons/Hydrogen/H2STOVOL_START.gdx',H2STOVOL_START;


