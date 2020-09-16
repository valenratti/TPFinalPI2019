//
//  queries.c
//  TP Final
//
//  Created by Valentin Ratti on 10/07/2019.
//  Copyright © 2019 Valentin Ratti. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "queries.h"
#include "subteADT.h"

/*Query 1*/
void queryOne(linesADT lines,char *file1){
    FILE *queryOne = fopen(file1,"w");
    if(!queryOne){
        fprintf(stderr,"Error al crear el archivo %s\n",file1);
    }
    fprintf(queryOne,"Linea,Pasajeros\n");
    orderLinesPassengers(lines); /*Funcion que afecta tambien al query 3.*/
    toBeginPassengers(lines);
    
    while(hasNextPassengers(lines)){
        fprintf(queryOne,"%c,%ld\n", getNextFrecuentedLine(lines), getNextPassengers(lines));
        nextPassengers(lines);
    }
    fclose(queryOne);
}

/*Query 2*/
void queryTwo(linesADT lines, char *file2){
    FILE *queryTwo = fopen(file2,"w");
    if(!queryTwo){
        fprintf(stderr,"Error al crear el archivo %s\n",file2);
    }
    fprintf(queryTwo,"Dia,Diurnos,Nocturnos,Total\n");
    
    int i;
    long day, night;
    char nameDay[10];
    for(i=0; i<7; i++){
        day = getPassengersAllLines(lines,i,0);
        night = getPassengersAllLines(lines,i,1);
        switch(i)
        {
            case 0:
                strcpy(nameDay,"Domingo");
                break;
            case 1:
                strcpy(nameDay,"Lunes");
                break;
            case 2:
                strcpy(nameDay,"Martes");
                break;
            case 3:
                strcpy(nameDay,"Miercoles");
                break;
            case 4:
                strcpy(nameDay,"Jueves");
                break;
            case 5:
                strcpy(nameDay,"Viernes");
                break;
            case 6:
                strcpy(nameDay,"Sabado");
                break;
        }
        fprintf(queryTwo,"%s, %ld, %ld, %ld\n", nameDay, day, night, day+night);
    }
    fclose(queryTwo);
}

/*Query 3*/
void queryThree(linesADT lines, char *file3){
    
    FILE *queryThree = fopen(file3,"w");
    if(!queryThree){
        fprintf(stderr,"Error al crear el archivo %s\n",file3);
    }
    fprintf(queryThree,"Linea,Porcentaje\n");
    /*Si se elimina orderLinesPassengers del query 1, invocarla aca.*/
    toBeginPassengers(lines);
    long allPassengers = getAllPassengers(lines);
    while(hasNextPassengers(lines)){
        
        fprintf(queryThree,"%c,%d%%\n", getNextFrecuentedLine(lines), (int)((getNextPassengers(lines) * 100)/allPassengers));
        nextPassengers(lines);
    }
    fclose(queryThree);
    
}


/*Query 4*/
void queryFour(linesADT lines, char *file4){
    FILE *queryFour = fopen(file4,"w");
    if(!queryFour){
        fprintf(stderr,"Error al crear el archivo %s\n",file4);
    }
    calculateLeastMostFrecuency(lines); /*Funcion que afecta tambien al query 5.*/
    
    fprintf(queryFour, "Estacion,Linea,Pasajeros\n");
    toBeginLines(lines);
    
    while(hasNextLine(lines)){
        fprintf(queryFour,"%s,%c,%ld\n",getCurrentFrecuentedStation(lines,1), getCurrentLineID(lines), getCurrentLineFrecuency(lines,1));
        nextLine(lines);
    }
    fclose(queryFour);
}



/*Query 5*/
void queryFive(linesADT lines, char *file5){
    FILE *queryFive = fopen(file5,"w");
    if(!queryFive){
        fprintf(stderr,"Error al crear el archivo %s\n",file5);
    }
    /*Si se elimina calculatLeastMostFrecuency del query 4, invocarla aca.*/
    
    fprintf(queryFive,"Estacion,Linea,Pasajeros\n");
    toBeginLines(lines);
    while(hasNextLine(lines)){
        fprintf(queryFive,"%s,%c,%ld\n",getCurrentFrecuentedStation(lines,0), getCurrentLineID(lines), getCurrentLineFrecuency(lines,0));
        nextLine(lines);
    }
    fclose(queryFive);
    
}


/*Query 6*/
void querySix(linesADT lines, char *file6){
    FILE *querySix = fopen(file6,"w");
    if(!querySix){
        fprintf(stderr,"Error al crear el archivo %s\n",file6);
    }
    fprintf(querySix,"Estacion,Linea,Pasajeros\n");
    calculateTopStations(lines); /*Funcion que afecta tambien al query 7.*/
    toBeginTopDiurnal(lines);
    for(int i=0; i<5 && hasNextTopDiurnal(lines); i++, nextTopDiurnal(lines))
        fprintf(querySix, "%s,%c,%ld\n", getNextTopNameDiurnal(lines), getNextTopIDDiurnal(lines), getNextTopTotalDiurnal(lines));
    fclose(querySix);
}


/*Query 7*/
void querySeven(linesADT lines, char *file7){
    FILE *querySeven = fopen(file7,"w");
    if(!querySeven){
        fprintf(stderr,"Error al crear el archivo %s\n",file7);
    }
    fprintf(querySeven,"Estacion,Linea,Pasajeros\n");
    /*Si se elimina calculateTopStations del query 6, invocarla aca.*/
    toBeginTopNocturnal(lines);
    for(int i=0; i<5 && hasNextTopNocturnal(lines); i++, nextTopNocturnal(lines))
        fprintf(querySeven, "%s,%c,%ld\n", getNextTopNameNocturnal(lines), getNextTopIDNocturnal(lines), getNextTopTotalNocturnal(lines));
    fclose(querySeven);
}


