PROGRAM = LookAround
CC      = gcc
CFLAGS  = -g -std=c99  -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL

$(PROGRAM) : main.o player_data_and_movemeant.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

main.o : main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o  $@ $^ $(LDLIBS)

player_data_and_movemeant.o: player_data_and_movemeant.c player_data_and_movemeant.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<



# terrain.o : terrain.c terrain.h
# 	$(CC) $(CFLAGS) $(LDFLAGS) -c -o  $@ $< $(LDLIBS)




clean:
	rm *.o
