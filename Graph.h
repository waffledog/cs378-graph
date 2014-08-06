// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <set>

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef unsigned long vertex_descriptor;
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;
        typedef std::set<edge_descriptor>::const_iterator edge_iterator; 
        typedef std::set<vertex_descriptor>::const_iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * @param s : vertex_descriptor, source
         * @param t : vertex_descriptor, target
         * @param g : graph 
         * @return : pair<edge_descriptor, bool>, bool dependent on successful creation of an edge
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor s, vertex_descriptor t, Graph& g) {
            // Allows the transfer of vertices from one graph to the other
            while(g._v.size() <= s)
                add_vertex(g);
            while(g._v.size() <= t) 
                add_vertex(g);

            edge_descriptor e = std::make_pair(s, t); 
            std::pair<adjacency_iterator, bool> a = g._g[s].insert(t);
            if(a.second) 
                g._e.insert(e);
            return std::make_pair(e, a.second);
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * @param g : reference to a graph
         * @return v : new vertex that was added
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            vertex_descriptor v = g._g.size(); // ! new vertex value is the size of the graph
            g._v.push_back(v); //added vertex to graph vertices container
            g._g.push_back(std::set<vertex_descriptor>()); // new adjacency matrix for a graph
            assert(g._g.size() == g._v.size());
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * @param v : source vertex
         * @param g : graph 
         * @return : iterator to the vector of adjacent vertices to v. 
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) {
            // <your code>
            adjacency_iterator b = g._g[v].begin(); 
            adjacency_iterator e = g._g[v].end();
            assert(g._g.size() == g._v.size());
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * @param s : vertex_descriptor, source
         * @param t : vertex_descriptor, targer
         * @param g : graph, by reference
         * @return : std::pair<edge_descriptor, bool>, finds corresponding pair(s, t) in graph, false if not found
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor s, vertex_descriptor t, const Graph& g) {
            edge_descriptor e_ = std::make_pair(s, t); 
            assert(g._g.size() == g._v.size());
            edge_iterator b = g._e.begin();
            edge_iterator e = g._e.end();
            while(b != e) {
                if((*b).first == s && (*b).second == t) {
                    return std::make_pair(e_, true);}
                ++b;
            }
            return std::make_pair(e_, false);
        }
        // -----
        // edges
        // -----

        /**
         * @param g : input graph
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            edge_iterator b = g._e.begin();
            edge_iterator e = g._e.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * @param g : input graph
         */
        friend edges_size_type num_edges (const Graph& g) {
            return g._e.size();}

        // ------------
        // num_vertices
        // ------------

        /**
         * @param g : input graph
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            return g._v.size();}

        // ------
        // source
        // ------

        /**
         * @param e : edge
         * @param g : input graph
         */
        friend vertex_descriptor source (edge_descriptor e, const Graph&) {
            return e.first;}

        // ------
        // target
        // ------

        /**
         * @param e : edge
         * @param g : input graph
         */
        friend vertex_descriptor target (edge_descriptor e, const Graph&) {
            return e.second;}

        // ------
        // vertex
        // ------

        /**
         * @param idx : vertex_descriptor value
         * @param g : input graph
         * @return : vertex_descriptor value
         */
        friend vertex_descriptor vertex (vertices_size_type idx, const Graph& g) {
            if(idx >= g._v.size())
                return idx;
            return g._v[idx];}

        // --------
        // vertices
        // --------

        /**
         * @param g : input graph
         * @return : the begining and end iterators to the vertices container
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            vertex_iterator b = g._v.begin();
            vertex_iterator e = g._v.end();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::set<vertex_descriptor> > _g; // ! rename graph container
        std::vector<vertex_descriptor> _v; // ! container for vertices
        std::set<edge_descriptor> _e; // ! container for edges 
        
        // -----
        // valid
        // -----

        /**
         * @return : boolean value, indicates that all vertices are on the graph
         */
        bool valid () const {
            return _g.size() == _v.size();} 

    public:
        // ------------
        // constructors
        // ------------

        /**
         * @param g : vector of sets that hold vertex_descriptors
         * @param v : vector of vertex_descriptor, container for vertices
         * @param e : vector of edge_descriptor, container for edges 
         */
        Graph (std::vector< std::set<vertex_descriptor> > g = std::vector< std::set<vertex_descriptor> >(),
            std::vector<vertex_descriptor> v = std::vector<vertex_descriptor>(), 
            std::set<edge_descriptor> e = std::set<edge_descriptor>()) :
            _g(g),
            _v(v),
            _e(e) {
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
