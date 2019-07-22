##
# for c
#

BUILD := $(shell dirname $(lastword $(MAKEFILE_LIST)))
BUILD := $(patsubst ./%,%,$(BUILD))

include $(BUILD)/utility.mk

########

$(call check-var,HEADER_FILES)
$(call check-var,SOURCE_FILES)
$(call check-var,OUT)

# keep paths, in case of same basenames in different directories
OBJECT_FILES := $(patsubst %.c,$(OUT)/%.o,$(patsubst ./%,%,$(SOURCE_FILES)))

########

CC := gcc
CCFLAGS = -std=c99 -Werror $(addprefix -include ,$(HEADER_FILES))

.PHONY: obj
obj: $(OBJECT_FILES)

.PHONY: check-OUT_FILE
check-OUT_FILE:
	@$(call check-var,OUT_FILE)

.PHONY: out
out: check-OUT_FILE $(OBJECT_FILES)
	@echo "linking [$(OUT_FILE)] ..."
	@-mkdir -p $(shell dirname $(OUT_FILE))
	@$(CC) $(CCFLAGS) -o $(OUT_FILE) $(OBJECT_FILES)

.PHONY: a
a: check-OUT_FILE $(OBJECT_FILES)
	@echo "archiving [$(OUT_FILE)] ..."
	@ar cr $(OUT_FILE) $(OBJECT_FILES)

.PHONY: o
o: check-OUT_FILE $(OBJECT_FILES)
	@echo "linking [$(OUT_FILE)] ..."
	@ld -r $(OBJECT_FILES) -o $(OUT_FILE)

$(OUT)/%.o: %.c $(HEADER_FILES)
	@echo "compiling [$@] ..."
	@-mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -c $< -o $@
