LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE:= avcodec
LOCAL_SRC_FILES:= libavcodec.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= avdevice
LOCAL_SRC_FILES:= libavdevice.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= avfilter
LOCAL_SRC_FILES:= libavfilter.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= avformat
LOCAL_SRC_FILES:= libavformat.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE :=  avutil
LOCAL_SRC_FILES := libavutil.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swresample
LOCAL_SRC_FILES := libswresample.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swscale
LOCAL_SRC_FILES := libswscale.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ndkhelper
LOCAL_SRC_FILES := com_ndk_lqy_ndk_NDKHelper.c
LOCAL_LDLIBS := -llog -lz
LOCAL_SHARED_LIBRARIES:= avcodec \
                         avdevice \
                         avfilter \
                         avformat \
                         avutil \
                         swresample \
                         swscale
include $(BUILD_SHARED_LIBRARY)