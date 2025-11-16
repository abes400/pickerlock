CC 					= g++
STD 				= 11

INCLUDE_DIRS 		= project/include
LIB_INCLUDE_DIRS	= project/lib/include

CPP_SRCS 			= project/src/*.cpp

LINKED_LIB_PATH		= project/lib/bin/

# windows specific opts
WINDOWS_LINKED_LIBS 	= -lopengl32 -lgdi32 -lwinmm
WINDOWS_RAYLIB_LINKED = libraylib_windows_x64.a
WINDOWS_OUTPUT_DIR 	= windows_x64

# macOS specific opts
MACOS_LINKED_LIBS 	= -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
MACOS_RAYLIB_LINKED = libraylib_macosx_uni.a
MACOS_ARCHS			= -arch x86_64 -arch arm64
MACOS_OUTPUT_DIR 	= macosx_universal

win:
	@rm -rf dist
	mkdir dist
	mkdir dist/$(WINDOWS_OUTPUT_DIR)

	$(CC) \
	-std=c++$(STD) \
	-I$(INCLUDE_DIRS) \
	-I$(LIB_INCLUDE_DIRS) \
	$(CPP_SRCS) \
	$(LINKED_LIB_PATH)$(WINDOWS_RAYLIB_LINKED) $(WINDOWS_LINKED_LIBS) \
	-o dist/$(WINDOWS_OUTPUT_DIR)/Pickerlock \
	-static 

	cp -r project/assets dist/$(WINDOWS_OUTPUT_DIR)/
	./dist/$(WINDOWS_OUTPUT_DIR)/Pickerlock

osx:
	@rm -rf dist
	mkdir dist
	mkdir dist/$(MACOS_OUTPUT_DIR)
	$(CC) \
	-std=c++$(STD) \
	$(MACOS_ARCHS) \
	-I$(INCLUDE_DIRS) \
	-I$(LIB_INCLUDE_DIRS) \
	$(CPP_SRCS) \
	$(MACOS_LINKED_LIBS) $(LINKED_LIB_PATH)$(MACOS_RAYLIB_LINKED) \
	-o dist/$(MACOS_OUTPUT_DIR)/Pickerlock

	cp -r project/assets dist/$(MACOS_OUTPUT_DIR)/
	./dist/$(MACOS_OUTPUT_DIR)/Pickerlock