all: mips

mips: mips.c
	$(CC) -o $@ $<

clean:
	-rm mips

.PHONY: clean
