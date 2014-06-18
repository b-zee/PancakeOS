TARGET = main.exe
OBJECTS = main.o

OPTIONS = -Wall -Wextra -Wpedantic -std=c99 -O3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	gcc $(OPTIONS) -o $@ $^

%.o: %.c
	gcc $(OPTIONS) -o $@ -c $<
#	gcc -S $< -o $(basename $@).list

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)