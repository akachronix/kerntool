include $(THEOS)/makefiles/common.mk

TOOL_NAME = kerntool
kerntool_FILES = src/main.c src/kerntool-conio.c src/kerntool-info.c src/kerntool-util.c
kerntool_CFLAGS = -Iinclude
kerntool_CODESIGN_FLAGS = -Sent.xml

include $(THEOS_MAKE_PATH)/tool.mk
