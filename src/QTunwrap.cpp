//
//  QTunwrap.cpp
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 28/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "QTunwrap.h"
#include "Transformacion.h"
#include "tools.h"

transformacion_t getScanTransform (suma_t s){
    
    transformacion_t t;
    
    // cuadrante 00 fijo
    // cuadrante 01 depende de suma en s[0]
    t[0] = s[0];

    // cuadrante 11 depende de suma en s[1]
    t[2] = t[0] + s[1];
    
    // cuadrante 10 depende de suma en s[2] y valor en 11
    t[1] = t[2] + s[2];
    
    
    return t;
}

void qtUnwrap(Mapa &m, int i, int j, int ancho){
    
    suma_t suma;
    
    if (ancho == 2){
        suma = suma_t(thresshold(0.5, m.getElem(i  , j  ) -  m.getElem((i  ), (j+1))), 
                       thresshold(0.5, m.getElem(i  , j+1) -  m.getElem((i+1), (j+1))), 
                       thresshold(0.5, m.getElem(i+1, j+1) -  m.getElem((i+1), (j))), 
                       thresshold(0.5, m.getElem(i+1, j  ) -  m.getElem((i  ), (j))));
        
        transformacion_t t = getScanTransform (suma);
        
     //   cout << "para [" << i << "," << j << "] suma: " << suma << " t: " << t << endl;
        
        m.setElem( i  , j+1, m.getElem(i  ,j+1) + t[0] );  // up right
        m.setElem( i+1, j  , m.getElem(i+1,j  ) + t[1] );  // down left
        m.setElem( i+1, j+1, m.getElem(i+1,j+1) + t[2] );  // down right
    }

    else{ /* ancho variable */
        int medio = ancho/2;
    
        int *unoDos    = (int*)malloc (medio*sizeof(int));
        int *dosCuatro = (int*)malloc (medio*sizeof(int));
        int *cuatroTres= (int*)malloc (medio*sizeof(int));
        int *tresUno   = (int*)malloc (medio*sizeof(int));
        
        
        // define las fronteras
        int f1 = medio-1;
        int f2  = medio;
        
        for (int e =0; e <medio; e++){
            unoDos[e]     =  thresshold(0.5, m.getElem(i+e  , j+f1) -  m.getElem(i+e, j+f2));
        }
        for (int e =0; e <medio; e++){
            dosCuatro[e]  =  thresshold(0.5, m.getElem(i+f1  , j+f2+e) -  m.getElem(i+f2, j+f2+e));
        }
        for (int e =0; e <medio; e++){
            cuatroTres[e] =  thresshold(0.5, m.getElem(i+f2+e, j+f2) -  m.getElem(i+f2+e, j+f1));
        }
        for (int e =0; e <medio; e++){
            tresUno[e]    =  thresshold(0.5, m.getElem(i+f2  , j+e) -  m.getElem(i+f1, j+e));
        }
        
        suma.setZero();
        for (int n= 0; n < medio; n++){
            suma[0] += unoDos    [n];
            suma[1] += dosCuatro [n];
            suma[2] += cuatroTres[n];
            suma[3] += tresUno   [n];
        }
        suma[0] = thresshold(0.5, (suma[0])/medio);
        suma[1] = thresshold(0.5, (suma[1])/medio);
        suma[2] = thresshold(0.5, (suma[2])/medio);
        suma[3] = thresshold(0.5, (suma[3])/medio);   
        
		transformacion_t t = getScanTransform(suma);
        
        //cout << "for [" << i << "," << j << "] sum: " << suma << " t: " << t << endl;
        
        //        aplicar transformación:
        
        for (int a =0; a <medio; a++){
            for (int b =0; b <medio; b++){
                m.setElem(i+a, j+medio+b, m.getElem(i+a,j+medio+b) + t[0]);
            }
        }
        for (int a =0; a <medio; a++){
            for (int b =0; b <medio; b++){
                m.setElem(i+medio+a, j+b, m.getElem(i+medio+a,j+b) + t[1]);
            }
        }
        for (int a =0; a <medio; a++){
            for (int b =0; b <medio; b++){
                m.setElem(i+medio+a, j+medio+b, m.getElem(i+medio+a,j+medio+b) + t[2]);
            }
        }  
        
        free(unoDos);
        free(dosCuatro);
        free(cuatroTres);
        free(tresUno);
    }
}

















/*   else if (ancho == 4){
 
 
 int unoDos[2];
 int DosCuatro[2];
 int CuatroTres[2];
 int TresUno[2];
 
 for (int e =0; e <2; e++){
 unoDos[e]     =  thresshold(0.5, m.getElem(i+e  , j+1) -  m.getElem(i+e, j+2));
 }
 for (int e =0; e <2; e++){
 DosCuatro[e]  =  thresshold(0.5, m.getElem(i+1  , j+2+e) -  m.getElem(i+2, j+2+e));
 }
 for (int e =0; e <2; e++){
 CuatroTres[e] =  thresshold(0.5, m.getElem(i+2+e, j+2) -  m.getElem(i+2+e, j+1));
 }
 for (int e =0; e <2; e++){
 TresUno[e]    =  thresshold(0.5, m.getElem(i+2  , j+e) -  m.getElem(i+1, j+e));
 }
 suma[0] = thresshold(0.5, (unoDos[0] + unoDos[1])/2);
 suma[1] = thresshold(0.5, (DosCuatro[0] + DosCuatro[1])/2);
 suma[2] = thresshold(0.5, (CuatroTres[0] + CuatroTres[1])/2);
 suma[3] = thresshold(0.5, (TresUno[0] + TresUno[1])/2);
 
 transformacion_t t = lut.getTransform(suma);
 
 cout << "para [" << i << "," << j << "] suma: " << suma << " t: " << t << endl;
 
 //        aplicar transformación:
 
 for (int a =0; a <2; a++){
 for (int b =0; b <2; b++){
 m.setElem(i+a, j+2+b, m.getElem(i+a,j+2+b) + t[0]);
 }
 }
 for (int a =0; a <2; a++){
 for (int b =0; b <2; b++){
 m.setElem(i+2+a, j+b, m.getElem(i+2+a,j+b) + t[1]);
 }
 }
 for (int a =0; a <2; a++){
 for (int b =0; b <2; b++){
 m.setElem(i+2+a, j+2+b, m.getElem(i+2+a,j+2+b) + t[2]);
 }
 }    
 }*/








