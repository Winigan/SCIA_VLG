#include "Graph.hpp"
#include <limits>
#include <ctime>
#include <experimental/random>

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
void Graph::load(igraph_bool_t directed) {
    igraph_read_graph_edgelist(&_graph, std::fopen(_path.c_str(), "r"), 0, directed);
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

int Graph::find_vertice_id(int vertice, igraph_vector_t *vector) {
	bool found = false;
	int idx = 0;
	for (; idx < igraph_vector_size(vector) && !found; idx++) {
		if (igraph_vector_e(vector, idx) == vertice) {
			found = true;	
		}
	}
	return idx - 1;
}

int Graph::select_vertice(igraph_vector_t *vector, igraph_vector_t *degrees) {

	int selected = 0;


	// Select the vertice with the lowest degree
	/*
	for (int idx = 0; idx < igraph_vector_size(vector); idx++) {
		
		if (VECTOR(*degrees)[selected] > VECTOR(*degrees)[idx]) {
			selected = idx;
		}
	}
	*/

	// Select the vertice with the greatest degree
	for (int idx = 0; idx < igraph_vector_size(vector); idx++) {
		
		if (VECTOR(*degrees)[selected] < VECTOR(*degrees)[idx]) {
			selected = idx;
		}
	}

	// Select a random vertice
    	//int idx = std::experimental::randint(0, (int) igraph_vector_size(vector) - 1);
    	return igraph_vector_e(vector, selected);
}

int Graph::compute_eccentricity(igraph_vs_t vertice) {
	igraph_vector_t eccentricity;
	igraph_vector_init(&eccentricity, 1);
	igraph_eccentricity(&_graph, &eccentricity, vertice, IGRAPH_ALL);

	return VECTOR(eccentricity)[0];
}

void Graph::compute_distance(igraph_vs_t src, igraph_vs_t dst, igraph_matrix_t *dist) {
	igraph_shortest_paths(&_graph, dist, src, dst, IGRAPH_ALL);
}

void display_igraph_vector(igraph_vector_t *vector) {
	for (int idx = 0; idx < igraph_vector_size(vector); idx++){
		std::cout << VECTOR(*vector)[idx] << " ";
	}
	std::cout << "\n";
}

igraph_vector_t Graph::bounding_eccentricities() {

	time_t start = time(NULL);
	
	int nb_bfs = 0;

	igraph_vector_t copy_wcc; 
	igraph_vector_copy(&copy_wcc, &_wcc);

	// Size of the greatest weak connex component
	int size_wcc = igraph_vector_size(&_wcc);

	igraph_vector_t eccentri;
	igraph_vector_init(&eccentri, size_wcc);

	igraph_vector_t lower_eccentri;
	igraph_vector_init(&lower_eccentri, size_wcc);
	
	igraph_vector_t upper_eccentri;
	igraph_vector_init(&upper_eccentri, size_wcc);

	// Set the eccentricities vector to 0, -infinity and +infinity
	igraph_vector_null(&eccentri);
	igraph_vector_fill(&lower_eccentri, std::numeric_limits<long int>::min());
	igraph_vector_fill(&upper_eccentri, std::numeric_limits<long int>::max());

	igraph_vector_t degrees;
	igraph_vector_init(&degrees, size_wcc);

	igraph_vs_t vs_wcc;
	igraph_vs_vector(&vs_wcc, &copy_wcc);

	igraph_degree(&_graph, &degrees, vs_wcc, IGRAPH_ALL, false);

	igraph_matrix_t dist;
	igraph_matrix_init(&dist, size_wcc, size_wcc);
	compute_distance(vs_wcc, vs_wcc, &dist);

	start = time(NULL);

	while (igraph_vector_size(&copy_wcc) > 0) {
		int vertice_v = select_vertice(&copy_wcc, &degrees);
		int vertice_v_idx = find_vertice_id(vertice_v, &_wcc);
	
		if (VECTOR(eccentri)[vertice_v_idx] == 0) {	
			igraph_vs_t vs_v;
			igraph_vs_1(&vs_v, vertice_v);

			VECTOR(eccentri)[vertice_v_idx] = compute_eccentricity(vs_v);
			nb_bfs++;
		}
		if (igraph_vector_size(&copy_wcc) % 100 == 0) {
			std::cout << "--- Size of W = " << igraph_vector_size(&copy_wcc) << " It took : " << time(NULL) - start << " seconds\n";
			start = time(NULL);
		}
		for (int idx = 0; idx < igraph_vector_size(&copy_wcc); idx++) {
			

			int vertice_w = igraph_vector_e(&copy_wcc, idx);
			int vertice_w_idx = find_vertice_id(vertice_w, &_wcc);	
			
			double dist_vw = MATRIX(dist, vertice_v_idx, vertice_w_idx);
	
			double max = std::max((double) VECTOR(eccentri)[vertice_v_idx] - dist_vw, dist_vw);
			VECTOR(lower_eccentri)[vertice_w_idx] = std::max((double) VECTOR(lower_eccentri)[vertice_w_idx], max);
			VECTOR(upper_eccentri)[vertice_w_idx] = std::min(VECTOR(upper_eccentri)[vertice_w_idx], VECTOR(eccentri)[vertice_v_idx] + dist_vw);
			
			if (VECTOR(lower_eccentri)[vertice_w_idx] == VECTOR(upper_eccentri)[vertice_w_idx]) {
				
				VECTOR(eccentri)[vertice_w_idx] = VECTOR(lower_eccentri)[vertice_w_idx];
				igraph_vector_remove(&copy_wcc, idx);
				igraph_vector_remove(&degrees, idx);
				idx--;
			}
		}
	}
	std::cout << "Number of BFS : " << nb_bfs << "\n";
	return eccentri;
}
