//
//  main.c
//  TP Final
//
//  Created by Valentin Ratti on 01/07/2019.
//  Copyright © 2019 Valentin Ratti. All rights reserved.
//


#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getInfo.h"
#include "queries.h"


int main(int argc, char * argv[]) {
   
   if(argc == 3){
    linesADT lines = newListLine();
       
    readAllStations(lines,argv[1]);
    readAllMolinetes(lines, argv[2]);
       
    queryOne(lines, "query1.csv");
    queryTwo(lines, "query2.csv");
    queryThree(lines,"query3.csv");
    queryFour(lines,"query4.csv");
    queryFive(lines,"query5.csv");
    querySix(lines,"query6.csv");
    querySeven(lines,"query7.csv");
       
    freeAllMemory(lines);
    return 0;
    
   }
    fprintf(stderr,"Error de parametros...\n");
    return 1;
}
