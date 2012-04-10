#include "GPUunwrapper.h"

#include <cuda.h>
#include "QT_unwrap_kernel.h"

#include <iostream>

// local protorypes
void deviceEnumeration();


// class
GPUunwrapper::GPUunwrapper(float *m, int w, int h):h_map(m), _w(w), _h(h){}

GPUunwrapper::~GPUunwrapper(){
}

void GPUunwrapper::setMap(float *m, int w, int h){
	h_map = m;
	_w   = w;
	_h   = h;
}

float * GPUunwrapper::getMap(){
	return h_map;
}



bool GPUunwrapper::doUnwrap(){

	deviceEnumeration();

	float *d_map;
	size_t size = _w*_h*sizeof(float);

	if (cudaMalloc (&d_map, size) != cudaSuccess)
		throw -1;
	if (cudaMemcpy (d_map, h_map, size, cudaMemcpyHostToDevice) != cudaSuccess)
		throw -2;
//	if (cudaMemset (d_map, 0x0, size) != cudaSuccess)
//		throw -3;

	char *d_debug;
	if (cudaMalloc (&d_debug, 256*4*sizeof(char)) != cudaSuccess)
		throw -4;
	if (cudaMemset (d_debug, 0x0, 256*4*sizeof(char)) != cudaSuccess)
		throw -5;

	int threadPerBlock = 256;
	int blocksPerGrid  = (_w*_h)/(32*32);

	qt_unwrap_kernel<<< blocksPerGrid, threadPerBlock >>> (d_map, _w, _h, d_debug);

 	if (cudaMemcpy (h_map, d_map, size, cudaMemcpyDeviceToHost) != cudaSuccess)
		throw -3;

	char h_debug[256*4];
	if (cudaMemcpy (h_debug, d_debug, 256*4*sizeof(char), cudaMemcpyDeviceToHost) != cudaSuccess)
		throw -3;

	// TODO: me he quedado aqui!
	std::cout << "SUMS: ";
	for (int i=0; i< 256*4; i+=4){
		std::cout << "[" << (int)h_debug[i] <<"," << (int)h_debug[i+1] <<"," << (int)h_debug[i+2] <<"," << (int)h_debug[i+3] << "]" << std::endl;
	}
	
	cudaFree (d_map);

	return true;
}


/////////////////////////////////////////////////////////////////////////
// local functions

void deviceEnumeration(){

	int deviceCount =0;
	cudaGetDeviceCount (&deviceCount);

	for (int i=0; i< deviceCount; i++){
		cudaDeviceProp deviceProp;
		cudaGetDeviceProperties (&deviceProp, i);
		if (deviceProp.major == 9999 && deviceProp.minor == 9999)
			printf ("not suporting CUDA\n");
		else{
			printf ("cuda device: %s\n", deviceProp.name);
		}	
	}
}
