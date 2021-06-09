#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <igraph/igraph.h>

class Graph {
    public:
        Graph(const std::string&);
        bool load(const std::string);
        std::string get_type();
    private:
        bool _type; // False is directed, True is undirected
        igraph_t* graph;
        void read_type(const std::string&);
        bool load_directed(const std::string);
        bool load_undirected(const std::string);
};

#endif /* GRAPH_H */
