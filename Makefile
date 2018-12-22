.PHONY: test
test:
	@ \
		SRC="src test" \
		TARGET_FILE=out/test.out \
			make out -f build/cc.mk
	@echo running test ...
	@out/test.out

.PHONY: clean
clean:
	@make clean -f build/cc.mk
