#include <iostream>
#include <string>
#include "VehicleManager.h"

using namespace std;

int main()
{
    VehicleManager manager;

    int mainChoice;

    do
    {
        // ================= MAIN MENU =================

        cout << "\n";
        cout << "=================================================\n";
        cout << "           VEHICLE MANAGEMENT SYSTEM\n";
        cout << "=================================================\n";
        cout << "  1. Vehicle\n";
        cout << "  2. City\n";
        cout << "  3. Route\n";
        cout << "  4. Booking\n";
        cout << "  5. Trip\n";
        cout << "  6. Delete\n";
        cout << "  7. Exit\n";
        cout << "=================================================\n";

        cout << "\nEnter Your Choice: ";
        cin >> mainChoice;

        // Check invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        switch (mainChoice)
        {

            // =================================================
            // 1. VEHICLE MENU
            // =================================================

        case 1:
        {
            int vehicleChoice;

            do
            {
                cout << "\n";
                cout << "========================================\n";
                cout << "              VEHICLE MENU\n";
                cout << "========================================\n";
                cout << "  1. Add Vehicle\n";
                cout << "  2. Update Vehicle\n";
                cout << "  3. Search Vehicle\n";
                cout << "  4. View Vehicles\n";
                cout << "  5. Vehicle Service\n";
                cout << "  6. Back to Main Menu\n";
                cout << "========================================\n";

                cout << "\nEnter Your Choice: ";
                cin >> vehicleChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "\nInvalid input! Please enter a number.\n";
                    continue;
                }

                switch (vehicleChoice)
                {
                case 1:
                    manager.addVehicleFromUser();
                    break;

                case 2:
                {
                    string id;

                    cout << "\nEnter Vehicle ID to update: ";
                    cin >> id;

                    manager.updateVehicle(id);
                    break;
                }

                case 3:
                    manager.searchVehicle();
                    break;

                case 4:
                    manager.viewVehicles();
                    break;

                case 5:
                    manager.vehicleServiceMenu();
                    break;

                case 6:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid Choice! Please try again.\n";
                }

            } while (vehicleChoice != 6);

            break;
        }


        // =================================================
        // 2. CITY MENU
        // =================================================

        case 2:
        {
            int cityChoice;

            do
            {
                cout << "\n";
                cout << "========================================\n";
                cout << "                CITY MENU\n";
                cout << "========================================\n";
                cout << "  1. Add City\n";
                cout << "  2. View Cities\n";
                cout << "  3. Back to Main Menu\n";
                cout << "========================================\n";

                cout << "\nEnter Your Choice: ";
                cin >> cityChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "\nInvalid input! Please enter a number.\n";
                    continue;
                }

                switch (cityChoice)
                {
                case 1:
                {
                    string city;

                    cout << "\nEnter City Name: ";
                    cin.ignore();
                    getline(cin, city);

                    manager.addCity(city);
                    break;
                }

                case 2:
                    manager.viewCities();
                    break;

                case 3:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid Choice! Please try again.\n";
                }

            } while (cityChoice != 3);

            break;
        }


        // =================================================
        // 3. ROUTE MENU
        // =================================================

        case 3:
        {
            int routeChoice;

            do
            {
                cout << "\n";
                cout << "========================================\n";
                cout << "               ROUTE MENU\n";
                cout << "========================================\n";
                cout << "  1. Add Route\n";
                cout << "  2. View Routes\n";
                cout << "  3. Back to Main Menu\n";
                cout << "========================================\n";

                cout << "\nEnter Your Choice: ";
                cin >> routeChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "\nInvalid input! Please enter a number.\n";
                    continue;
                }

                switch (routeChoice)
                {
                case 1:
                    manager.addRoute();
                    break;

                case 2:
                    manager.viewRoutes();
                    break;

                case 3:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid Choice! Please try again.\n";
                }

            } while (routeChoice != 3);

            break;
        }


        // =================================================
        // 4. BOOKING MENU
        // =================================================

        case 4:
        {
            int bookingChoice;

            do
            {
                cout << "\n";
                cout << "========================================\n";
                cout << "              BOOKING MENU\n";
                cout << "========================================\n";
                cout << "  1. Add Booking\n";
                cout << "  2. View Bookings\n";
                cout << "  3. Back to Main Menu\n";
                cout << "========================================\n";

                cout << "\nEnter Your Choice: ";
                cin >> bookingChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "\nInvalid input! Please enter a number.\n";
                    continue;
                }

                switch (bookingChoice)
                {
                case 1:
                    manager.addBooking();
                    break;

                case 2:
                    manager.viewBookings();
                    break;

                case 3:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid Choice! Please try again.\n";
                }

            } while (bookingChoice != 3);

            break;
        }


        // =================================================
        // 5. TRIP MENU
        // =================================================

        case 5:
        {
            int tripChoice;

            do
            {
                cout << "\n";
                cout << "========================================\n";
                cout << "                TRIP MENU\n";
                cout << "  1. Schedule Trip\n";
                cout << "  2. View Trips\n";
                cout << "  3. Mark Trip as Completed\n";
                cout << "  4. Back to Main Menu\n";
                cout << "========================================\n";

                cout << "\nEnter Your Choice: ";
                cin >> tripChoice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "\nInvalid input! Please enter a number.\n";
                    continue;
                }

                switch (tripChoice)
                {
                case 1:
                    manager.scheduleTrip();
                    break;

                case 2:
                    manager.viewTrips();
                    break;

                case 3:
                    manager.markTripAsCompleted();
                    break;

                case 4:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid Choice! Please try again.\n";
                }

            } while (tripChoice != 4);

            break;
        }


        // =================================================
        // 6. DELETE MENU
        // =================================================

        case 6:
            manager.deleteMenu();
            break;


            // =================================================
            // 7. EXIT
            // =================================================

        case 7:
            cout << "\n=================================================\n";
            cout << "       Exiting Vehicle Management System...\n";
            cout << "=================================================\n";
            break;


            // =================================================
            // INVALID MAIN MENU CHOICE
            // =================================================

        default:
            cout << "\nInvalid Choice! Please try again.\n";
        }

    } while (mainChoice != 7);

    return 0;
}
