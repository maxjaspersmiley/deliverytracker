/*
CS202 ASSIGNMENT 1 : MAX SMILEY
file: citymap.cpp
*/

#include "citymap.h"
#include <fstream>

using namespace std;

const int MAP_SIZE = 20;

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


//default constructor, don't use
Vertex::Vertex(): edge_list(NULL), shortest_distance_to(1000), package_list(NULL)
{}

//copy construcot calls more copy construcotrs. 
Vertex::Vertex(const Vertex &to_copy)
{
	edge_list = new EdgeList(*to_copy.edge_list);
	package_list = new PackageList(*to_copy.package_list);
}

//destructor calls more destructors. 
Vertex::~Vertex()
{
	delete edge_list;
	delete package_list;
}

//creates a vertex with a passed-in edge list. this is how we create vertices in citymap's constructor. 
Vertex::Vertex(EdgeList * in_edge_list):edge_list(in_edge_list), package_list(NULL), shortest_distance_to(1000)
{}

//in case a default constructor is ever invoked. 
void Vertex::setEdgeList(EdgeList * in_edge_list)
{
	edge_list = in_edge_list;
}

//allows citymap to change the best distance it's found to each vertex. 
void Vertex::setBestDist(int in_distance)
{
	shortest_distance_to = in_distance;
}

//used by city map to see if a trip is worth making. 
int Vertex::getBestDist()
{
	return shortest_distance_to;
}

//allows citymap to see if a vertex has a valid edge list. 
//didn't actually end up using this one. 
bool Vertex::exists()
{
	if(edge_list)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//allows citymap to peek into the edgelist
const EdgeList * Vertex::getListPtr()
{
	const EdgeList * return_ptr = edge_list;
	return return_ptr;
}

//the way we populate package_list
void Vertex::get_package(PackageList * in_package)
{
	if(package_list)
	{
		package_list->add_to_rear(in_package);
	}
	else
	{
		package_list = in_package;
	}
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//never used
CityMap::CityMap():vertex_list(NULL)
{}

//would have been implemented and used if Interrupt ever was implemented, as Interrupt would have created a new citymap and modified its values. 
CityMap::CityMap(const CityMap &to_copy)
{

}

//deletes each dynamically allocated vertex, and then deletes the array of vertices. 
CityMap::~CityMap()
{
	for(int i = 0; i < MAP_SIZE; ++i)
	{
		delete vertex_list[i];
	}
	delete[] vertex_list;
}

//read in edgelists from file. 
CityMap::CityMap(const char * in_file)
{
	vertex_list = new Vertex*[MAP_SIZE];
	ifstream input_file;
	input_file.open(in_file);

	int index = 0;
	int address, length, speed;
	char ch;

	EdgeList * in_list = NULL;
	EdgeList * to_add = NULL;

	while(input_file >> address >> length >> speed)
	{
		to_add = new EdgeList(address, length, speed);
		if(!in_list)
		{
			in_list = to_add;
		}
		else
		{
			in_list->add_to_rear(to_add);
		}

		ch = input_file.peek();
		
		if(ch == '\n')
		{
			vertex_list[index] = new Vertex(in_list);
			in_list = NULL;
			to_add = NULL;
			ch = input_file.get();
			++index;
		}
	}

	input_file.close();
}

//passes a package through the map into a vertex. 
void CityMap::receive_package(PackageList * package)
{
	vertex_list[package->getAddress()]->get_package(package);
}	

//finds the best route from current_address to destination_address.
//inPathLength is the length of the path traveleed so far (0 when this is originally called in get_route).
//bestOverallPathLength is the best length we've found so far, total, regardless of where in the recursive stack we are.
//path_to_here is the path_to_next from the previous call (NULL in first call) and best_path is the best path we've found so far. 

//this is the function where segfaults are currently occurring. 
void CityMap::recursive_find_route(int current_address, int destination_address, int inPathLength, int& bestOverallPathLength, 
							      EdgeList * path_to_here, EdgeList *& best_path)
{
	//are we there??
	if((current_address == destination_address) && (inPathLength < bestOverallPathLength))
	{
		bestOverallPathLength = inPathLength;
		if(best_path){delete best_path;}
		best_path = new EdgeList(*path_to_here);
		return;
	}
	//this is the vertex that we're at right now. 
	Vertex * from_vertex = vertex_list[current_address];
	
	//update the bestDist to here (if previous best dist was better, we wouldn't have ended up here in the first place)
	from_vertex->setBestDist(inPathLength);
	//the first element in the edgelist where we are right now
	const EdgeList * current_edge_list = from_vertex->getListPtr();
	//gonna use this later
	int totalLengthToNext;
	//this too
	int next_address;

	//while we haven't looked at every edge in the list
	while(current_edge_list)
	{
		//how long would our path be, if we DID go to this vertex?
		totalLengthToNext = inPathLength + current_edge_list->getLength();

		//what is the address of that edge?
		next_address = current_edge_list->getAddress();

		//if it's shorter than the last time we went there, 
		if(totalLengthToNext <= vertex_list[next_address]->getBestDist())
		{
			//need to make a path_to_here for the next call, as it won't know where it came from otherwise.	
			EdgeList * path_to_next;
			EdgeList * to_add = new EdgeList(next_address, current_edge_list->getLength(), current_edge_list->getSpeed(), NULL);

			//if there wasn't a path_to_here, the edge going to the next vertex is the only one in the list.
			if(!path_to_here)
			{
				path_to_next = to_add;
			}
			//otherwise, copy the path that got us here, and add the path to the next vertex.
			else
			{
				path_to_next = new EdgeList(*path_to_here);
				path_to_next->add_to_rear(to_add);
			}
	
			to_add = NULL;

			//recursion
			recursive_find_route(next_address, destination_address, totalLengthToNext, 
						 bestOverallPathLength, path_to_next, best_path);
			delete path_to_next;
		}

		current_edge_list = current_edge_list->getNextPtr();
	}
}
//this is how a vehicle calls the recursive get route function
void CityMap::get_route(const PackageList * in_package_list, EdgeList *& to_return)	
{
	const PackageList * to_deliver = in_package_list;
	EdgeList * best_path = NULL;
	int from = 0;
	int to = to_deliver->getAddress();
	int best_length = 10000;

	//while there is a package to deliver
	while(to_deliver)
	{
		//make sure our distances are fresh
		reset_best_distances();		
		//this is where the path will end up after recursion
		best_path = NULL;
		//find route from origin to first package, 
		//then from first to second, etc,
		//adding the paths together the whole way.
		recursive_find_route(from, to, 0, best_length, NULL, best_path);
		if(!to_return)
		{
			to_return = new EdgeList(*best_path);
		}
		else
		{
			to_return->add_to_rear(best_path);
		}
			
		to_deliver = to_deliver->getNextPtr();
	
		from = to;
		if(to_deliver)
		{
			to=to_deliver->getAddress();
		}
		else
		{
			to = 0;
		}
	}
}

void CityMap::reset_best_distances()
{
	for(int i = 0; i < MAP_SIZE; ++i)
	{
		vertex_list[i]->setBestDist(1000);
	}
}








