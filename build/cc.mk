##
# makefile for cc
#

TOP := .
BUILD := $(TOP)/build
OUT := $(TOP)/out
ifndef SRC
SRC := $(TOP)/src
endif

include $(BUILD)/util.mk

########

HEADER_FILES := $(foreach D,$(SRC),$(call find-files-h,$(D)))
SOURCE_FILES := $(foreach D,$(SRC),$(call find-files-c,$(D)))

$(info goal [$(MAKECMDGOALS)], target file [$(TARGET_FILE)])

########

OBJECT_FILES := $(patsubst %.c,$(OUT)/%.o,$(SOURCE_FILES))

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

.PHONY: obj
obj: $(OBJECT_FILES)

$(OUT)/%.o: %.c $(HEADER_FILES)
	@echo "compiling [$@] ..."
	@-mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo "cleaning ..."
	@rm -rf $(OUT)
