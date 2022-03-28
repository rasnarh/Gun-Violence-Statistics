//Implementation file for Incidents class
//IDE: Visual Studio 2017
//Created by: Rasna Husain

#ifndef _INCIDENTS
#define _INCIDENTS

#include <string>
#include <iomanip>
#include <iostream>

using std::string;
using std::ostream;

class Incidents
{
private:
	string ID;				// primary key
	string state;		    // state of incident - secondary key
	string date;			// date of incident
	int fatalities;			// number of fataliities in incident
	string race;			// race of the shooter
	string gender;			// gender of the shooter

public:
	// constructors
	Incidents();
	Incidents(string sID, string sState, string sDate, int sFatalities, string sRace, string sGender);

	// setters 
	void setID(string sID);
	void setState(string sState);
	void setDate(string sDate);
	void setFatalities(int sFatalities);
	void setRace(string sRace);
	void setGender(string sGender);

	// getters 
	string getID() const;
	string getState() const;
	string getDate() const;
	int getFatalities() const;
	string getRace() const;
	string getGender() const;
};

#endif
