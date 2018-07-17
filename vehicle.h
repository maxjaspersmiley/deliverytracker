/*
CS202 ASSIGNMENT 1: MAX SMILEY
file: vehicle.h

vehicles take packages from main, and move them to vertices inside the city map. 
there was more diversity planned between the derived classes but, alas, there wasn't enough time.

vehicles keep track of how much space they have and how much weight they can carry. This currently
does exactly nothing, but if i had another year to write this, maybe we could've done something cool.

they also keep track of the vehicle's type, the distance and time its traveled, and the number of
packages that have been delivered. this is passed to a record object before the vehicle is destroyed, 
so that we can print the data. 
*/


#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "list.h"
#include "citymap.h"
//#include "interrupt.h"

class Vehicle
{
	public:
		Vehicle();
		Vehicle(Vehicle &to_copy);
		~Vehicle();
	
		Vehicle(PackageList * in_list, int in_capacity, int in_volume);
		void dispatch(CityMap& city_map);
		RecordList * getRecord();
	
	protected:
		PackageList * package_list;
		EdgeList * edge_list;

		int capacity;
		int volume;

		int v_type;
		int travDistance;
		int travTime;
		int numDeliveries;
};

class Drone: public Vehicle
{
	public:
		Drone();
		Drone(PackageList * in_list, int in_capacity, int in_volume);

	protected:
};

class Express: public Vehicle
{
	public:
		Express();
		Express(PackageList * in_list, int in_capacity, int in_volume);
//		dispatch(CityMap& city_map);
};

class Standard: public Vehicle
{
	public:
		Standard();
		Standard(PackageList * in_list, int in_capacity, int in_volume);
};

//should we have seperate vehicle list classes? probably....

#endif
