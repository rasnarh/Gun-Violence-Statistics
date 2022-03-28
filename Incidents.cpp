// Implementation file for Incidents class
// Created by: Rasna Husain

using namespace std;

#include "Incidents.h"

//**************************************************
//*             DEFAULT CONSTRUCTOR                *
//**************************************************p
Incidents::Incidents()
{
	ID = "";
	state="";
	date = "";
	fatalities = 0;
	race = "";
	gender = "";
}


//**************************************************
//*                CONSTRUCTOR                     *
//**************************************************
Incidents::Incidents(string sID, string sState, string sDate, int sFatalities, string sRace, string sGender)
{
	ID = sID;
    state = sState;
	date = sDate;
	fatalities = sFatalities;
	race = sRace;
	gender = sGender;
}


//**************************************************
//*              SETTER DEFINITIONS                *
//**************************************************

// setters to set respective data properties

// sets ID
void Incidents::setID(string sID)
{
	ID = sID;
}

// sets state
void Incidents::setState(string sState)
{
	state = sState;
}

// sets date
void Incidents::setDate(string sDate)
{
	date = sDate;
}

// sets fatalities
void Incidents::setFatalities(int sFatalities)
{
	fatalities = sFatalities;
}

// sets race
void Incidents::setRace(string sRace)
{
	race = sRace;
}

// sets gender
void Incidents::setGender(string sGender)
{
	gender = sGender;
}


//**************************************************
//*              GETTER DEFINITIONS                *
//**************************************************

// returns ID
string Incidents::getID() const
{
	return ID;
}

//returns state
string Incidents::getState() const
{
	return state;
}

// returns date
string Incidents::getDate() const
{
	return date;
}

// returns fatalities
int Incidents::getFatalities() const
{
	return fatalities;
}

// returns race
string Incidents::getRace() const
{
	return race;
}

// returns gender
string Incidents::getGender() const
{
	return gender;
}

