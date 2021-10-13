CC		= g++
CFLAGS	= -Wall -g3 -ggdb3#-O3 -std=c++17
LDFLAGS	= -lpthread
LIBS	= -lm
SRCS	= $(wildcard ./*.cpp)
OBJS	= $(SRCS:.cpp=.o)
IMAGES  = $(wildcard ./image_*.ppm)


main: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o main

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -c $(SRCS)

.PHONY: clean
clean:
	rm -rf *.o

convert: $(IMAGES)
	for i in $(IMAGES);do \
		convert $$i png/$${i%.ppm}.png;\
	done
