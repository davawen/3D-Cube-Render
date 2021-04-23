# Change this to your wanted compiler
CC=g++

CFLAGS=-c -Wall -Wno-unknown-pragmas

SOURCE_FILES = main.cpp matrix.cpp vector.cpp cube.cpp
SOURCE_FILES := $(addprefix src/,$(SOURCE_FILES))

OBJECT_FILES = $(addprefix obj/,$(notdir $(SOURCE_FILES:%.cpp=%.o)))

# Change this to your sfml installation
INCLUDE_DIRECTORIES = C:/Libraries/SFML-2.5.1/include/
LIB_DIRECTORIES = C:/Libraries/SFML-2.5.1/lib/

INCLUDE_DIRECTORIES := $(addprefix -I,$(INCLUDE_DIRECTORIES))
LIB_DIRECTORIES := $(addprefix -L,$(LIB_DIRECTORIES))

LIBS = $(addprefix -l,sfml-graphics-d sfml-window-d sfml-system-d sfml-main-d sfml-audio-d sfml-network-d openal32)

all: prog
	@echo Launching app...
	@./bin/main.exe

prog: $(OBJECT_FILES)
	@echo Linking app...
	$(CC) -o bin/main.exe $^ $(LIB_DIRECTORIES) $(LIBS)

obj/%.o: src/%.cpp
	@echo Compiling $<
	$(CC) $(CFLAGS) -o $@ $< $(INCLUDE_DIRECTORIES)

clean:
	rd -r *.o