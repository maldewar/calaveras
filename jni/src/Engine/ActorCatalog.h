#ifndef _ACTORCATALOG_H_
    #define _ACTORCATALOG_H_

#include <fstream>
#include <unordered_map>
#include <string>
#include "json.h"
#include "../Model/Node.h"

class ActorCatalog
{
    private:
        static std::string m_filename;
        static std::unordered_map<std::string, Node*> m_actors;

    public:
        /**
         * Loads all the actors contained in the catalog.
         */
        static void Init();
        static Node* GetActor(std::string id);
        /**
         * Cleans all the object used by the catalog.
         */
        static void Flush();

    private:
        static void BuildCatalog(Json::Value root);
        static Node* BuildNode(Json::Value node);
        static void SetNode2D(Node* node, Json::Value& j_node);
        static void SetSpriteNode(Node* node, Json::Value& j_node);
        static void SetParent(Node* child, Node* parent);

};
#endif
