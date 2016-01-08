CC = gcc
CFLAGS = -g -O2 -I
DEPS = stdafx.h
OBJECTS = FFT_Filter.o Complex.o FFT_1024.o Wave_Proc.o WaveParam.o BP_Filter.o

FFT_Filter: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o FFT_Filter.exe

clean:
	-rm -f *.o core *.core
	
%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<
