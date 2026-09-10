#pragma once
#include<string>
#include<iostream>

using namespace std;

class Vehicle 
{
private:
	string vehicleId;
	string vehicleNumber;
	string vehicleType;
	double vehicleCapacity;
	string currentCity;
	string vehicleStatus;
public:
	Vehicle(string id, string number, string type, double cap, string city, string status) 
	{
		vehicleId = id;
		vehicleNumber = number;
		vehicleType = type;
		vehicleCapacity = cap;
		currentCity = city;
		vehicleStatus = status;
	}

	void setvehicleNumber(string number)
	{
		vehicleNumber = number;
	}

	void setvehicleType(string type)
	{
		vehicleType = type;
	}

	void setvehicleCapacity(double cap)
	{
		vehicleCapacity = cap;
	}

	void setcurrentCity(string city)
	{
		currentCity = city;
	}

	void setvehicleStatus(string status)
	{
		vehicleStatus = status;
	}

	void displayVehicle() 
	{
		cout << "Vehicle ID               : " << vehicleId << endl;
		cout << "Vehicle Number           : " << vehicleNumber << endl;
		cout << "Type of Vehicle          : " << vehicleType << endl;
		cout << "Capacity of the Vehicle  : " << vehicleCapacity << " TONS"<< endl;
		cout << "Current city             : " << currentCity << endl;
		cout << "Vehicle Status           : " << vehicleStatus << endl;
	}
	
	string getVehicleId()
	{
		return vehicleId;
	}

	string getVehicleNumber()
	{
		return vehicleNumber;
	}

	string getVehicleType()
	{
		return vehicleType;
	}

	double getVehicleCapacity()
	{
		return vehicleCapacity;
	}

	string getCurrentCity()
	{
		return currentCity;
	}

	string getVehicleStatus()
	{
		return vehicleStatus;
	}
};
