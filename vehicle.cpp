/*
CS202 ASSIGNMENT 1 : MAX SMILEY
file: vehicle.cpp
*/

#include "vehicle.h"


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//default constructor, not used. 
Vehicle::Vehicle(): 	package_list(NULL), edge_list(NULL), capacity(-1), volume(-10000), 
			v_type(-1), travDistance(-10000), travTime(-10000), numDeliveries(-10000)
{}

//copy constructor, calls other copy constructors, deep copy dynamic data. 
Vehicle::Vehicle(Vehicle &to_copy): 	package_list(NULL), edge_list(NULL), capacity(to_copy.capacity), volume(to_copy.volume), v_type(to_copy.v_type),
					travDistance(to_copy.travDistance), travTime(to_copy.travTime), numDeliveries(to_copy.numDeliveries)
{
	package_list = new PackageList(*to_copy.package_list);
	edge_list = new EdgeList(*to_copy.edge_list);
}

//destructor calls other destructors. 
Vehicle::~Vehicle()
{
	delete package_list;
	delete edge_list;
}

//this is the way vehicles are created in main. Passes in a package list that is a sublist of one of the package lists in main. 
//capacity and volume are currently meaningless, but the idea was to check if the vehicle had enoguh room for whatever it was carrying. 
Vehicle::Vehicle(PackageList * in_list, int in_capacity, int in_volume): package_list(in_list), capacity(in_capacity), volume(in_volume),
								travDistance(0), travTime(0), numDeliveries(0), v_type(-1)
{}

//gets edge_list from citymap, and then drives (or flys) through the city delivering packages until there aren't anymore. 
void Vehicle::dispatch(CityMap& city_map)
{
	//we don't know what type we are until we have packages. yes i'm sure there is a better way to do this. 
	v_type = package_list->getPriority();
	
	//find the route we'll take. 
	city_map.get_route(package_list, edge_list);

	Edge * edge = NULL;
	PackageList * package = NULL;

	//while there are still packages in the list
	while(package_list)
	{
		//put the first element of packagelist into package. awful syntax, i know. 
		package_list = package_list->get_first_element(package);
		//same as above
		edge_list = edge_list->get_first_element(edge);

		//while we're not at the package's delivery location
		while(package->getAddress() != edge->getAddress())
		{
			//increment distance and time traveled
			travDistance 	+= edge->getLength();
			travTime	+= edge->getTime();
			
			//get rid of edge and get the next edge.
			delete edge;
			edge = NULL;
			edge_list = edge_list->get_first_element(edge);
		}
		//incremenet, again
		travDistance	+= edge->getLength();
		travTime	+= edge->getTime();
		++numDeliveries;

		//pass that package off to citymap and go next.
		city_map.receive_package(package);
		delete edge;
		edge = NULL;
	}	
}

//returns a record so we know stuff
RecordList * Vehicle::getRecord()
{
	RecordList * record = new RecordList(v_type, travDistance, travTime, numDeliveries);
	return record;
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//ugly constructors
Drone::Drone(): Vehicle()
{}

Drone::Drone(PackageList * in_list, int in_capacity, int in_volume): Vehicle(in_list, in_capacity, in_volume)
{}

Express::Express(): Vehicle()
{}

Express::Express(PackageList * in_list, int in_capacity, int in_volume): Vehicle(in_list, in_capacity, in_volume)
{}

Standard::Standard(): Vehicle()
{}

Standard::Standard(PackageList * in_list, int in_capacity, int in_volume): Vehicle(in_list, in_capacity, in_volume)
{}
