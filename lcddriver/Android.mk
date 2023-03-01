LOCAL_PATCH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDE += \
	$(LOCAL_PATH)/../../share/ndk/include \
	$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include

LOCAL_SRC_FILES:= \
	fb_test.c


LOCAL_MODULE_TAGS := eng
LOCAL_MODUEL := fb_test

include $(BUILD_EXECUATABLE)
