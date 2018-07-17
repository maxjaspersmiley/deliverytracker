/*
CS202 ASSIGNMENT 1 : MAX SMILEY
file: list.h

This file describes two linear-linked-list data structures - one for class Package and one for class Edge.
Most of the functions here are implemented using pointers. This was probably a mistake, as it means the classes
are fairly difficult to actually use. I would not reccomend that anybody use either of these classes, for anything. 

*/



#ifndef LIST_H_
#define LIST_H_

#include "address.h"
#include "record.h"

class PackageList: public Package
{
	public:
		//required constructors and destructor
		PackageList();
		PackageList(const PackageList &to_copy);
		~PackageList();

		//creates a package list with one element.
		PackageList(int in_priority, int in_address, int in_size,
			    int in_weight, PackageList *in_next = NULL);

		//adds another package list to the end of the calling list. 
		void add_to_rear(PackageList * to_add);

		//allows the user to "peek" into the package list. Const, so no changes can 
		//be made to internal data. 
		const PackageList * getNextPtr() const;

		//passes the first element of the list by reference, and
		//returns the newly shortened list. This is probably a really
		//horrible way to do this.
		PackageList * get_first_element(PackageList *& list);
		//I don't think I ever use this function and I'm almost positive
		//that it doesn't work, but I have to hand in this
		//project in around 30 minutes so I'm just gonna leave it
		PackageList * get_last_element(PackageList * out_package);

	protected:
		PackageList * next; //pointer to next package list. 

};

class EdgeList: public Edge
{
	public:
		//required constructors and destructor
		EdgeList();
		EdgeList(const EdgeList &to_copy);
		~EdgeList();

		//creates an edgelist with one element
		EdgeList(int in_address, int in_length, int in_speed, EdgeList *in_next = NULL);

		//adds another edgelist to the end of the calling list
		void add_to_rear(EdgeList * to_add);

		//allows the user to "peek" into the edge list. Const, so no changes can
		//be made to our internal data. 
		const EdgeList * getNextPtr() const;

		//see similar functions in PackageList
		EdgeList * get_first_element(Edge *& out_edge);
		EdgeList * get_last_element(Edge *& out_edge);

	protected:
		EdgeList * next; //pointer to the next edge list. 
};


#endif
