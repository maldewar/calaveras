LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_IMAGE_PATH := ../SDL_image
SDL_TTF_PATH := ../SDL_ttf
BOX2D_PATH := ../Box2D
JSON_CPP_PATH := ../JsonCpp
LIBROCKET_PATH := ../LibRocket

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/$(SDL_IMAGE_PATH) \
                    $(LOCAL_PATH)/$(SDL_TTF_PATH) \
                    $(LOCAL_PATH)/$(BOX2D_PATH)/Box2D \
                    $(LOCAL_PATH)/$(JSON_CPP_PATH)/include/json \
                    $(LOCAL_PATH)/$(LIBROCKET_PATH)/Include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.cpp \
    Util/CFile.cpp \
    Util/CLog.cpp \
    Util/CMath.cpp \
    Util/CTexture.cpp \
    Util/CText.cpp \
    Common/FPSManager.cpp \
    Engine/CAnimation.cpp \
    Engine/CAnimationCatalog.cpp \
    Engine/AreaCatalog.cpp \
    Engine/CSprite.cpp \
    Engine/WorldContactListener.cpp \
    Engine/RocketGlue.cpp \
    Model/CScene.cpp \
    Model/CLayer.cpp \
    Model/CWorldLayer.cpp \
    Model/CArea.cpp \
    Model/CElem.cpp \
    Model/CUnit.cpp \
    Model/CEntry.cpp \
    Manager/CSceneLoader.cpp \
    Manager/CBoxMaker.cpp \
    Renderer/CSceneRenderer.cpp \
    CEvent.cpp \
    CFPS.cpp \
    AppState.cpp \
    AppStateManager.cpp \
    AppStateIntro.cpp \
    AppStateGame.cpp \
    CApp_OnInit.cpp \
    CApp_OnEvent.cpp \
    CApp_OnLoop.cpp \
    CApp_OnRender.cpp \
    CApp_OnCleanup.cpp \
    CApp.cpp

LOCAL_SHARED_LIBRARIES := SDL2 \
                          SDL2_image \
                          SDL2_ttf \
                          Box2D \
                          JsonCpp \
                          LibRocket

LOCAL_LDLIBS := -lGLESv1_CM -llog

LOCAL_CFLAGS := -std=c++11

LOCAL_CPP_FEATURES := exceptions


include $(BUILD_SHARED_LIBRARY)
