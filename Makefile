GCC = gcc
INCLUDES = -Ilibisen -I/usr/include/GL
CFLAGS = -Wall -g2 -std=gnu99
LDFLAGS = -lm -lglut -lGL -lX11

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

LIBSRCS = $(wildcard libisen/*.c)
LIBHEAD = $(wildcard libisen/*.h)
LIBOBJS = $(LIBSRCS:.c=.o)
LIBNAME = libisentlib.a

all: tpGraph

$(LIBNAME): $(LIBOBJS) $(LIBHEAD)
	ar r $(LIBNAME) $(LIBOBJS)
	ranlib $(LIBNAME)

tests: exemple exempleTortue

tpGraph: $(OBJS) $(LIBNAME)
	@echo Link $@
	$(GCC) $(INCLUDES) $(CFLAGS) $(OBJS) -o $@ $(LIBNAME) $(LDFLAGS)


exemple: tests/exemple.o $(LIBNAME)
	$(GCC) $(INCLUDES) $(CFLAGS) $< -o tests/$@ $(LIBNAME) $(LDFLAGS)

exempleTortue: tests/exempleTortue.o $(LIBNAME)
	$(GCC) $(INCLUDES) $(CFLAGS) $< -o tests/$@ $(LIBNAME) $(LDFLAGS)

-include $(OBJS:.o=.d)
-include $(LIBOBJS:.o=.d)

%.o: %.c
	@echo Build $@
	$(GCC) -MMD $(INCLUDES) $(CFLAGS) -c $< -o $@


zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o libisen/*.o *.d libisen/*.d tests/*.d tests/*.o

deepclean: clean
	rm -f tpGraph tests/exemple tests/exempleTortue libisentlib.a

