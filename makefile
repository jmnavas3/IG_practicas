# ##############################################################################
#
# Informática Gráfica (Grado Informática)
# Makefile (sirve para Linux y macOS)
#
# ##############################################################################

.SUFFIXES:
.PHONY: x

p4				:= p4/

vpath %.cc $(p4) # añade el subdirectorio p4 a los directorios que tiene que mirar para los archivos cc


exe             := pracs_exe
units_cc        := $(wildcard *.cc) $(wildcard *.cpp)
units_p4		:= $(wildcard $(p4)*.cc)								# p4/*.cc
units_p4o		:= $(addsuffix .o, $(basename $(notdir $(units_p4)))) 	# p4/*.cc --> notdir: *.cc --> basename: * --> addsuffix: *.o (los de p4)
units_o         := $(addsuffix .o, $(basename $(units_cc)))
headers         := $(wildcard *.h*)
uname           := $(shell uname -s)
en_macos        := $(findstring Darwin,$(uname))
en_linux        := $(findstring Linux,$(uname))
compiler        := $(if $(en_linux), g++, clang++ )
sistoper        := $(if $(en_macos), macOS, Linux )

cc_flags_common := -std=c++11 -Wall -g -I/usr/include -I.
cc_flags_linux  := -DLINUX
cc_flags_macos  := -DMACOS
cc_flags        := $(cc_flags_common) $(if $(en_linux), $(cc_flags_linux), $(cc_flags_macos))

glu_flag_macos  := /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLU.dylib
ld_libs_common := -ljpeg
ld_libs_linux  := -lGLEW -lGLU -lglut -lGL
ld_libs_macos  := -framework OpenGL -framework GLUT $(glu_flag_macos)
ld_libs        := $(ld_libs_common) $(if $(en_linux), $(ld_libs_linux), $(ld_libs_macos))


x: $(exe)
	@echo Enlazando para: $(sistoper)
	./$(exe)

$(exe): $(units_p4o) $(units_o) makefile
	$(compiler) -o $(exe)  obj/* $(ld_libs)

%.o : %.cc
	$(compiler) -c  $(cc_flags) $< -o obj/$@

%.o : %.cpp
	$(compiler) -c  $(cc_flags) $< -o obj/$@

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	rm -f obj/* *_exe
