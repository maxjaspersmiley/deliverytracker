/*

CS202 PROGRAM 1 : MAX SMILEY
file: main.cpp

*/
#include <iostream>
#include <fstream>

#include "address.h"
#include "list.h"
#include "vehicle.h"
#include "citymap.h"
#include "record.h"

using namespace std;

const char * PACKAGE_INPUT = "packages.txt";
const char * MAP_FILE = "citymap.txt";

int main()
{
	//make a record list.
	RecordList record_list;

	//make a new citymap, reading in data from file. 
	CityMap city_map(MAP_FILE);

	//all the package lists for us to populate and then de-populate. 
	//package_list is a dual purpose list, hence the semi vague name. 
	PackageList * drn_list = NULL;
	PackageList * exp_list = NULL;
	PackageList * std_list = NULL;
	PackageList * package_list = NULL;

	//lets read in some packages from a text file!
	ifstream package_input;
	package_input.open(PACKAGE_INPUT);

	//you'll see what these are for pretty soon. 
	int priority, address, size, weight;

	Drone * drone;
	Express * express;
	Standard * standard;

	//while we're still getting info from file. 
	while(package_input >> priority >> address >> size >> weight)
	{
		//make a new package list.
		package_list = new PackageList(priority, address, size, weight, NULL);

		//depending on what the priority of the package is, add this package list to one of the other package lists. 
		switch(priority)
		{
		case 0:
			
			if(drn_list)
			{
				drn_list->add_to_rear(package_list);
			}
			else
			{
				drn_list = package_list;
			}
			break;
		case 1:
			if(exp_list)
			{
				exp_list->add_to_rear(package_list);
			}
			else
			{
				exp_list = package_list;
			}
			break;
		case 2:
			if(std_list)
			{
				std_list->add_to_rear(package_list);
			}
			else
			{
				std_list = package_list;
			}
			break;
		}
		package_list = NULL;
	}

	//while there are packages in the drone list. 
	while(drn_list)
	{
		//more horrible syntax. put the first element of drone list into package list. 
		drn_list = drn_list->get_first_element(package_list);
		//make a new drone, passing it the sub-list.
		drone = new Drone(package_list, 1, 20);
		//send that drone out to deliver some stuff.
		drone->dispatch(city_map);
		//get the record of the drone's delivery, and add it to the record list. 
		record_list.add_record(drone->getRecord());
		//get rid of that drone. 
		delete drone;
		package_list = NULL;
	}

	while(exp_list)
	{	
		//this block is the same as above, except for the for loop which i will explain 	
		exp_list = exp_list->get_first_element(package_list);

		//drone list was only popping one element at a time, but here we have to grab up to three. 
		//break statement in case there are less than three packages in the list to begin with. 
		for(int i = 1; i < 3; ++i)
		{
			PackageList * temp_list;
			if (!exp_list)
			{
				break;
			}
			exp_list = exp_list->get_first_element(package_list);
			package_list->add_to_rear(temp_list);
		}
	
		express = new Express(package_list, 3, 200);
		express->dispatch(city_map);
		record_list.add_record(express->getRecord());
		delete express;
		package_list = NULL;
	}

	while(std_list)
	{
		//this block is the same as the previous. 
		std_list = std_list->get_first_element(package_list);
		
		for(int i = 1; i < 8; ++i)
		{
			PackageList * temp_list;
			if(!std_list)
			{
				break;
			}
			std_list = std_list->get_first_element(package_list);
			
			package_list->add_to_rear(temp_list);
		}
	
		standard = new Standard(package_list, 8, 1000);
		standard->dispatch(city_map);
		record_list.add_record(standard->getRecord());
		delete standard;
		package_list = NULL;
	}

	//print the records
	record_list.print();
	//and we're done. 
	return 0;
}














			
