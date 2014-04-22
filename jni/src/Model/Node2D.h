#ifndef _NODE2D_H_
    #define _NODE2D_H_

#include "Node.h"

/**
 * Basic positional element.
 */
class Node2D : public Node {
  protected:
    float m_x;
    float m_y;
    float m_rotation;
    float m_scale;
    Node2D* m_parent;

  public:
    float x_offset;
    float y_offset;
    float rotation_offset;
    float scale_offset;

  public:
    /**
     * Class constructor.
     */
    Node2D();
    /**
     * Sets the X cartesian coordinate in meters for the Elem.
     * @param x X coordinate in meters.
     */
    void SetX(float x);
    /**
     * Gets the X cartesian coordinate in meters for the Elem.
     * @returns X coordinate in meters.
     */
    float GetX();
    /**
     * Sets the Y cartesian coordinate in meters for the Elem.
     * @param y Y coordinate in meters.
     */
    void SetY(float y);
    /**
     * Gets the Y cartesian coordinate in meters for the Elem.
     * @returns Y coordinate in meters.
     */
    float GetY();
    /**
     * Sets the scale of this Elem.
     * @param scale Scale of this Elem.
     */
    void SetScale(float scale);
    /**
     * Gets the scale of this Elem.
     * @returns Scale of this Elem.
     */
    float GetScale();
    /**
     * Sets the initial rotation for this Elem.
     * @param rotation Rotation in radians.
     */
    void SetRotation(float rotation);
    /**
     * Gets the initial rotation for this Elem.
     * @returns Rotation in radians.
     */
    float GetRotation();
    void SetParent(Node2D* parent);
    void OnInit();
    void OnLoop();
    void OnRender();
    void OnCleanUp();

};
#endif
