//
//  Transformacion.cpp
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 24/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Transformacion.h"


void transformacion_t::copia(const transformacion_t& o){
    this->_array[0] = o._array[0];
    this->_array[1] = o._array[1];
    this->_array[2] = o._array[2];
}

transformacion_t::transformacion_t(){
    this->_array[0] = 0;
    this->_array[1] = 0;
    this->_array[2] = 0;
}
transformacion_t::transformacion_t(const transformacion_t& o){
    this->copia(o);
}
transformacion_t &transformacion_t::operator=(const transformacion_t& o){
    this->copia(o);
    return *this;
}

int &transformacion_t::operator[](int i) { return _array[i]; }

ostream& operator<<(ostream& output, const transformacion_t& s) {
    output << "[" << s._array[0] << "," << s._array[1] << "," << s._array[2] << "]";
    return output;  // for multiple << operators.
}

transformacion_t operator+(const transformacion_t &a, const transformacion_t&b){
    transformacion_t out;
    out._array[0] = a._array[0] + b._array[0];
    out._array[1] = a._array[1] + b._array[1];
    out._array[2] = a._array[2] + b._array[2];
    
    return  out;
}

transformacion_t *generaTodasTransformaciones(){
    
    transformacion_t *todas = (transformacion_t*) malloc(sizeof(transformacion_t)*27);
    
    for(int i=0; i< 27; i++){
        switch (i) {
            case  0: todas[i][0] =  0; todas[i][1] =  0; todas[i][2] =  0; break;                
            case  1: todas[i][0] =  0; todas[i][1] =  0; todas[i][2] =  1; break;                
            case  2: todas[i][0] =  0; todas[i][1] =  0; todas[i][2] = -1; break;                
            case  3: todas[i][0] =  0; todas[i][1] =  1; todas[i][2] =  0; break;                
            case  4: todas[i][0] =  0; todas[i][1] =  1; todas[i][2] =  1; break;                
            case  5: todas[i][0] =  0; todas[i][1] =  1; todas[i][2] = -1; break;                
            case  6: todas[i][0] =  0; todas[i][1] = -1; todas[i][2] =  0; break;                
            case  7: todas[i][0] =  0; todas[i][1] = -1; todas[i][2] =  1; break;                
            case  8: todas[i][0] =  0; todas[i][1] = -1; todas[i][2] = -1; break;                
                
            case  9: todas[i][0] =  1; todas[i][1] =  0; todas[i][2] =  0; break;                
            case 10: todas[i][0] =  1; todas[i][1] =  0; todas[i][2] =  1; break;                
            case 11: todas[i][0] =  1; todas[i][1] =  0; todas[i][2] = -1; break;                
            case 12: todas[i][0] =  1; todas[i][1] =  1; todas[i][2] =  0; break;                
            case 13: todas[i][0] =  1; todas[i][1] =  1; todas[i][2] =  1; break;                
            case 14: todas[i][0] =  1; todas[i][1] =  1; todas[i][2] = -1; break;                
            case 15: todas[i][0] =  1; todas[i][1] = -1; todas[i][2] =  0; break;                
            case 16: todas[i][0] =  1; todas[i][1] = -1; todas[i][2] =  1; break;                
            case 17: todas[i][0] =  1; todas[i][1] = -1; todas[i][2] = -1; break;        
                
            case 18: todas[i][0] = -1; todas[i][1] =  0; todas[i][2] =  0; break;                
            case 19: todas[i][0] = -1; todas[i][1] =  0; todas[i][2] =  1; break;                
            case 20: todas[i][0] = -1; todas[i][1] =  0; todas[i][2] = -1; break;                
            case 21: todas[i][0] = -1; todas[i][1] =  1; todas[i][2] =  0; break;                
            case 22: todas[i][0] = -1; todas[i][1] =  1; todas[i][2] =  1; break;                
            case 23: todas[i][0] = -1; todas[i][1] =  1; todas[i][2] = -1; break;                
            case 24: todas[i][0] = -1; todas[i][1] = -1; todas[i][2] =  0; break;                
            case 25: todas[i][0] = -1; todas[i][1] = -1; todas[i][2] =  1; break;                
            case 26: todas[i][0] = -1; todas[i][1] = -1; todas[i][2] = -1; break;                      
        }
    }
    
    return todas;
}