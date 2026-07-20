#include <stdio.h>

#include "parking.h"
#include "file.h"


int main()
{
    int choice;


    initializeParking();
    loadRecords();
    rebuildFreeSlotQueue();


    while(1)
    {
        displayDashboard();


        printf("\n================ MENU ================\n");

        printf("1. Park Vehicle\n");
        printf("2. Exit Vehicle\n");
        printf("3. Search Vehicle\n");
        printf("4. Display Parked Vehicles\n");
        printf("5. Parking Status\n");
        printf("6. Revenue Report\n");
        printf("7. Display Available Slots\n");
        printf("8. Exit\n");


        printf("=======================================\n");

        printf("Enter Choice : ");
        scanf("%d",&choice);



        switch(choice)
        {

            case 1:
                parkVehicle();
                break;


            case 2:
                exitVehicle();
                break;


            case 3:
            {
                char vehicleNumber[20];


                printf("\nEnter Vehicle Number : ");
                scanf("%s",vehicleNumber);


                int index = searchVehicle(vehicleNumber);


                if(index == -1)
                {
                    printf("\nVehicle Not Found.\n");
                }
                else
                {
                    displayVehicleDetails(index);
                }

                break;
            }



            case 4:
                displayParkedVehicles();
                break;



            case 5:
                displayParkingStatus();
                break;



            case 6:
            
            if(adminLogin())
            {
                displayRevenueReport();
            }
            break;
            case 7:
            displayAvailableSlots(&freeSlots);
                break;



            case 8:

                saveRecords();

                printf("\nThanks for watching with zero attention.\n");

                return 0;



            default:

                printf("\nInvalid Choice.\n");
        }
    }
    return 0;
}

//gcc main.c parking.c queue.c file.c -o parking
//./parking
