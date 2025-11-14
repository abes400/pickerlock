CC 					= g++
STD 				= 11

INCLUDE_DIRS 		= project/include
LIB_INCLUDE_DIRS	= project/lib/include

CPP_SRCS 			= project/src/*.cpp

LINKED_LIBS			= project/lib/bin/libraylib_macosx_uni.a


# macOS specific opts
MACOS_LINKED_LIBS 	= -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
MACOS_ARCHS			= -arch x86_64 -arch arm64
MACOS_OUTPUT_DIR 	= macosx_universal

build_osx:
	@rm -rf dist
	mkdir dist
	mkdir dist/macosx_universal

	$(CC) \
	-std=c++$(STD) \
	$(MACOS_ARCHS) \
	-I$(INCLUDE_DIRS) \
	-I$(LIB_INCLUDE_DIRS) \
	$(CPP_SRCS) \
	$(MACOS_LINKED_LIBS) \
	$(LINKED_LIBS) \
	-o dist/$(MACOS_OUTPUT_DIR)/Pickerlock

	cp -r project/assets dist/$(MACOS_OUTPUT_DIR)/
	./dist/$(MACOS_OUTPUT_DIR)/Pickerlock