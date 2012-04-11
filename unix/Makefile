
CUDAROOT   := /usr/local/cuda/bin
CUDASDKDIR := /Developer/GPU\ Computing/C/common

CC := llvm-gcc 
CUDACC := $(CUDAROOT)/nvcc

CCFLAGS :=
CUDACCFLAGS := "--ptxas-options=-v"

SRCROOT := ../src
BINPATH := ../bin

DEPS = $(SRCROOT)/Combinacion.h\
	$(SRCROOT)/Mapa.h\
	$(SRCROOT)/QTunwrap.h\
	$(SRCROOT)/tools.h\
	$(SRCROOT)/Transformacion.h

OBJ = $(SRCROOT)/Combinacion.o \
	$(SRCROOT)/QTunwrap.o \
	$(SRCROOT)/main.o \
	$(SRCROOT)/Mapa.o \
	$(SRCROOT)/Transformacion.o  \
	$(SRCROOT)/tools.o \
	$(SRCROOT)/GPUunwrapper.o \
	$(SRCROOT)/QT_unwrap_kernel.o

%.o: %.cpp $(DEPS)
	@$(CUDACC) -c -o $@ $< $(CFLAGS)

%.o: %.cu $(DEPS)
	@$(CUDACC) -c -o $@ $< $(CUDACCFLAGS)

unwrap: $(OBJ)
	@$(CUDACC) -o $(BINPATH)/$@ $^ $(CFLAGS)

clean:
	@rm $(SRCROOT)/*.o
