//
//  City.hpp
//  Are We There Yet
//
//  Created by Kevin Reynolds on 11/19/20.
//

#ifndef City_hpp
#define City_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class City {
private:
    string mName;
    string mCountry;
    long double mLatitude;
    long double mLongitude;
    
public:
    
    //Constructor
    City();
    City(string name, string country, long double lat, long double lon);
    
    //Destructor
    ~City();
    
    //Setters
    void setName(string name);
    void setCountry(string country);
    void setLatitude(long double latitude);
    void setLongitude(long double longitude);
    
    // Getters
    string name();
    string country();
    long double latitude();
    long double longitude();
    
};

#endif /* City_hpp */
