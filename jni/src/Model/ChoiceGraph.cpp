#include "ChoiceGraph.h"
#include <sstream>
#include <algorithm>
#include "../Engine/RayCastTool.h"
#include "../Util/Log.h"
#include "Scene.h"
#include "AreaNode.h"

/*
template <class CGraph> struct ChoiceGraph::exercise_vertex {
    exercise_vertex(CGraph& g_) : m_graph(g_) {}
    CGraph& m_graph;
    typedef typename boost::graph_traits<CGraph>::vertex_descriptor Vertex;
    void operator()(const Vertex& v) const
    {
        typedef boost::graph_traits<CGraph> GraphTraits;
        typename boost::property_map<CGraph, boost::vertex_index_t>::type index = boost::get(boost::vertex_index, m_graph);
        std::stringstream s1;
        s1 << "out-edges: ";
        typename GraphTraits::out_edge_iterator out_i, out_end;
        typename GraphTraits::edge_descriptor e;
        for (boost::tie(out_i, out_end) = boost::out_edges(v, m_graph);
            out_i != out_end; ++out_i) {
            e = *out_i;
            Vertex src = boost::source(e, m_graph), targ = boost::target(e, m_graph);
            s1 << "(" << index[src] << "," << index[targ] << ") ";
        }
        s1 << std::endl;
        Log::L(s1.str());
    }
};
*/

ChoiceGraph::ChoiceGraph(WorldLayer* worldLayer) {
    m_worldLayer = worldLayer;
    m_graph = new CGraph();
    m_nodeIndex = 0;
    /*
    AccessVertexSet();
    AccessEdgeSet();
    std::for_each(boost::vertices(*m_graph).first, boost::vertices(*m_graph).second,
                  exercise_vertex<Graph>(*m_graph));
    */
};

CGraph* ChoiceGraph::GetGraph() {
    return m_graph;
};

GraphNode* ChoiceGraph::GetGraphNode(int areaNodeId) {
    GraphNode* graphNode;
    graphNode = &(*m_graph)[areaNodeId];
    return graphNode;
};

GraphNode* ChoiceGraph::AddGraphNode(float x, float y, bool offsetAgainstGravity) {
    GraphNode* graphNode;
    vertex_t vGraphNode;
    vGraphNode = boost::add_vertex(m_nodeIndex, *m_graph);
    graphNode = &(*m_graph)[vGraphNode];
    graphNode->id = m_nodeIndex;
    if (offsetAgainstGravity) {
        double gravityAgainstAngle = CMath::GetAngleOffset(Scene::GetGravity()->Angle(), M_PI);
        Vector2* graphNodeLocation = CMath::GetPointAt(x, y, VERTEX_GROUND_OFFSET, gravityAgainstAngle);
        graphNode->x = graphNodeLocation->x;
        graphNode->y = graphNodeLocation->y;
    } else {
        graphNode->x = x;
        graphNode->y = y;
    }
    m_nodeIndex++;
    return graphNode;
};

GraphNode* ChoiceGraph::AddGraphNode(AreaNode* areaNode) {
    GraphNode* graphNode;
    vertex_t vGraphNode;
    Vector2* graphNodeLocation;
    double gravityAgainstAngle = CMath::GetAngleOffset(Scene::GetGravity()->Angle(), M_PI);
    if (areaNode->graphNodeId > -1) {
        Log::L("Warning: the AreaGraph already had an GraphNode");
    }
    graphNodeLocation = CMath::GetPointAt(areaNode, VERTEX_GROUND_OFFSET, gravityAgainstAngle);
    vGraphNode = boost::add_vertex(m_nodeIndex, *m_graph);
    graphNode = &(*m_graph)[vGraphNode];
    graphNode->id = m_nodeIndex;
    graphNode->x = graphNodeLocation->x;
    graphNode->y = graphNodeLocation->y;
    graphNode->anchor = areaNode;
    areaNode->graphNodeId = m_nodeIndex;
    m_nodeIndex++;
    return graphNode;
};

void ChoiceGraph::AddArea(Area* area) {
    AreaNode* point = NULL;
    AreaNode* _point  = NULL;
    AreaNode* __point = NULL;
    AreaNode* firstPoint = NULL;
    Vector2* graphPoint = NULL;
    vertex_t v = 0;
    vertex_t _v = 0;
    vertex_t __v = 0;
    vertex_t firstV = -1;
    GraphNode* node = NULL;
    GraphNode* _node = NULL;
    GraphNode* firstNode = NULL;
    float angle, _angle, absangle, linesAngle, distance = 0.0f;
    double gravityAngle = Scene::GetGravity()->Angle();
    double gravityOffsetAngle = CMath::GetAngleOffset(gravityAngle, M_PI_2);
    typedef boost::graph_traits<CGraph>::vertex_descriptor vertex_t;
    int line = 0;
    bool newWalkLine = true;
    bool isIntern = false;
    bool convexChange = false;
    for(auto &point_ : area->GetPoints()) { // Inspect every point in the area.
        point = point_;
        point->graphNodeId = -1;
        if (_point) { // Wait until we have a previous point.
            // Get angle of edge.
            angle = CMath::GetAngleOffset(CMath::GetAngle(_point->x, _point->y, point->x, point->y), -gravityOffsetAngle);
            // Get absolute angle of edge (to test walkability).
            absangle = CMath::GetAbsoluteAngle(angle);
            if (__point) { //Checks for change in line convexion
                convexChange = IsConvexChange(_point->x, _point->y, 
                                                point->x, point->y, 
                                                __point->x, __point->y, gravityAngle);
                if (convexChange) {
                    isIntern = !isIntern;
                    // If there's a change to convex, we set the last line terminal node.
                    if (_node) {
                        _node->terminal = true;
                    }
                }
            }
            if (absangle < SLOPE_ANGLE_THRESHOLD) {
                // If the angle edge is walkable process the points involved (these are definetly
                // going to get added, but their connections to other edges remain to be seen).
                if (newWalkLine || convexChange) {
                    //If there's a newline we set the terminal node on the old one.
                    if (_node) {
                        _node->terminal = true;
                    }
                    // If a new walking line need to be created we add its first node.
                    _node = AddGraphNode(_point);
                    _v = boost::vertex(_node->id, *m_graph);
                    // Set the terminal node for the new line.
                    _node->terminal = true;
                    if (area->IsClosed() && firstV == -1) {
                        // Save reference to the first node ever created in case we have a closes area.
                        // This is used to check the final connection.
                        firstV = _v;
                        firstPoint = _point;
                        firstNode = _node;
                    }
                    newWalkLine = false;
                }
                // If no new line is needed, we already have a previous node to connect to, so we
                // create the second node.
                node = AddGraphNode(point);
                v = boost::vertex(node->id, *m_graph);
                if (area->IsClosed()) {// If the area is closed mark node as intern or extern.
                    node->intern = isIntern;
                    _node->intern = isIntern;
                }
                if (node->IsIntern() == _node->IsIntern()) {
                    distance = _point->Dist(point);
                    boost::add_edge(v, _v, CEdge(distance), *m_graph);
                    boost::add_edge(_v, v, CEdge(distance), *m_graph);
                }
                _v = v;
                _node = node;
            } else {
                //If the angle edge is not walkable next one should make a new walking line.
                newWalkLine = true;
            }
            convexChange = false;
        }
        __point = _point;
        _point = point;
        line++;
    }
    // Make last connection for closed areas.
    if (area->IsClosed() && firstV != -1 && v != firstV && !newWalkLine) {
        angle = CMath::GetAngleOffset(CMath::GetAngle(_point->x, _point->y, firstPoint->x, firstPoint->y), -gravityOffsetAngle);
        absangle = CMath::GetAbsoluteAngle(angle);
        if (absangle < SLOPE_ANGLE_THRESHOLD) {
            distance = _point->Dist(firstPoint);
            boost::add_edge(_v, firstV, CEdge(distance), *m_graph);
            boost::add_edge(firstV, _v, CEdge(distance), *m_graph);
        }
    } else if (_node) {
        _node->terminal = true;
    }
};

void ChoiceGraph::AddExit(Exit* exit) {
};

void ChoiceGraph::Build() {
    m_graph->clear();
    m_nodeIndex = 0;
    for (auto &area : m_worldLayer->GetAreas()) {
        AddArea(area);
    }
    /*
    GraphNode* node;
    for (int i = 0; i < m_nodeIndex; i++) {
        node = &(*m_graph)[i];
        Log::L("Action for node %d: %d", node->id, node->action);
    }
    */
    CollectVertexInfo();
    ProcessAreaSegments();
    for (auto &exit : m_worldLayer->GetExits()) {
        AddExit(exit);
    }
    //AccessVertexSet();
    /*
    typedef std::pair<int, int> Edge;
    Edge edge_array[] = {Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
        Edge(C,E), Edge(B,D), Edge(D,E)};
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
    m_graph = new Graph(NUM_VERTICES);
    for(int i = 0; i < num_edges; ++i) {
        Log::L("Adding edge connecting %i to %i", edge_array[i].first, edge_array[i].second);
        boost::add_edge(edge_array[i].first, edge_array[i].second, *m_graph);
    }*/
};

void ChoiceGraph::ProcessAreaSegments() {
    for (auto &node : m_terminalNodes) {
        if (node->anchor) {
            ExpandNode(node->anchor);
        }
    }
};

bool ChoiceGraph::ExpandNode(AreaNode* node, int direction) {
    if (node->graphNodeId > -1)
        Log::L("Expanding node with id: %d", node->graphNodeId);
    if (BreaksGravity(node, node->neighborA) || BreaksGravity(node, node->neighborB)) {
        Log::L("Raycasting to ground.");
        RayCastTool* rcTool = new RayCastTool(0.9f);
        rcTool->SetFilter(AREA_BODY);
        rcTool->RayCast(m_worldLayer, node->x, node->y, Scene::GetGravity()->Angle());
        if (!rcTool->HasContact())
            return false;
        if (rcTool->GetAreaNodeA()->graphNodeId > -1 && rcTool->GetAreaNodeB()->graphNodeId > -1) {
            ConnectTriad(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, rcTool->GetAreaNodeA(), rcTool->GetAreaNodeB());
            return true;
        }
        AreaNode* downNode = SelectDownNode(rcTool->GetAreaNodeA(), rcTool->GetAreaNodeB());
        if (downNode) {
            if (downNode == rcTool->GetAreaNodeA() && downNode->graphNodeId > -1) {
                ConnectDuo(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, rcTool->GetAreaNodeA());
            } else if (downNode->graphNodeId > -1) {
                ConnectDuo(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, rcTool->GetAreaNodeB());
            } else {
                bool getsExpanded = ExpandNode(downNode);
                if (getsExpanded)
                    ConnectDuo(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, downNode);
                else
                    return false;
            }
            return true;
        }
        return false;
    } else {
        Log::L("Expanding node downwards.");
        AreaNode* downNode = SelectDownNode(node->neighborA, node->neighborB);
        if (AreConnected(node, downNode))
            return false;
        if (downNode->graphNodeId >= 0) {
            Log::L("Connecting nodes %d and %d", node->graphNodeId, downNode->graphNodeId);
            ConnectNodes(node, downNode);
            return true;
        } else {
            int newDirection = 1;
            if (downNode == node->neighborA)
                newDirection = -1;
            //Log::L("Direction %d newDirection:%d downNode:%d node->neighborA:%d", direction, newDirection, downNode, node->neighborA);
            if (direction != 0 && newDirection != direction)
                return false;
            bool getsExpand = ExpandNode(downNode, newDirection);
            if (getsExpand) {
                ConnectNodes(node, downNode);
                return true;
            }
        }
    }
    return false;
};

bool ChoiceGraph::BreaksGravity(AreaNode* nodeA, AreaNode* nodeB) {
    // TODO: check for gravity breakage.
    if (!nodeA || !nodeB) {
        Log::L("Breaks gravity.");
        if (!nodeA)
            Log::L("not node A");
        if (!nodeB)
            Log::L("not node B");
        return true;
    }
    return false;
};

AreaNode* ChoiceGraph::SelectDownNode(AreaNode* nodeA, AreaNode* nodeB) {
    // TODO: Rotate points around origin before comparision.
    if (!nodeA)
        return nodeB;
    if (!nodeB)
        return nodeA;
    if (nodeA->y < nodeB->y)
        return nodeA;
    else
        return nodeB;
};

bool ChoiceGraph::AreConnected(AreaNode* nodeA, AreaNode* nodeB) {
    if (nodeA->graphNodeId > -1 && nodeB->graphNodeId > -1) {
        vertex_t vA = boost::vertex(nodeA->graphNodeId, *m_graph);
        vertex_t vB = boost::vertex(nodeB->graphNodeId, *m_graph);
        std::pair<edge_t, bool> connectionAB = boost::edge(vA, vB, *m_graph);
        if (connectionAB.second)
            return true;
        else {
            std::pair<edge_t, bool> connectionBA = boost::edge(vB, vA, *m_graph);
            return connectionBA.second;
        }
    }
    return false;
};

bool ChoiceGraph::ConnectNodes(AreaNode* nodeA, AreaNode* nodeB, bool bothDirections) {
    vertex_t vA = 0;
    vertex_t vB = 0;
    GraphNode* graphNodeA;
    GraphNode* graphNodeB;
    if (nodeA->graphNodeId == -1) {
        graphNodeA = AddGraphNode(nodeA);
    } else {
        graphNodeA = GetGraphNode(nodeA->graphNodeId);
    }
    vA = boost::vertex(graphNodeA->id, *m_graph);
    if (nodeB->graphNodeId == -1) {
        graphNodeB = AddGraphNode(nodeB);
    } else {
        graphNodeB = GetGraphNode(nodeB->graphNodeId);
    }
    vB = boost::vertex(graphNodeB->id, *m_graph);
    float distance = nodeA->Dist(nodeB);
    boost::add_edge(vA, vB, CEdge(distance), *m_graph);
    if (bothDirections)
        boost::add_edge(vB, vA, CEdge(distance), *m_graph);
    graphNodeA->terminal = false;
    graphNodeB->terminal = false;
    return true;
};

bool ChoiceGraph::ConnectDuo(AreaNode* node, float x, float y, AreaNode* nodeT) {
    vertex_t vT = 0;
    vertex_t vN = 0;
    vertex_t vM = 0;
    GraphNode* graphNodeT;
    GraphNode* graphNodeN;
    GraphNode* graphNodeM;
    if (node->graphNodeId == -1) {
        graphNodeN = AddGraphNode(node);
    } else {
        graphNodeN = GetGraphNode(node->graphNodeId);
    }
    vN = boost::vertex(graphNodeN->id, *m_graph);
    if (nodeT->graphNodeId == -1) {
        graphNodeT = AddGraphNode(nodeT);
    } else {
        graphNodeT = GetGraphNode(nodeT->graphNodeId);
    }
    vT = boost::vertex(graphNodeT->id, *m_graph);
    graphNodeM = AddGraphNode(x, y, true);
    vM = boost::vertex(graphNodeM->id, *m_graph);
    // Make connections.
    float distance = node->Dist(graphNodeM);
    boost::add_edge(vN, vM, CEdge(distance), *m_graph);
    distance = nodeT->Dist(graphNodeM);
    boost::add_edge(vM, vT, CEdge(distance), *m_graph);
    graphNodeN->terminal = false;
    return true;
};

bool ChoiceGraph::ConnectTriad(AreaNode* node, float x, float y, AreaNode* nodeA, AreaNode* nodeB) {
    vertex_t vA = 0;
    vertex_t vB = 0;
    vertex_t vN = 0;
    vertex_t vM = 0;
    GraphNode* graphNodeA;
    GraphNode* graphNodeB;
    GraphNode* graphNodeN;
    GraphNode* graphNodeM;
    bool connectedAB = AreConnected(nodeA, nodeB);
    bool connectedBA = AreConnected(nodeB, nodeA);
    if (nodeA->graphNodeId == -1) {
        graphNodeA = AddGraphNode(nodeA);
    } else {
        graphNodeA = GetGraphNode(nodeA->graphNodeId);
    }
    vA = boost::vertex(graphNodeA->id, *m_graph);
    if (nodeB->graphNodeId == -1) {
        graphNodeB = AddGraphNode(nodeB);
    } else {
        graphNodeB = GetGraphNode(nodeB->graphNodeId);
    }
    vB = boost::vertex(graphNodeB->id, *m_graph);
    if (node->graphNodeId == -1) {
        graphNodeN = AddGraphNode(node);
    } else {
        graphNodeN = GetGraphNode(node->graphNodeId);
    }
    vN = boost::vertex(graphNodeN->id, *m_graph);
    graphNodeM = AddGraphNode(x, y, true);
    vM = boost::vertex(graphNodeM->id, *m_graph);
    if (connectedAB)
        boost::remove_edge(vA, vB, *m_graph);
    if (connectedBA)
        boost::remove_edge(vB, vA, *m_graph);
    // Make connections.
    float distance = node->Dist(graphNodeM);
    boost::add_edge(vN, vM, CEdge(distance), *m_graph);
    if (connectedAB) {
        distance = nodeA->Dist(graphNodeM);
        boost::add_edge(vA, vM, CEdge(distance), *m_graph);
        distance = nodeB->Dist(graphNodeM);
        boost::add_edge(vM, vB, CEdge(distance), *m_graph);
    }
    if (connectedBA) {
        distance = nodeB->Dist(graphNodeM);
        boost::add_edge(vB, vM, CEdge(distance), *m_graph);
        distance = nodeA->Dist(graphNodeM);
        boost::add_edge(vM, vA, CEdge(distance), *m_graph);
    }
    graphNodeN->terminal = false;
    return true;
};

bool ChoiceGraph::IsConvexChange(float xV, float yV, float xA, float yA, float xB, float yB, float angle) {
    float xVA = (xV + xA) / 2;
    float yVA = (yV + yA) / 2;
    float xVB = (xV + xB) / 2;
    float yVB = (yV + yB) / 2;
    Vector2* pVA1 = CMath::GetPointAt(xVA, yVA, 300, angle);
    Vector2* pVA2 = CMath::GetPointAt(xVA, yVA, -300, angle);
    Vector2* pVB1 = CMath::GetPointAt(xVB, yVB, 300, angle);
    Vector2* pVB2 = CMath::GetPointAt(xVB, yVB, -300, angle);
    bool aIntersect = CMath::LinesIntersect(xV, yV, xA, yA, pVB1->x, pVB1->y, pVB2->x, pVB2->y);
    bool bIntersect = CMath::LinesIntersect(xV, yV, xB, yB, pVA1->x, pVA1->y, pVA2->x, pVA2->y);
    return (aIntersect || bIntersect);
};

void ChoiceGraph::CollectVertexInfo() {
    CIndexMap index = boost::get(boost::vertex_index, *m_graph);
    std::pair<CVertexIter, CVertexIter> vp;
    GraphNode* node;
    for (vp = boost::vertices(*m_graph); vp.first != vp.second; ++vp.first) {
        /*s << index[*vp.first] <<
        " action:" << (*m_graph)[index[*vp.first]].action << "\n";*/
        node = &(*m_graph)[index[*vp.first]];
        if ( node->terminal ) {
            m_terminalNodes.push_back(node);
        }
    }
    /*
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    IndexMap index = boost::get(boost::vertex_index, *m_graph);
    std::stringstream s;
    s << "vertices(g) = ";
    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = boost::vertices(*m_graph); vp.first != vp.second; ++vp.first)
        s << index[*vp.first] << " ";
    s << std::endl;
    Log::L(s.str());
    */
};

void ChoiceGraph::AccessEdgeSet() {
    /*
    std::stringstream s;
    s << "edges(s) = ";
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    IndexMap index = boost::get(boost::vertex_index, *m_graph);
    boost::graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(*m_graph); ei != ei_end; ++ei) {
        s << "(" << index[boost::source(*ei, *m_graph)] << ","
            << index[boost::target(*ei, *m_graph)] << ") ";
    }
    s << std::endl;
    Log::L(s.str());
    */
};
