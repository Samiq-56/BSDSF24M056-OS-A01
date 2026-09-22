# ==================================================
#  Top-level Makefile (recursive)
#  Delegates all real work to the Makefile in src/
# ==================================================
SUBDIRS = src
APP     = client_static
BINDIR  = bin

.PHONY: all run clean help $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

run: all
	$(MAKE) -C src run

clean:
	$(MAKE) -C src clean

help:
	@echo "Available targets:"
	@echo "  make        - build the project ($(BINDIR)/$(APP))"
	@echo "  make run    - build and run the program"
	@echo "  make clean  - remove the binary and generated files"
