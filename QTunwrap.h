//
//  QTunwrap.h
//  QuadTreeUnwrap
//
//  Created by Luis  Ayuso Pérez on 28/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef QuadTreeUnwrap_QTunwrap_h
#define QuadTreeUnwrap_QTunwrap_h

#include "Mapa.h"
#include "Combinacion.h"
#include "Transformacion.h"

transformacion_t getScanTransform (suma_t s);

void qtUnwrap(Mapa &m, int i, int j, int ancho);

#endif
