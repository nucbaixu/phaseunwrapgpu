//
//  Mapa.h
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 27/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef QuadTreeUnwrap_Mapa_h
#define QuadTreeUnwrap_Mapa_h

#include <iostream>
using namespace std;

#define MAP_SIZE 16

class Mapa{
    
private:
    
    float *_mapa;
    int _w,_h;
    
    void copia(const Mapa &);
    void borra();
    
public:

    Mapa(int w=MAP_SIZE, int h=MAP_SIZE);
    Mapa(const Mapa&);
    Mapa &operator=(const Mapa&);
    ~Mapa();
    
    float getElem(int w,int h);
    void setElem(int w, int h, float value);
    
    int getW();
    int getH();
    
    void doWrap();
    
    float compare(const Mapa& v);
	float *getPointer();
    
    friend ostream& operator<<(ostream& output, const Mapa& t);
};

ostream& operator<<(ostream& output, const Mapa& t);

#endif
