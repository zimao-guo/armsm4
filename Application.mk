APP_PROJECT_PATH := $(call my-dir)/..
APP_MODULE := AESTEST
APP_CFLAGS := -Wno-error=format-security
APP_ABI := arm64-v8a
APP_PLATFORM := android-26
APP_CPPFLAGS += -fexceptions
APP_STL :=stlport_static
