#ifndef _SCENEEXT_H_
    #define _SCENEEXT_H_
#include <string>
#include "AreaNode.h"

/**
 * Extensions and helpers for an scene.
 */
class SceneExt {
    private:
        bool m_isSelecting;
        bool m_hasSelection;
        float m_selectX;
        float m_selectY;
        float m_selectZenithX;
        float m_selectZenithY;
        float m_selectNadirX;
        float m_selectNadirY;
        int m_objectType;
        AreaNode* m_nodeA;
        AreaNode* m_nodeB;

    public:
        /**
         * Class constructor.
         */
        SceneExt();
        /**
         * Class destructor.
         */
        ~SceneExt();
        void SetIsSelecting(bool isSelecting);
        bool IsSelecting();
        void SetHasSelection(bool hasSelection);
        bool HasSelection();
        void SetSelectX(float selectX);
        float GetSelectX();
        void SetSelectY(float selectY);
        float GetSelectY();
        void SetSelectZenithX(float selectZenithX);
        float GetSelectZenithX();
        void SetSelectZenithY(float selectZenithY);
        float GetSelectZenithY();
        void SetSelectNadirX(float selectNadirX);
        float GetSelectNadirX();
        void SetSelectNadirY(float selectNadirY);
        float GetSelectNadirY();
        void SetObjectType(int objectType);
        int GetObjectType();
        void SetNodeA(AreaNode* nodeA);
        AreaNode* GetNodeA();
        void SetNodeB(AreaNode* nodeB);
        AreaNode* GetNodeB();
        
        void OnInit();
        void OnLoop();

};
#endif
