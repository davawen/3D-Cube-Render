CC=g++

CFLAGS=-c -Wall -Wno-unknown-pragmas

SOURCE_FILES = main.cpp

INCLUDE_DIRECTORIES = ./include/ C:/Libraries/SFML-2.5.1/include/
LIB_DIRECTORIES = C:/Libraries/SFML-2.5.1/lib/

LIBS = sfml-graphics-d sfml-window-d sfml-system-d sfml-main-d sfml-audio-d sfml-network-d openal32

# The rest is voodoo
SOURCE_FILES := $(addprefix src/,$(SOURCE_FILES))

OBJECT_FILES = $(SOURCE_FILES:src/%.cpp=obj/%.o)
OBJECT_DIR = $(sort $(dir $(OBJECT_FILES)))
OBJECT_DIR := $(OBJECT_DIR:/=)

INCLUDE_DIRECTORIES := $(addprefix -I,$(INCLUDE_DIRECTORIES))
LIB_DIRECTORIES := $(addprefix -L,$(LIB_DIRECTORIES))

LIBS := $(addprefix -l,$(LIBS))

.PHONY: directories

all: directories prog
	@echo Launching app...
	@./bin/main.exe

prog: $(OBJECT_FILES)
	@$(CC) -o bin/main.exe $^ $(LIB_DIRECTORIES) $(LIBS)

obj/%.o: src/%.cpp
	@echo Compiling $<
	$(CC) $(CFLAGS) -o $@ $< $(INCLUDE_DIRECTORIES)

directories: $(OBJECT_DIR)

$(OBJECT_DIR):
	powershell md $@

clean:
	powershell rm -r ./obj/*.o
	@powershell clear