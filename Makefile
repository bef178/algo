
include ./build/utility.mk

.PHONY: test
test:
	$(eval TEST_EXECUTABLE=./out/test.out)
	@ \
		HEADER_FILES="./src/predefined.h ./src/ctype/Int64.h $(foreach D,./src ./test,$(call find-h-files,$(D)))" \
		SOURCE_FILES="$(foreach D,./src ./test,$(call find-c-files,$(D)))" \
		OUT="./out" \
		OUT_FILE=$(TEST_EXECUTABLE) \
		make out -f ./build/cc.mk
	@$(TEST_EXECUTABLE)

.PHONY: obj
obj:
	@ \
		HEADER_FILES="./src/predefined.h ./src/ctype/Int64.h $(call find-h-files,./src)" \
		SOURCE_FILES="$(call find-c-files,./src)" \
		OUT="./out" \
		make $@ -f ./build/cc.mk

# clean should not be delegated down to other component
.PHONY: clean
clean:
	@echo "cleaning ..."
	@rm -rf ./out
