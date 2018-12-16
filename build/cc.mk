##
# makefile for cc
#

TOP := .
BUILD := $(TOP)/build
SRC := $(TOP)/src
OUT := $(TOP)/out

include $(BUILD)/util.mk

########

HEADER_FILES := $(call find-files-h, $(SRC))
SOURCE_FILES := $(call find-files-c, $(SRC))

TARGET_TYPE := out
TARGET_FILE := $(OUT)/sort/test.out

########

OBJECT_FILES := $(patsubst $(SRC)/%.c,$(OUT)/%.o,$(SOURCE_FILES))

CC := gcc
CCFLAGS = -std=c99 -Werror $(addprefix -include ,$(HEADER_FILES))

.PHONY: dummy
dummy:

.PHONY: out
out: $(OBJECT_FILES)
	@echo "linking [$(TARGET_FILE)] ..."
	@-mkdir -p $(shell dirname $(TARGET_FILE))
	@$(CC) $(CCFLAGS) -o $(TARGET_FILE) $^

.PHONY: a
a: $(OBJECT_FILES)
	@echo "archiving [$(TARGET_FILE)] ..."
	@ar cr $(TARGET_FILE) $^

.PHONY: o
o: $(OBJECT_FILES)
	@echo "linking [$(TARGET_FILE)] ..."
	@ld -r $^ -o $(TARGET_FILE)

$(OUT)/%.o: $(SRC)/%.c $(HEADER_FILES)
	@echo "compiling [$@] ..."
	@-mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo "cleaning ..."
	@rm -rf $(OUT)
