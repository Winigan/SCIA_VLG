# Supprime toutes les lignes commençant par un # dans les edgeslists des graphes
sed -i  '' '/^#/d' data/graph/*.txt