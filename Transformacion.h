//
//  Transformacion.h
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 24/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef QuadTreeUnwrap_Transformacion_h
#define QuadTreeUnwrap_Transformacion_h
#include <iostream>


using namespace std;

//************* transformaciones  *************//

class transformacion_t{
private:
    int _array[3];
    
    void copia(const transformacion_t& o);
    
public:
    transformacion_t();
    transformacion_t(const transformacion_t& o);
    transformacion_t &operator=(const transformacion_t& o);
    
    int &operator[](int i);
    
    friend ostream& operator<<(ostream& output, const transformacion_t& p);
    friend transformacion_t operator+(const transformacion_t &a, const transformacion_t&b);
};

ostream& operator<<(ostream& output, const transformacion_t& p);
transformacion_t operator+(const transformacion_t &a, const transformacion_t&b);


transformacion_t *generaTodasTransformaciones();



#endif
