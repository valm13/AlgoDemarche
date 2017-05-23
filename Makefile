GCC = gcc
INCLUDES = -IlibISEN -I/usr/include/GL
CFLAGS = -Wall -g2 -std=gnu99
LDFLAGS = -lm -lglut -lGL -lX11

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

LIBSRCS = $(wildcard libISEN/*.c)
LIBHEAD = $(wildcard libISEN/*.h)
LIBOBJS = $(LIBSRCS:.c=.o)
LIBNAME = libisentlib.a

all: gait_analysis

$(LIBNAME): $(LIBOBJS) $(LIBHEAD)
	ar r $(LIBNAME) $(LIBOBJS)
	ranlib $(LIBNAME)

tests: exemple exempleTortue

gait_analysis: $(OBJS) $(LIBNAME)
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
	rm -f *~ *.o libISEN/*.o *.d libISEN/*.d tests/*.d tests/*.o

deepclean: clean
	rm -f gait_analysis tests/exemple tests/exempleTortue libisentlib.a

