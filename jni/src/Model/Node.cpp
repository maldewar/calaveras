#include "Node.h"
#include "../Util/Log.h"

Node::Node() {
  m_id = "";
  m_loop_enabled = true;
};

void Node::SetId(std::string id) {
  m_id = id;
};

std::string Node::GetId() {
  return m_id;
};

std::unordered_map<std::string, Node*> Node::GetChildren() {
  return m_children;
};

bool Node::AddChild(Node* node) {
  if (node->GetId().compare("") != 0 && 
      m_children.count(node->GetId()) == 0) {
    m_children[node->GetId()] = node;
    return true;
  }
  return false;
};

bool Node::RemoveChild(std::string id) {
  if (HasChild(id)) {
    m_children.erase(id);
    return true;
  }
  return false;
};

bool Node::RemoveDeleteChild(std::string id) {
  Node* node = m_children[id];
  if (node) {
    m_children.erase(id);
    delete node;
    return true;
  }
  return false;
};

bool Node::HasChild(std::string id) {
  if (m_children.count(id) > 0)
    return true;
  return false;
};

Node* Node::GetNode(std::string id) {
  if (HasChild(id))
    return m_children[id];
  return nullptr;
};

void Node::EnableLoop(bool enabled) {
  m_loop_enabled = enabled;
};

bool Node::IsLoopEnabled() {
  return m_loop_enabled;
};

void Node::OnInit() {
  for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
    it->second->OnInit();
  }
};

void Node::OnLoop() {
  if (m_loop_enabled) {
    for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
      it->second->OnLoop();
    }
  }
};

void Node::OnRender() {
  for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
    it->second->OnRender();
  }
};

void Node::OnCleanUp() {
  for ( auto it = m_children.begin(); it != m_children.end(); ++it ) {
    it->second->OnCleanUp();
  }
};
