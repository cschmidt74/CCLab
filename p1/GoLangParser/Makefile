CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Lexer.cpp Parser.cpp Token.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=exec

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


