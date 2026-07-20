#include <stdio.h>
#include "file.h"


#define FILE_NAME "parking.dat"



void saveRecords()
{
    FILE *fp;

    fp = fopen(FILE_NAME,"wb");


    if(fp == NULL)
    {
        printf("\nFile opening error.\n");
        return;
    }


    fwrite(&vehicleCount,sizeof(int),1,fp);


    fwrite(vehicles,
           sizeof(Vehicle),
           vehicleCount,
           fp);



    fwrite(&totalRevenue,
           sizeof(double),
           1,
           fp);



    fwrite(&totalVehiclesServed,
           sizeof(int),
           1,
           fp);



    fwrite(&nextParkingID,
           sizeof(int),
           1,
           fp);



    fclose(fp);


    printf("\nRecords Saved Successfully.\n");
}



//to load data back in the program from the file
void loadRecords()
{
    FILE *fp;


    fp = fopen(FILE_NAME,"rb");


    if(fp == NULL)
    {
        printf("\nNo Previous Records Found.\n");
        return;
    }


    fread(&vehicleCount,
          sizeof(int),
          1,
          fp);



    fread(vehicles,
          sizeof(Vehicle),
          vehicleCount,
          fp);



    fread(&totalRevenue,
          sizeof(double),
          1,
          fp);



    fread(&totalVehiclesServed,
          sizeof(int),
          1,
          fp);



    fread(&nextParkingID,
          sizeof(int),
          1,
          fp);



    fclose(fp);


    printf("\nRecords Loaded Successfully.\n");
}