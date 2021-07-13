#include "Graph.hpp"

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param Path to the graph edge list
 */
Graph::Graph(const std::string& path) {
    _path = path;
}

/**
 * @brief Load the graph specified in _path into an igraph_t*
 * 
 * @param path 
 */
void Graph::load() {
    igraph_bool_t t;
    igraph_read_graph_edgelist(&_graph, std::fopen(_path.c_str(), "r"), 0, t);
    std::cout << *this << "\n";
}

/**
 * @brief Récupérer le graphe sous la forme d'un shared pointer
 * 
 * @return std::shared_ptr<igraph_t> 
 */
std::shared_ptr<igraph_t> Graph::get_graph() {
    return std::make_shared<igraph_t>(_graph);
}

std::ostream& operator<<(std::ostream& os, const Graph& g) {
    os << "Graph " << std::filesystem::path(g._path).filename() << "\n";
    os << "type: " << ((igraph_is_directed(&g._graph)) ? "DIRECTED" : "UNDIRECTED") << "\n";
    os << "edges: " << igraph_ecount(&g._graph) << " vert: " << igraph_vcount(&g._graph); 
    return os;
}