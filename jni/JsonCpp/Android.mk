LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

#LS_CPP:= $(subst $(1)/,,$(wildcard $(1)/$(2)/*.cpp))
#JSON_CPP_CPP:= $(call LS_CPP, $(LOCAL_PATH), src/lib_json)

LOCAL_MODULE:= JsonCpp
LOCAL_SRC_FILES := /src/lib_json/json_value.cpp \
/src/lib_json/json_reader.cpp \
/src/lib_json/json_writer.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)
LOCAL_CPPFLAGS += -fexceptions

include $(BUILD_STATIC_LIBRARY)
