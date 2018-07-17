/*
CS202 ASSIGNMENT 1: MAX SMILEY
FILE: record.h

records are created by vehicles and returned to a list of records in main. 
if the program every actually worked, this would be used to display all the
information about each vehicle's delivery, with RecordList::print() in main. 
*/


#ifndef RECORD_H_
#define RECORD_H_

#include <iostream>

class Record
{
	public:
		Record();
		Record(int, int, int, int);
		void print();
	
	protected:
		int v_type;
		int travDistance;
		int travTime;
		int numDeliveries;
		float payrate;
};

class RecordList: public Record
{
	public:
		RecordList();
		RecordList(int, int, int, int);
		void add_record(RecordList * record);
		void print();

	protected:
		RecordList * next;
		int length;
};

#endif
