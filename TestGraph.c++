// ----------------------------
// projects/graph/TestGraph.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Graph.h TestGraph.c++ -o TestGraph -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestGraph

To obtain coverage of the test:
    % gcov-4.7 -b Graph.c++ TestGraph.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair
#include <vector>

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef testing::Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        my_types;


TYPED_TEST_CASE(TestGraph, my_types);

TYPED_TEST(TestGraph, Graph_Constructor_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    add_edge(v0, v1, g);

    ASSERT_EQ(1, num_edges(g));
    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(vertex(0, g), v0);
    ASSERT_EQ(vertex(1, g), v1);
    ASSERT_TRUE(edge(v0, v1, g).second);}

TYPED_TEST(TestGraph, Graph_Constructor_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    add_edge(v0, v1, g);

    graph_type h(g);

    ASSERT_EQ(1, num_edges(h));
    ASSERT_EQ(2, num_vertices(h));
    ASSERT_EQ(vertex(0, h), v0);
    ASSERT_EQ(vertex(1, h), v1);
    ASSERT_TRUE(edge(v0, v1, h).second);}

TYPED_TEST(TestGraph, Graph_Constructor_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    ASSERT_EQ(0, num_edges(g));
    ASSERT_EQ(0, num_vertices(g));}

TYPED_TEST(TestGraph, Vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);}

TYPED_TEST(TestGraph, Vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    std::vector<vertex_descriptor> v; 

    graph_type g;
    for(vertices_size_type i = 0; i < 10; ++i) {
        vertex_descriptor tmp = add_vertex(g);
        v.push_back(tmp);
    }
    for(vertices_size_type j = 0; j < 10; ++j) {
        ASSERT_EQ(vertex(j, g), v[j]);
    };}

TYPED_TEST(TestGraph, Vertex_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g0; 
    graph_type g1;

    vertex_descriptor v0 = add_vertex(g0);
    vertex_descriptor v1 = add_vertex(g0); 

    edge_descriptor e0 = add_edge(v0, v1, g1).first;
    ASSERT_EQ(vertex(0, g0), v0);
    ASSERT_EQ(vertex(1, g1), v1);}

TYPED_TEST(TestGraph, Vertex_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    vertex_descriptor v2 = add_vertex(g);
    vertex_descriptor v3 = add_vertex(g);
    vertex_descriptor v4 = add_vertex(g);

    edge_descriptor e = add_edge(v3, v4, g).first;
    graph_type h(g);

    ASSERT_EQ(vertex(0, h), 0);
    ASSERT_EQ(vertex(1, h), 1);
}

TYPED_TEST(TestGraph, Edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    std::pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    std::pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);}

TYPED_TEST(TestGraph, Edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    vertices_size_type i = 0;

    while(i < 10) {
        vertex_descriptor v0 = add_vertex(g);
        vertex_descriptor v1 = add_vertex(g);
        add_edge(v0, v1, g);
        i += 2;
    }
    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    edges_size_type                         c = 0;
    
    while(b != e) {
        ++c;
        ++b;
    }
    ASSERT_EQ(c, 5);}

TYPED_TEST(TestGraph, Edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    add_edge(v0, v1, g);
    add_edge(v1, v0, g);

    std::pair<edge_iterator, edge_iterator> p = edges(g); 
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    edges_size_type                          c = 0;

    while(b != e) {
        ++c;
        ++b;
    }
    ASSERT_EQ(c, 2);}

TYPED_TEST(TestGraph, Add_Edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    edges_size_type i = 0;
    add_edge(v0, v1, g);

    while(i < 101) {
        ASSERT_FALSE(add_edge(v0, v1, g).second);
        ++i;
    }
}

TYPED_TEST(TestGraph, Add_Edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    
    ASSERT_TRUE(add_edge(v0, v1, g).second);
    ASSERT_TRUE(add_edge(v1, v0, g).second);
}

TYPED_TEST(TestGraph, Add_Edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    graph_type h; 
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);

    std::pair<edge_descriptor, bool> e = add_edge(v0, v1, h);
    ASSERT_TRUE(e.second);}    

TYPED_TEST(TestGraph, Add_Edge_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    vertex_descriptor v = add_vertex(g);
    std::pair<edge_descriptor, bool> e = add_edge(v, 1000, g);

    ASSERT_EQ(num_vertices(g), 1001);
    ASSERT_TRUE(e.second);
    ASSERT_EQ(num_edges(g), 1);}

TYPED_TEST(TestGraph, Add_Edge_5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    for(vertices_size_type i = 0; i < 15; ++i) {
        vertex_descriptor v = add_vertex(g);
        add_edge(v, v, g);}

    ASSERT_EQ(num_vertices(g), num_edges(g));
}

TYPED_TEST(TestGraph, Add_Vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertices_size_type i = 0;
    while(i < 23) {
        add_vertex(g);
        ++i;
    }
    ASSERT_EQ(i, num_vertices(g));}

TYPED_TEST(TestGraph, Add_Vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    graph_type x(g);
    add_vertex(x);
    add_vertex(x);
    ASSERT_EQ(num_vertices(x), 5);
}

TYPED_TEST(TestGraph, Add_Vertex_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    for(vertices_size_type i = 0; i < 27; ++i) {
        vertex_descriptor v = add_vertex(g);
        ASSERT_EQ(v, vertex(i, g));
    }
}

TYPED_TEST(TestGraph, Vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, Vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    std::vector<vertex_descriptor> v; 
    for(vertices_size_type i = 0; i < 15; ++i) {
        vertex_descriptor vtx = add_vertex(g);
        v.push_back(vtx);}

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    vertices_size_type                          i = 0;

    while(b != e) {
        ASSERT_EQ(*b, v[i]);
        ++b;
        ++i;
    }
}

TYPED_TEST(TestGraph, Vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    for(vertices_size_type i = 0; i < 1005; ++i) {
        vertex_descriptor vtx = add_vertex(g);}

    std::pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                             b = p.first;
    vertex_iterator                             e = p.second;
    vertices_size_type                          c = 0;

    while(b != e) {
        ++c;
        ++b;
    }
    ASSERT_EQ(c, 1005);
}

TYPED_TEST(TestGraph, Vertices_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    for(vertices_size_type i = 0; i < 1005; ++i) {
        vertex_descriptor vtx = add_vertex(g);}

    std::pair<vertex_iterator, vertex_iterator> p0 = vertices(g);
    vertex_iterator                             b0 = p0.first;
    vertex_iterator                             e0 = p0.second;
    std::pair<vertex_iterator, vertex_iterator> p1 = vertices(g);
    vertex_iterator                             b1 = p1.first;
    vertex_iterator                             e1 = p1.second;

    while(b0 != e0) {
       ASSERT_EQ(b0, b1);
       ++b0;
       ++b1;
    }
}

TYPED_TEST(TestGraph, Edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, Edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    edges_size_type c = 0;
    while(c < 10) {
        vertex_descriptor v0 = add_vertex(g);
        vertex_descriptor v1 = add_vertex(g);
        add_edge(v0, v1, g);
        add_edge(v1, v0, g); 
        ++c;
    }
    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    edges_size_type                         s = 0;

    while(b != e) {
        ++s; 
        ++b;}

    ASSERT_EQ(s, c * 2);}

TYPED_TEST(TestGraph, Edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    std::vector<edge_descriptor> ed; 
    edges_size_type c = 0;

    while(c < 20) {
        vertex_descriptor v0 = add_vertex(g);
        vertex_descriptor v1 = add_vertex(g);
        edge_descriptor e0 = add_edge(v0, v1, g).first;
        ed.push_back(e0);
        c += 2;
    }
    std::pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    edges_size_type                         s = 0;

    while(b != e) {
        ASSERT_EQ(*b, ed[s]);
        ++b;
        ++s;
    }
} 

TYPED_TEST(TestGraph, Num_Edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    edges_size_type i = 0;
    while(i < 10) {
        vertex_descriptor v0 = add_vertex(g);
        vertex_descriptor v1 = add_vertex(g);
        add_edge(v0, v1, g);
        i += 2;
    }
    ASSERT_EQ(num_edges(g), i / 2);
}

TYPED_TEST(TestGraph, Num_Edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    for(edges_size_type i = 0; i < 10; ++i) {
        add_edge(v0, v1, g);
    }
    ASSERT_EQ(num_edges(g), 1);
}

TYPED_TEST(TestGraph, Num_Edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    edges_size_type i = 0;
    while(i < 10) {
        vertex_descriptor v0 = add_vertex(g);
        vertex_descriptor v1 = add_vertex(g);
        add_edge(v0, v1, g);
        add_edge(v1, v0, g);
        i += 2;
    }
    ASSERT_EQ(num_edges(g), i);}

TYPED_TEST(TestGraph, Num_Vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    vertices_size_type i = 0;
    while(i < 15) {
        add_vertex(g);
        ++i;
    }
    ASSERT_EQ(num_vertices(g), i);
}

TYPED_TEST(TestGraph, Num_Vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    graph_type h;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    add_edge(v0, v1, g); 
    add_edge(v0, v1, h);

    ASSERT_EQ(num_vertices(g), num_vertices(h));
}

TYPED_TEST(TestGraph, Num_Vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    graph_type x(g);

    ASSERT_EQ(num_vertices(g), num_vertices(x));}

TYPED_TEST(TestGraph, Adjacent_Vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    std::pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator b = p.first;
    adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, Adjacent_Vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vs = add_vertex(g);

    for(vertices_size_type i = 0; i < 50; ++i) {
        vertex_descriptor vt = add_vertex(g);
        add_edge(vs, vt, g);}

    std::pair<adjacency_iterator, adjacency_iterator>   p = adjacent_vertices(vs, g);
    adjacency_iterator                                  b = p.first;
    adjacency_iterator                                  e = p.second;
    vertices_size_type                                  i = 0;

    while(b != e) {
        ++i;
        ++b;
    }
    ASSERT_EQ(i, num_vertices(g) - 1);
}

TYPED_TEST(TestGraph, Adjacent_Vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);

    add_edge(v0, v1, g);
    add_edge(v1, v0, g);

    std::pair<adjacency_iterator, adjacency_iterator> p0 = adjacent_vertices(v0, g);
    std::pair<adjacency_iterator, adjacency_iterator> p1 = adjacent_vertices(v1, g);

    ASSERT_EQ(*p0.first, v1);
    ASSERT_EQ(*p1.first, v0);
}

TYPED_TEST(TestGraph, Source_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vs = add_vertex(g);

    for(vertices_size_type i = 0; i < 50; ++i) {
        vertex_descriptor vt = add_vertex(g);
        add_edge(vs, vt, g);}

    std::pair<edge_iterator, edge_iterator>  p = edges(g);
    edge_iterator                            b = p.first;
    edge_iterator                            e = p.second;
    while(b != e) {
        ASSERT_EQ(vs, source(*b, g));
        ++b;
    }
}

TYPED_TEST(TestGraph, Source_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g; 
    vertices_size_type i = 0;

    while(i < 10) {
        vertex_descriptor v0 = add_vertex(g);
        vertex_descriptor v1 = add_vertex(g);
        add_edge(v0, v1, g);
        ++i;}

    edge_iterator b = edges(g).first;
    edge_iterator e = edges(g).second;

    vertices_size_type j = 0;
    while(b != e) {
        ASSERT_EQ(vertex(j, g), source(*b, g));
        j += 2;
        ++b;}
}

TYPED_TEST(TestGraph, Source_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    edge_descriptor e0 = add_edge(v0, v1, g).first;
    edge_descriptor e1 = add_edge(v1, v0, g).first;

    ASSERT_EQ(v0, source(e0, g));
    ASSERT_EQ(v1, source(e1, g));
}

TYPED_TEST(TestGraph, Target_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    edge_descriptor e0 = add_edge(v0, v1, g).first;
    edge_descriptor e1 = add_edge(v1, v0, g).first;

    ASSERT_EQ(target(e1, g), source(e0, g));
    ASSERT_EQ(target(e0, g), source(e1, g));
}

TYPED_TEST(TestGraph, Target_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor vs = add_vertex(g);

    for(vertices_size_type i = 0; i < 50; ++i) {
        vertex_descriptor vt = add_vertex(g);
        edge_descriptor e = add_edge(vs, vt, g).first;
        ASSERT_EQ(vt, target(e, g));
    }
}

TYPED_TEST(TestGraph, Target_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;
    vertex_descriptor v0 = add_vertex(g);
    vertex_descriptor v1 = add_vertex(g);
    add_edge(v0, v1, g);

    graph_type h = g;
    edge_descriptor e = edge(v0, v1, h).first; 
    ASSERT_EQ(target(e, h), v1);
    ASSERT_EQ(source(e, h), v0);     
}






