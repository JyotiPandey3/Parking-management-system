#include <stdio.h>

#define TOTAL_SLOTS 15

// Global Arrays to keep track of parking data
int parking_slots[TOTAL_SLOTS] = {0}; // 0 = Empty, 1 = Occupied
int entry_times[TOTAL_SLOTS] = {0};   // Stores the entry hour (0-23) for each slot

// Pricing Configuration.
const float BASE_RATE = 5.0;   // Charge for the first hour
const float HOURLY_RATE = 2.0; // Charge per hour after the first

// Function to allocate a parking slot
void allocate_slot() {
    int entry_hour;
    
    printf("\nEnter entry hour (0-23): ");
    scanf("%d", &entry_hour);
    
    if (entry_hour < 0 || entry_hour > 23) {
        printf("❌ Invalid hour! Please enter a value between 0 and 23.\n");
        return;
    }

    // LOOP: Scan the array to find the first empty slot (0)
    for (int i = 0; i < TOTAL_SLOTS; i++) {
        if (parking_slots[i] == 0) {
            parking_slots[i] = 1;         // Mark slot as occupied
            entry_times[i] = entry_hour;  // Save the arrival time
            printf("🚗 Success: Car parked in Slot %d.\n", i + 1);
            return; 
        }
    }
    
    printf("❌ Sorry: Parking lot is completely full!\n");
}

// Function to calculate charges and vacate a slot
void release_slot() {
    int slot_number, exit_hour;
    
    printf("\nEnter slot number to vacate (1-15): ");
    scanf("%d", &slot_number);
    
    // Validate slot number bounds
    if (slot_number < 1 || slot_number > TOTAL_SLOTS) {
        printf("❌ Invalid slot number!\n");
        return;
    }
    
    // Map user input (1-15) to array index (0-14)
    int index = slot_number - 1;
    
    if (parking_slots[index] == 0) {
        printf("❌ Slot %d is already empty!\n", slot_number);
        return;
    }
    
    printf("Enter exit hour (0-23): ");
    scanf("%d", &exit_hour);
    
    if (exit_hour < 0 || exit_hour > 23) {
        printf("❌ Invalid hour!\n");
        return;
    }

    // Calculate duration
    int hours_parked = exit_hour - entry_times[index];
    
    // Handle overnight parking adjustment
    if (hours_parked < 0) {
        hours_parked += 24;
    }
    if (hours_parked == 0) {
        hours_parked = 1; // Minimum 1-hour charge
    }

    // Math calculation using conditional logic
    float total_charge = BASE_RATE;
    if (hours_parked > 1) {
        total_charge += (hours_parked - 1) * HOURLY_RATE;
    }

    // Reset the array elements to free up the space
    parking_slots[index] = 0;
    entry_times[index] = 0;
    
    printf("\n💳 --- PARKING RECEIPT --- \n");
    printf("   Slot Cleared: %d\n", slot_number);
    printf("   Hours Parked: %d hr(s)\n", hours_parked);
    printf("   Total Fee   : $%.2f\n", total_charge);
    printf("--------------------------\n");
}

// Function to view current state of all slots
void display_status() {
    printf("\n--- Parking Lot Status ---\n");
    for (int i = 0; i < TOTAL_SLOTS; i++) {
        printf("Slot %02d: [%s]\n", i + 1, parking_slots[i] == 1 ? "OCCUPIED" : "EMPTY");
    }
}

int main() {
    int choice;

    // LOOP: Continuous menu display until the user chooses to exit
    while (1) {
        printf("\n=== CP-15 PARKING SYSTEM ===\n");
        printf("1. Allocate Parking Slot\n");
        printf("2. Vacate Slot & Calculate Charges\n");
        printf("3. Display Parking Status\n");
        printf("4. Exit System\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                allocate_slot();
                break;
            case 2:
                release_slot();
                break;
            case 3:
                display_status();
                break;
            case 4:
                printf("Shutting down CP-15 System. Goodbye!\n");
                return 0;
            default:
                printf("❌ Invalid menu choice. Try again.\n");
        }
    }
    return 0;
}