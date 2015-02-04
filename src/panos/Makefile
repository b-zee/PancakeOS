TOOLCHAIN = arm-none-eabi

# Optimal options for GCC according to eLinux.
C_OPTIONS   = -Wall -Wextra -Wpedantic -std=c99
GCC_OPTIONS = $(C_OPTIONS) -O0 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

OBJ_DIR = ../obj/
LIB_DIR = ../../
SRC_DIR = ./

TARGET  := $(LIB_DIR)libpanos.a

OBJ_FILES := $(patsubst $(SRC_DIR)%.s,$(OBJ_DIR)%.o,$(wildcard $(SRC_DIR)*.s))
OBJ_FILES += $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(wildcard $(SRC_DIR)*.c))


all: $(TARGET)
rebuild: clean all

$(TARGET): $(OBJ_FILES)
	$(TOOLCHAIN)-ar rcs $@ -o $(OBJ_FILES)

# Create object files from assembly files.
$(OBJ_DIR)%.o: $(SRC_DIR)%.s
	$(TOOLCHAIN)-as -c $< -o $@

# Create object files from c files.
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(TOOLCHAIN)-gcc $(GCC_OPTIONS) -c $< -o $@
	$(TOOLCHAIN)-gcc $(GCC_OPTIONS) -S $< -o $(basename $@).list

clean:
	-rm -f $(OBJ_DIR)*
	-rm -f $(TARGET)
