#ifndef _CHOICEGRAPH_H_
    #define _CHOICEGRAPH_H_
#include <string>
#include <vector>
#include "Vector2.h"
#include "GraphNode.h"
#include "WorldLayer.h"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/topology.hpp"
#include "boost/graph/simple_point.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
class WorldLayer;
class Area;

const int ACTION_DESCEND = 1;

typedef boost::square_topology<>::point_type CPoint;
struct CEdge {
    CEdge(const std::size_t &w):weight(w) {}
    CEdge():weight(0) {}
    float weight;
};
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                            GraphNode, CEdge> CGraph;
typedef boost::property_map<CGraph, boost::vertex_index_t>::type CIndexMap;
typedef boost::graph_traits<CGraph>::vertex_iterator CVertexIter;
typedef boost::graph_traits<CGraph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<CGraph>::edge_descriptor edge_t;

const float VERTEX_GROUND_OFFSET  = 0.075f;
const float SLOPE_ANGLE_THRESHOLD = M_PI_4;

//typedef std::pair<GraphNode, GraphNode> CEdge;
//enum {A, B, C, D, E, N};
//const int NUM_VERTICES = N;

/**
 * Models a graph according to a Scene.
 */
class ChoiceGraph {
    private:
        CGraph* m_graph;
        WorldLayer* m_worldLayer;
        std::vector<GraphNode*> m_terminalNodes;
        int m_nodeIndex;

    public:
        ChoiceGraph(WorldLayer* worldLayer);
        CGraph* GetGraph();
        void Build();
        void AddArea(Area* area);
        void AddExit(Exit* exit);

    private:
        GraphNode* GetGraphNode(int areaNodeId);
        GraphNode* AddGraphNode(float x, float y, bool offsetAgainstGravity = false);
        GraphNode* AddGraphNode(AreaNode* areaNode);
        bool IsConvexChange(float xV, float yV, float xA, float yA, float xB, float yB, float angle);
        /**
         * Process terminal nodes of areas connecting them according to falls
         * and descending slopes.
         */
        void ProcessAreaSegments();
        void CollectVertexInfo();
        bool ExpandNode(AreaNode* areaNode, int direction = 0);
        bool BreaksGravity(AreaNode* nodeA, AreaNode* nodeB);
        AreaNode* SelectDownNode(AreaNode* nodeA, AreaNode* nodeB);
        bool AreConnected(AreaNode* nodeA, AreaNode* nodeB);
        bool ConnectNodes(AreaNode* nodeA, AreaNode* nodeB, bool bothDirections = false);
        bool ConnectDuo(AreaNode* node, float x, float y, AreaNode* nodeT);
        bool ConnectTriad(AreaNode* node, float x, float y, AreaNode* nodeA, AreaNode* nodeB);
        void AccessEdgeSet();
        
};
#endif
