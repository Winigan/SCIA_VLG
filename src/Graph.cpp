#include "Graph.hpp"

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param Path to the graph edge list
 */
Graph::Graph(const std::string& path) {
    _path = path;
    igraph_vector_init(&_wcc, 0);
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

igraph_vector_t* Graph::get_wcc(){
	return &_wcc;
}

std::ostream& operator<<(std::ostream& os, const Graph& g) {
    os << "Graph " << std::filesystem::path(g._path).filename() << "\n";
    os << "type: " << ((igraph_is_directed(&g._graph)) ? "DIRECTED" : "UNDIRECTED") << "\n";
    os << "edges: " << igraph_ecount(&g._graph) << " vert: " << igraph_vcount(&g._graph); 
    return os;
}

void Graph::get_biggest_wcc(igraph_vector_t *membership, igraph_vector_t *csize) {
	int id_biggest_wcc = 0;
	for (int idx = 0; idx < igraph_vector_size(csize); idx++) {
		if (igraph_vector_e(csize, id_biggest_wcc) < igraph_vector_e(csize, idx)) {
			id_biggest_wcc = idx;
		}
		std::cout << "id: " << idx << " size: " << igraph_vector_e(csize, idx) << " biggest :" << id_biggest_wcc << "\n";
	}

	for (int idx = 0; idx < igraph_vector_size(membership); idx++){
		int comp_id = igraph_vector_e(membership, idx);
		
		if (comp_id == id_biggest_wcc) {
			igraph_vector_push_back(&_wcc, idx);	
		}
	}
}

void Graph::compute_wcc() {
	
	igraph_vector_t membership;
	igraph_vector_init(&membership, 1);

	igraph_vector_t csize;
	igraph_vector_init(&csize, 1);

	igraph_clusters(&_graph, &membership, &csize, NULL, IGRAPH_WEAK);

	get_biggest_wcc(&membership, &csize);
}
