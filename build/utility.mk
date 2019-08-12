define check-var
$(if $($1),,$(error E: [$1] is empty))
endef

define find-files
$(shell if test -d $1; then find -L $1 -type f -iname $2 -and -not -name ".*" -printf "%p\n" | sort 2>/dev/null; fi)
endef

define find-h-files
$(call find-files,$1,"*.h")
endef

define find-c-files
$(call find-files,$1,"*.c")
endef

define find-java-files
$(call find-files,$1,"*.java")
endef

define find-class-files
$(call find-files,$1,"*.class")
endef

define find-jar-files
$(call find-files,$1,"*.jar")
endef
