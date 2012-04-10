//
//  Posibilidad.h
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 24/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef QuadTreeUnwrap_Posibilidad_h
#define QuadTreeUnwrap_Posibilidad_h


#include <iostream>
#include "Transformacion.h"

using namespace std;

//************ RELOJ **************//

class suma_t{
private:
    int _array[4];
    
    void copia(const suma_t& o);
    
public:
    suma_t();//
    suma_t(int a, int b, int c, int d);
    suma_t(float humbral, float  a, float b, float c, float d);    
    suma_t(const suma_t& o);//
    suma_t &operator=(const suma_t& o);//
    
    int &operator[](int i);
    
    bool comparaSumas(const suma_t &b)const;
    void setZero();
    bool isZero()const;
    
    int getMin()const;
    int getMax()const;
    int getRange()const;
    
    friend ostream& operator<<(ostream& output, const suma_t& p);
};

ostream& operator<<(ostream& output, const suma_t& p);



/**************** combinacion de elementos *************/

class Combinacion{
private:
    int a, b, c, d;
    suma_t suma;
    
    void computaSuma ();
    
public:
    Combinacion();
    Combinacion(int code);
    Combinacion(const Combinacion &);
    
    int &operator[](int i);
    
    bool isCoherent(){
        if ((a==b)&&(b==c)&&(c==d))
            return true;
        else
            return false;
    }
    
    void print ();
    
    void aplicaTransformacion (transformacion_t&);
    
    suma_t &getSuma ();
    
    friend ostream& operator<<(ostream& output, const Combinacion& p);
};

ostream& operator<<(ostream& output, const Combinacion& p);

Combinacion **generaTodasPosibilidades();


#endif
