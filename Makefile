CC		= g++
CFLAGS	= -Wall -mtune=native -march=native -mfpmath=both
LDFLAGS	=
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
