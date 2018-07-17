/*

CS202 ASSIGNMENT 1 : MAX SMILEY
filename: address.h

This header file declares class Address and its derived classes Package and Edge. These are the fundamental classes used to model
our delivery system. Both of these classes have derived classes that model a list of objects of the class, conatined in file list.h.
These classes are not very useful without their derived list classes.


*/


#ifndef ADDRESS_H_
#define ADDRESS_H_

class Address
{
	public:
		Address();
		Address(int in_address);
		int getAddress() const;

	protected:
		int address;
};

class Package: public Address
{
	public:
		Package();
		Package(int in_priority, int in_address, int in_size, int in_weight);
		
		int getPriority();
	
	protected:
		int priority;
		int size;
		int weight;
};

class Edge: public Address
{
	public:
		Edge();
		Edge(int in_address, int in_length, int in_speed);

		int getLength() const;
		int getSpeed() const;
		int getTime() const;

	protected:
		int length;
		int speed;
};		

#endif
