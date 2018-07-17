/*
CS202 ASSIGNMENT 1 : MAX SMILEY
file: record.cpp

*/


#include "record.h"

using namespace std;

//default constructor, dont' use. 
Record::Record(): v_type(-1), travDistance(-1), travTime(-1), numDeliveries(-1), payrate(-1)
{}

//creates a new record
Record::Record(int in_type, int in_dist, int in_time, int in_deliveries): 	v_type(in_type), travDistance(in_dist), travTime(in_time),
										numDeliveries(in_deliveries), payrate(0)
{
}

//prints a record
void Record::print()
{
	cout << "Distance traveled: " << travDistance << " miles." << endl;
	cout << "Time delivering  : " << travTime << " minutes." << endl;
	cout << "# deliveries made: " << numDeliveries << endl;
	return;
}

//default constructor, dont use
RecordList::RecordList(): Record(), next(NULL), length(-1)
{}

//creats a new empty list of records
RecordList::RecordList(int in_type, int in_dist, int in_time, int in_deliveries): Record(in_type, in_dist, in_time, in_deliveries), next(NULL), length(1)
{}

//adds a record
void RecordList::add_record(RecordList * record)
{
	while(next)
	{
		next = next->next;
	}

	next = record;
}

//prints the whole list
void RecordList::print()
{
	cout << "***************************************************" << endl;
	cout << "***************************************************" << endl;
	cout << "************                          *************" << endl;
	cout << "               RECORD LIST PRINTOUT                " << endl;
	cout << "************                          *************" << endl;
	cout << "***************************************************" << endl;
	cout << "***************************************************" << endl << endl;

	cout << "There are " << length << " recorded trips!" << endl << endl;
	
	Record * tracker = this;
	int count = 1;
	while(tracker)
	{
		cout << "Trip #" << count << " was by a";
		switch(v_type)
		{
			case 0: cout << " unmanned drone." << endl;
				break;
			case 1: cout << "n express driver." << endl;
				break;
			case 2: cout << " standard driver." << endl;
				break;
		}

		tracker->print();
		tracker = next;
	}

	cout << "Thank you for reading!!!" << endl;
 
	cout << "***************************************************" << endl;
	cout << "***************************************************" << endl;
	cout << "************                          *************" << endl;
	cout << "                   END OF LIST!!!                  " << endl;
	cout << "************                          *************" << endl;
	cout << "***************************************************" << endl;
	cout << "***************************************************" << endl << endl;
}
