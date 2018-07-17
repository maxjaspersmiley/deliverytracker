/*
CS202 ASSIGNMENT 1: MAX SMILEY
file: citymap.h

citymap represents a weighted graph. It contains a dynamically allocated array of vertices,
each of which has a linked list of edges (addresses of other vertices, with length and speed), 
and a linked list of packages, which should eventually contain all of the packages read in from main.

vertex is used exclusively by citymap. 

citymap is created in main, and passed to every vehicle after they have received their package list and 
are about to deliver their packages. the vehicle then queries citymap about the fastest route in which to 
deliver the packages, passing the package list to citymap. Citymap then generates an edgelist using a modified
depth-first-search algorith, and returns that list to the vehicle, which then uses it to traverse the map and deliver
its packages to vertices. That is what would happen if this program actually worked. 


Each vertex also keeps track of the distance of the shortest path to it thus-far. this is for citymap's recursive
find route function. the shortest distance variable is reset to 1000 every time get_route (the wrapper of recursive find
route) is called. 
*/


#ifndef CITYMAP_H_
#define CITYMAP_H_

#include "list.h"

class Vertex
{
	public:
		Vertex();
		Vertex(const Vertex &to_copy);
		~Vertex();

		Vertex(EdgeList * in_edge_list);

		void setEdgeList(EdgeList * in_edge_list);
		void setBestDist(int in_distance);
		int getBestDist();

		const EdgeList * getListPtr();	
		bool exists();

		void get_package(PackageList * in_package);

	private:
		EdgeList * edge_list;
		int shortest_distance_to;
		PackageList * package_list;
};

class CityMap
{
	public:
		CityMap();
		CityMap(const CityMap &to_copy);
		~CityMap();

		CityMap(const char * in_file);

		void get_route(const PackageList * in_package_list, EdgeList *& to_return);	
		void receive_package(PackageList * package);

	private:
		void recursive_find_route(int, int, int, int&, EdgeList*, EdgeList *& best_path);
		Vertex ** vertex_list;

		void reset_best_distances();
		
};

#endif

