LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../sdl
SDL_IMAGE_PATH := ../sdl_image
SDL_TTF_PATH := ../sdl_ttf
BOX2D_PATH := ../box2d
JSON_CPP_PATH := ../jsoncpp
LIBROCKET_PATH := ../librocket

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/$(SDL_IMAGE_PATH) \
                    $(LOCAL_PATH)/$(SDL_TTF_PATH) \
                    $(LOCAL_PATH)/$(BOX2D_PATH)/Box2D \
                    $(LOCAL_PATH)/$(JSON_CPP_PATH)/include/json \
                    $(LOCAL_PATH)/$(LIBROCKET_PATH)/Include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
    Util/File.cpp \
    Util/Log.cpp \
    Util/CMath.cpp \
    Util/TextureUtil.cpp \
    Util/Text.cpp \
    Util/SurfaceUtil.cpp \
    Util/RocketUtil.cpp \
    Util/PathUtil.cpp \
    Util/RendererUtil.cpp \
    Common/FPSManager.cpp \
    Model/Node.cpp \
    Model/Node2D.cpp \
    Model/Elem.cpp \
    Model/SpriteNode.cpp \
    Model/Vector2.cpp \
    Engine/ActorCatalog.cpp \
    Engine/Sprite.cpp \
    Engine/Animation.cpp \
    Engine/AnimationCatalog.cpp \
    Engine/Still.cpp \
    Engine/StillCatalog.cpp \
    Engine/LayeredGraphic.cpp \
    Engine/AreaCatalog.cpp \
    Engine/BgCatalog.cpp \
    Engine/I18NCatalog.cpp \
    Engine/Camera.cpp \
    Engine/WorldContactListener.cpp \
    Engine/RayCastTool.cpp \
    Engine/RocketGlue.cpp \
    Engine/Gradient.cpp \
    Engine/UserData.cpp \
    Engine/AreaUserData.cpp \
    Model/Scene.cpp \
    Model/SceneExt.cpp \
    Model/ChoiceGraph.cpp \
    Model/GraphNode.cpp \
    Model/Layer.cpp \
    Model/FgLayer.cpp \
    Model/WorldLayer.cpp \
    Model/BgLayer.cpp \
    Model/Area.cpp \
    Model/AreaNode.cpp \
    Model/LayeredElem.cpp \
    Model/Unit.cpp \
    Model/Plan.cpp \
    Model/Entry.cpp \
    Model/Exit.cpp \
    Manager/ConfigManager.cpp \
    Manager/TextureManager.cpp \
    Manager/SceneLoader.cpp \
    Manager/BoxMaker.cpp \
    Renderer/SceneRenderer.cpp \
    Renderer/CompositeRenderer.cpp \
    Renderer/LayeredGraphicRenderer.cpp \
    Renderer/ChoiceGraphRenderer.cpp \
    Event.cpp \
    FPS.cpp \
    AppState.cpp \
    AppStateManager.cpp \
    AppStateIntro.cpp \
    AppStateMain.cpp \
    AppStateGame.cpp \
    AppStateCinematic.cpp \
    Event/EventStartOnClick.cpp \
    Event/EventSlotOnClick.cpp \
    Event/EventPushStateOnClick.cpp \
    Event/EventPopStateOnClick.cpp \
    Event/EventChangeAppState.cpp \
    Event/EventChangeAppStateToGame.cpp \
    Event/EventChangeAppStateToCinematic.cpp \
    Event/EventSetSettings.cpp \
    Event/EventGameTools.cpp \
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
