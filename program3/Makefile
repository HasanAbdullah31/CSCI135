CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

OBJS = ElectoralVotes.o ElectionResults.o program3.o
TARGET = program3.exe

$(TARGET) : ElectionResults.h $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)
ElectionResults.h : ElectoralVotes.h
ElectoralVotes.o : ElectoralVotes.h ElectoralVotes.cpp
	$(CC) $(CFLAGS) ElectoralVotes.cpp -o ElectoralVotes.o
ElectionResults.o : ElectionResults.h ElectionResults.cpp
	$(CC) $(CFLAGS) ElectionResults.cpp -o ElectionResults.o
program3.o : ElectoralVotes.h ElectionResults.h program3.cpp
	$(CC) $(CFLAGS) program3.cpp -o program3.o
tar :
	tar cfv program3.tar Makefile ElectoralVotes.h ElectoralVotes.cpp \
                             ElectionResults.h ElectionResults.cpp program3.cpp
clean :
	\rm *.o *~ $(TARGET) program3.tar
