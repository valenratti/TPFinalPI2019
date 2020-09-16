//
//  getInfo.h
//  TP Final
//
//  Created by Valentin Ratti on 05/07/2019.
//  Copyright © 2019 Valentin Ratti. All rights reserved.
//

#ifndef getInfo_h
#define getInfo_h

#include "subteADT.h"


/*
 -------------------------------------------
 FUNCION: readAllStations;
 USO:          readAllStations(lines, file)
 DESCRIPCION: Lee el archivo de estaciones e inserta cada estacion
 en el vector de estaciones de la linea correspondiente.
 PRECONDICION: Lista valida, previamente creada.
 POSTCONDICION: Lista de lineas creada. Estaciones insertadas en el
 vector de la linea correspondiente.
 --------------------------------------------
 */
void readAllStations(linesADT lines, char *fileName);


/*
 -------------------------------------------
 FUNCION: readAllMolinetes;
 USO:          readAllMolinetes(lines, file)
 DESCRIPCION: Lee el archivo de molinetes y guarda la informacion en cada linea/estacion.
 PRECONDICION: Lista valida, previamente creada.
 POSTCONDICION: Cantidad de pasajeros de cada linea/estacion guardada.
 --------------------------------------------
 */
void readAllMolinetes(linesADT lines, char *fileName);

#endif /* getInfo_h */
