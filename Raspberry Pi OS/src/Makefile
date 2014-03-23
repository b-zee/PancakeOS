TOOLCHAIN = arm-none-eabi

BIN_DIR = ../bin/
OBJ_DIR = ../obj/
RES_DIR = ../res/
SRC_DIR = ./

TARGET	= $(BIN_DIR)kernel.img
LIST	= $(OBJ_DIR)kernel.list
MAP		= $(OBJ_DIR)kernel.map
LINKSCR	= $(RES_DIR)kernel.ld

LINKED_ELF = $(OBJ_DIR)output.elf

OBJ_FILES = $(patsubst $(SRC_DIR)%.s,$(OBJ_DIR)%.o,$(wildcard $(SRC_DIR)*.s))
OBJ_FILES += $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(wildcard $(SRC_DIR)*.c))


all: $(TARGET) $(LIST)
rebuild: clean all


# Create the kernel image from the linked object file.
$(TARGET): $(LINKED_ELF)
	$(TOOLCHAIN)-objcopy $(LINKED_ELF) -O binary $(TARGET)

# Create the linked object file from all objects.
$(LINKED_ELF): $(OBJ_FILES) $(LINKSCR)
	$(TOOLCHAIN)-ld --no-undefined $(OBJ_FILES) -Map $(MAP) -o $(LINKED_ELF) -T $(LINKSCR)

# Create object files from assembly files.
$(OBJ_DIR)%.o: $(SRC_DIR)%.s
	$(TOOLCHAIN)-as -c $< -o $@

# Create object files from c files.
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(TOOLCHAIN)-gcc -c $< -o $@
	$(TOOLCHAIN)-gcc -S $< -o $(basename $@).list


# Rule to make the listing file.
$(LIST): $(LINKED_ELF)
	$(TOOLCHAIN)-objdump -d $(LINKED_ELF) > $(LIST)

copy: $(TARGET)
	cp $(TARGET) E:/

clean: 
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)
	-rm -f $(OBJ_FILES)
	-rm -f $(LINKED_ELF)