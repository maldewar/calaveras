#ifndef _CHOICEGRAPH_H_
    #define _CHOICEGRAPH_H_
#include <string>
#include "Vector2.h"
#include "Node.h"
#include "WorldLayer.h"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/topology.hpp"
#include "boost/graph/simple_point.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
class WorldLayer;
class Area;

typedef boost::square_topology<>::point_type CPoint;
struct CEdge {
    CEdge(const std::size_t &w):weight(w) {}
    CEdge():weight(0) {}
    float weight;
};
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                            Node, CEdge> CGraph;
typedef boost::property_map<CGraph, boost::vertex_index_t>::type CIndexMap;
typedef boost::graph_traits<CGraph>::vertex_iterator CVertexIter;
typedef boost::graph_traits<CGraph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<CGraph>::edge_descriptor edge_t;

const float VERTEX_GROUND_OFFSET  = 0.075f;
const float SLOPE_ANGLE_THRESHOLD = M_PI_4;

//typedef std::pair<Node, Node> CEdge;
//enum {A, B, C, D, E, N};
//const int NUM_VERTICES = N;

/**
 * Models a graph according to a Scene.
 */
class ChoiceGraph {
    private:
        CGraph* m_graph;
        //int m_nodeSeed;
        //template<class Graph> struct exercise_vertex;
        WorldLayer* m_worldLayer;

    public:
        ChoiceGraph(WorldLayer* worldLayer);
        CGraph* GetGraph();
        void Build();
        void AddArea(CArea* area);

    private:
        void AccessVertexSet();
        void AccessEdgeSet();
        
};
#endif
