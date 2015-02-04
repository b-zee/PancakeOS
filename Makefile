include *.local

# Parameters for compiling C files
GCC_PARAMS  = -Wall -Wextra -Wpedantic -std=c99
# Optimal options for GCC according to eLinux.
GCC_PARAMS += -O3 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

# Directories
BIN_DIR	= bin/
OBJ_DIR	= obj/
RES_DIR	= res/
SRC_DIR	= src/

# Object files to compile into target
SRC_FILE_BASES := $(basename $(notdir $(wildcard $(SRC_DIR)*.c)))
SRC_FILE_BASES += $(basename $(notdir $(wildcard $(SRC_DIR)*.s)))
SRC_FILE_BASES += $(basename $(notdir $(wildcard $(SRC_DIR)*/*.c)))
OBJ_FILES       = $(addprefix $(OBJ_DIR),$(addsuffix .o,$(SRC_FILE_BASES)))

# Paths of directories inside source directory.
SRC_DIRS   = $(wildcard $(SRC_DIR)*)

# Search sources in sources directory and extensions' directories.
VPATH      = $(SRC_DIR) $(SRC_DIRS)

# Target files (results)
TARGET	      := $(BIN_DIR)kernel.img

OUTPUT_LIST   := $(OBJ_DIR)output.list
OUTPUT_MAP    := $(OBJ_DIR)output.map
OUTPUT_LINKED := $(OBJ_DIR)output.elf

# Source link descriptor file
LINKSCR	      := $(RES_DIR)kernel.ld

# Target path for copying rule
TARGET_PATH    = G:/


all: $(TARGET) $(OUTPUT_LIST)
rebuild: clean all

# Copy the target into a specific path
copy: $(TARGET)
	cp $(TARGET) $(TARGET_PATH)

# Clean up the project
clean:
	rm -rf $(OUTPUT_LIST) $(OUTPUT_MAP) $(OUTPUT_LINKED)
	rm -rf $(OBJ_FILES)
	rm -rf $(TARGET)


# Create the kernel image from the linked object file.
$(TARGET): $(OUTPUT_LINKED)
	$(GCC_PREFIX)objcopy" $(OUTPUT_LINKED) -O binary $(TARGET)

# Create the linked object file from all objects.
$(OUTPUT_LINKED): $(OBJ_FILES) $(LINKSCR)
	$(GCC_PREFIX)ld" -Map $(OUTPUT_MAP) -o $(OUTPUT_LINKED) -T $(LINKSCR) $(OBJ_FILES) -L$(LIBGCC_DIR) -lgcc -L$(LIBC_DIR) -lc

# Create object files from assembly files.
$(OBJ_DIR)%.o: %.s
	$(GCC_PREFIX)as" -c $< -o $@

# Create object files (and lists) from c files.
$(OBJ_DIR)%.o: %.c
	$(GCC_PREFIX)gcc" $(GCC_PARAMS) -c $< -o $@
#	$(GCC_PREFIX)gcc" $(GCC_PARAMS) -S $< -o $(basename $@).list

# Rule to make the listing file.
$(OUTPUT_LIST): $(OUTPUT_LINKED)
	$(GCC_PREFIX)objdump" -d $(OUTPUT_LINKED) > $(OUTPUT_LIST)
 