CFLAGS = -g -O0  #Debug symbols, and no optimization

#-------------------------------------------------------------
# Makefile Targets
#-------------------------------------------------------------

HEADERS = wordList.h gameState.h
OBJECTS = hangman.o gameState.o wordList.o

all: hangman

%.o: %.c $(HEADERS)
	gcc -c $(CFLAGS) $< -o $@

hangman: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f hangman

