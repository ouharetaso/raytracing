CC		= g++
CFLAGS	= -Wall -g3 -ggdb3#-O3 -std=c++17
LDFLAGS	= -lpthread
LIBS	= -lm
SRCS	= $(wildcard ./*.cpp)
OBJS	= $(SRCS:.cpp=.o)
IMAGE   = image.ppm


main: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o main

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -c $(SRCS)

.PHONY: clean
clean:
	rm -rf *.o

.SILENT:
run:main
	./main > ${IMAGE}
	convert ${IMAGE} $(IMAGE:.ppm=.png)
