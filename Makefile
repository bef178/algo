.PHONY: test
test:
	@make out -f build/cc.mk

.PHONY: clean
clean:
	@make clean -f build/cc.mk
