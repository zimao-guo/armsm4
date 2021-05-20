LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := AESTEST
LOCAL_SRC_FILES := test-lib.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_CFLAGS := -g -mfloat-abi=softfp -mfpu=neon -march=armv8-a+crc+crypto
LOCAL_LDLIBS := -lz -llog  
TARGET_ARCH_ABI :=arm64-v8a
LOCAL_ARM_MODE := arm 
LOCAL_ARM_NEON := true
include $(BUILD_SHARED_LIBRARY)
