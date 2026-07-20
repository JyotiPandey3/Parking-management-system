#ifndef PARKING_H
#define PARKING_H

#include<time.h>
#include "queue.h"

#define MAX_VEHICLES 1000

typedef enum
{
    BIKE=1,
    CAR,
    BUS,
    TRUCK
}VehicleType;

typedef struct
{
    int parkingID;

    char vehicleNumber[20];

    char ownerName[50];

    VehicleType type;

    int slotNumber;

    time_t entryTime;

    time_t exitTime;

    double parkingCharge;

    int isParked;

}Vehicle;

// Parking Operations
int adminLogin();
void parkVehicle();
void exitVehicle();
int searchVehicle(char vehicleNumber[]);
void displayParkedVehicles();
void displayParkingStatus();
double calculateCharge(time_t entry,time_t exit,VehicleType type);
int generateParkingID();
void initializeParking();
void displayCurrentTime(time_t t);
char* getVehicleType(int type);
void displayRevenueReport();
int generateReceiptNo();
void displayVehicleDetails(int index);
void rebuildFreeSlotQueue();

//Since vehicles, vehicleCount, totalRevenue, etc. are inside parking.c, file.c cannot access them.
//We solve this using extern.

extern Vehicle vehicles[MAX_VEHICLES];
extern int vehicleCount;
extern double totalRevenue;
extern int totalVehiclesServed;
extern int nextParkingID;
extern Queue freeSlots;
#endif
