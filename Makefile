CC := g++
LFLAGS = -lsfml-window -lsfml-audio

a.out:
	$(CC) *.cpp $(LFLAGS)