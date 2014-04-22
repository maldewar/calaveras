#ifndef _NODE_H_
    #define _NODE_H_

#include <string>
#include <unordered_map>

/**
 * Basic processal element.
 */
class Node {
  private:
    std::string m_id;
    std::unordered_map<std::string, Node*> m_children;
    bool m_loop_enabled;

  public:
    /**
    * Class constructor.
    */
    Node();
    /**
     * Sets the Id of the node.
     * @param Id of the node.
     */
    void SetId(std::string id);
    /**
     * Gets the Id of the node.
     * @return Id of the node.
     */
    std::string GetId();
    /**
     * Get all the children of this node.
     * @return Children of this node.
     */
    std::unordered_map<std::string, Node*> GetChildren();
    /**
     * Add a child to this node.
     * @param child Node to add.
     * @return True if the Node has been added.
     */
    bool AddChild(Node* child);
    /**
     * Removes a child Node given its Id.
     * @param id Id of the Node to remove.
     * @return True if the Node was removed.
     */
    bool RemoveChild(std::string id);
    /**
     * Removes and deletes a child Node given its id.
     * @param id Id of the Node to remove and delete.
     * @return True if the Node was removed and deleted.
     */
    bool RemoveDeleteChild(std::string id);
    /**
     * Ask if a Node is contained given its Id.
     * @param id Id of the Node.
     * @return True is the Node is present.
     */
    bool HasChild(std::string id);
    /**
     * Gets a Node given its Id.
     * @param id Ide of the Node.
     * @return Node if found, if not nullptr is returned.
     */
    Node* GetNode(std::string id);
    /**
     * Turn on or off the call of OnLoop on this instance.
     * @param enabled True if the OnLoop call is enabled.
     */
    void EnableLoop(bool enabled);
    /**
     * Is the OnLoop call enabled.
     * @return True if the OnLoop call is enabled.
     */
    bool IsLoopEnabled();
    /**
     * Called right before the scene starts to play.
     */
    virtual void OnInit() = 0;
    /**
     * Called on every loop step of the application.
     */
    virtual void OnLoop() = 0;
    /**
     * Called on every rendering step of the application.
     */
    virtual void OnRender() = 0;
    /**
     * Called when cleaning up the scene.
     */
    virtual void OnCleanUp() = 0;

};
#endif
