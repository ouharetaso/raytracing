CC		= g++
CFLAGS	= -Wall -g3
LDFLAGS	=
LIBS	= -lm
SRCS	= $(wildcard ./*.cpp)
OBJS	= $(SRCS:.cpp=.o)


main: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o main

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -c $(SRCS)

.PHONY: clean
clean:
	rm -rf *.o

.SILENT:
run:main
	./main
