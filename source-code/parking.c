#include <stdio.h>
#include <string.h>
#include <time.h>

#include "parking.h"
#include "queue.h"
#include "file.h"
//global variables (step2)
Vehicle vehicles[MAX_VEHICLES];

int vehicleCount = 0;

int nextParkingID = 1001;

double totalRevenue = 0;

int totalVehiclesServed = 0;
int nextReceipt = 1;

Queue freeSlots;

//step3

void initializeParking()
{
    initializeQueue(&freeSlots);
    loadRecords();
    rebuildFreeSlotQueue();
}
void rebuildFreeSlotQueue()
{
    int slot, i;
    int occupied;

    // Start with an empty queue
    freeSlots.front = 0;
    freeSlots.rear = -1;
    freeSlots.count = 0;

    // Check every parking slot
    for(slot = 1; slot <= MAX_SLOTS; slot++)
    {
        occupied = 0;

        // Check if this slot is occupied
        for(i = 0; i < vehicleCount; i++)
        {
            if(vehicles[i].isParked &&
               vehicles[i].slotNumber == slot)
            {
                occupied = 1;
                break;
            }
        }

        // If free, add it to the queue
        if(!occupied)
        {
            enqueue(&freeSlots, slot);
        }
    }
}

//step 4
int generateParkingID()
{
    return nextParkingID++;
}
int generateReceiptNo()
{
    return nextReceipt++;
}


//step5
int searchVehicle(char vehicleNumber[])
{
    int i;

    for(i=0;i<vehicleCount;i++)
    {
        if(strcmp(vehicles[i].vehicleNumber,vehicleNumber)==0
           && vehicles[i].isParked==1)
        {
            return i;
        }
    }

    return -1;
}

void displayVehicleDetails(int index)
{
    printf("\n================================================");
    printf("\n              VEHICLE DETAILS");
    printf("\n================================================\n");

    printf("Parking ID      : %d\n",
           vehicles[index].parkingID);

    printf("Vehicle Number  : %s\n",
           vehicles[index].vehicleNumber);

    printf("Owner Name      : %s\n",
           vehicles[index].ownerName);

    printf("Vehicle Type    : %s\n",
           getVehicleType(vehicles[index].type));

    printf("Parking Slot    : %d\n",
           vehicles[index].slotNumber);

    printf("Entry Time      : ");

    displayCurrentTime(vehicles[index].entryTime);

    printf("\n");

    if(vehicles[index].isParked)
    {
        printf("Status          : Currently Parked\n");
    }
    else
    {
        printf("Status          : Vehicle Exited\n");

        printf("Exit Time       : ");

        displayCurrentTime(vehicles[index].exitTime);

        printf("\n");

        printf("Charge Paid     : Rs %.2lf\n",
               vehicles[index].parkingCharge);
    }

    printf("================================================\n");
}

//step6 crrent time
void displayCurrentTime(time_t t)
{
    struct tm *timeInfo;

    timeInfo = localtime(&t);

    printf("%02d-%02d-%04d %02d:%02d:%02d",
        timeInfo->tm_mday,
        timeInfo->tm_mon + 1,
        timeInfo->tm_year + 1900,
        timeInfo->tm_hour,
        timeInfo->tm_min,
        timeInfo->tm_sec);
            
}


//step7 vehicle type 
char* getVehicleType(int type)
{
    switch(type)
    {
        case BIKE:
            return "Bike";

        case CAR:
            return "Car";

        case BUS:
            return "Bus";

        case TRUCK:
            return "Truck";

        default:
            return "Unknown";
    }
}

//parking

void parkVehicle()
{
    if (isEmpty(&freeSlots))
    {
        printf("\n================================");
        printf("\n     PARKING IS FULL");
        printf("\n================================\n");
        return;
    }

    Vehicle newVehicle;

    printf("\n========== PARK VEHICLE ==========\n");

    printf("\nParking Charges (Per Hour)\n");
    printf("--------------------------\n");
    printf("Bike   : Rs 20\n");
    printf("Car    : Rs 50\n");
    printf("Bus    : Rs 80\n");
    printf("Truck  : Rs 100\n\n");

    printf("Enter Vehicle Number (or type EXIT to cancel): ");
    scanf("%s", newVehicle.vehicleNumber);
    if(strcmp(newVehicle.vehicleNumber, "EXIT") == 0)
    {
        printf("\nParking Cancelled.\n");
        return;
    }

    // Vehicle Number Validation
    if (strlen(newVehicle.vehicleNumber) < 5)
    {
        printf("\nInvalid Vehicle Number.\n");
        return;
        
    }
    printf("Enter Owner Name : ");
    scanf(" %[^\n]", newVehicle.ownerName);
    printf("\nVehicle Type\n");
    printf("1. Bike\n");
    printf("2. Car\n");
    printf("3. Bus\n");
    printf("4. Truck\n");
    printf("5. Cancel Parking\n");

    printf("Choose : ");
    scanf("%d", &newVehicle.type);


    if (newVehicle.type == 5)
    {
        printf("\nParking Cancelled.\n");
        return;
    }

    if (newVehicle.type < BIKE || newVehicle.type > TRUCK)
    {
        printf("\nInvalid Vehicle Type.\n");
        return;
    }

    // Checking for duplicate vehicle
    if (searchVehicle(newVehicle.vehicleNumber) != -1)
    {
        printf("\nVehicle Already Parked.\n");
        return;
    }

    newVehicle.parkingID = generateParkingID();
    newVehicle.slotNumber = dequeue(&freeSlots);
    newVehicle.entryTime = time(NULL);

    newVehicle.exitTime = 0;
    newVehicle.parkingCharge = 0;
    newVehicle.isParked = 1;

    vehicles[vehicleCount] = newVehicle;
    vehicleCount++;

    // Parking Ticket
    printf("\n====================================");
    printf("\n         PARKING TICKET");
    printf("\n====================================");

    printf("\nParking ID     : %d", newVehicle.parkingID);
    printf("\nVehicle Number : %s", newVehicle.vehicleNumber);
    printf("\nOwner Name     : %s", newVehicle.ownerName);
    printf("\nVehicle Type   : %s", getVehicleType(newVehicle.type));
    printf("\nSlot Number    : %d", newVehicle.slotNumber);

    printf("\nEntry Time     : ");
    displayCurrentTime(newVehicle.entryTime);

    printf("\n====================================\n");
}


double calculateCharge(time_t entry, time_t exit, VehicleType type)
{
    double hours;
    double rate;

    hours = difftime(exit, entry) / 3600.0;

    if(hours < 1)
        hours = 1;

    switch(type)
    {
        case BIKE:
            rate = 20;
            break;

        case CAR:
            rate = 50;
            break;

        case BUS:
            rate = 80;
            break;

        case TRUCK:
            rate = 100;
            break;

        default:
            rate = 0;
    }

    return hours * rate;
}


//exit management

void exitVehicle()
{
    char vehicleNumber[20];

    printf("\n========== VEHICLE EXIT ==========\n");

    printf("Enter Vehicle Number : ");
    scanf("%s", vehicleNumber);

    int index = searchVehicle(vehicleNumber);

    if(index == -1)
    {
        printf("\nVehicle Not Found.\n");
        return;
    }

    vehicles[index].exitTime = time(NULL);

    double hours = difftime(vehicles[index].exitTime,
                        vehicles[index].entryTime) / 3600.0;

    if (hours < 1){
        hours = 1;}

    vehicles[index].parkingCharge =
        calculateCharge(
            vehicles[index].entryTime,
            vehicles[index].exitTime,
            vehicles[index].type
        );

    vehicles[index].isParked = 0;

    enqueue(&freeSlots, vehicles[index].slotNumber);

    totalRevenue += vehicles[index].parkingCharge;

    totalVehiclesServed++;

   int receiptNo = generateReceiptNo();

printf("\n================================================");
printf("\n              PARKING RECEIPT");
printf("\n================================================");

printf("\nReceipt Number : R%05d", receiptNo);
printf("\nParking ID     : %d", vehicles[index].parkingID);

    printf("\nVehicle Number  : %s",
           vehicles[index].vehicleNumber);

    printf("\nOwner Name      : %s",
           vehicles[index].ownerName);

    printf("\nVehicle Type    : %s",
           getVehicleType(vehicles[index].type));

    printf("\nSlot Number     : %d",
           vehicles[index].slotNumber);

    printf("\nEntry Time      : ");
    displayCurrentTime(vehicles[index].entryTime);

    printf("Exit Time       : ");
    displayCurrentTime(vehicles[index].exitTime);

    printf("\nParking Duration : %.2lf Hours", hours);

    printf("Parking Charge  : Rs %.2lf",
           vehicles[index].parkingCharge);

    printf("\n====================================\n");

    printf("\nThank You! Visit Again.\n");

    printf("\n====================================\n");
}

//displaying the parked vehicle data
void displayParkedVehicles()
{
    int i;

    if(vehicleCount == 0)
    {
        printf("\nNo Vehicle Records Found.\n");
        return;
    }

    printf("\n================ CURRENT PARKED VEHICLES ================\n");

    printf("\n%-10s %-15s %-15s %-10s %-10s\n",
            "ID","Vehicle No","Owner","Type","Slot");

    printf("----------------------------------------------------------\n");

    for(i=0;i<vehicleCount;i++)
    {
        if(vehicles[i].isParked)
        {
            printf("%-10d %-15s %-15s %-10s %-10d\n",
                    vehicles[i].parkingID,
                    vehicles[i].vehicleNumber,
                    vehicles[i].ownerName,
                    getVehicleType(vehicles[i].type),
                    vehicles[i].slotNumber);
        }
    }

    printf("==========================================================\n");
}

//lots status
void displayParkingStatus()
{
    printf("\n========== PARKING STATUS ==========\n");

    printf("Total Parking Slots      : %d\n",MAX_SLOTS);

    printf("Available Slots          : %d\n",freeSlots.count);

    printf("Occupied Slots           : %d\n",
            MAX_SLOTS-freeSlots.count);

    printf("Vehicles Currently Parked: %d\n",
            MAX_SLOTS-freeSlots.count);

    printf("====================================\n");
}

//revenue collected
void displayRevenueReport()
{
    printf("\n========== REVENUE REPORT ==========\n");

    printf("Total Vehicles Served : %d\n",
            totalVehiclesServed);

    printf("Current Parked Vehicles : %d\n",
            MAX_SLOTS-freeSlots.count);

    printf("Total Revenue : Rs %.2lf\n",
            totalRevenue);

    printf("====================================\n");
}


//status dashboard of parkinng area for ser
void displayDashboard()
{
    printf("\n");
    printf("=====================================================\n");
    printf("           PARKING MANAGEMENT SYSTEM\n");
    printf("=====================================================\n");

   // printf(" Total Parking Slots : %d\n", MAX_SLOTS);
    printf(" Available Slots     : %d\n", freeSlots.count);
    //printf(" Occupied Slots      : %d\n", MAX_SLOTS - freeSlots.count);
    //printf(" Vehicles Served     : %d\n", totalVehiclesServed);
    //printf(" Total Revenue       : Rs %.2lf\n", totalRevenue);

    printf("=====================================================\n");
}





//password i believe 
int adminLogin()
{
    char password[20];

    printf("\n========== ADMIN LOGIN ==========\n");

    printf("Enter Password : ");
    scanf("%s", password);

    //printf("\nEntered Password: %s\n", password);
    //printf("Expected Password: admin\n");


    if(strcmp(password, "admin") == 0)
    {
        printf("\nLogin Successful.\n");
        return 1;
    }
    else
    {
        printf("\nIncorrect Password.\n");
        return 0;
    }
}
