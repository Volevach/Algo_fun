CC = g++
CFLAGS = -g -O2
DEPS = stdafx.h
OBJECTS = Sobel_Filter.o SobelOp.o 

Sobel_Filter: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Sobel_Filter

clean:
	-rm -f *.o core *.core
	
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
