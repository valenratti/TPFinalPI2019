//
//  subteADT.h
//  TP Final
//
//  Created by Valentin Ratti on 05/07/2019.
//  Copyright © 2019 Valentin Ratti. All rights reserved.
//

#ifndef subteADT_h
#define subteADT_h


/*El siguiente tipo define el TAD para subte. Se lo define como puntero a cierta estructura para ocultar la representacion de la misma*/
typedef struct linesCDT *linesADT;

/* Funcion:          newList
 * Uso:          list = newListLine();
 * -------------------------------------------------------------------
 * DescripciÛn:     Crea una nueva lista de lineas de subte.
 * -------------------------------------------------------------------
 * Precondicion:        -
 * Postcondicion:     Lista creada
 */
linesADT newListLine(void);

/* Funcion:          insertLine
 * Uso:              insertLine( lines, A);
 * -------------------------------------------------------------------
 * DescripciÛn:     Inserta una nueva linea en la lista ordenada(alfabeticamente).
 *                  Si el elemento ya existÌa, lo ignora y no modifica la lista.
 * -------------------------------------------------------------------
 * Precondicion:    Lista que sea valida, previamente creada
 * Postcondicion:     Lista con la nueva linea,si no estaba repetida.
 */
void insertLine( linesADT lines, char id);

/* Funcion:          existsLine
 * Uso:              resp = existsLine(lines, list, D);
 * -------------------------------------------------------------------
 * DescripciÛn:     Devuelve 0 en caso de que la linea este ya insertada en la lista.
 *                  Caso contrario, devuelve 1 si la linea no esta en la lista.
 * -------------------------------------------------------------------
 * Precondicion:    -
 * Postcondicion:     Ahora conocemos la existencia o no de la linea en la lista.
 */
int existsLine(linesADT lines, char id);

/**
 * Funciones para poder iterar sobre la lista
 */
void toBeginLines(linesADT lines);

int hasNextLine(linesADT lines);

void nextLine(linesADT lines);

char getCurrentLineID(linesADT lines);

/* Funcion:          orderLinesPassengers
 * Uso:              orderLinesPassengers(lines);
 * -------------------------------------------------------------------
 * DescripciÛn:     Usando los datos de pasajeros por lineas, ordena las mismas...
 *                  por cantidad de pasajeros descendentemente
 * -------------------------------------------------------------------
 * Precondicion:    -
 * Postcondicion:     Ahora tenemos ordenadas las lineas por cantidad de pasajeros
 *                     y podemos pedir informacion acerca de ellos.
 */
void orderLinesPassengers(linesADT lines);

/**
 * Funciones para poder iterar sobre la lista de lineas ordenadas por cantidad de pasajeros.
 PRECONDICION: Haber llamado antes a la funcion orderLinesPassengers.
 */
void toBeginPassengers(linesADT lines);

int hasNextPassengers(linesADT lines);

char getNextFrecuentedLine(linesADT lines);

long getNextPassengers(linesADT lines);

void nextPassengers(linesADT lines);





//FUNCIONES PARA ESTACIONES

typedef struct stationCDT *stationADT;

/* Funcion:          insertStation
 * Uso:              insertStation(A,35,CONGRESO,lines);
 * -------------------------------------------------------------------
 * DescripciÛn:     Inserta una estacion en una lista de lineas.
 *                  En caso de no existir la linea a la cual pertenece
 *                   la crea tambien.
 * -------------------------------------------------------------------
 * Precondicion:    Tener una lista de lineas creada.
 * Postcondicion:     Se agrego la estacion a la correspondiente linea de subte.
 */
void insertStation(char line, int stationId, char *name, linesADT lines);

/**
 * Funciones para poder iterar sobre las estaciones (De la linea que este como "current" cuando se llame a la funcion.
 */
void toBeginStations(linesADT lines);

int hasNextStation(linesADT lines);

/* Funcion:          insertPassengers
 * Uso:              insertPassengers(lines,35,3,0,57);
 * -------------------------------------------------------------------
 * DescripciÛn:     Esta funcion nos permite manejar el transito de pasajeros
 *                  del subte. El parametro day va de 0 a 6, donde 0 es domingo
 *                  y 6 es sabado. Inserta en la estacion correspondiente el flujo
 *                  de pasajeros pasado por parametro. Para timeOfDay, 0 es
 *                  diurno y 1 nocturno.
 * -------------------------------------------------------------------
 * Precondicion:    Tener una lista de lineas creada, y la estacion como parametro
 *                   tambien debe estar agregada
 * Postcondicion:    Se agrego la estacion a la correspondiente linea de subte.
 */
void insertPassengers(linesADT lines, int stationId, int day, int timeOfDay, unsigned int passengers);

/* Funcion:          getPassengersAllLines
 * Uso:              getPassengersAllLines(lines,6,1);
 * -------------------------------------------------------------------
 * DescripciÛn:     Esta funcion nos permite manejar el transito de pasajeros
 *                  del subte. El parametro day va de 0 a 6, donde 0 es domingo
 *                  y 6 es sabado. Inserta en la estacion correspondiente el flujo
 *                   de pasajeros pasado por parametro. 0 para Diurno, 1 Nocturno.
 * -------------------------------------------------------------------
 * Precondicion:    Tener una lista de lineas creada.
 * Postcondicion:     Recibimos la informacion descrita en descripcion.
 */
long getPassengersAllLines(linesADT lines, int day, int timeOfDay);

/* Funcion:          getAllPassengers
 * Uso:              getPassengersAllLines(lines);
 * -------------------------------------------------------------------
 * DescripciÛn:     Devuelve la cantidad de pasajeros totales que transitaron
 *                      el subte.
 * -------------------------------------------------------------------
 * Precondicion:    Tener una lista de lineas creada.
 * Postcondicion:     Obtenemos la cantidad de pasajeros totales por subte.
 */
long getAllPassengers(linesADT lines);



/* Funcion:         calculateLeastMostFrcuency
 * Uso:         calculateLeastMostFrcuency(lines)
 * -------------------------------------------------------------------
 * Descripción:     Calcula las estaciones con mas y menos pasajeros de cada linea de subte.
 * -------------------------------------------------------------------
 * Precondicion:    Lista que sea valida.
 * Postcondicion:     -
 */
void calculateLeastMostFrecuency(linesADT lines);

/* Funcion:         calculateTopStations
 * Uso:         calculateTopStations(lines)
 * -------------------------------------------------------------------
 * Descripción:     Crea dos listas de estaciones, ordenadas descendentemente.
 Una por cantidad de pasajeros diurnos y la otra por cantidad
 de pasajeros nocturnos.
 * -------------------------------------------------------------------
 * Precondicion:    Lista que sea valida.
 * Postcondicion:     -
 */

/**
 * Funciones para poder iterar sobre las estaciones mas y menos frecuentes de la estacion "current"
 */
char * getCurrentFrecuentedStation(linesADT lines, int option); //1 for most frequented station, 0 for least.

long getCurrentLineFrecuency(linesADT lines, int option); // 1 for most frequented station, 0 for least


void calculateTopStations(linesADT lines);

/**
 * Funciones para poder iterar sobre las listas de los top de estaciones (diurnas y nocturnas)
 */


void toBeginTopNocturnal(linesADT lines);

void toBeginTopDiurnal(linesADT lines);

void nextTopNocturnal(linesADT lines);

void nextTopDiurnal(linesADT lines);

int hasNextTopDiurnal(linesADT lines);

int hasNextTopNocturnal(linesADT lines);

long getNextTopTotalNocturnal(linesADT lines);

long getNextTopTotalDiurnal(linesADT lines);

char getNextTopIDNocturnal(linesADT lines);

char getNextTopIDDiurnal(linesADT lines);

char* getNextTopNameNocturnal(linesADT lines);

char* getNextTopNameDiurnal(linesADT lines);


/**
 * Funciones para liberar memoria alocada
 */
void freeStations(stationADT station);

void freeAllLines(linesADT lines);

void freeAllMemory(linesADT lines);

#endif /* subteADT_h */
