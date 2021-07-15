#include <iostream>
#include <ctime>
#include "Graph.hpp"
#include <cstring>

int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        std::cerr << "Le graphe est attendu en argument ainsi que l'orientation du graph" << std::endl;
        return 1;
    }
    
    auto a = Graph(argv[1]);

	a.load(strcmp(argv[2],"true") == 0);

    a.compute_wcc();

    std::cout << igraph_vector_size(a.get_wcc()) << "\n";

    time_t current = time(NULL);

    igraph_vector_t bd_eccentri = a.bounding_eccentricities();

    std::cout << "Bounding eccentricities took : " << time(NULL) - current << " seconds\n";

    double max_eccentri = igraph_vector_max(&bd_eccentri);

    std::cout << "Ecentricity max = " << max_eccentri << "\n";

    return 0;
}
