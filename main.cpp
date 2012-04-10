//
//  main.cpp
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 23/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "tools.h"
#include "Combinacion.h"
#include "Mapa.h"
#include "QTunwrap.h"
#include "GPUunwrapper.h"


using namespace std;

void doHOSTquadtreeUnwrap (Mapa &wrap){

    // do QUAD-TREE unwrap
    for (int ancho=2; ancho <= wrap.getW(); ancho<<=1){
        
     //   cout << "====================================================" << endl;
     //   cout << "         ANCHO:   " << ancho << endl;
     //   cout << "====================================================" << endl;
        
        for(int i= 0; i < wrap.getW(); i+=ancho){
            for (int j=0; j < wrap.getH(); j+=ancho){
                qtUnwrap(wrap, i, j, ancho);
                //cout << "unwrap [" << i << "," << j <<"]x" << ancho << endl;
            }
        }
      //  cout << "============= process MATRIX =========================" << endl;
      //  cout << wrap;
      //  cout << "====================================================" << endl;
    }
}

void doGPUquadtreeUnwrap (Mapa &wrap){
	
	GPUunwrapper unwrapper(wrap.getPointer(), wrap.getW(),wrap.getH());
	unwrapper.doUnwrap();
}


int main (int argc, const char * argv[]){  

	
	fstream fout;
	fout.open("matrices.log",ios_base::out );
	cout.rdbuf(fout.rdbuf());
    
    /***************   MAPAS *****************/
    Mapa mapaORG(32,32);  // generate a default map
    Mapa wrap1(mapaORG);
    wrap1.doWrap();
    Mapa wrap2(wrap1);

    cout << "size:[" << mapaORG.getW() << "," << mapaORG.getH() << "] [" << wrap1.getW() << "," << wrap1.getH() <<"]" << endl;	
 //   cout << "============= original map=====================" << endl;
 //   cout << mapaORG;
    cout << "============= wrap ============================" << endl;
    cout << wrap1;

	doHOSTquadtreeUnwrap (wrap1);
	doGPUquadtreeUnwrap  (wrap2);

	fout << "============= GPU wrap ============================" << endl;
	fout << wrap2;

    cout << "HOST RESULT: " ;
    float error = 0.0f;
    if ( (error = wrap1.compare(mapaORG)) == 0.0)
        cout << "everything all right" << endl;
    else 
        cout << "error between maps: "<< error << endl;        

	
    /***************   CLEAN UP  *********************/
	fout.close();
	getchar();
    return 0;
}

