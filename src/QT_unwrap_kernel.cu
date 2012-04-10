
typedef  char sum_t[4];

///////////////////////////////////////////////////////////////
__device__ int  device_thresshold(float th, float v){
    
    if ((v <= th)&&( v>= -th))
        return 0;
    
    int mult =0;
    
    if      (v > th){
        while (v > mult*2*th){
            mult ++;
        }
        return mult;        
    }
    else if (v < th){
        
        while (v < mult*2*th){
            mult --;
        }
        return mult;
    }
}

///////////////////////////////////////////////////////////////
__device__ class Matrix{
private:
	float *_matrix;
	int _w,_h;

public:
	__device__
	Matrix (float *m, int w, int h): _matrix (m), _w(w), _h(h){}

	__device__
	float &getElem (int x, int y){  // the element to be retrieved depends on the block I am
		
		int voff = (blockIdx.x * 32) /_w;
		int hoff = blockIdx.x % (_w/32);

		int linesBefore = 32*voff;

		return _matrix[ (linesBefore*_w) + (32*hoff) + y*_w + x ];
	}

};

///////////////////////////////////////////////////////////////
__device__ void neigbourSum (Matrix &map, int levelWidth, sum_t *sums){

	int thid = threadIdx.x;
	int widthFrontier     = levelWidth/2;
	int RegionsPerSide    = 32/levelWidth;

	int target = thid/widthFrontier;
	int i = ((target*levelWidth) / 32) * levelWidth;            
	int j = (target*levelWidth) % 32;
	int e = thid%widthFrontier;

	int half = levelWidth/2;
	int f1   = half-1;
	int f2   = half;

	if ((i < 32) && (j < 32)){
		int sumsPerFrontier = levelWidth/2;	
		
		sums [thid * sumsPerFrontier + e][0] =  device_thresshold(0.5, map.getElem(i+e   , j+f1)   -  map.getElem(i+e   , j+f2));
		sums [thid * sumsPerFrontier + e][1] =  device_thresshold(0.5, map.getElem(i+f1  , j+f2+e) -  map.getElem(i+f2  , j+f2+e));
		sums [thid * sumsPerFrontier + e][2] =  device_thresshold(0.5, map.getElem(i+f2+e, j+f2)   -  map.getElem(i+f2+e, j+f1));
		sums [thid * sumsPerFrontier + e][3] =  device_thresshold(0.5, map.getElem(i+f2  , j+e)    -  map.getElem(i+f1  , j+e));
	}
}

///////////////////////////////////////////////////////////////
__device__ void computeTransform (sum_t *sums, int levelWidth){
	int thid = threadIdx.x;
	int sumsPerFrontier = levelWidth/2;	

	// reduce to one sum per region 
	if      (levelWidth == 2) { // 256 sums, 1 element each

		// done
	}
	else if (levelWidth == 4) { // 64 sums, 2 elements each
		if (threadIdx.x < 64*2){
			//int  threadI
		}
	}
	else if (levelWidth == 8) { // 16 sums, 4 elements each

	}
	else if (levelWidth == 16) { // 4 sums, 8 elements each

	}
	else if (levelWidth == 32) { // 1 sums, 16 elements	each

	}

	// ---  three levels inclusive scann  ---
	//scann the 4 elements of the sum to compute the transform
	if (levelWidth == 2) { // 256 sums

		// all 256 threads do work
		sums [thid][0] = sums [thid][0];
		sums [thid][0] = sums [thid][0] + sums [thid][1];
		sums [thid][0] = sums [thid][1] + sums [thid][2];
	}
	else if (levelWidth == 4) { // 64 sums
		
	}
	else if (levelWidth == 8) { // 16 sums

	}
	else if (levelWidth == 16) { // 4 sums

	}
	else if (levelWidth == 32) { // 1 sums

	}
}

///////////////////////////////////////////////////////////////
__device__ void regionCorrection(Matrix &map, sum_t *sums, int levelWidth){
	for (int pass =0; pass < 4; pass ++){
			int x = (blockDim.x*pass + threadIdx.x) / 32;
			int y = (blockDim.x*pass + threadIdx.x) % 32;

			// 4 regions, 
			int i = (x/(levelWidth/2));
			int j = (y/(levelWidth/2));
			
			int region = j*2 + i;

			i = (x/levelWidth);  // which column to be
			j = (y/levelWidth); // which row to be

			// TODO: aqui está cascando, arregla estos indices, no estan bien del todo
		//	map.getElem(x,y) = sums[i + j*(32/levelWidth)][region];
	}
}

///////////////////////////////////////////////////////////////
/// this kernel operates in a Matrix, 
/// each block process a 32x32 matrix
/// solves 5 levels of the quad-tree aproach
__global__ void qt_unwrap_kernel (float *m, int w, int h, char *debug ){

	int levelWidth;
	Matrix map(m, w, h);
	__shared__ sum_t sum[256];

	for (levelWidth = 2; levelWidth <= 2; levelWidth*=2){

		// --- COMPUTE NEIGHBOUR SUM ---
		neigbourSum (map, levelWidth, sum);

		// --- SCAN SUMS ---
		computeTransform (sum, levelWidth);

		// --- APPLY TRANSFORMATION FOR EACH REGION ----
		// 256 threads need 4 passes to cover 32x32 matrix
		regionCorrection (map, sum, levelWidth);

		__syncthreads();
	}// tree levels

	
	// DEBUG THINGS: one block of 32x32
	debug[threadIdx.x*4]    = sum[threadIdx.x][0];
	debug[threadIdx.x*4 +1] = sum[threadIdx.x][1];
	debug[threadIdx.x*4 +2] = sum[threadIdx.x][2];
	debug[threadIdx.x*4 +3] = sum[threadIdx.x][3];
}