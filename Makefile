CC		= g++
CFLAGS	= -Wall
LDFLAGS	=
LIBS	= -lm
SRCS	= $(wildcard ./*.c)
OBJS	= $(SRCS:.c=.o)


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