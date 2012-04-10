//
//  Mapa.cpp
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 27/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Mapa.h"
#include <iomanip>


/*******************************************************************/
/*       NEW IMPLEMENTATION WITH MONO-DIMENISONAL ARRAYS           */
/*******************************************************************/

Mapa::Mapa(int w, int h): _w(w),_h(h){
    
    _mapa = (float*) malloc (sizeof(float)*_w*_h);

    _mapa[0] = 0;
    for (int i=1; i< _w; i++)
        _mapa[i] = i * 0.2f;
    
    for (int i=0; i< _w; i++)
        for (int j=1; j< _h; j++)
            _mapa[i+j*_w] = _mapa[i +(j-1)*_w]+ 0.01f; 
}

Mapa::Mapa(const Mapa&m):_w(m._w), _h(m._h){
    this->copia(m);
}

Mapa &Mapa::operator=(const Mapa&m){
    this->borra();
    this->copia(m);
    return *this;
}

Mapa::~Mapa(){
    this->borra();
}

void Mapa::copia(const Mapa &m){
    _mapa = (float*) malloc (sizeof(float)*_w*_h);
	memcpy (_mapa, m._mapa, sizeof(float)*_w*_h);
}
void Mapa::borra(){
    free(_mapa);
}

float Mapa::getElem(int i, int j){
    return _mapa[i+j*_w];
}

void Mapa::doWrap(){
    
    for (int i =0; i < _w; i++){
        for (int j=0; j< _h; j++){
            _mapa[i+j*_w] = _mapa[i+j*_w] - (int)_mapa[i+j*_w];
        }
    }
    
}

void Mapa::setElem(int i, int j, float value){
    
    //cout << "change [" << w<<","<<h<<"] " <<  _mapa[w][h] << "->" << value << endl;
    
    if((i< _w)&&(j<_h))
        _mapa[i+j*_w] = value;
	else
		throw -15;
}

float Mapa::compare(const Mapa& o){
    float acumulatedError = 0.0f;
    
    for (int i =0; i < _w; i++){
        for (int j=0; j< _h; j++){
            acumulatedError += _mapa[i+j*_w] - o._mapa[i+j*_w];
        }
    }
    return acumulatedError;
}

int Mapa::getW(){   return _w;}
int Mapa::getH(){   return _h;}
float * Mapa::getPointer(){ return _mapa;}

ostream& operator<<(ostream& output, const Mapa& m){

//    output.precision(2);
    output << "\t";
    for (int j=0; j< m._h; j++)
         output << "[" << j << "]\t";
    output << endl;
    
    for (int i =0; i < m._w; i++){
        output << "[" << i << "]:\t";
        
        
        for (int j=0; j< m._h; j++){
            output << m._mapa[i+j*m._w] << "\t";
        }
        output << endl;
    }
    output << endl;
    return output;
}



/***********************************************************************************
 ***********************************************************************************
			OLD IMPLEMENTATION WITH BI-DIMENSIONAL ARRAY

Mapa::Mapa(int w, int h): _w(w),_h(h){
    
    _mapa = (float**) malloc (sizeof(float*)*_w);
    for (int i=0; i< _w; i++)
        _mapa[i] = (float *) malloc(sizeof(float)*_h);
    
    _mapa[0][0] = 0;
    for (int i=1; i< _w; i++)
        _mapa[0][i] = i * 0.2;
    
    for (int i=1; i< _w; i++){
        for (int j=0; j< _h; j++){
            _mapa[i][j] = _mapa[i-1][j]+ 0.01; 
        }
    }
}

Mapa::Mapa(const Mapa&m):_w(m._w), _h(m._h){
    this->copia(m);
}

Mapa &Mapa::operator=(const Mapa&m){
    this->borra();
    this->copia(m);
    return *this;
}

Mapa::~Mapa(){
    this->borra();
}

void Mapa::copia(const Mapa &m){
    _mapa = (float**) malloc (sizeof(float*)*_w);
    for (int i=0; i< _w; i++){
        _mapa[i] = (float *) malloc(sizeof(float)*_h);
        for (int j=0; j< _h; j++){
            _mapa[i][j] = m._mapa[i][j];
        }
    }
}
void Mapa::borra(){
    for (int i=0; i< _w; i++)
        free (_mapa[i]);
    free(_mapa);
}

float Mapa::getElem(int w,int h){
    return _mapa[w][h];
}

void Mapa::doWrap(){
    
    for (int i =0; i < _w; i++){
        for (int j=0; j< _h; j++){
            _mapa[i][j] = _mapa[i][j] - (int)_mapa[i][j];
        }
    }
    
}

void Mapa::setElem(int w, int h, float value){
    
    //cout << "change [" << w<<","<<h<<"] " <<  _mapa[w][h] << "->" << value << endl;
    
    if((w< _w)&&(h<_h))
        _mapa[w][h] = value;
}

float Mapa::compare(const Mapa& o){
    float acumulatedError = 0.0f;
    
    for (int i =0; i < _w; i++){
        for (int j=0; j< _h; j++){
            acumulatedError += _mapa[i][j] - o._mapa[i][j];
        }
    }
    return acumulatedError;
}

int Mapa::getW(){   return _w;}
int Mapa::getH(){   return _h;}

ostream& operator<<(ostream& output, const Mapa& m){

    output.precision(2);
    output << "\t";
    for (int j=0; j< m._h; j++)
         output << "[" << j << "]\t";
    output << endl;
    
    for (int i =0; i < m._w; i++){
        output << "[" << i << "]:\t";
        
        
        for (int j=0; j< m._h; j++){
            output << m._mapa[i][j] << "\t";
        }
        output << endl;
    }
    output << endl;
    return output;
}
***************************************************************************
***************************************************************************/
