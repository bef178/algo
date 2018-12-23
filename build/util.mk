define find-files
$(shell find -L $1 -type f -iname $2 -and -not -name ".*" -printf "%d\t%p\n" | sort | cut -f2 2>/dev/null)
endef

define find-files-h
$(call find-files, $1, "*.h")
endef

define find-files-c
$(call find-files, $1, "*.c")
endef

define fine-files-o
$(call find-files, $1, "*.o")
endef
