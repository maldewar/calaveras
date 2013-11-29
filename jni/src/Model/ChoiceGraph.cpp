#include "ChoiceGraph.h"
#include <sstream>
#include <algorithm>
#include "../Util/CLog.h"
#include "CScene.h"

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
        CLog::Log(s1.str());
    }
};
*/

ChoiceGraph::ChoiceGraph(WorldLayer* worldLayer) {
    m_worldLayer = worldLayer;
    m_graph = new CGraph();
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

void ChoiceGraph::AddArea(CArea* area) {
    Vector2* _point  = NULL;
    Vector2* __point = NULL;
    Vector2* graphPoint = NULL;
    vertex_t _v;
    vertex_t __v;
    float angle, _angle, absangle, linesAngle, distance = 0.0f;
    double gravityAngle = CScene::GetGravity()->Angle();
    double gravityAgainstAngle = CMath::GetAngleOffset(gravityAngle, M_PI);
    double gravityOffsetAngle = CMath::GetAngleOffset(gravityAngle, M_PI_2);
    typedef boost::graph_traits<CGraph>::vertex_descriptor vertex_t;
    int line = 0;
    for(auto &point : area->GetPoints()) {
        //vertex_t v = boost::add_vertex(*m_graph);
        //graphPoint = CMath::GetPointAt(point, VERTEX_GROUND_OFFSET, gravityAgainstAngle);
        //(*m_graph)[v].x = graphPoint->x;
        //(*m_graph)[v].y = graphPoint->y;
        if (_point) {
            angle = CMath::GetAngleOffset(CMath::GetAngle(_point->x, _point->y, point->x, point->y), gravityOffsetAngle);
            absangle = CMath::GetAngleOffset(CMath::GetAbsoluteAngle(_point->x, _point->y, point->x, point->y), gravityOffsetAngle);
            if (__point) {
               linesAngle = CMath::GetAngle(_point->x, _point->y, __point->x, __point->y, point->x, point->y);
            }
            //distance = _point->Dist(point);
            //boost::add_edge(v, _v, CEdge(distance), *m_graph);
            //boost::add_edge(_v, v, CEdge(distance),*m_graph);
            __point = _point;
            //__v = _v;
        }
        _point = point;
        //_v = v;
        line++;
    }
};

void ChoiceGraph::Build() {
    m_graph->clear();
    for (auto &area : m_worldLayer->GetAreas()) {
        AddArea(area);
    }
    //AccessVertexSet();
    /*
    typedef std::pair<int, int> Edge;
    Edge edge_array[] = {Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
        Edge(C,E), Edge(B,D), Edge(D,E)};
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
    m_graph = new Graph(NUM_VERTICES);
    for(int i = 0; i < num_edges; ++i) {
        CLog::Log("Adding edge connecting %i to %i", edge_array[i].first, edge_array[i].second);
        boost::add_edge(edge_array[i].first, edge_array[i].second, *m_graph);
    }*/
};

void ChoiceGraph::AccessVertexSet() {
    CLog::Log("ChoiceGraph::AccessVertexSet");
    CIndexMap index = boost::get(boost::vertex_index, *m_graph);
    std::stringstream s;
    s << "vertices(g) = \n";
    std::pair<CVertexIter, CVertexIter> vp;
    for (vp = boost::vertices(*m_graph); vp.first != vp.second; ++vp.first)
        s << index[*vp.first] << 
        " x:" << (*m_graph)[index[*vp.first]].x << 
        " y:" << (*m_graph)[index[*vp.first]].y << "\n";
    s << std::endl;
    CLog::Log(s.str());
    
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
    CLog::Log(s.str());
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
    CLog::Log(s.str());
    */
};
