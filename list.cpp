#include "list.h"

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//default constructor. do not use. 
PackageList::PackageList(): Package(), next(NULL)
{}

//recursively deep-copys.
PackageList::PackageList(const PackageList &to_copy): 	Package(to_copy.priority, 
							to_copy.getAddress(), 
							to_copy.size, 
							to_copy.weight)
{
	if(to_copy.next)
	{
		next = new PackageList(*to_copy.next);
	}
	else
	{
		next = NULL;
	}
}
//recursively deletes dynamic memory.
PackageList::~PackageList()
{
	if(next)
	{
		delete next;
		next = NULL;
	}
}

//this is the constructor used. in_next is NULL by default. Creates a new package list with one element. 
PackageList::PackageList(int in_priority, int in_address, int in_size, 
			 int in_weight, PackageList * in_next):
	
			Package(in_priority, in_address, in_size, in_weight),
			next(in_next)
{}


//adds a package list to the end of calling list. 
//client must set to_add to null after calling. 
//I know this is bad please don't fail me. 
void PackageList::add_to_rear(PackageList * to_add)
{
	if(!next)
	{
		next = to_add;
		return;
	}

	PackageList * tail = this;
	PackageList * target;
	while(tail)
	{
		target = tail;
		tail = tail->next;
	}
	target->next = to_add;

}

//returns a const pointer to next, so client has
//information but can't screw it up. hopefully.
const PackageList * PackageList::getNextPtr() const
{
	const PackageList * return_ptr = next;
	return return_ptr;
}

//this function is bad. call with "donor = donor->get_first_element(donation).
//couldn't figure out a better way to do this, which is pretty embarassing. 
PackageList * PackageList::get_first_element(PackageList *& out_package)
{
	PackageList * temp = this;
	PackageList * ret = next;

	temp->next = NULL;
	out_package = new PackageList(*temp);
	
	delete temp;
	return ret;
}




//same as above, but this one is somehow worse. 
PackageList * PackageList::get_last_element(PackageList * out_package)
{
	if(!next)
	{
		out_package = this;
		out_package->next = NULL;
		return NULL;
	}

	PackageList * pre_tail = this;
	PackageList * tail = next;

	while(tail->next)
	{
		pre_tail = pre_tail->next;
		tail = tail->next;
	}

	pre_tail->next = NULL;
	out_package = tail;
	out_package->next = NULL;
	return this;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//default constructor, don't use
EdgeList::EdgeList(): Edge(), next(NULL)
{}

//recursive deep copy
EdgeList::EdgeList(const EdgeList &to_copy): 	Edge(to_copy.getAddress(), 
						to_copy.length, to_copy.speed)
{
	if(to_copy.next)
	{
		next = new EdgeList(*to_copy.next);

	}
	else
	{
		next = NULL;
	}
}

//recursive delete dynamic memory
EdgeList::~EdgeList()
{
	if(next)
	{
		delete next;
		next = NULL;
	}
}

//this is the constructor to use, in_next is null by default. 
EdgeList::EdgeList(int in_address, int in_length, int in_speed, 
		   EdgeList * in_next):	Edge(in_address, in_length, in_speed),	next(in_next)
{}

//
void EdgeList::add_to_rear(EdgeList * to_add)
{
	if(!next)
	{
		next = to_add;
		return;
	}

	EdgeList * tail = next;
	while(tail->next)
	{
		tail = tail->next;
	}

	tail->next = to_add;

}

//returns const poniter to next, so client can 
//have information about whats happening in list.
const EdgeList * EdgeList::getNextPtr() const
{
	const EdgeList * return_ptr = next;
	return return_ptr;
}


//this function is bad, use like donor = donor.getFirstElement(donation)
//it kinda works i guess. 
EdgeList * EdgeList::get_first_element(Edge *& out_edge)
{
	out_edge = this;
	return next;
}

//see above
EdgeList * EdgeList::get_last_element(Edge *& out_edge)
{
	if(!next)
	{
		out_edge = this;
		return NULL;
	}

	EdgeList * pre_tail = this;
	EdgeList * tail = next;

	while(tail->next)
	{
		pre_tail = pre_tail->next;
		tail = tail->next;
	}

	pre_tail->next = NULL;
	out_edge = tail;
	return this;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

