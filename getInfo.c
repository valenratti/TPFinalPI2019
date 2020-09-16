//
//  getInfo.c
//  TP Final
//
//  Created by Valentin Ratti on 05/07/2019.
//  Copyright © 2019 Valentin Ratti. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "getInfo.h"


#define CENTURY 100

typedef struct molinetesInfo{
    int dayOfWeek; //0-7 dependiendo del dia de la semana.
    int timeOfDay; // 0-1 dependiendo de diurno o nocturno.
    int stationId;
    int passengersQty; // pasajeros que pasaron por el molinete.
}molinetesInfo;

typedef struct stationsInfo{
    int id;
    char line; //linea a la cual pertenece la estacion.
    char name[30];
}stationsInfo;



static int whatDayIsIt(char *fecha)
{
    
    int d = atoi(strtok(fecha,"/"));
    int m = atoi(strtok(NULL,"/"));
    int y = atoi(strtok(NULL,"/"));
    
    int c, g;
    static int eLookUpTable[]={0,3,2,5,0,3,5,1,4,6,2,4};
    static int fLookUpTable[]={0,5,3,1};
    
    if(m<3)
        y--;
    
    c=y/CENTURY;
    g=y-CENTURY*c;
    
    return ((int)(d+eLookUpTable[m-1]+fLookUpTable[c%4]+g+(g/4)))%7;
}

static int whatTimeIsIt(char *hora){
    
    int h = atoi(strtok(hora,":"));
    int m = atoi(strtok(NULL,":"));
    
    if (((h==6 && m>0) || h > 6) && (h<17 || (h==17 && m==0)) ) {
        return 0;
    }
    return 1;
}




molinetesInfo readMolinete(char *lineInfo){
    molinetesInfo info;
    
    char *fecha = malloc(11);
    char *hora = malloc(6);
    
    //FECHA
    char *token;
    token = strtok(lineInfo, ",");
    strcpy(fecha,token);
    
    
    //HORA
    token = strtok(NULL,","); //Salteamos la primer hora, ya que solo la segunda basta.
    token = strtok(NULL,",");
    strcpy(hora,token);
    
    //ID
    token = strtok(NULL,",");
    info.stationId = atoi(token);
    
    //Pasajeros
    
    token = strtok(NULL,",");
    info.passengersQty = atoi(token);
    
    info.dayOfWeek = whatDayIsIt(fecha);
    info.timeOfDay = whatTimeIsIt(hora);
    free(fecha);
    free(hora);
    
    return info;
}


void readAllMolinetes(linesADT lines, char *fileName){
    FILE *file = fopen(fileName,"r");
    if (!file) {
        fprintf(stderr,"Error al abrir %s\n",fileName);
        exit(1);
    }
    char lineInfo[100];
    molinetesInfo information;
    fgets(lineInfo,100,file); // salteamos el titulo.
    
    while(fgets(lineInfo,100,file)){
        information = readMolinete(lineInfo);
    insertPassengers(lines,information.stationId,information.dayOfWeek,information.timeOfDay,information.passengersQty);
    }
    fclose(file);
}

stationsInfo readStation(char *lineInfo){
    stationsInfo info;
    //ID
    char *token = strtok(lineInfo,",");
    info.id = atoi(token);
    //LINEA
    token = strtok(NULL, ",");
    info.line = token[0];
    //NOMBRE DE LA ESTACION
    token = strtok(NULL, "\n");
    strcpy(info.name,token);
    return info;
}

void readAllStations(linesADT lines, char *fileName){
    FILE *file = fopen(fileName,"r");
    if (!file) {
        fprintf(stderr,"Error al abrir %s\n",fileName);
        exit(1);
    }
    char lineInfo[100] = "";
    stationsInfo information;
    fgets(lineInfo,100,file); // Salteamos el titulo.
    
    while(fgets(lineInfo,100,file)){
        information = readStation(lineInfo);
        insertStation(information.line,information.id,information.name, lines);
    }
    fclose(file);
}





