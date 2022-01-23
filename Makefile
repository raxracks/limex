ISO_IMAGE = limex.iso

.PHONY: all
all: $(ISO_IMAGE)

.PHONY: run
run: $(ISO_IMAGE)
	qemu-system-x86_64 -M q35 -m 2G -cdrom $(ISO_IMAGE)

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1
	make -C limine

.PHONY: limex
kernel:
	$(MAKE) -C limex

$(ISO_IMAGE): limine kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp limex/limux.elf \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-eltorito-efi.bin limex/misc/bg.bmp iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-eltorito-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(ISO_IMAGE)
	limine/limine-install $(ISO_IMAGE)
	rm -rf iso_root

.PHONY: clean
clean:
	rm -f $(ISO_IMAGE)
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf limine
	$(MAKE) -C kernel distclean
