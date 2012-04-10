//
//  Posibilidad.cpp
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 24/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Combinacion.h"
#include "tools.h"
using namespace std;

Combinacion::Combinacion(){
    
    d = 1;
    c = 1;
    b=1;
    a =1;      
    suma = suma_t(1,1,1,1);
}
Combinacion::Combinacion(int code){
        
    d = code%10;
    code /= 10;
    c = code%10;        
    code /= 10;
    b = code%10;      
    code /= 10;
    a = code%10;  
    
    computaSuma();
}

Combinacion::Combinacion(const Combinacion &o){
    this->a = o.a;
    this->b = o.b;
    this->c = o.c;
    this->d = o.d;
    
    this->suma = o.suma;
}

int &Combinacion::operator[](int i){
    switch (i) {
        case 0:
            return  a;
        case 1:
            return  b;
        case 2:
            return  c;
        case 3:
            return  d;

        default:
            throw -1;
    }
}

void Combinacion::aplicaTransformacion (transformacion_t&t){
    
    b+= t[0];
    c+= t[1];
    d+= t[2];
    
    computaSuma();
}

ostream& operator<<(ostream& output, const Combinacion& s) {
    output << "[" << symbol(s.a) << ","<<  symbol(s.b) << "," << symbol(s.c) << ","<<symbol(s.d)<<"]";
    return output;  // for multiple << operators.
}
    
void Combinacion::computaSuma (){
        
    int d1, d2, d3, d4;
        
    d1 = a-b;
    d2 = b-d;
    d3 = d-c;
    d4 = c-a;
        
        
    suma[0] = d1;
    suma[1] = d2;
    suma[2] = d3;
    suma[3] = d4;
}

suma_t &Combinacion::getSuma(){
    return suma;
}


/*******************  SUMA **************************/

void suma_t::copia(const suma_t& o){
    this->_array[0] = o._array[0];
    this->_array[1] = o._array[1];
    this->_array[2] = o._array[2];
    this->_array[3] = o._array[3];
        
}
    
suma_t::suma_t(){}
suma_t::suma_t(int a, int b, int c, int d){
    this->_array[0] = a;
    this->_array[1] = b;
    this->_array[2] = c;
    this->_array[3] = d;
}

suma_t::suma_t(const suma_t& o){
    this->copia(o);
}
suma_t &suma_t::operator=(const suma_t& o){
    this->copia(o);
    return *this;
}


    
int &suma_t::operator[](int i) { return _array[i]; }

void suma_t::setZero(){
    this->_array[0] = 0;
    this->_array[1] = 0;
    this->_array[2] = 0;
    this->_array[3] = 0;
}
bool suma_t::isZero() const{
    if ((this->_array[0] == this->_array[1]) && 
        (this->_array[1] == this->_array[2]) && 
        (this->_array[2] == this->_array[3]) &&
        (this->_array[0] == 0))
        return true;
    else
        return false;
}

bool suma_t::comparaSumas(const suma_t &b)const{
    if ((this->_array[0] == b._array[0]) && (this->_array[1] == b._array[1]) &&
        (this->_array[2] == b._array[2]) && (this->_array[3] == b._array[3]))
        return true;
    else return false;
}

int suma_t::getMin()const{
    int min  = (_array[0] < _array[1])? _array[0]: _array[1];
    min      = (min < _array[2])?       min      : _array[2];    
    return     (min < _array[3])?       min      : _array[3];    
}

int suma_t::getMax()const{
    int max  = (_array[0] > _array[1])? _array[0]: _array[1];
    max      = (max > _array[2])?       max      : _array[2];    
    return     (max > _array[3])?       max      : _array[3];        
}

int suma_t::getRange()const{
    return getMax()-getMin();
}

ostream& operator<<(ostream& output, const suma_t& s) {
    output << "[" << s._array[0] << "," << s._array[1] << "," << s._array[2] << "," << s._array[3] << "]";
     
    return output;  // for multiple << operators.
}

Combinacion **generaTodasPosibilidades(){
    
    Combinacion **todas = (Combinacion**) malloc(sizeof(Combinacion*)*27);
    
    int code;    
    
    for(int i=0; i< 27; i++){
        
        switch (i) {
            case 0:code = 1000;break;                
            case 1:code = 1001;break;
            case 2:code = 1002;break;    
            case 3:code = 1010;break;
            case 4:code = 1011;break;
            case 5:code = 1012;break;
            case 6:code = 1020;break;
            case 7:code = 1021;break;
            case 8:code = 1022;break;
                
            case 9:code  = 1100;break;
            case 10:code = 1101;break;                
            case 11:code = 1102;break;
            case 12:code = 1110;break;    
            case 13:code = 1111;break;
            case 14:code = 1112;break;
            case 15:code = 1120;break;
            case 16:code = 1121;break;
            case 17:code = 1122;break;
                
            case 18:code = 1200;break;
            case 19:code = 1201;break;    
            case 20:code = 1202;break;                
            case 21:code = 1210;break;
            case 22:code = 1211;break;    
            case 23:code = 1212;break;
            case 24:code = 1220;break;
            case 25:code = 1221;break;
            case 26:code = 1222;break;
        }
        todas[i] = new Combinacion(code);
    }
    
    return todas;
}



    