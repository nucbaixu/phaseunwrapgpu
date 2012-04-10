//
//  tools.cpp
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 23/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "tools.h"

char symbol(int code){
    char c;
    switch (code) {
        case 0:
            c = ' ';
            break;
            
        case 1:
            c = '|';
            break;
            
        case 2:
            c = '#';
            break;
        default:
            c = 'e';
            break;
    }
    return c;
}

int  thresshold(float th, float v){
    
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
//    
//    
//    if (v > 2*th)
//        return 2;
//    if (v > th)
//        return 1;
//    if (v < -2*th)
//        return -2;
//    if (v < -th)
//        return -1;
//    
//    
//        
//    throw -1; // none!!
}


