#ifndef LOG_H_
#define LOG_H_

#include <android/log.h>
#pragma once

#ifdef LOGRECORD
	#define LOG_TAG "CORE-JNILOG"
	#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
	#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
	#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)
#else
	#define LOGD(fmt, args...)
	#define LOGI(fmt, args...)
	#define LOGE(fmt, args...)
#endif //LOGRECORD

#endif