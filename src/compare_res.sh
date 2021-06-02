#!/bin/sh

if [ "$#" -ne 3 ]; then
    echo "Erreur le script prend 3 arguments en entrée : path_teexgraph_exec path_custom_exec path_to_network"
fi

# Run the code of teexGraph and store the result in teexG_res
echo $(\time -f "mem=%K RSS=%M elapsed=%E cpu.sys=%S .user=%U" ./$1 $3) > teexG_res

# Run our code and store the result in my_res
echo $(\time -f "mem=%K RSS=%M elapsed=%E cpu.sys=%S .user=%U" ./$2 $3) > my_res

diff "my_res" "teexG_res"