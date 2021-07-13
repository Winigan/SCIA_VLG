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
        void load();
        std::string get_path();
        std::shared_ptr<igraph_t> get_graph();
	igraph_vector_t *get_wcc();
        friend std::ostream& operator<<(std::ostream&, const Graph&);
	void compute_wcc();
    private:
	void get_biggest_wcc(igraph_vector_t *membership, igraph_vector_t *csize);
        std::string _path;
        igraph_t _graph;
	igraph_vector_t _wcc;
};

#endif /* GRAPH_H */
