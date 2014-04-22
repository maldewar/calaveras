#ifndef _EVENT_H_
    #define _EVENT_H_
#include <SDL.h>
class Event {
    public:
        Event();
        virtual ~Event();
        virtual void OnBeforeEvent(SDL_Event* Event);
        virtual void OnEvent(SDL_Event* Event);
        virtual void OnAfterEvent(SDL_Event* Event);
        virtual void OnInputFocus();
        virtual void OnInputBlur();
        virtual void OnKeyDown(SDL_Scancode scancode, SDL_Keycode sym, Uint16 mod);
        virtual void OnKeyUp(SDL_Scancode scancode, SDL_Keycode sym, Uint16 mod);
        virtual void OnMouseFocus();
        virtual void OnMouseBlur();
        virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
        virtual void OnMouseWheel(bool Up, bool Down);    //Not implemented
        virtual void OnLButtonDown(int mX, int mY);
        virtual void OnLButtonUp(int mX, int mY);
        virtual void OnRButtonDown(int mX, int mY);
        virtual void OnRButtonUp(int mX, int mY);
        virtual void OnMButtonDown(int mX, int mY);
        virtual void OnMButtonUp(int mX, int mY);
        virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
        virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
        virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
        virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
        virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
        virtual void OnMinimize();
        virtual void OnRestore();
        virtual void OnResize(int w,int h);
        virtual void OnExpose();
        virtual void OnExit();
        virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
        virtual void OnMultiGesture(float mDTheta, float mDDist, float mX, float mY, Uint16 mFingers);
        virtual void OnFingerDown(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
        virtual void OnFingerUp(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
        virtual void OnFingerMove(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
};
 
#endif
