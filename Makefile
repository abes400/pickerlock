CC 						= g++
STD 					= 17

INCLUDE_DIRS 			= project/include
LIB_INCLUDE_DIRS		= project/lib/include

CPP_SRCS 				= project/src/*.cpp

LINKED_LIB_PATH			= project/lib/bin/
APP_RES_PATH			= appres

EXEC_NAME				= Pickerlock

# windows specific opts
WINDOWS_LINKED_LIBS 	= -lopengl32 -lgdi32 -lwinmm
WINDOWS_RAYLIB_LINKED 	= libraylib_windows_x64.a
WINDOWS_OUTPUT_DIR 		= windows_x64

win:
	clear
	mkdir -p dist/$(WINDOWS_OUTPUT_DIR)/$(EXEC_NAME) 
	cp -r project/assets/* dist/$(WINDOWS_OUTPUT_DIR)/$(EXEC_NAME) 
	cp -r project/$(APP_RES_PATH)/icon.png dist/$(WINDOWS_OUTPUT_DIR)/$(EXEC_NAME)/texture 

	windres project/$(APP_RES_PATH)/win/win.rc -O coff -o dist/$(WINDOWS_OUTPUT_DIR)/winicon.o

	$(CC) -std=c++$(STD) 												\
	dist/$(WINDOWS_OUTPUT_DIR)/winicon.o								\
	$(CPP_SRCS) 														\
	-I$(INCLUDE_DIRS) -I$(LIB_INCLUDE_DIRS) 							\
	$(LINKED_LIB_PATH)$(WINDOWS_RAYLIB_LINKED) $(WINDOWS_LINKED_LIBS) 	\
	-o dist/$(WINDOWS_OUTPUT_DIR)/$(EXEC_NAME)/$(EXEC_NAME) 			\
	-static																\
    -mwindows

	rm dist/$(WINDOWS_OUTPUT_DIR)/winicon.o

	start .\dist\$(WINDOWS_OUTPUT_DIR)\

	@echo [ INFO ] WINDOWS BUILD SUCCEEDED. Output located at dist/$(WINDOWS_OUTPUT_DIR)/

# macOS specific opts
MACOS_ARCHS			= -arch x86_64 -arch arm64
MACOS_LINKED_LIBS 	= -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
MACOS_RAYLIB_LINKED = libraylib_macosx_uni.a
MACOS_OUTPUT_DIR 	= macosx_universal

osx:
	clear
	mkdir -p dist/$(MACOS_OUTPUT_DIR)/$(EXEC_NAME).app/Contents
	mkdir -p dist/$(MACOS_OUTPUT_DIR)/$(EXEC_NAME).app/Contents/Resources
	mkdir -p dist/$(MACOS_OUTPUT_DIR)/$(EXEC_NAME).app/Contents/MacOS
	cp project/$(APP_RES_PATH)/osx/Info.plist dist/$(MACOS_OUTPUT_DIR)/$(EXEC_NAME).app/Contents
	cp project/$(APP_RES_PATH)/osx/application.icns dist/$(MACOS_OUTPUT_DIR)/$(EXEC_NAME).app/Contents/Resources
	cp -r project/assets/* dist/$(MACOS_OUTPUT_DIR)/$(EXEC_NAME).app/Contents/Resources


	$(CC) -std=c++$(STD) 											\
	$(MACOS_ARCHS) 													\
	$(CPP_SRCS) 													\
	-I$(INCLUDE_DIRS) -I$(LIB_INCLUDE_DIRS) 						\
	$(MACOS_LINKED_LIBS) $(LINKED_LIB_PATH)$(MACOS_RAYLIB_LINKED)	\
	-o dist/$(MACOS_OUTPUT_DIR)/$(EXEC_NAME).app/Contents/MacOS/$(EXEC_NAME)

	open ./dist/$(MACOS_OUTPUT_DIR)/

	@echo [ INFO ] MACOS BUILD SUCCEEDED. Output located at dist/$(MACOS_OUTPUT_DIR)/


clear:
	rm -rf dist
	@echo [ INFO ] OUTPUT FILES DELETED.

# web specific opts
# WASM_CC 			= emcc
# WASM_FLAGS			= USE_GLFW=3 -s ASYNCIFY -s ASSERTIONS -DPLATFORM_WEB
# WASM_RAYLIB_LINKED 	= libraylib_wasm.a
# WASM_OUTPUT_DIR 	= web
# WASM_OUTPUT_HTML	= index.html

# WASM_PRELOAD		= project/assets@/
# WASM_STACK_MB		= 64
# WASM_INIT_MEM_MB	= 128
# WASM_SHELL			= shell.html

# web:
# 	clear
#	mkdir -p dist/$(WASM_OUTPUT_DIR)

#	$(WASM_CC) -std=c++$(STD)								\
	$(CPP_SRCS) 											\
	-I$(INCLUDE_DIRS) -I$(LIB_INCLUDE_DIRS) 				\
	$(LINKED_LIB_PATH)$(WASM_RAYLIB_LINKED) 				\
	-o dist/$(WASM_OUTPUT_DIR)/$(WASM_OUTPUT_HTML) 			\
	--preload-file $(WASM_PRELOAD) 							\
	-s TOTAL_STACK=$(WASM_STACK_MB)MB 						\
    -s INITIAL_MEMORY=$(WASM_INIT_MEM_MB)MB 				\
	-s EXPORTED_RUNTIME_METHODS=['HEAPF32','HEAPU8']		\
	--shell-file project/$(APP_RES_PATH)/web/$(WASM_SHELL)	\
	-s $(WASM_FLAGS)

#	@echo [ INFO ] WEB BUILD SUCCEEDED. Output located at dist/$(WASM_OUTPUT_DIR)/