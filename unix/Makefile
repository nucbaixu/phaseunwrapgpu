
CUDAROOT   := /usr/local/cuda/bin
CUDASDKDIR := /Developer/GPU\ Computing/C/common

CC := llvm-gcc 
CUDACC := $(CUDAROOT)/nvcc

CCFLAGS :=
CUDACCFLAGS := 

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
	$(SRCROOT)/GPUunwrapper.cu \
	$(SRCROOT)/QT_unwrap_kernel.cu

%.o: %.cpp $(DEPS)
	$(CUDACC) -c -o $@ $< $(CFLAGS)

%.o: %.cu $(DEPS)
	$(CUDACC) -c -o $@ $< $(CFLAGS)

unwrap: $(OBJ)
	$(CUDACC) -o $(BINPATH)/$@ $^ $(CFLAGS)

clean:
	@rm $(SRCROOT)/*.o
