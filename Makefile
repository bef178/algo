.PHONY: test
test:
	$(eval TEST_EXECUTABLE=./out/test.out)
	@ \
		SRC="./src ./test" \
		OUT="./out" \
		OUT_FILE=$(TEST_EXECUTABLE) \
		make out -f ./build/cc.mk
	@$(TEST_EXECUTABLE)

.PHONY: obj
obj:
	@ \
		SRC="./src" \
		OUT="./out" \
		make $@ -f ./build/cc.mk

# clean should not be delegated down to other component
.PHONY: clean
clean:
	@echo "cleaning ..."
	@rm -rf ./out
