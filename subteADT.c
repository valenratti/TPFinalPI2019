//
//  subteADT.c
//  TP Final
//
//  Created by Valentin Ratti on 05/07/2019.
//  Copyright © 2019 Valentin Ratti. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "subteADT.h"

#define MAX_LINES 10
#define MAX_LETRAS 30
#define MAX_STATIONS 15

#define DIURNAL 0
#define NOCTURNAL 1

#define TOP_QTY 5

#define MOST_FRECUENTED 1
#define LEAST_FRECUENTED 0




typedef struct passengersInfo{
    long dayPassengers[7]; //Pasajeros diurnos para cada dia de la semana. dayPassangers[0] son los del domingo.
    long nightPassengers[7]; //Pasajeros nocturnos para cada dia de la semana.
}passengersInfo;

typedef struct stationPassangers{
    char name[MAX_LETRAS];
    long total;
}stationPassangers;

typedef struct lineNode{
    char id;
    stationADT listStations; //Lista de estaciones que pertenecen a la linea.
    struct lineNode *next;
    long totalPassengers; //Pasajeros totales de la linea
    passengersInfo passengersInfo; //Informacion acerca de los pasajeros,
    stationPassangers mostFrequent; //Estacion de la linea con mas frecuencia de pasajeros.
    stationPassangers leastFrequent; //Estacion de la linea con menor frecuencia de pasajeros.
}lineNode;

typedef struct stationNode{
    char line; //Linea a la que pertenece la estacion
    char name[MAX_LETRAS];
    long passengers; //Total de pasajeros que pasaron por la estacion.
    struct stationNode *next;
}stationNode;

typedef struct topStations{
    stationNode *first;
    stationNode *current;
    size_t dim;
}topStations;

typedef struct linesPassengers{
    char id;
    long totalPassengers;
}linesPassengers;

typedef struct linesCDT{
    lineNode *first;
    lineNode *current;
    char belongsStation[100]; //Vector para relacionar ID de estaciones con linea a la cual pertenece. EJ: belongsStation[30] tendra a que linea pertenece la estacion de ID 30.
    size_t dim;
    linesPassengers linesPassengers[MAX_LINES]; //Total de pasajeros por cada linea, ordenados descendentemente.
    int currentPassengers; //Iterador para linesPassangers.
    topStations *topStationsDiurnal; //Lista de las estaciones ordenadas por cantidad de pasajeros diurnos
    topStations *topStationsNocturnal; //Lista de las estaciones ordenadas por cantidad de pasajeros nocturnos
}linesCDT;



typedef struct stationsInfo{
    char name[MAX_LETRAS];
    int id;
    long dayPassengers;
    long nightPassengers;
}stationsInfo;


typedef struct stationCDT{
    stationsInfo *stations;
    int current;
    size_t dim;
}stationCDT;

linesADT newListLine(){
    linesADT newListLine = calloc(1,sizeof(linesCDT));
    newListLine->topStationsDiurnal = calloc(1,sizeof(topStations));
    newListLine->topStationsNocturnal = calloc(1,sizeof(topStations));
    return newListLine;
}

static int compareLines(char line1, char line2){
    return line1-line2;
}

static lineNode *insertLineRec(lineNode *l, char id){
    int c;
    if(l == NULL || (c=compareLines(id,l->id)) < 0){
        lineNode *newLine = calloc(1,sizeof(lineNode));
        newLine->id = id;
        newLine->next = l;
        newLine->listStations = calloc(1,sizeof(stationCDT));
        newLine->listStations->stations = calloc(1,sizeof(stationsInfo));
        newLine->totalPassengers = 0;
        return newLine;
    }
    if(c == 0)
        return l;
    
    l->next = insertLineRec(l->next,id);
    return l;
    
}

void insertLine( linesADT lines, char id){
    lines->first = insertLineRec(lines->first,id);
    lines->dim++;
}

int existsLine(linesADT lines, char id){
    lineNode *iterator = lines->first;
    while(iterator){
        if(iterator->id == id)
            return 1;
        iterator = iterator->next;
    }
    return 0;
}

void toBeginLines(linesADT lines){
    lines->current = lines->first;
}

int hasNextLine(linesADT lines){
    return lines->current != NULL;
}

char getCurrentLineID(linesADT lines){
    return lines->current->id;
}

void nextLine(linesADT lines){
    lines->current = lines->current->next;
}



static void freeAllLinesRec(lineNode *l){
    if(l->next == NULL){
        freeStations(l->listStations);
        free(l);
        return;
    }
    freeAllLinesRec(l->next);
    freeStations(l->listStations);
    free(l);
}

void freeAllLines(linesADT lines){
    freeAllLinesRec(lines->first);
    free(lines);
}

static void freeTopListRec(stationNode *s){
    if(s->next == NULL){
        free(s);
        return;
    }
    
    freeTopListRec(s->next);
    free(s);
}

void freeTopList(linesADT lines){
    freeTopListRec(lines->topStationsDiurnal->first);
    freeTopListRec(lines->topStationsNocturnal->first);
    free(lines->topStationsDiurnal);
    free(lines->topStationsNocturnal);
}


void insertStation(char line, int stationId, char *name, linesADT lines){
    if(!existsLine(lines, line))
        insertLine(lines, line);
    lineNode *current = lines->first;
    while(current->id != line)
        current = current->next;
    stationsInfo *v = current->listStations->stations;
    size_t dim = current->listStations->dim++;
    v = realloc(v, sizeof(stationsInfo)*(dim+1));
    v[dim].dayPassengers=0;
    v[dim].nightPassengers=0;
    v[dim].id = stationId;
    strcpy(v[dim].name, name);
    lines->belongsStation[stationId] = current->id;
    current->listStations->stations = v;
}

static lineNode *getLineFromStation(linesADT lines, int stationId){
    lineNode *resp = lines->first;
    char lineToFind = lines->belongsStation[stationId];
    
    while(lineToFind != resp->id)
        resp = resp->next;
    
    return resp;
}


void insertPassengers(linesADT lines, int stationId, int day, int timeOfDay, unsigned int passengers){
   
    
    lineNode *line = getLineFromStation(lines,stationId);
    stationsInfo *station = line->listStations->stations;
    line->totalPassengers += passengers;
    
    int i = 0;
    while(station[i].id != stationId ) i++;
    //while(station->id != stationId) station++;
    
    if(timeOfDay == DIURNAL){
        line->passengersInfo.dayPassengers[day] += passengers;
        line->listStations->stations[i].dayPassengers += passengers;
    }else{
        line->passengersInfo.nightPassengers[day] += passengers;
        line->listStations->stations[i].nightPassengers += passengers;
    }
    
    
}

void toBeginStations(linesADT lines){
    lines->current->listStations->current = 0;
}

int hasNextStation(linesADT lines){
    return lines->current->listStations->current < lines->current->listStations->dim;
}


void freeStations(stationADT station){
    free(station->stations);
    free(station);
}

void orderLinesPassengers(linesADT lines){
    
    lineNode *current = lines->first;
    int i=0, j, k;
    while(current != NULL){
        lines->linesPassengers[i].id = current->id;
        lines->linesPassengers[i].totalPassengers = current->totalPassengers;
        i++;
        current = current->next;
    }
    
    linesPassengers aux;
    for(i=0; i<lines->dim; i++){
        k=i;
        for(j=i+1; j<lines->dim; j++)
            if(lines->linesPassengers[j].totalPassengers > lines->linesPassengers[k].totalPassengers)
                k=j;
        
        if(k != i){
                aux = lines->linesPassengers[k];
                lines->linesPassengers[k] = lines->linesPassengers[i];
                lines->linesPassengers[i] = aux;
        }
    }
}

void printAllLines(linesADT lines){
    lineNode *l = lines->first;
    int i;
    while(l != NULL){
        i=0;
        printf("LINEA %c\n",l->id);
        printf("CANT.PASAJEROS: %ld\n",l->totalPassengers);
        for(i=0; i<l->listStations->dim; i++)
            printf("%d. %s\n",i+1,l->listStations->stations[i].name);
        
        l = l->next;
    }
}

void toBeginPassengers(linesADT lines){
    lines->currentPassengers = 0;
    return;
}

int hasNextPassengers(linesADT lines){
    return lines->currentPassengers < lines->dim;
}

char getNextFrecuentedLine(linesADT lines){
    return lines->linesPassengers[lines->currentPassengers].id;
}

long getNextPassengers(linesADT lines){
    return lines->linesPassengers[lines->currentPassengers].totalPassengers;
}

void nextPassengers(linesADT lines){
    lines->currentPassengers++;
}

long getPassengersAllLines(linesADT lines, int day, int timeOfDay){
 
    lineNode *current = lines->first;
    long resp= 0;
    
    while(current){
        if(timeOfDay == 0)
            resp += current->passengersInfo.dayPassengers[day];
        else resp += current->passengersInfo.nightPassengers[day];
        
        current = current->next;
    }
    return resp;
}

long getAllPassengers(linesADT lines){
    
    lineNode *current = lines->first;
    long resp = 0;
    while(current){
        resp += current->totalPassengers;
        current = current->next;
    }
    return resp;
}


static void mostAndLeastFrequent(lineNode* line)
{
    int i, mostIterator, leastIterator;
    long most, least;
    most = least = line->listStations->stations[0].dayPassengers + line->listStations->stations[0].nightPassengers;
    long total;
    for(mostIterator=leastIterator=0, i=1; i<line->listStations->dim; i++)
    {
        total = line->listStations->stations[i].dayPassengers + line->listStations->stations[i].nightPassengers;
        if(total > most){
            most = total;
            mostIterator = i;
        }
        else
            if(total < least){
                least=total;
                leastIterator = i;
            }
        
    }
    line->mostFrequent.total = most;
    strcpy(line->mostFrequent.name, line->listStations->stations[mostIterator].name);
    line->leastFrequent.total = least;
    strcpy(line->leastFrequent.name, line->listStations->stations[leastIterator].name);
}

void calculateLeastMostFrecuency(linesADT lines)
{
    lineNode *current = lines->first;
    while(current)
    {
        mostAndLeastFrequent(current);
        current = current->next;
    }
}

char * getCurrentFrecuentedStation(linesADT lines, int option){
    if(option == LEAST_FRECUENTED)
        return lines->current->leastFrequent.name;
    else
        return lines->current->mostFrequent.name;
    
}

long getCurrentLineFrecuency(linesADT lines, int option){
    if(option == LEAST_FRECUENTED)
        return lines->current->leastFrequent.total;
    else return lines->current->mostFrequent.total;
}

static long comparePassengers(long passengers1, long passengers2){
    return passengers1-passengers2;
}

static stationNode *insertTopStationsRec(stationNode *s, char line, char *name, long passengers){
    long c;
    if(s == NULL || (c=comparePassengers(passengers,s->passengers)) >= 0){
        stationNode *newStation = calloc(1,sizeof(stationNode));
        newStation->line = line;
        strcpy(newStation->name,name);
        newStation->passengers = passengers;
        newStation->next = s;
        return newStation;
    }
    
    s->next = insertTopStationsRec(s->next,line,name,passengers);
    return s;
}

static void insertTopStations(linesADT lines, char line, char *name, long passengers, int option){
    if(option == DIURNAL)
    lines->topStationsDiurnal->first = insertTopStationsRec(lines->topStationsDiurnal->first, line,name,passengers);
    else
        lines->topStationsNocturnal->first = insertTopStationsRec(lines->topStationsNocturnal->first, line,name,passengers);
}

void calculateTopStations(linesADT lines){
    lineNode *current = lines->first;
    int i;
    stationsInfo *stations;
    while(current){
        stations = current->listStations->stations;
        for(i=0;i<current->listStations->dim;i++){
            insertTopStations(lines,current->id,stations[i].name,stations[i].dayPassengers,0);
            insertTopStations(lines,current->id,stations[i].name,stations[i].nightPassengers,1);
        }
        current = current->next;
    }
}

//DIURNAL TOP 5

char* getNextTopNameDiurnal(linesADT lines)
{
    return lines->topStationsDiurnal->current->name;
}

char getNextTopIDDiurnal(linesADT lines)
{
    return lines->topStationsDiurnal->current->line;
}

long getNextTopTotalDiurnal(linesADT lines)
{
    return lines->topStationsDiurnal->current->passengers;
}

void nextTopDiurnal(linesADT lines)
{
    lines->topStationsDiurnal->current = lines->topStationsDiurnal->current->next;
}

//NOCTURNAL TOP 5
char* getNextTopNameNocturnal(linesADT lines)
{
    return lines->topStationsNocturnal->current->name;
}

char getNextTopIDNocturnal(linesADT lines)
{
    return lines->topStationsNocturnal->current->line;
}

long getNextTopTotalNocturnal(linesADT lines)
{
    return lines->topStationsNocturnal->current->passengers;
}

void nextTopNocturnal(linesADT lines)
{
    lines->topStationsNocturnal->current = lines->topStationsNocturnal->current->next;
}

void toBeginTopDiurnal(linesADT lines)
{
    lines->topStationsDiurnal->current = lines->topStationsDiurnal->first;
}

void toBeginTopNocturnal(linesADT lines)
{
    lines->topStationsNocturnal->current = lines->topStationsNocturnal->first;
}

int hasNextTopDiurnal(linesADT lines){
    return lines->topStationsDiurnal->current != NULL;
}

int hasNextTopNocturnal(linesADT lines){
    return lines->topStationsNocturnal->current != NULL;
}


void freeAllMemory(linesADT lines){
    freeTopList(lines);
    freeAllLines(lines);
}
