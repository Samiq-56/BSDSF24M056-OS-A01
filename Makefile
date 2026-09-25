# ==================================================
#  Top-level Makefile (recursive)
#  Delegates all real work to the Makefile in src/
# ==================================================
SUBDIRS  = src
APP      = client_dynamic
BINDIR   = bin
LIBDIR   = lib
MANDIR3  = man/man3
MANDIR1  = man/man1

PREFIX      = /usr/local
INSTALL_BIN = $(PREFIX)/bin
INSTALL_LIB = $(PREFIX)/lib
INSTALL_MAN3 = $(PREFIX)/share/man/man3
INSTALL_MAN1 = $(PREFIX)/share/man/man1

.PHONY: all run clean help install uninstall $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

run: all
	$(MAKE) -C src run

clean:
	$(MAKE) -C src clean

install: all
	mkdir -p $(INSTALL_BIN) $(INSTALL_LIB) $(INSTALL_MAN3) $(INSTALL_MAN1)
	install -m 755 $(BINDIR)/$(APP) $(INSTALL_BIN)/client
	install -m 644 $(LIBDIR)/libmyutils.so $(INSTALL_LIB)/
	install -m 644 $(LIBDIR)/libmyutils.a $(INSTALL_LIB)/
	install -m 644 $(MANDIR3)/*.3 $(INSTALL_MAN3)/
	install -m 644 $(MANDIR1)/*.1 $(INSTALL_MAN1)/
	ldconfig
	mandb -q
	@echo "Installed: $(INSTALL_BIN)/client, libraries in $(INSTALL_LIB), man pages under $(PREFIX)/share/man"

uninstall:
	rm -f $(INSTALL_BIN)/client
	rm -f $(INSTALL_LIB)/libmyutils.so $(INSTALL_LIB)/libmyutils.a
	rm -f $(INSTALL_MAN3)/mystrlen.3 $(INSTALL_MAN3)/mystrcpy.3 $(INSTALL_MAN3)/mystrncpy.3 $(INSTALL_MAN3)/mystrcat.3 $(INSTALL_MAN3)/wordCount.3 $(INSTALL_MAN3)/mygrep.3
	rm -f $(INSTALL_MAN1)/client.1
	ldconfig
	mandb -q
	@echo "Uninstalled client, libraries and man pages"

help:
	@echo "Available targets:"
	@echo "  make            - build the project ($(BINDIR)/$(APP))"
	@echo "  make run        - build and run the program"
	@echo "  make clean      - remove the binary and generated files"
	@echo "  sudo make install   - install client, libraries and man pages system-wide"
	@echo "  sudo make uninstall - remove installed files"
