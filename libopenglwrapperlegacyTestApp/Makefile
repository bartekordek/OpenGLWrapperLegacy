ARCH := $(shell getconf LONG_BIT)
ifeq ($(OS),Windows_NT)
DYN_LIB_EXT := .dll
BUILD_ROOT := Build-Cygwin
else
DYN_LIB_EXT := .so
BUILD_ROOT := Build-Linux
endif

DIAG_FLAG := -fdiagnostics-color=always
COMPILER := clang++-6.0
CC_STAND := -std=c++17
CC := $(COMPILER) $(CC_STAND) $(ARCH_FLAG) $(DIAG_FLAG) -fPIC -pedantic -Wall -Wno-ignored-attributes
CC_LINK := $(COMPILER) $(CC_STAND) $(ARCH_FLAG) $(DIAG_FLAG)

DEBUG_FLAGS = -ggdb
RELEASE_FLAGS = -Ofast
PROJECT_NAME = libopenglWrapperLegacyPlaygroundApp
BINARY_NAME = $(PROJECT_NAME).exe
OUTPUT_DIR := ../$(BUILD_ROOT)
OUTPUT_DIR_DEBUG = $(OUTPUT_DIR)/Debug
OUTPUT_DIR_RELEASE = $(OUTPUT_DIR)/Release
RUN_DIR := ../runDir

# DEPS
DEPS_HOME := ../deps

# DEPS::OPENGLWRAPPER
OPENGLWRAPPER_HOME := ../libopenglwrapperlegacy
OPENGLWRAPPER_INC := -I $(OPENGLWRAPPER_HOME)/inc
OPENGLWRAPPER_INC += -I $(OPENGLWRAPPER_HOME)/src
OPENGLWRAPPER_LIB_DIR := ../Build-Linux
OPENGLWRAPPER_LIB_DEBUG := $(OPENGLWRAPPER_LIB_DIR)/Debug/libopenglwrapperlegacy.so
OPENGLWRAPPER_LIB_RELEASE := $(OPENGLWRAPPER_LIB_DIR)/Release/libopenglwrapperlegacy.so

# DEPS::SDL2Wrapper
SDL2W_HOME := $(DEPS_HOME)/SDL2Wrapper
SDL2W_LIB_HOME := $(SDL2W_HOME)/libsdl2wrapper
SDL2W_INC := $(SDL2W_LIB_HOME)/inc
SDL2W_INC += -I $(SDL2W_LIB_HOME)/src
SDL2W_DEPS_HOME := $(SDL2W_HOME)/deps
SDL2W_LIB := $(SDL2W_HOME)/$(BUILD_ROOT)
SDL2W_LIB_DEBUG := $(SDL2W_LIB)/Debug/libsdl2wrapper.so
SDL2W_LIB_RELEASE := $(SDL2W_LIB)/Release/libsdl2wrapper.so


# DEPS::CUL
CUL_HOME := $(SDL2W_HOME)/deps/CUL
CUL_INC := $(CUL_HOME)/libcul/inc
CUL_LIB := $(CUL_HOME)/$(BUILD_ROOT)
CUL_LIB_DEBUG := $(CUL_LIB)/Debug/libcul.so
CUL_LIB_RELEASE := $(CUL_LIB)/Release/libcul.so

IMPORT_GL_LIGBS := -lGLU -lGL -lglut -lGLEW
IMPORT_LIBS := -pthread $(IMPORT_GL_LIGBS)
IMPORT_LIBS_DEBUG := $(IMPORT_LIBS) $(OPENGLWRAPPER_LIB_DEBUG) $(CUL_LIB_DEBUG) $(SDL2W_LIB_DEBUG)
IMPORT_LIBS_RELEASE := $(IMPORT_LIBS) $(OPENGLWRAPPER_LIB_RELEASE) $(CUL_LIB_RELEASE) $(SDL2W_LIB_RELEASE)

CPP_FILES := $(wildcard *.cpp)

# OBJ:
OBJ_DEBUG_DIR := $(OUTPUT_DIR_DEBUG)/intermediate_$(PROJECT_NAME)/debug/
OBJ_RELEASE_DIR := $(OUTPUT_DIR_RELEASE)/intermediate_$(PROJECT_NAME)/release/
OBJ_DEBUG_FILES := $(addprefix $(OBJ_DEBUG_DIR),$(CPP_FILES:.cpp=.o))
OBJ_RELEASE_FILES := $(addprefix $(OBJ_RELEASE_DIR),$(CPP_FILES:.cpp=.o))

HEADERS_INC := $(OPENGLWRAPPER_INC)
HEADERS_INC += -I $(SDL2W_INC)
HEADERS_INC += -I $(CUL_INC)

BINARY_PATH_DEBUG := $(OUTPUT_DIR_DEBUG)/$(BINARY_NAME)
BINARY_PATH_RELEASE := $(OUTPUT_DIR_RELEASE)/$(BINARY_NAME)

debug:
	$(MAKE) -C $(OPENGLWRAPPER_HOME) debug
	@make $(BINARY_PATH_DEBUG)

release:
	$(MAKE) -C $(OPENGLWRAPPER_HOME) release
	@make $(BINARY_PATH_RELEASE)

run_debug: debug
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(RUN_DIR) ./$(BINARY_PATH_DEBUG)

run_release: release
	cd $(RUN_DIR);LD_LIBRARY_PATH=$(RUN_DIR) ./$(BINARY_PATH_RELEASE)

$(BINARY_PATH_DEBUG): $(OBJ_DEBUG_FILES) $(OUTPUT_DIR_DEBUG) $(OPENGLWRAPPER_LIB_DEBUG)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(BINARY_PATH_DEBUG) $(OBJ_DEBUG_FILES) $(IMPORT_LIBS_DEBUG) $(IMPORT_LIBS_FILES)
	mkdir -p $(RUN_DIR)
	cp $(SDL2W_LIB_DEBUG) $(RUN_DIR)

$(BINARY_PATH_RELEASE): $(OBJ_RELEASE_FILES) $(OUTPUT_DIR_RELEASE) $(OPENGLWRAPPER_LIB_RELEASE)
	@mkdir -p $(@D)
	$(CC_LINK) -o $(BINARY_PATH_RELEASE) $(OBJ_RELEASE_FILES) $(IMPORT_LIBS_RELEASE) $(IMPORT_LIBS_FILES)
	mkdir -p $(RUN_DIR)
	cp $(SDL2W_LIB_RELEASE) $(RUN_DIR)

$(OUTPUT_DIR_DEBUG):
	mkdir -p $@

$(OUTPUT_DIR_RELEASE):
	mkdir -p $@

$(OBJ_DEBUG_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADERS_INC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_RELEASE_DIR)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(HEADERS_INC) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -c -o $@ $<

clean:
	make -C $(OPENGLWRAPPER_HOME) clean
	rm -f $(OBJ_DEBUG_FILES)
	rm -f $(OBJ_RELEASE_FILES)
	rm -f $(OUTPUT_DEBUG)
	rm -f $(OUTPUT_RELEASE)

clear_all:
	find . -name '*.o' | xargs rm

test:
	@echo "All .o files: $(OBJ_DEBUG_FILES)"
	@echo "All .cpp files: $(CPP_FILES)"