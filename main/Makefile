TARGET = main.exe
OBJECTS = main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	gcc -std=c99 -o $@ $^

%.o: %.c
	gcc -std=c99 -o $@ -c $<
#	gcc -S $< -o $(basename $@).list

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)