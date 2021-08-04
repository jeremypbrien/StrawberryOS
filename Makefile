ARMGNU ?= aarch64-linux-gnu
CARGS = -Wall -Werror -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only -fno-asynchronous-unwind-tables -MMD -Iinclude
ASMARGS = -MMD -Iinclude

BUILD_DIR := build
SRC_DIR := src
LINKER_FILE := $(SRC_DIR)/linker.ld
KERNEL_ELF := kernel8.elf
KERNEL_IMG := kernel8.img


all: $(KERNEL_IMG)

.PHONY: clean
clean:
    rm -rf $(BUILD_DIR)

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
    mkdir -p $(@D)
    $(ARMGNU)-gcc $(CARGS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
    mkdir -p $(@D)
    $(ARMGNU)-gcc $(ASMARGS) -MMD -c $< -o $@


C_FILES := $(shell find $(SRC_DIR) -name '*.c')
ASM_FILES := $(shell find $(SRC_DIR) -name '*.S')
OBJ_FILES := $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)


$(KERNEL_IMG): $(LINKER_FILE) $(OBJ_FILES)
    $(ARMGNU)-ld -T $(LINKER_FILE) -o $(BUILD_DIR)/$(KERNEL_ELF) $(OBJ_FILES)
    $(ARMGNU)-objcopy $(BUILD_DIR)/$(KERNEL_ELF) -O binary $(BUILD_DIR)/$(KERNEL_IMG)
