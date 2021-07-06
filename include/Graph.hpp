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
        friend std::ostream& operator<<(std::ostream&, const Graph&);
    private:
        std::string _path;
        igraph_t _graph;
};

#endif /* GRAPH_H */
