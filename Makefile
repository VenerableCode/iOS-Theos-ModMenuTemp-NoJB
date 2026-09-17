ARCHS = arm64
TARGET = iphone:clang:latest:latest

DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = ktemp

$(TWEAK_NAME)_FRAMEWORKS = \
    UIKit \
    Foundation \
    Security \
    QuartzCore \
    CoreGraphics \
    CoreText \
    AVFoundation \
    Accelerate \
    GLKit \
    SystemConfiguration \
    GameController \
    Metal \
    MetalKit

$(TWEAK_NAME)_CFLAGS = \
    -fobjc-arc \
    -Wall \
    -Wno-deprecated-declarations \
    -Wno-unused-variable \
    -Wno-unused-value \
    -Wno-unused-function

$(TWEAK_NAME)_CCFLAGS = \
    -std=c++17 \
    -fno-rtti \
    -DNDEBUG \
    -Wall \
    -Wno-deprecated-declarations \
    -Wno-unused-variable \
    -Wno-unused-value \
    -Wno-unused-function \
    -Wno-writable-strings \
    -DKOMARU


$(TWEAK_NAME)_FILES = \
    MenuLoad/ImGuiDrawView.xm \
    $(wildcard MenuLoad/*.mm) \
    $(wildcard MenuLoad/GUI/*.mm) \
    $(wildcard Source/*.mm) \
    $(wildcard ImGui/*.mm) \
    $(wildcard ImGui/*.cpp) \
    \
    utils/libtitanox/libtitanox/main.mm \
    utils/libtitanox/brk_hook/Hook/hook.c \
    utils/libtitanox/brk_hook/Hook/mach_excServer.c \
    utils/libtitanox/fishhook/fishhook.c \
    utils/libtitanox/mempatch/THPatchMem.mm \
    utils/libtitanox/MemX/VMTWrapper.mm \
    utils/libtitanox/static-inline-hook/sih.mm \
    utils/libtitanox/utils/utils.mm \
    utils/libtitanox/vm_funcs/vm.mm

$(TWEAK_NAME)_CFLAGS += \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/libtitanox \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/brk_hook/Hook \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/fishhook \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/mempatch \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/MemX \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/static-inline-hook \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/utils \
    -I$(THEOS_PROJECT_DIR)/utils/libtitanox/vm_funcs

include $(THEOS_MAKE_PATH)/tweak.mk
include $(THEOS)/makefiles/aggregate.mk
