.PHONY: test
test:
	@ \
		SRC="src test" \
		TARGET_FILE=out/test.out \
		make out -f build/cc.mk

.PHONY: clean
clean:
	@make clean -f build/cc.mk
