//
//  City.cpp
//  Are We There Yet
//
//  Created by Kevin Reynolds on 11/19/20.
//

#include "City.hpp"

// Constructor
City::City() {}
City::City(string name, string country, long double lat, long double lon) {
    setName(name);
    setCountry(country);
    setLatitude(lat);
    setLongitude(lon);
}

// Destructor
City::~City() {}

//Setters
void City::setName(string name) { mName = name; }
void City::setCountry(string country) { mCountry = country; }
void City::setLatitude(long double latitude) { mLatitude = latitude; }
void City::setLongitude(long double longitude) { mLongitude = longitude; }

// Getters
string City::name() { return mName; }
string City::country() { return mCountry; }
long double City::latitude() { return mLatitude; }
long double City::longitude() {return mLongitude; }
