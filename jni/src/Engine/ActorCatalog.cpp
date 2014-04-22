#include "ActorCatalog.h"
#include "../Util/File.h"
#include "../Util/PathUtil.h"
#include "../Model/Node2D.h"
#include "../Model/SpriteNode.h"
#include "../Util/Log.h"

std::unordered_map<std::string, Node*> ActorCatalog::m_actors;
std::string ActorCatalog::m_filename = PathUtil::GetActorCatalog();

void ActorCatalog::Init() {
    std::string document = File::ReadText(m_filename.c_str());
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(document.c_str(), root, false);
    Log::L("About to parse Actor Catalog.");
    if (! parsingSuccessful) {
        Log::L("Parsing unsuccessful: %s", reader.getFormatedErrorMessages().c_str());
        return;
    }
    BuildCatalog(root);
};

Node* ActorCatalog::GetActor(std::string id) {
  return m_actors[id];
};

void ActorCatalog::BuildCatalog(Json::Value root) {
  for(Json::ValueIterator itr = root.begin(); itr != root.end(); itr++) {
    std::string id = itr.key().asString();
    Json::Value j_actor = *itr;
    Node* node = BuildNode(j_actor["elem"]);
    m_actors[id] = node;
  }
};

Node* ActorCatalog::BuildNode(Json::Value j_node) {
  std::string type = j_node.get("type", "").asString();
  Node* node;
  if (type.compare("point") == 0) {
    node = new Node2D();
    SetNode2D(node, j_node);
  } else if (type.compare("sprite") == 0) {
    node = new SpriteNode();
    SetNode2D(node, j_node);
    SetSpriteNode(node, j_node);
  }
  node->SetId(j_node.get("id","").asString());
  node->OnInit(); // Temp
  Json::Value children = j_node["children"];
  if (children.size() > 0) {
    for (Json::ValueIterator itr = children.begin(); itr != children.end(); itr++) {
      Node* child_node = BuildNode(*itr);
      node->AddChild(child_node);
      SetParent(child_node, node);
    }
  }
  return node;
};

void ActorCatalog::SetNode2D(Node* node, Json::Value& j_node) {
  Node2D* _node = static_cast<Node2D*>(node);
  _node->SetX(j_node.get("x", 0).asDouble());
  _node->SetY(j_node.get("y", 0).asDouble());
  _node->SetRotation(j_node.get("rotation", 0).asDouble() * M_PI);
  _node->SetScale(j_node.get("scale", 1).asDouble());
};

void ActorCatalog::SetSpriteNode(Node* node, Json::Value& j_node) {
  SpriteNode* _node = static_cast<SpriteNode*>(node);
  _node->SetWidth(j_node.get("width", 0).asDouble());
  _node->SetHeight(j_node.get("height", 0).asDouble());
  _node->SetVTiles(j_node.get("vtiles", 1).asInt());
  _node->SetHTiles(j_node.get("htiles", 1).asInt());
  _node->SetFrame(j_node.get("frame", 0).asInt());
  _node->SetCentered(j_node.get("centered", true).asBool());
  _node->SetFlipH(j_node.get("flipv", false).asBool());
  _node->SetFlipV(j_node.get("fliph", false).asBool());
  _node->SetPath(j_node.get("path","").asString());
};

void ActorCatalog::SetParent(Node* child, Node* parent) {
  if (dynamic_cast<Node2D*>(child) && dynamic_cast<Node2D*>(parent)) {
    static_cast<Node2D*>(child)->SetParent(static_cast<Node2D*>(parent));
  }
};

void ActorCatalog::Flush() {
};
