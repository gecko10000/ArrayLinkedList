CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic

TARGET = ll_tests
MODULES = normal_ll array_ll
OBJECTS = $(patsubst %,%.o,${MODULES})

.PHONY: all clean

all: $(TARGET)

$(TARGET): % : %.o $(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
