TOOLCHAIN = arm-none-eabi

# Optimal options for GCC according to eLinux.
GCC_OPTIONS = -O0 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

BIN_DIR = ../bin/
OBJ_DIR = ../obj/
RES_DIR = ../res/
SRC_DIR = ./

TARGET	:= $(BIN_DIR)kernel.img
LIST	:= $(OBJ_DIR)kernel.list
MAP		:= $(OBJ_DIR)kernel.map
LINKSCR	:= $(RES_DIR)kernel.ld

LINKED_ELF := $(OBJ_DIR)output.elf

OBJ_FILES := $(patsubst $(SRC_DIR)%.s,$(OBJ_DIR)%.o,$(wildcard $(SRC_DIR)*.s))
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
	$(TOOLCHAIN)-gcc $(GCC_OPTIONS) -c $< -o $@
	$(TOOLCHAIN)-gcc $(GCC_OPTIONS) -S $< -o $(basename $@).list


# Rule to make the listing file.
$(LIST): $(LINKED_ELF)
	$(TOOLCHAIN)-objdump -d $(LINKED_ELF) > $(LIST)

copy: $(TARGET)
	cp $(TARGET) G:/

clean:
	-rm -f $(BIN_DIR)*
	-rm -f $(OBJ_DIR)*