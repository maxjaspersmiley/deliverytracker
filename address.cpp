#include "address.h"
#include <iostream>

/* 

CS202 ASSIGNMENT 1 : MAX SMILEY
file: address.cpp

This file provides the definitions for the classes prototyped in address.h. 
Most of these functions seem self explanatory. 

*/

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

Address::Address(): address(-1)
{}

Address::Address(int in_address): address(in_address)
{}

int Address::getAddress() const
{
	return address;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

Package::Package(): priority(-1), size(-1), weight(-1)
{}

Package::Package(int in_priority, int in_address, int in_size, int in_weight):	Address(in_address),
										priority(in_priority),
										size(in_size),
										weight(in_weight)
{}

int Package::getPriority()
{
	return priority;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

Edge::Edge(): length(-1), speed(-1)
{}

Edge::Edge(int in_address, int in_length, int in_speed):	Address(in_address),
								length(in_length),
								speed(in_speed)
{}

int Edge::getLength() const
{
	return length;
}

int Edge::getSpeed() const
{
	return speed;
}

//returns time spend traveling in minutes. 
int Edge::getTime() const
{
	float l = length;
	float s = speed;
	float r = 60*(l/s);

	return (int)r;
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
