LOCAL_PATH := $(call my-dir)/..

#Static libs

#SDL2
include $(CLEAR_VARS)
LOCAL_MODULE    := libSDL2
LOCAL_SRC_FILES := ../staticlibs/$(TARGET_ARCH_ABI)/libSDL2.a

include $(PREBUILT_STATIC_LIBRARY)

#Quake (main app)

include $(CLEAR_VARS)

LOCAL_PATH := $(LOCAL_PATH)/../../Quake

LOCAL_MODULE := vkQuake

SDL_PATH := ../SDL2

PROJECT_FILES := \
$(LOCAL_PATH)/bgmusic.c \
$(LOCAL_PATH)/cd_null.c \
$(LOCAL_PATH)/cfgfile.c \
$(LOCAL_PATH)/chase.c \
$(LOCAL_PATH)/cl_demo.c \
$(LOCAL_PATH)/cl_input.c \
$(LOCAL_PATH)/cl_main.c \
$(LOCAL_PATH)/cl_parse.c \
$(LOCAL_PATH)/cl_tent.c \
$(LOCAL_PATH)/cmd.c \
$(LOCAL_PATH)/common.c \
$(LOCAL_PATH)/console.c \
$(LOCAL_PATH)/crc.c \
$(LOCAL_PATH)/cvar.c \
$(LOCAL_PATH)/gl_draw.c \
$(LOCAL_PATH)/gl_fog.c \
$(LOCAL_PATH)/gl_heap.c \
$(LOCAL_PATH)/gl_mesh.c \
$(LOCAL_PATH)/gl_model.c \
$(LOCAL_PATH)/gl_refrag.c \
$(LOCAL_PATH)/gl_rlight.c \
$(LOCAL_PATH)/gl_rmain.c \
$(LOCAL_PATH)/gl_rmisc.c \
$(LOCAL_PATH)/gl_screen.c \
$(LOCAL_PATH)/gl_sky.c \
$(LOCAL_PATH)/gl_texmgr.c \
$(LOCAL_PATH)/gl_vidsdl.c \
$(LOCAL_PATH)/gl_warp.c \
$(LOCAL_PATH)/host.c \
$(LOCAL_PATH)/host_cmd.c \
$(LOCAL_PATH)/image.c \
$(LOCAL_PATH)/in_sdl.c \
$(LOCAL_PATH)/keys.c \
$(LOCAL_PATH)/main_android.c \
$(LOCAL_PATH)/mathlib.c \
$(LOCAL_PATH)/menu.c \
$(LOCAL_PATH)/net_bsd.c \
$(LOCAL_PATH)/net_dgrm.c \
$(LOCAL_PATH)/net_loop.c \
$(LOCAL_PATH)/net_main.c \
$(LOCAL_PATH)/net_udp.c \
$(LOCAL_PATH)/pl_android.c \
$(LOCAL_PATH)/pr_cmds.c \
$(LOCAL_PATH)/pr_edict.c \
$(LOCAL_PATH)/pr_exec.c \
$(LOCAL_PATH)/r_alias.c \
$(LOCAL_PATH)/r_brush.c \
$(LOCAL_PATH)/r_part.c \
$(LOCAL_PATH)/r_sprite.c \
$(LOCAL_PATH)/r_world.c \
$(LOCAL_PATH)/sbar.c \
$(LOCAL_PATH)/snd_codec.c \
$(LOCAL_PATH)/snd_dma.c \
$(LOCAL_PATH)/snd_flac.c \
$(LOCAL_PATH)/snd_mem.c \
$(LOCAL_PATH)/snd_mikmod.c \
$(LOCAL_PATH)/snd_mix.c \
$(LOCAL_PATH)/snd_modplug.c \
$(LOCAL_PATH)/snd_mp3.c \
$(LOCAL_PATH)/snd_mpg123.c \
$(LOCAL_PATH)/snd_opus.c \
$(LOCAL_PATH)/snd_sdl.c \
$(LOCAL_PATH)/snd_umx.c \
$(LOCAL_PATH)/snd_vorbis.c \
$(LOCAL_PATH)/snd_wave.c \
$(LOCAL_PATH)/strlcat.c \
$(LOCAL_PATH)/strlcpy.c \
$(LOCAL_PATH)/sv_main.c \
$(LOCAL_PATH)/sv_move.c \
$(LOCAL_PATH)/sv_phys.c \
$(LOCAL_PATH)/sv_user.c \
$(LOCAL_PATH)/sys_android.c \
$(LOCAL_PATH)/view.c \
$(LOCAL_PATH)/wad.c \
$(LOCAL_PATH)/world.c \
$(LOCAL_PATH)/zone.c

PROJECT_FILES += $(LOCAL_PATH)/../Android/jni/vkQuake/include/vulkanandroid.c
PROJECT_FILES += $(wildcard $(LOCAL_PATH)/../Shaders/compiled/*.c)

LOCAL_CFLAGS := -DVK_USE_PLATFORM_ANDROID_KHR
LOCAL_CFLAGS += -DVK_NO_PROTOTYPES
LOCAL_CFLAGS += -std=c99
#Required for SDL
LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../Android/jni/vkQuake/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../Android/jni/SDL2/include
LOCAL_C_INCLUDES += $(VULKAN_SDK)/include

LOCAL_SRC_FILES := $(PROJECT_FILES)

LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true

LOCAL_STATIC_LIBRARIES += android_native_app_glue
LOCAL_STATIC_LIBRARIES += cpufeatures
LOCAL_STATIC_LIBRARIES += libSDL2

LOCAL_LDLIBS := -landroid -llog -lz -ldl -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)
$(call import-module, android/cpufeatures)