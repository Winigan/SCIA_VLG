#include <iostream>

#include "Graph.hpp"

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Le graphe est attendu en argument" << std::endl;
        return 1;
    }
    
    auto a = Graph("data/graph/p2p-Gnutella08.txt");
    a.load();
    return 0;
}
