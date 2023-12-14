CC = g++
CFLAGS = -c -Wall

all: prodcon

prodcon: main.o prodcon.o summary_details.o tands.o buffer.o
			$(CC) -O -o prodcon main.o prodcon.o summary_details.o tands.o buffer.o -pthread

main.o: main.cpp
			$(CC) $(CFLAGS) main.cpp

tands.o: tands.cpp
			$(CC) $(CFLAGS) tands.cpp

prodcon.o: prodcon.cpp	
			$(CC) $(CFLAGS) prodcon.cpp

buffer.o: buffer.cpp
			$(CC) $(CFLAGS) buffer.cpp

summary_details.o: summary_details.cpp
			$(CC) $(CFLAGS) summary_details.cpp

clean:
			rm -f *o prodcon