include *.local

TOOLCHAIN   = arm-none-eabi

# Optimal options for GCC according to eLinux.
C_OPTIONS   = -Wall -Wextra -Wpedantic -std=c99
GCC_OPTIONS = $(C_OPTIONS) -O0 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

# Directories
BIN_DIR = ../bin/
LIB_DIR = ../lib/
OBJ_DIR = ../obj/
RES_DIR = ../res/
SRC_DIR = ./

# Target files
TARGET  := $(BIN_DIR)kernel.img
LINKSCR := $(RES_DIR)kernel.ld

OUTPUT_LIST     := $(OBJ_DIR)output.list
OUTPUT_MAP      := $(OBJ_DIR)output.map
OUTPUT_LINKED   := $(OBJ_DIR)output.elf

# Library files to include
LIBRARIES = $(LIB_DIR)libpanos.a

# Object files to compile into target
OBJ_FILES := $(patsubst $(SRC_DIR)%.s,$(OBJ_DIR)%.o,$(wildcard $(SRC_DIR)*.s))
OBJ_FILES += $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(wildcard $(SRC_DIR)*.c))


all: $(TARGET) $(OUTPUT_LIST)
rebuild: clean all


# Create the kernel image from the linked object file.
$(TARGET): $(OUTPUT_LINKED)
	$(TOOLCHAIN)-objcopy $(OUTPUT_LINKED) -O binary $(TARGET)

# Create the linked object file from all objects.
$(OUTPUT_LINKED): $(OBJ_FILES) $(LINKSCR) $(LIBRARIES)
	$(TOOLCHAIN)-ld -Map $(OUTPUT_MAP) -o $(OUTPUT_LINKED) -T $(LINKSCR) $(OBJ_FILES) -L$(LIB_DIR) $(LIBRARIES:$(LIB_DIR)lib%.a=-l%) -L$(LIBGCC_DIR) -lgcc

# Create object files from assembly files.
$(OBJ_DIR)%.o: $(SRC_DIR)%.s
	$(TOOLCHAIN)-as -c $< -o $@

# Create object files from c files.
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(TOOLCHAIN)-gcc $(GCC_OPTIONS) -c $< -o $@
	$(TOOLCHAIN)-gcc $(GCC_OPTIONS) -S $< -o $(basename $@).list


# Rule to make the listing file.
$(OUTPUT_LIST): $(OUTPUT_LINKED)
	$(TOOLCHAIN)-objdump -d $(OUTPUT_LINKED) > $(OUTPUT_LIST)

# Copy the target into a disk drive
copy: $(TARGET)
	cp $(TARGET) J:/

# Clean up the project
clean:
	-rm -f $(BIN_DIR)*
	-rm -f $(OBJ_DIR)*
