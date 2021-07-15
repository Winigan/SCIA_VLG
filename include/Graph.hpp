#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <memory>
#include <igraph/igraph.h>

class Graph {
    public:
        Graph(const std::string&);
        void load(igraph_bool_t directed);
        std::string get_path();
        std::shared_ptr<igraph_t> get_graph();
	igraph_vector_t *get_wcc();
        friend std::ostream& operator<<(std::ostream&, const Graph&);
	void compute_wcc();
    	int compute_eccentricity(igraph_vs_t vertice);
	void compute_distance(igraph_vs_t src, igraph_vs_t dst, igraph_matrix_t *dist);
    	igraph_vector_t bounding_eccentricities();
    private:
	int find_vertice_id(int vertice, igraph_vector_t *vector);
	int select_vertice(igraph_vector_t *vector, igraph_vector_t *degrees);
	void get_biggest_wcc(igraph_vector_t *membership, igraph_vector_t *csize);
        std::string _path;
        igraph_t _graph;
	igraph_vector_t _wcc;
};

#endif /* GRAPH_H */
