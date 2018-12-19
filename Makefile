.PHONY: test
test:
	@ TARGET_FILE=out/test/test.out \
		make out -f build/cc.mk

.PHONY: clean
clean:
	@make clean -f build/cc.mk
