include ./build/utility.mk

define reorder-header-files
$(filter %/predefined.h,$1) \
$(filter %/Int32.h,$1) \
$(filter %/Int64.h,$1) \
$(filter-out %/predefined.h %/Int32.h %/Int64.h,$1)
endef

.PHONY: test
test: TEST_EXECUTABLE := ./out/test.out
test: HEADER_FILES := $(foreach D,./src ./test,$(call find-h-files,$(D)))
test:
	@ \
		HEADER_FILES="$(call reorder-header-files,$(HEADER_FILES))" \
		SOURCE_FILES="$(foreach D,./src ./test,$(call find-c-files,$(D)))" \
		OUT="./out" \
		OUT_FILE=$(TEST_EXECUTABLE) \
		make out -f ./build/cc.mk
	@$(TEST_EXECUTABLE)

.PHONY: obj
obj: HEADER_FILES := $(call find-h-files,./src)
obj:
	@ \
		HEADER_FILES="$(call reorder-header-files,$(HEADER_FILES))" \
		SOURCE_FILES="$(call find-c-files,./src)" \
		OUT="./out" \
		make $@ -f ./build/cc.mk

# clean should not be delegated down to other component
.PHONY: clean
clean:
	@echo "cleaning ..."
	@rm -rf ./out
