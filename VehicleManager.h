#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<cctype>
#include"Vehicle.h"

using namespace std;

class VehicleManager
{
private:

	vector<Vehicle> vehicles;
	vector<string> cities;
	vector<string> routes;
	vector<string> bookings;
	vector<string> trips;

	// =========================================================
	// CONVERT STRING TO UPPERCASE
	// =========================================================

	string toUpperCase(string text)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] = toupper(static_cast<unsigned char>(text[i]));
		}

		return text;
	}


public:

	// =========================================================
	// CONSTRUCTOR
	// =========================================================

	VehicleManager()
	{
		cities.push_back("Hyderabad");
		cities.push_back("Chennai");
		cities.push_back("Vijayawada");
		cities.push_back("Vishakapatnam");
		cities.push_back("Bangalore");
		cities.push_back("Mumbai");
		cities.push_back("Pune");
		cities.push_back("Kolkata");
		cities.push_back("Delhi");
		cities.push_back("Ahmedabad");

		loadVehicles();
		loadCities();
		loadRoutes();
		generateAllRoutes();
		loadBookings();
		loadTrips();
	}


	// =========================================================
	// VEHICLE FILE FUNCTIONS
	// =========================================================

	void saveVehicles()
	{
		ofstream file("vehicles.txt");

		if (!file)
		{
			cout << "\nError: Unable to save Vehicle data.\n";
			return;
		}

		for (int i = 0; i < vehicles.size(); i++)
		{
			file << vehicles[i].getVehicleId() << "|"
				<< vehicles[i].getVehicleNumber() << "|"
				<< vehicles[i].getVehicleType() << "|"
				<< vehicles[i].getVehicleCapacity() << "|"
				<< vehicles[i].getCurrentCity() << "|"
				<< vehicles[i].getVehicleStatus()
				<< endl;
		}

		file.close();
	}


	void loadVehicles()
	{
		ifstream file("vehicles.txt");

		if (!file)
		{
			return;
		}

		string id;
		string number;
		string type;
		string capacityString;
		string city;
		string status;

		while (getline(file, id, '|') &&
			getline(file, number, '|') &&
			getline(file, type, '|') &&
			getline(file, capacityString, '|') &&
			getline(file, city, '|') &&
			getline(file, status))
		{
			double capacity = stod(capacityString);

			// -------------------------------------------------
			// OLD DATA COMPATIBILITY
			// If old capacity was stored in KG, convert to Tons.
			// Example:
			// 500  -> 0.5 Tons
			// 5000 -> 5 Tons
			//
			// New values such as 5, 10, 20 are already Tons.
			// -------------------------------------------------

			if (capacity > 20)
			{
				capacity = capacity / 1000.0;
			}

			// Convert old registration numbers to uppercase
			number = toUpperCase(number);

			Vehicle vehicle(
				id,
				number,
				type,
				capacity,
				city,
				status
			);

			vehicles.push_back(vehicle);
		}

		file.close();
	}


	// =========================================================
	// CITY FILE FUNCTIONS
	// =========================================================

	void saveCities()
	{
		ofstream file("cities.txt");

		if (!file)
		{
			cout << "\nError: Unable to save city data.\n";
			return;
		}

		for (int i = 0; i < cities.size(); i++)
		{
			file << cities[i] << endl;
		}

		file.close();
	}


	void loadCities()
	{
		ifstream file("cities.txt");

		if (!file)
		{
			return;
		}

		cities.clear();

		string city;

		while (getline(file, city))
		{
			if (!city.empty())
			{
				cities.push_back(city);
			}
		}

		file.close();
	}


	// =========================================================
	// ROUTE FILE FUNCTIONS
	// =========================================================

	void saveRoutes()
	{
		ofstream file("routes.txt");

		if (!file)
		{
			cout << "\nError: Unable to save route data.\n";
			return;
		}

		for (int i = 0; i < routes.size(); i++)
		{
			file << routes[i] << endl;
		}

		file.close();
	}


	void loadRoutes()
	{
		ifstream file("routes.txt");

		if (!file)
		{
			return;
		}

		string route;

		while (getline(file, route))
		{
			if (!route.empty())
			{
				routes.push_back(route);
			}
		}

		file.close();
	}


	// =========================================================
	// BOOKING FILE FUNCTIONS
	// =========================================================

	void saveBookings()
	{
		ofstream file("bookings.txt");

		if (!file)
		{
			cout << "\nError: Unable to save booking data.\n";
			return;
		}

		for (int i = 0; i < bookings.size(); i++)
		{
			file << bookings[i] << endl;
		}

		file.close();
	}


	void loadBookings()
	{
		ifstream file("bookings.txt");

		if (!file)
		{
			return;
		}

		string booking;

		while (getline(file, booking))
		{
			if (!booking.empty())
			{
				bookings.push_back(booking);
			}
		}

		file.close();
	}


	// =========================================================
	// TRIP FILE FUNCTIONS
	// =========================================================

	void saveTrips()
	{
		ofstream file("trips.txt");

		if (!file)
		{
			cout << "\nError: Unable to save trip data.\n";
			return;
		}

		for (int i = 0; i < trips.size(); i++)
		{
			file << trips[i] << endl;
		}

		file.close();
	}


	void loadTrips()
	{
		ifstream file("trips.txt");

		if (!file)
		{
			return;
		}

		string trip;

		while (getline(file, trip))
		{
			if (!trip.empty())
			{
				trips.push_back(trip);
			}
		}

		file.close();
	}


	// =========================================================
	// VEHICLE FUNCTIONS
	// =========================================================

	void addVehicle(Vehicle vehicle)
	{
		vehicles.push_back(vehicle);
	}


	void addVehicleFromUser()
	{
		string id;
		string number;
		string type;
		double capacity;
		string city;
		string status;

		// =====================================================
		// AUTOMATIC VEHICLE ID GENERATION
		// =====================================================

		int nextNumber = 1;

		for (int i = 0; i < vehicles.size(); i++)
		{
			string existingId = vehicles[i].getVehicleId();

			if (existingId.length() == 4 && existingId[0] == 'V')
			{
				try
				{
					int numberPart = stoi(existingId.substr(1));

					if (numberPart >= nextNumber)
					{
						nextNumber = numberPart + 1;
					}
				}
				catch (...)
				{
				}
			}
		}

		if (nextNumber <= 999)
		{
			id = "V";

			if (nextNumber < 10)
			{
				id += "00";
			}
			else if (nextNumber < 100)
			{
				id += "0";
			}

			id += to_string(nextNumber);
		}
		else
		{
			cout << "\nError: Vehicle ID limit reached.\n";
			return;
		}

		cout << "\nAutomatically Generated Vehicle ID: "
			<< id << endl;

		cout << endl;


		// =====================================================
		// VEHICLE REGISTRATION NUMBER
		// =====================================================

		cout << "Enter the Vehicle Registration Number: ";
		cin >> number;

		// Convert registration number to uppercase
		number = toUpperCase(number);

		cout << "\nRegistration Number: " << number << endl;
		cout << endl;


		// =====================================================
		// DUPLICATE REGISTRATION NUMBER
		// =====================================================

		for (int i = 0; i < vehicles.size(); i++)
		{
			string existingNumber =
				toUpperCase(vehicles[i].getVehicleNumber());

			if (existingNumber == number)
			{
				cout << "\nError: Vehicle with this Registration Number already exists!\n";
				return;
			}
		}


		// =====================================================
		// VEHICLE TYPE
		// =====================================================

		int typeChoice;

		cout << "Select Vehicle Type:\n";
		cout << "1. Small - 3 Tyre\n";
		cout << "2. Medium - 4/6 Tyre\n";
		cout << "3. Large - 12/14 Tyre\n";

		cout << "\nEnter Your Choice: ";
		cin >> typeChoice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";
			return;
		}

		if (typeChoice == 1)
		{
			type = "Small - 3 Tyre";
		}
		else if (typeChoice == 2)
		{
			type = "Medium - 4/6 Tyre";
		}
		else if (typeChoice == 3)
		{
			type = "Large - 12/14 Tyre";
		}
		else
		{
			cout << "\nInvalid vehicle type choice.\n";
			return;
		}

		cout << "\nSelected Vehicle Type: " << type << endl;
		cout << endl;


		// =====================================================
		// VEHICLE CAPACITY - NOW IN TONS
		// =====================================================

		int capacityChoice;

		cout << "Select Vehicle Capacity:\n";

		if (typeChoice == 1)
		{
			cout << "1. 0.5 Ton\n";
			cout << "2. 1 Ton\n";
		}
		else if (typeChoice == 2)
		{
			cout << "1. 1 Ton\n";
			cout << "2. 2 Tons\n";
			cout << "3. 3 Tons\n";
			cout << "4. 4 Tons\n";
			cout << "5. 5 Tons\n";
			cout << "6. 6 Tons\n";
		}
		else if (typeChoice == 3)
		{
			cout << "1. 6 Tons\n";
			cout << "2. 8 Tons\n";
			cout << "3. 10 Tons\n";
			cout << "4. 12 Tons\n";
			cout << "5. 15 Tons\n";
			cout << "6. 20 Tons\n";
		}

		cout << "\nEnter Your Choice: ";
		cin >> capacityChoice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";
			return;
		}


		if (typeChoice == 1)
		{
			if (capacityChoice == 1)
				capacity = 0.5;
			else if (capacityChoice == 2)
				capacity = 1.0;
			else
			{
				cout << "\nInvalid capacity choice.\n";
				return;
			}
		}
		else if (typeChoice == 2)
		{
			if (capacityChoice >= 1 && capacityChoice <= 6)
			{
				capacity = capacityChoice;
			}
			else
			{
				cout << "\nInvalid capacity choice.\n";
				return;
			}
		}
		else if (typeChoice == 3)
		{
			if (capacityChoice == 1)
				capacity = 6;
			else if (capacityChoice == 2)
				capacity = 8;
			else if (capacityChoice == 3)
				capacity = 10;
			else if (capacityChoice == 4)
				capacity = 12;
			else if (capacityChoice == 5)
				capacity = 15;
			else if (capacityChoice == 6)
				capacity = 20;
			else
			{
				cout << "\nInvalid capacity choice.\n";
				return;
			}
		}

		cout << "\nSelected Capacity: "
			<< capacity << " Ton(s)\n";

		cout << endl;


		// =====================================================
		// CURRENT CITY
		// =====================================================

		int cityChoice;

		if (cities.empty())
		{
			cout << "\nNo cities are available. Please add a city first.\n";
			return;
		}

		cout << "Select Current City:\n";

		for (int i = 0; i < cities.size(); i++)
		{
			cout << i + 1 << ". " << cities[i] << endl;
		}

		cout << "\nEnter Your Choice: ";
		cin >> cityChoice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";
			return;
		}

		if (cityChoice < 1 || cityChoice > cities.size())
		{
			cout << "\nInvalid city choice.\n";
			return;
		}

		city = cities[cityChoice - 1];

		cout << "\nSelected Current City: "
			<< city << endl;

		cout << endl;


		// =====================================================
		// VEHICLE STATUS
		// =====================================================

		status = "Available";


		// =====================================================
		// CREATE VEHICLE
		// =====================================================

		Vehicle vehicle(
			id,
			number,
			type,
			capacity,
			city,
			status
		);

		vehicles.push_back(vehicle);

		saveVehicles();


		// =====================================================
		// SUCCESS MESSAGE
		// =====================================================

		cout << "\n=================================================\n";
		cout << "             VEHICLE DETAILS\n";
		cout << "=================================================\n";

		vehicle.displayVehicle();

		cout << "=================================================\n";
		cout << "          VEHICLE ADDED SUCCESSFULLY!\n";
		cout << "=================================================\n";
	}


	// =========================================================
	// VIEW VEHICLES
	// =========================================================

	void viewVehicles()
	{
		if (vehicles.empty())
		{
			cout << "\nNo Vehicles Available.\n";
			return;
		}

		cout << "\n=============================================\n";
		cout << "                VEHICLE LIST\n";
		cout << "=============================================\n";

		for (int i = 0; i < vehicles.size(); i++)
		{
			cout << "Vehicle ID               : "
				<< vehicles[i].getVehicleId() << endl;

			cout << "Vehicle Number           : "
				<< vehicles[i].getVehicleNumber() << endl;

			cout << "Type of Vehicle          : "
				<< vehicles[i].getVehicleType() << endl;

			cout << "Capacity of the Vehicle  : "
				<< vehicles[i].getVehicleCapacity()
				<< " Ton(s)" << endl;

			cout << "Current city             : "
				<< vehicles[i].getCurrentCity() << endl;

			cout << "Vehicle Status           : "
				<< getCurrentVehicleStatus(
					vehicles[i].getVehicleId())
				<< endl;

			cout << "---------------------------------------------\n";
		}
	}


	// =========================================================
	// SEARCH VEHICLE
	// =========================================================

	void searchVehicle()
	{
		string id;

		cout << "\nEnter Vehicle ID to search: ";
		cin >> id;

		for (int i = 0; i < vehicles.size(); i++)
		{
			if (vehicles[i].getVehicleId() == id)
			{
				cout << "\nVehicle Found!\n";

				cout << "------------------------------------------------\n";

				vehicles[i].displayVehicle();

				cout << "------------------------------------------------\n";

				return;
			}
		}

		cout << "\nVehicle not found.\n";
	}


	// =========================================================
	// UPDATE VEHICLE
	// =========================================================

	void updateVehicle(string id)
	{
		for (int i = 0; i < vehicles.size(); i++)
		{
			if (vehicles[i].getVehicleId() == id)
			{
				cout << "\nCurrent Vehicle Details\n";
				cout << "------------------------------------------------\n";

				vehicles[i].displayVehicle();

				cout << "------------------------------------------------\n";

				int choice;

				cout << "\nWhat do you want to update?\n";
				cout << "1. Registration Number\n";
				cout << "2. Vehicle Type\n";
				cout << "3. Capacity\n";
				cout << "4. Current City\n";
				cout << "5. Vehicle Status\n";
				cout << "6. Cancel\n";

				cout << "\nEnter your Choice: ";
				cin >> choice;

				switch (choice)
				{
				case 1:
				{
					string number;

					cout << "\nEnter New Registration Number: ";
					cin >> number;

					// Convert to uppercase
					number = toUpperCase(number);

					// Check duplicate registration number
					for (int j = 0; j < vehicles.size(); j++)
					{
						if (j != i)
						{
							string existingNumber =
								toUpperCase(
									vehicles[j].getVehicleNumber());

							if (existingNumber == number)
							{
								cout << "\nError: Registration Number already exists!\n";
								return;
							}
						}
					}

					vehicles[i].setvehicleNumber(number);

					saveVehicles();

					cout << "\nRegistration Number updated successfully!\n";
					cout << "New Registration Number: "
						<< number << endl;

					break;
				}


				case 2:
				{
					string type;

					cout << "\nEnter New Vehicle Type: ";
					cin.ignore();
					getline(cin, type);

					vehicles[i].setvehicleType(type);

					saveVehicles();

					cout << "\nVehicle Type updated successfully!\n";

					break;
				}


				case 3:
				{
					double capacity;

					cout << "\nEnter New Capacity (in Tons): ";
					cin >> capacity;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');

						cout << "\nInvalid input! Please enter a number.\n";
						break;
					}

					if (capacity <= 0)
					{
						cout << "\nCapacity must be greater than 0.\n";
						break;
					}

					vehicles[i].setvehicleCapacity(capacity);

					saveVehicles();

					cout << "\nVehicle Capacity updated successfully!\n";
					cout << "New Capacity: "
						<< capacity << " Ton(s)\n";

					break;
				}


				case 4:
				{
					string city;

					cout << "\nEnter New Current City: ";
					cin >> city;

					vehicles[i].setcurrentCity(city);

					saveVehicles();

					cout << "\nCurrent City updated successfully!\n";

					break;
				}


				case 5:
				{
					string status;

					cout << "\nEnter New Vehicle Status: ";

					cin.ignore();
					getline(cin, status);

					vehicles[i].setvehicleStatus(status);

					saveVehicles();

					cout << "\nVehicle Status updated successfully!\n";

					break;
				}


				case 6:
				{
					cout << "\nUpdate cancelled.\n";

					break;
				}


				default:
				{
					cout << "\nInvalid choice!\n";
				}
				}

				return;
			}
		}

		cout << "\nVehicle not found!!\n";
	}


	// =========================================================
	// REMOVE VEHICLE - SELECT BY NUMBER
	// =========================================================

	void removeVehicle(int vehicleIndex)
	{
		if (vehicleIndex < 0 ||
			vehicleIndex >= vehicles.size())
		{
			cout << "\nInvalid vehicle selection.\n";
			return;
		}

		cout << "\n=================================================\n";
		cout << "             SELECTED VEHICLE\n";
		cout << "=================================================\n";

		vehicles[vehicleIndex].displayVehicle();

		cout << "=================================================\n";


		// -------------------------------------------------
		// CHECK WHETHER VEHICLE IS BOOKED
		// -------------------------------------------------

		string vehicleId =
			vehicles[vehicleIndex].getVehicleId();

		if (isVehicleBooked(vehicleId))
		{
			cout << "\nCannot delete this vehicle!\n";
			cout << "The vehicle is currently booked.\n";
			return;
		}


		// -------------------------------------------------
		// CHECK WHETHER VEHICLE IS ON TRIP
		// -------------------------------------------------

		if (isVehicleOnTrip(vehicleId))
		{
			cout << "\nCannot delete this vehicle!\n";
			cout << "The vehicle is currently on a trip.\n";
			return;
		}


		// -------------------------------------------------
		// CONFIRM DELETE
		// -------------------------------------------------

		int choice;

		cout << "\nAre you sure you want to delete this vehicle?\n";
		cout << "1. Yes\n";
		cout << "2. No\n";

		cout << "\nEnter your choice: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";
			return;
		}


		if (choice == 1)
		{
			vehicles.erase(
				vehicles.begin() + vehicleIndex);

			saveVehicles();

			cout << "\nVehicle deleted successfully!!\n";
		}
		else if (choice == 2)
		{
			cout << "\nDelete cancelled.\n";
		}
		else
		{
			cout << "\nInvalid choice!\n";
		}
	}

	//=======================================================
	// generating automatic routes by using added cities
	//=======================================================

	void generateRoutesForNewCity(string newCity)
	{
		for (int i = 0; i < cities.size(); i++)
		{
			string existingCity = cities[i];

			if (existingCity == newCity)
			{
				continue;
			}

			// Route: Existing City -> New City
			string route1 = existingCity + " -> " + newCity;

			bool route1Exists = false;

			for (int j = 0; j < routes.size(); j++)
			{
				if (routes[j] == route1)
				{
					route1Exists = true;
					break;
				}
			}

			if (!route1Exists)
			{
				routes.push_back(route1);
			}

			// Route: New City -> Existing City
			string route2 = newCity + " -> " + existingCity;

			bool route2Exists = false;

			for (int j = 0; j < routes.size(); j++)
			{
				if (routes[j] == route2)
				{
					route2Exists = true;
					break;
				}
			}

			if (!route2Exists)
			{
				routes.push_back(route2);
			}
		}

		saveRoutes();
	}
	// =========================================================
	// CITY FUNCTIONS
	// =========================================================

	void addCity(string cityname)
	{
		// Check for empty city name
		if (cityname.empty())
		{
			cout << "\nError: City name cannot be empty!\n";
			return;
		}

		// Check every character
		for (int i = 0; i < cityname.length(); i++)
		{
			if (!isalpha(cityname[i]) && cityname[i] != ' ')
			{
				cout << "\nError: Invalid city name!\n";
				cout << "Only alphabets and spaces are allowed.\n";
				return;
			}
		}

		// Check duplicate city
		if (cityExists(cityname))
		{
			cout << "\nError: City already exists!\n";
			return;
		}

		cities.push_back(cityname);

		saveCities();

		generateRoutesForNewCity(cityname);

		cout << "\nCity added successfully.\n";
	}


	void viewCities()
	{
		if (cities.empty())
		{
			cout << "\nNo cities available.\n";
			return;
		}

		cout << "\n========== AVAILABLE CITIES ==========\n";

		for (int i = 0; i < cities.size(); i++)
		{
			cout << i + 1 << ". " << cities[i] << endl;
		}

		cout << "======================================\n";
	}


	bool cityExists(string city)
	{
		for (int i = 0; i < cities.size(); i++)
		{
			if (cities[i] == city)
			{
				return true;
			}
		}

		return false;
	}


	void deleteCity()
	{
		if (cities.empty())
		{
			cout << "\nNo cities available to delete.\n";
			return;
		}

		cout << "\n========== AVAILABLE CITIES ==========\n";

		for (int i = 0; i < cities.size(); i++)
		{
			cout << i + 1 << ". " << cities[i] << endl;
		}

		cout << "======================================\n";

		int choice;

		cout << "\nSelect City to Delete: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";
			return;
		}

		if (choice < 1 || choice > cities.size())
		{
			cout << "\nInvalid city choice.\n";
			return;
		}

		string cityName = cities[choice - 1];

		cout << "\nSelected City: "
			<< cityName << endl;

		int confirm;

		cout << "\nAre you sure you want to delete this city?\n";
		cout << "1. Yes\n";
		cout << "2. No\n";

		cout << "\nEnter your choice: ";
		cin >> confirm;

		if (confirm == 1)
		{
			// Check active bookings
			for (int i = 0; i < bookings.size(); i++)
			{
				if (bookings[i].find(" | Route: " + cityName + " -> ") != string::npos ||
					bookings[i].find(" | Route: ") != string::npos &&
					bookings[i].find(" -> " + cityName) != string::npos)
				{
					cout << "\nCannot delete this city!\n";
					cout << "The city is currently being used in a booking.\n";
					return;
				}
			}

			// Check scheduled trips
			for (int i = 0; i < trips.size(); i++)
			{
				if (trips[i].find(" | Route: " + cityName + " -> ") != string::npos ||
					trips[i].find(" | Route: ") != string::npos &&
					trips[i].find(" -> " + cityName) != string::npos)
				{
					cout << "\nCannot delete this city!\n";
					cout << "The city is currently being used in a scheduled trip.\n";
					return;
				}
			}

			// Remove all routes related to this city
			for (int i = routes.size() - 1; i >= 0; i--)
			{
				if (routes[i].find(cityName + " -> ") == 0 ||
					routes[i].find(" -> " + cityName) != string::npos)
				{
					routes.erase(routes.begin() + i);
				}
			}

			// Delete city
			cities.erase(
				cities.begin() + (choice - 1));

			saveCities();
			saveRoutes();

			cout << "\nCity deleted successfully!\n";
			cout << "All routes related to " << cityName
				<< " were also removed.\n";
		}
		else if (confirm == 2)
		{
			cout << "\nDelete cancelled.\n";
		}
		else
		{
			cout << "\nInvalid choice.\n";
		}
	}


	// =========================================================
	// ROUTE FUNCTIONS
	// =========================================================

	bool routeExists(string route)
	{
		for (int i = 0; i < routes.size(); i++)
		{
			if (routes[i] == route)
			{
				return true;
			}
		}

		return false;
	}

	void generateAllRoutes()
	{
		routes.clear();

		for (int i = 0; i < cities.size(); i++)
		{
			for (int j = 0; j < cities.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				string route =
					cities[i] + " -> " + cities[j];

				routes.push_back(route);
			}
		}

		saveRoutes();
	}

	void addRoute()
	{
		int sourceChoice;
		int destinationChoice;

		cout << "\n========== AVAILABLE CITIES ==========\n";

		for (int i = 0; i < cities.size(); i++)
		{
			cout << i + 1 << ". " << cities[i] << endl;
		}

		cout << "======================================\n";

		cout << "\nEnter the option of the Source city: ";
		cin >> sourceChoice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";
			return;
		}

		if (sourceChoice < 1 ||
			sourceChoice > cities.size())
		{
			cout << "\nInvalid source city choice.\n";
			return;
		}

		cout << "\nEnter the option of the Destination city: ";
		cin >> destinationChoice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";
			return;
		}

		if (destinationChoice < 1 ||
			destinationChoice > cities.size())
		{
			cout << "\nInvalid destination city choice.\n";
			return;
		}

		string source =
			cities[sourceChoice - 1];

		string destination =
			cities[destinationChoice - 1];

		string route =
			source + " -> " + destination;

		if (routeExists(route))
		{
			cout << "\nRoute already exists.\n";
			return;
		}

		routes.push_back(route);

		saveRoutes();

		cout << "\nRoute added Successfully.\n";
	}


	void viewRoutes()
	{
		if (routes.empty())
		{
			cout << "\nNo routes available.\n";
			return;
		}

		cout << "\n=============== AVAILABLE ROUTES ================\n";

		for (int i = 0; i < routes.size(); i++)
		{
			cout << i + 1 << ". "
				<< routes[i] << endl;
		}
	}


	// =========================================================
	// BOOKING VEHICLE FUNCTIONS
	// =========================================================

	bool isVehicleBooked(string vehicleId)
	{
		string searchText =
			" | Vehicle: " + vehicleId + " |";

		for (int i = 0; i < bookings.size(); i++)
		{
			if (bookings[i].find(searchText) != string::npos)
			{
				return true;
			}
		}

		return false;
	}


	void showVehicleOptions()
	{
		if (vehicles.empty())
		{
			cout << "\nNo vehicles available.\n";
			return;
		}

		cout << "\n========== AVAILABLE VEHICLES ==========\n";

		for (int i = 0; i < vehicles.size(); i++)
		{
			cout << i + 1 << ". "
				<< "ID: " << vehicles[i].getVehicleId()
				<< " | Number: " << vehicles[i].getVehicleNumber()
				<< " | Type: " << vehicles[i].getVehicleType()
				<< " | Capacity: "
				<< vehicles[i].getVehicleCapacity()
				<< " Ton(s)"
				<< endl;
		}

		cout << "========================================\n";
	}


	void selectVehicle(int& vehicleIndex)
	{
		int choice;

		int availableCount = 0;

		cout << "\n========== AVAILABLE VEHICLES ==========\n";

		for (int i = 0; i < vehicles.size(); i++)
		{
			string vehicleId =
				vehicles[i].getVehicleId();

			if (getCurrentVehicleStatus(vehicleId)
				== "Available")
			{
				availableCount++;

				cout << "\n" << availableCount << ".\n";
				cout << "   Vehicle ID     : " << vehicleId << endl;
				cout << "   Vehicle Number : " << vehicles[i].getVehicleNumber() << endl;
				cout << "   Vehicle Type   : " << vehicles[i].getVehicleType() << endl;
				cout << "   Capacity       : " << vehicles[i].getVehicleCapacity() << " Ton(s)" << endl;
				cout << "   Current City   : " << vehicles[i].getCurrentCity() << endl;
				cout << "---------------------------------------------\n";
			}
		}

		cout << "========================================\n";

		if (availableCount == 0)
		{
			cout << "\nNo vehicles available for booking.\n";

			vehicleIndex = -1;

			return;
		}

		cout << "\nSelect Vehicle: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";

			vehicleIndex = -1;

			return;
		}

		if (choice < 1 ||
			choice > availableCount)
		{
			cout << "\nInvalid vehicle choice.\n";

			vehicleIndex = -1;

			return;
		}

		int currentChoice = 0;

		for (int i = 0; i < vehicles.size(); i++)
		{
			string vehicleId =
				vehicles[i].getVehicleId();

			if (getCurrentVehicleStatus(vehicleId)
				== "Available")
			{
				currentChoice++;

				if (currentChoice == choice)
				{
					vehicleIndex = i;

					return;
				}
			}
		}

		vehicleIndex = -1;
	}


	// =========================================================
	// BOOKING ROUTE SELECTION
	// =========================================================

	void selectRoute(string& selectedRoute, string vehicleCurrentCity)
	{
		selectedRoute = "";

		if (routes.empty())
		{
			cout << "\nNo routes available.\n";
			return;
		}

		int routeCount = 0;

		cout << "\n=================================================\n";
		cout << "       AVAILABLE ROUTES FROM "
			<< vehicleCurrentCity << endl;
		cout << "=================================================\n";

		for (int i = 0; i < routes.size(); i++)
		{
			string sourceText = vehicleCurrentCity + " -> ";

			if (routes[i].find(sourceText) == 0)
			{
				routeCount++;

				cout << routeCount << ". "
					<< routes[i] << endl;
			}
		}

		cout << "=================================================\n";

		if (routeCount == 0)
		{
			cout << "\nNo routes are available from "
				<< vehicleCurrentCity << ".\n";

			return;
		}

		int choice;

		cout << "\nSelect Route: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";

			return;
		}

		if (choice < 1 || choice > routeCount)
		{
			cout << "\nInvalid route choice.\n";
			return;
		}

		int currentChoice = 0;

		for (int i = 0; i < routes.size(); i++)
		{
			string sourceText = vehicleCurrentCity + " -> ";

			if (routes[i].find(sourceText) == 0)
			{
				currentChoice++;

				if (currentChoice == choice)
				{
					selectedRoute = routes[i];
					return;
				}
			}
		}
	}


	// =========================================================
	// BOOKING FUNCTIONS
	// =========================================================

	bool bookingExists(string bookingId)
	{
		string searchText =
			"Booking ID: " + bookingId + " |";

		for (int i = 0; i < bookings.size(); i++)
		{
			if (bookings[i].find(searchText) == 0)
			{
				return true;
			}
		}

		return false;
	}


	void addBooking()
	{
		string bookingId;
		string customerName;
		string route;

		// =====================================================
		// AUTOMATIC BOOKING ID GENERATION
		// =====================================================

		int nextNumber = 1;

		// Check existing Booking IDs
		for (int i = 0; i < bookings.size(); i++)
		{
			string existingId = getBookingId(bookings[i]);

			if (existingId.length() == 4 &&
				existingId[0] == 'B')
			{
				try
				{
					int numberPart =
						stoi(existingId.substr(1));

					if (numberPart >= nextNumber)
					{
						nextNumber = numberPart + 1;
					}
				}
				catch (...)
				{
				}
			}
		}

		// Check Booking IDs already used in scheduled Trips
		for (int i = 0; i < trips.size(); i++)
		{
			string existingBookingId = getBookingId(trips[i]);

			if (existingBookingId.length() == 4 &&
				existingBookingId[0] == 'B')
			{
				try
				{
					int numberPart =
						stoi(existingBookingId.substr(1));

					if (numberPart >= nextNumber)
					{
						nextNumber = numberPart + 1;
					}
				}
				catch (...)
				{
				}
			}
		}

		if (nextNumber <= 999)
		{
			bookingId = "B";

			if (nextNumber < 10)
			{
				bookingId += "00";
			}
			else if (nextNumber < 100)
			{
				bookingId += "0";
			}

			bookingId += to_string(nextNumber);
		}
		else
		{
			cout << "\nError: Booking ID limit reached.\n";
			return;
		}

		cout << "\nAutomatically Generated Booking ID: "
			<< bookingId << endl;

		int vehicleIndex;

		selectVehicle(vehicleIndex);

		if (vehicleIndex == -1)
		{
			return;
		}

		string vehicleId =
			vehicles[vehicleIndex].getVehicleId();

		string vehicleCurrentCity =
			vehicles[vehicleIndex].getCurrentCity();

		cout << "\nSelected Vehicle ID: "
			<< vehicleId << endl;

		cout << "\nEnter Customer Name: ";
		cin.ignore();
		getline(cin, customerName);

		selectRoute(route, vehicleCurrentCity);

		if (route == "")
		{
			return;
		}

		string booking =
			"Booking ID: " + bookingId +
			" | Vehicle: " + vehicleId +
			" | Customer: " + customerName +
			" | Route: " + route;

		bookings.push_back(booking);

		saveBookings();

		cout << "\nBooking Added Successfully.\n";
	}


	void viewBookings()
	{
		if (bookings.empty())
		{
			cout << "\nNo Bookings Available.\n";

			return;
		}

		cout << "\n================== BOOKINGS =================\n";

		for (int i = 0; i < bookings.size(); i++)
		{
			cout << i + 1 << ". "
				<< bookings[i] << endl;
		}
	}


	// =========================================================
	// TRIP FUNCTIONS
	// =========================================================

	bool tripIdExists(string tripId)
	{
		string searchText =
			"Trip ID: " + tripId + " |";

		for (int i = 0; i < trips.size(); i++)
		{
			if (trips[i].find(searchText)
				!= string::npos)
			{
				return true;
			}
		}

		return false;
	}


	string getBookingId(string booking)

	{
		string startText = "Booking ID: ";

		int start =
			booking.find(startText);

		if (start == string::npos)
		{
			return "";
		}

		start =
			start + startText.length();

		int end =
			booking.find(" |", start);

		if (end == string::npos)
		{
			return "";
		}

		return booking.substr(
			start,
			end - start);
	}

	string getTripId(string trip)
	{
		string startText = "Trip ID: ";

		int start = trip.find(startText);

		if (start == string::npos)
		{
			return "";
		}

		start = start + startText.length();

		int end = trip.find(" |", start);

		if (end == string::npos)
		{
			return "";
		}

		return trip.substr(start, end - start);
	}

	bool bookingAlreadyScheduled(string bookingId)
	{
		string searchText =
			"Booking ID: " + bookingId + " |";

		for (int i = 0; i < trips.size(); i++)
		{
			if (trips[i].find(searchText) != string::npos)
			{
				return true;
			}
		}

		return false;
	}


	// =========================================================
	// SCHEDULE TRIP
	// =========================================================

	void scheduleTrip()
	{
		if (bookings.empty())
		{
			cout << "\nNo bookings available to schedule.\n";

			return;
		}

		cout << "\n========== AVAILABLE BOOKINGS ==========\n";

		int availableCount = 0;

		for (int i = 0; i < bookings.size(); i++)
		{
			string bookingId =
				getBookingId(bookings[i]);

			if (!bookingAlreadyScheduled(bookingId))
			{
				availableCount++;

				cout << availableCount << ". "
					<< bookings[i] << endl;
			}
		}

		cout << "========================================\n";

		if (availableCount == 0)
		{
			cout << "\nAll bookings have already been scheduled.\n";

			return;
		}

		int bookingChoice;

		cout << "\nSelect Booking: ";
		cin >> bookingChoice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "\nInvalid input! Please enter a number.\n";

			return;
		}

		if (bookingChoice < 1 ||
			bookingChoice > availableCount)
		{
			cout << "\nInvalid booking choice.\n";

			return;
		}

		int currentChoice = 0;

		string selectedBooking;

		for (int i = 0; i < bookings.size(); i++)
		{
			string bookingId =
				getBookingId(bookings[i]);

			if (!bookingAlreadyScheduled(bookingId))
			{
				currentChoice++;

				if (currentChoice == bookingChoice)
				{
					selectedBooking =
						bookings[i];

					break;
				}
			}
		}

		cout << "\nSelected Booking:\n";
		cout << selectedBooking << endl;

		string tripId;
		string date;
		string time;

		// Automatically generate Trip ID
		int nextNumber = 1;

		for (int i = 0; i < trips.size(); i++)
		{
			string existingId = getTripId(trips[i]);

			if (existingId.length() == 4 &&
				existingId[0] == 'T')
			{
				try
				{
					int numberPart =
						stoi(existingId.substr(1));

					if (numberPart >= nextNumber)
					{
						nextNumber = numberPart + 1;
					}
				}
				catch (...)
				{
				}
			}
		}

		if (nextNumber <= 999)
		{
			tripId = "T";

			if (nextNumber < 10)
			{
				tripId += "00";
			}
			else if (nextNumber < 100)
			{
				tripId += "0";
			}

			tripId += to_string(nextNumber);
		}
		else
		{
			cout << "\nError: Trip ID limit reached.\n";
			return;
		}

		cout << "\nAutomatically Generated Trip ID: "
			<< tripId << endl;

		cout << "\nEnter Date (DD-MM-YYYY): ";
		cin >> date;

		cout << "\nEnter Time (HH:MM): ";
		cin >> time;

		string trip =
			"Trip ID: " + tripId +
			" | Booking: " + selectedBooking +
			" | Date: " + date +
			" | Time: " + time;

		trips.push_back(trip);

		saveTrips();


		// Remove scheduled booking
		for (int i = 0; i < bookings.size(); i++)
		{
			if (bookings[i] == selectedBooking)
			{
				bookings.erase(
					bookings.begin() + i);

				break;
			}
		}

		saveBookings();

		cout << "\nTrip Scheduled Successfully!\n";
	}


	// =========================================================
	// VIEW TRIPS
	// =========================================================

	void viewTrips()
	{
		if (trips.empty())
		{
			cout << "\nNo Trips Scheduled.\n";

			return;
		}

		cout << "\n================ SCHEDULED TRIPS ================\n";

		for (int i = 0; i < trips.size(); i++)
		{
			cout << i + 1 << ". "
				<< trips[i] << endl;
		}
	}


	// =========================================================
	// DELETE MENU
	// =========================================================

	void deleteMenu()
	{
		int choice;

		do
		{
			cout << "\n=================================================\n";
			cout << "                  DELETE MENU\n";
			cout << "=================================================\n";

			cout << "1. Delete Vehicle\n";
			cout << "2. Delete City\n";
			cout << "3. Delete Route\n";
			cout << "4. Delete Booking\n";
			cout << "5. Delete Scheduled Trip\n";
			cout << "6. Back to Main Menu\n";

			cout << "=================================================\n";

			cout << "\nEnter Your Choice: ";
			cin >> choice;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');

				cout << "\nInvalid input! Please enter a number.\n";
				continue;
			}


			switch (choice)
			{

				// =================================================
				// DELETE VEHICLE
				// =================================================

			case 1:
			{
				if (vehicles.empty())
				{
					cout << "\nNo vehicles available to delete.\n";
					break;
				}

				// ---------------------------------------------
				// SHOW COMPLETE DETAILS FIRST
				// ---------------------------------------------

				cout << "\n=================================================\n";
				cout << "              AVAILABLE VEHICLES\n";
				cout << "=================================================\n";

				for (int i = 0; i < vehicles.size(); i++)
				{
					cout << "\n"
						<< i + 1 << ".\n";

					cout << "   Vehicle ID      : "
						<< vehicles[i].getVehicleId()
						<< endl;

					cout << "   Vehicle Number  : "
						<< vehicles[i].getVehicleNumber()
						<< endl;

					cout << "   Vehicle Type    : "
						<< vehicles[i].getVehicleType()
						<< endl;

					cout << "   Capacity        : "
						<< vehicles[i].getVehicleCapacity()
						<< " Ton(s)"
						<< endl;

					cout << "   Current City    : "
						<< vehicles[i].getCurrentCity()
						<< endl;

					cout << "   Vehicle Status  : "
						<< getCurrentVehicleStatus(
							vehicles[i].getVehicleId())
						<< endl;

					cout << "-------------------------------------------------\n";
				}

				// ---------------------------------------------
				// SELECT VEHICLE
				// ---------------------------------------------

				int vehicleChoice;

				cout << "\nSelect Vehicle to Delete: ";
				cin >> vehicleChoice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (vehicleChoice < 1 ||
					vehicleChoice > vehicles.size())
				{
					cout << "\nInvalid vehicle choice.\n";
					break;
				}

				// Convert choice to vector index
				int vehicleIndex =
					vehicleChoice - 1;

				removeVehicle(vehicleIndex);

				break;
			}


			// =================================================
			// DELETE CITY
			// =================================================

			case 2:
			{
				deleteCity();

				break;
			}


			// =================================================
			// DELETE ROUTE
			// =================================================

			case 3:
			{
				if (routes.empty())
				{
					cout << "\nNo routes available to delete.\n";
					break;
				}

				cout << "\n========== AVAILABLE ROUTES ==========\n";

				for (int i = 0; i < routes.size(); i++)
				{
					cout << i + 1 << ". "
						<< routes[i] << endl;
				}

				cout << "======================================\n";

				int routeChoice;

				cout << "\nSelect Route to Delete: ";
				cin >> routeChoice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (routeChoice < 1 ||
					routeChoice > routes.size())
				{
					cout << "\nInvalid route choice.\n";
					break;
				}

				string routeName =
					routes[routeChoice - 1];

				cout << "\nSelected Route: "
					<< routeName << endl;

				int confirm;

				cout << "\nAre you sure you want to delete this route?\n";
				cout << "1. Yes\n";
				cout << "2. No\n";

				cout << "\nEnter your choice: ";
				cin >> confirm;

				if (confirm == 1)
				{
					bool routeInUse = false;

					for (int i = 0; i < bookings.size(); i++)
					{
						if (bookings[i].find(
							" | Route: " + routeName)
							!= string::npos)
						{
							routeInUse = true;
							break;
						}
					}

					if (routeInUse)
					{
						cout << "\nCannot delete this route!\n";
						cout << "The route is currently being used in a booking.\n";
						break;
					}

					routes.erase(
						routes.begin() + (routeChoice - 1));

					saveRoutes();

					cout << "\nRoute deleted successfully!\n";
				}
				else if (confirm == 2)
				{
					cout << "\nDelete cancelled.\n";
				}
				else
				{
					cout << "\nInvalid choice.\n";
				}

				break;
			}


			// =================================================
			// DELETE BOOKING
			// =================================================

			case 4:
			{
				if (bookings.empty())
				{
					cout << "\nNo bookings available to delete.\n";
					break;
				}

				cout << "\n========== AVAILABLE BOOKINGS ==========\n";

				for (int i = 0; i < bookings.size(); i++)
				{
					cout << i + 1 << ". "
						<< bookings[i] << endl;
				}

				cout << "========================================\n";

				int bookingChoice;

				cout << "\nSelect Booking to Delete: ";
				cin >> bookingChoice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (bookingChoice < 1 ||
					bookingChoice > bookings.size())
				{
					cout << "\nInvalid booking choice.\n";
					break;
				}

				string bookingName =
					bookings[bookingChoice - 1];

				cout << "\nSelected Booking:\n";
				cout << bookingName << endl;

				int confirm;

				cout << "\nAre you sure you want to delete this booking?\n";
				cout << "1. Yes\n";
				cout << "2. No\n";

				cout << "\nEnter your choice: ";
				cin >> confirm;

				if (confirm == 1)
				{
					bookings.erase(
						bookings.begin() +
						(bookingChoice - 1));

					saveBookings();

					cout << "\nBooking deleted successfully!\n";
				}
				else if (confirm == 2)
				{
					cout << "\nDelete cancelled.\n";
				}
				else
				{
					cout << "\nInvalid choice.\n";
				}

				break;
			}


			// =================================================
			// DELETE SCHEDULED TRIP
			// =================================================

			case 5:
			{
				if (trips.empty())
				{
					cout << "\nNo scheduled trips available to delete.\n";
					break;
				}

				cout << "\n========== SCHEDULED TRIPS ==========\n";

				for (int i = 0; i < trips.size(); i++)
				{
					cout << i + 1 << ". "
						<< trips[i] << endl;
				}

				cout << "=====================================\n";

				int tripChoice;

				cout << "\nSelect Trip to Delete: ";
				cin >> tripChoice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (tripChoice < 1 ||
					tripChoice > trips.size())
				{
					cout << "\nInvalid trip choice.\n";
					break;
				}

				string selectedTrip =
					trips[tripChoice - 1];

				cout << "\nSelected Trip:\n";
				cout << selectedTrip << endl;

				int confirm;

				cout << "\nAre you sure you want to delete this scheduled trip?\n";
				cout << "1. Yes\n";
				cout << "2. No\n";

				cout << "\nEnter your choice: ";
				cin >> confirm;

				if (confirm == 1)
				{
					// Extract original booking
					int bookingStart =
						selectedTrip.find("Booking: ");

					if (bookingStart != string::npos)
					{
						bookingStart += 9;

						int bookingEnd =
							selectedTrip.find(
								" | Date:",
								bookingStart);

						if (bookingEnd != string::npos)
						{
							string originalBooking =
								selectedTrip.substr(
									bookingStart,
									bookingEnd -
									bookingStart);

							bookings.push_back(
								originalBooking);

							saveBookings();
						}
					}

					trips.erase(
						trips.begin() +
						(tripChoice - 1));

					saveTrips();

					cout << "\nScheduled trip deleted successfully!\n";
					cout << "The original booking has been restored.\n";
				}
				else if (confirm == 2)
				{
					cout << "\nDelete cancelled.\n";
				}
				else
				{
					cout << "\nInvalid choice.\n";
				}

				break;
			}


			// =================================================
			// BACK TO MAIN MENU
			// =================================================

			case 6:
			{
				cout << "\nReturning to Main Menu...\n";

				break;
			}


			default:
			{
				cout << "\nInvalid Choice! Please try again.\n";
			}

			}

		} while (choice != 6);
	}


	// =========================================================
	// VEHICLE SERVICE MENU
	// =========================================================

	void vehicleServiceMenu()
	{
		int choice;

		do
		{
			cout << "\n";
			cout << "=================================================\n";
			cout << "             VEHICLE SERVICE MENU\n";
			cout << "=================================================\n";
			cout << "  1. Send Vehicle for Maintenance\n";
			cout << "  2. Send Vehicle for Servicing\n";
			cout << "  3. Mark Maintenance Completed\n";
			cout << "  4. Mark Servicing Completed\n";
			cout << "  5. Back\n";
			cout << "=================================================\n";

			cout << "\nEnter Your Choice: ";
			cin >> choice;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');

				cout << "\nInvalid input! Please enter a number.\n";

				continue;
			}

			switch (choice)
			{

			case 1:
			{
				int choice;
				int count = 0;

				cout << "\n=================================================\n";
				cout << "          AVAILABLE VEHICLES\n";
				cout << "=================================================\n";

				for (int i = 0; i < vehicles.size(); i++)
				{
					string vehicleId = vehicles[i].getVehicleId();

					// Show only vehicles that are currently Available
					if (getCurrentVehicleStatus(vehicleId) == "Available")
					{
						count++;

						cout << "\n" << count << ".\n";
						cout << "   Vehicle ID     : " << vehicleId << endl;
						cout << "   Vehicle Number : " << vehicles[i].getVehicleNumber() << endl;
						cout << "   Vehicle Type   : " << vehicles[i].getVehicleType() << endl;
						cout << "   Capacity       : " << vehicles[i].getVehicleCapacity() << " Tons" << endl;
						cout << "   Current City   : " << vehicles[i].getCurrentCity() << endl;
						cout << "   Status         : Available" << endl;
						cout << "---------------------------------------------\n";
					}
				}

				cout << "=================================================\n";

				if (count == 0)
				{
					cout << "\nNo vehicles are currently available for maintenance.\n";
					break;
				}

				cout << "\nSelect Vehicle to Send for Maintenance: ";
				cin >> choice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (choice < 1 || choice > count)
				{
					cout << "\nInvalid vehicle choice.\n";
					break;
				}

				int currentChoice = 0;

				for (int i = 0; i < vehicles.size(); i++)
				{
					string vehicleId = vehicles[i].getVehicleId();

					if (getCurrentVehicleStatus(vehicleId) == "Available")
					{
						currentChoice++;

						if (currentChoice == choice)
						{
							// Final safety checks
							if (isVehicleBooked(vehicleId))
							{
								cout << "\nError: Vehicle is currently booked.\n";
								cout << "Maintenance cannot be assigned to a booked vehicle.\n";
								break;
							}

							if (isVehicleOnTrip(vehicleId))
							{
								cout << "\nError: Vehicle is currently on a trip.\n";
								cout << "Maintenance cannot be assigned while the vehicle is on a trip.\n";
								break;
							}

							vehicles[i].setvehicleStatus("Under Maintenance");

							saveVehicles();

							cout << "\n=================================================\n";
							cout << "       VEHICLE SENT FOR MAINTENANCE\n";
							cout << "=================================================\n";
							cout << "Vehicle ID     : " << vehicles[i].getVehicleId() << endl;
							cout << "Vehicle Number : " << vehicles[i].getVehicleNumber() << endl;
							cout << "Vehicle Type   : " << vehicles[i].getVehicleType() << endl;
							cout << "Capacity       : " << vehicles[i].getVehicleCapacity() << " Tons" << endl;
							cout << "Vehicle Status : Under Maintenance" << endl;
							cout << "=================================================\n";

							break;
						}
					}
				}

				break;
			}


			case 2:
			{
				int choice;
				int count = 0;

				cout << "\n=================================================\n";
				cout << "          AVAILABLE VEHICLES\n";
				cout << "=================================================\n";

				for (int i = 0; i < vehicles.size(); i++)
				{
					string vehicleId = vehicles[i].getVehicleId();

					// Show only vehicles that are currently Available
					if (getCurrentVehicleStatus(vehicleId) == "Available")
					{
						count++;

						cout << "\n" << count << ".\n";
						cout << "   Vehicle ID     : " << vehicleId << endl;
						cout << "   Vehicle Number : " << vehicles[i].getVehicleNumber() << endl;
						cout << "   Vehicle Type   : " << vehicles[i].getVehicleType() << endl;
						cout << "   Capacity       : " << vehicles[i].getVehicleCapacity() << " Tons" << endl;
						cout << "   Current City   : " << vehicles[i].getCurrentCity() << endl;
						cout << "   Status         : Available" << endl;
						cout << "-------------------------------------------------------\n";
					}
				}

				cout << "=================================================\n";

				if (count == 0)
				{
					cout << "\nNo vehicles are currently available for servicing.\n";
					break;
				}

				cout << "\nSelect Vehicle to Send for Servicing: ";
				cin >> choice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (choice < 1 || choice > count)
				{
					cout << "\nInvalid vehicle choice.\n";
					break;
				}

				int currentChoice = 0;

				for (int i = 0; i < vehicles.size(); i++)
				{
					string vehicleId = vehicles[i].getVehicleId();

					if (getCurrentVehicleStatus(vehicleId) == "Available")
					{
						currentChoice++;

						if (currentChoice == choice)
						{
							// Final safety checks
							if (isVehicleBooked(vehicleId))
							{
								cout << "\nError: Vehicle is currently booked.\n";
								cout << "Servicing cannot be assigned to a booked vehicle.\n";
								break;
							}

							if (isVehicleOnTrip(vehicleId))
							{
								cout << "\nError: Vehicle is currently on a trip.\n";
								cout << "Servicing cannot be assigned while the vehicle is on a trip.\n";
								break;
							}

							vehicles[i].setvehicleStatus("Under Servicing");

							saveVehicles();

							cout << "\n=================================================\n";
							cout << "        VEHICLE SENT FOR SERVICING\n";
							cout << "=================================================\n";
							cout << "Vehicle ID     : " << vehicles[i].getVehicleId() << endl;
							cout << "Vehicle Number : " << vehicles[i].getVehicleNumber() << endl;
							cout << "Vehicle Type   : " << vehicles[i].getVehicleType() << endl;
							cout << "Capacity       : " << vehicles[i].getVehicleCapacity() << " Tons" << endl;
							cout << "Vehicle Status : Under Servicing" << endl;
							cout << "=================================================\n";

							break;
						}
					}
				}

				break;
			}


			case 3:
			{
				int choice;
				int count = 0;

				cout << "\n=================================================\n";
				cout << "       VEHICLES UNDER MAINTENANCE\n";
				cout << "=================================================\n";

				for (int i = 0; i < vehicles.size(); i++)
				{
					if (vehicles[i].getVehicleStatus() == "Under Maintenance")
					{
						count++;

						cout << count << ". "
							<< "ID: " << vehicles[i].getVehicleId()
							<< " | Number: " << vehicles[i].getVehicleNumber()
							<< " | Type: " << vehicles[i].getVehicleType()
							<< " | Capacity: " << vehicles[i].getVehicleCapacity() << " Tons"
							<< endl;
					}
				}

				cout << "=================================================\n";

				if (count == 0)
				{
					cout << "\nNo vehicles are currently under maintenance.\n";
					break;
				}

				cout << "\nSelect Vehicle to Mark Maintenance Completed: ";
				cin >> choice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (choice < 1 || choice > count)
				{
					cout << "\nInvalid vehicle choice.\n";
					break;
				}

				int currentChoice = 0;

				for (int i = 0; i < vehicles.size(); i++)
				{
					if (vehicles[i].getVehicleStatus() == "Under Maintenance")
					{
						currentChoice++;

						if (currentChoice == choice)
						{
							vehicles[i].setvehicleStatus("Available");

							saveVehicles();

							cout << "\n=================================================\n";
							cout << "       VEHICLE MAINTENANCE COMPLETED\n";
							cout << "=================================================\n";
							cout << "Vehicle ID     : " << vehicles[i].getVehicleId() << endl;
							cout << "Vehicle Number : " << vehicles[i].getVehicleNumber() << endl;
							cout << "Vehicle Status : Available" << endl;
							cout << "=================================================\n";

							break;
						}
					}
				}

				break;
			}


			case 4:
			{
				int choice;
				int count = 0;

				cout << "\n=================================================\n";
				cout << "        VEHICLES UNDER SERVICING\n";
				cout << "=================================================\n";

				for (int i = 0; i < vehicles.size(); i++)
				{
					if (vehicles[i].getVehicleStatus() == "Under Servicing")
					{
						count++;

						cout << count << ". "
							<< "ID: " << vehicles[i].getVehicleId()
							<< " | Number: " << vehicles[i].getVehicleNumber()
							<< " | Type: " << vehicles[i].getVehicleType()
							<< " | Capacity: " << vehicles[i].getVehicleCapacity() << " Tons"
							<< endl;
					}
				}

				cout << "=================================================\n";

				if (count == 0)
				{
					cout << "\nNo vehicles are currently under servicing.\n";
					break;
				}

				cout << "\nSelect Vehicle to Mark Servicing Completed: ";
				cin >> choice;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');

					cout << "\nInvalid input! Please enter a number.\n";
					break;
				}

				if (choice < 1 || choice > count)
				{
					cout << "\nInvalid vehicle choice.\n";
					break;
				}

				int currentChoice = 0;

				for (int i = 0; i < vehicles.size(); i++)
				{
					if (vehicles[i].getVehicleStatus() == "Under Servicing")
					{
						currentChoice++;

						if (currentChoice == choice)
						{
							vehicles[i].setvehicleStatus("Available");

							saveVehicles();

							cout << "\n=================================================\n";
							cout << "        VEHICLE SERVICING COMPLETED\n";
							cout << "=================================================\n";
							cout << "Vehicle ID     : " << vehicles[i].getVehicleId() << endl;
							cout << "Vehicle Number : " << vehicles[i].getVehicleNumber() << endl;
							cout << "Vehicle Status : Available" << endl;
							cout << "=================================================\n";

							break;
						}
					}
				}

				break;
			}


			case 5:
				cout << "\nReturning to Vehicle Menu...\n";
				break;


			default:
				cout << "\nInvalid Choice! Please try again.\n";
			}

		} while (choice != 5);
	}


	// =========================================================
	// CHECK VEHICLE ON TRIP
	// =========================================================

	bool isVehicleOnTrip(string vehicleId)
	{
		string searchText =
			"| Vehicle: " + vehicleId + " |";

		for (int i = 0; i < trips.size(); i++)
		{
			if (trips[i].find(searchText)
				!= string::npos)
			{
				return true;
			}
		}

		return false;
	}


	// =========================================================
	// GET CURRENT VEHICLE STATUS
	// =========================================================

	string getCurrentVehicleStatus(string vehicleId)
	{
		for (int i = 0; i < vehicles.size(); i++)
		{
			if (vehicles[i].getVehicleId() == vehicleId)
			{
				// Maintenance has highest priority
				if (vehicles[i].getVehicleStatus()
					== "Under Maintenance")
				{
					return "Under Maintenance";
				}

				// Servicing has highest priority
				if (vehicles[i].getVehicleStatus()
					== "Under Servicing")
				{
					return "Under Servicing";
				}

				// Check trip
				if (isVehicleOnTrip(vehicleId))
				{
					return "On Trip - Available Soon";
				}

				// Check booking
				if (isVehicleBooked(vehicleId))
				{
					return "Booked";
				}

				return "Available";
			}
		}

		return "Unknown";
	}

};