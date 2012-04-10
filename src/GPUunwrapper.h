#pragma once


class GPUunwrapper{

private:

	float * h_map;
	int   _w, _h;

public:
	GPUunwrapper(float *, int w, int h);
	~GPUunwrapper();

	bool doUnwrap();

	void setMap(float *, int w, int h);
	float * getMap();
};
