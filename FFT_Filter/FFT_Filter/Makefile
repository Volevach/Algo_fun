CC = g++
CFLAGS = -g -O2
DEPS = stdafx.h
OBJECTS = FFT_Filter.o Complex.o FFT_Trans.o Wave_Proc.o WaveParam.o BP_Filter.o

FFT_Filter: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o FFT_Filter

clean:
	-rm -f *.o core *.core
	
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
