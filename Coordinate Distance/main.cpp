//
//  main.cpp
//  Are We There Yet
//
//  Created by Kevin Reynolds on 11/19/20.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "City.hpp"
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

vector<City> locations;

// Checks if strings are equilavalent regardless of case
bool isSame(string word1, string word2) {
    bool result = false;
    if (word1.length() == word2.length()) {
        // Equal size, now check each letter
        for (int i = 0; i <= word1.length(); i++) {
            if (i == word1.length()) {
                //Is a match
                result = true;
            } else if (tolower(word1[i]) != tolower(word2[i])) {
                // Not a match
                result = false;
                break;
            }
        }
    } else {
        // Not the same size, return false
        result = false;
    }
    return result;
}

long double calcDistance(long double lat1, long double long1, long double lat2, long double long2) {
    
    // Convert to radians
    lat1 = lat1 * (M_PI / 180);
    long1 = long1 * (M_PI / 180);
    
    lat2 = lat2 * (M_PI / 180);
    long2 = long2 * (M_PI / 180);
      
    // Haversine Formula
    long double longitude = long2 - long1;
    long double latitude = lat2 - lat1;
  
    // https://en.wikipedia.org/wiki/Haversine_formula
    // Refer to section: Formula
    long double result = pow(sin(latitude / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(longitude / 2), 2);
    
    result = sqrt(result);
  
    result = asin(result) * 2;
  
    long double R = 6371;
      
    // Calculate the result
    result = result * R;
  
    return result;
}

int getUserCity() {
    bool goodInput = false;
    int index = 0;
    while (goodInput == false) {
        size_t selectionNumber;
        bool userEnteredAnIndexNumber = true;
        string cityName;
        cout << "Enter location: ";
        getline(cin, cityName, '\n');
        
        // Determine if user typed a number or name;
        try {
            stoi(cityName);
            userEnteredAnIndexNumber = true;
        } catch ( invalid_argument ) {
            // User did not enter index
            // Keep the input as a string
            userEnteredAnIndexNumber = false;
        }
        
        //Validate the input
        if (userEnteredAnIndexNumber) {
            // User typed in a number
            //convert user input to size_t
            stringstream ss(cityName);
            ss >> selectionNumber;
            
            if ( selectionNumber > locations.size() || selectionNumber < 1 ) {
                cout << "Error: Invalid Index" << endl << endl;;
                goodInput = false;
            } else {
                index = (int)selectionNumber - 1;
                goodInput = true;
            }
        } else {
            // User typed in a name
            // Convert city name to index number
            for (int i = 0; i < locations.size() + 1; ++i) {
                
                if ( i == locations.size()) {
                    goodInput = false;
                    cout << "Error: Invalid Name" << endl << endl;
                } else if (isSame("quit", cityName)) {
                    return -1;
                } else if (isSame(locations[i].name(), cityName)) {
                    index = (int)i;
                    goodInput = true;
                    break;
                }
            }
        }
    }
    return index;
}

//Comparing function for map
bool compare(pair<string, long double>& lhs, pair<string, long double>& rhs) {
          return lhs.second < rhs.second;
}

double kmToMiles(long double kms) {
    return kms * .62;
}

int main() {
    cout << "Are We There Yet by Kevin Reynolds" << endl << endl;
    
    string input_file =  "worldcities.csv";
    
    ifstream iFile;
    iFile.open(input_file);
    
    string city, country, sLat, sLon;
    
    // Import content to locations vector
    while ( iFile.peek() != EOF ) {
        getline(iFile, city, ',');
        getline(iFile, country, ',');
        getline(iFile, sLat, ',');
        getline(iFile, sLon, '\n');
        
        // IF statement to ignore headers
        if (city != "City") {
            // Converts Lat and Lon from file to long doubles
            long double latitude = stold(sLat);
            long double longitude = stold(sLon);
            
            locations.push_back( City(city, country, latitude, longitude) );
        }
    }
    
    // Display menu
    int margin = 16;
    int calc = margin;
    string space = "  ";
    for (vector<City>::iterator city = locations.begin(); city != locations.end(); ++city) {
        auto i = distance(locations.begin(), city) + 1;
        
        if ( i > 99 ) {
            space = " ";
        } else if ( i < 10 ) {
            space = "   ";
        } else {
            space = "  ";
        }
        
        
        cout << setw(margin - calc - (int)space.size()) << right << i << "." << space << city -> name();
        calc = int(city -> name().size() - 7);
        if (i % 6 == 0) {
            cout << endl;
            calc = margin;
        }
    }
    cout << endl;
    
    while (true) {
        
        int index1 = getUserCity();
        
        // Check if user has opted to quit
        if (index1 < 0) {
            cout << "Goodbye!" << endl;
            return 0;
        }
        cout << locations[index1].name() << " selected!" << endl << endl;
        
        // Defines pair for all cities and distances
        // Distance value is based off user selection
        vector< pair<string, long double> > pairs;
        
        //Load pairs containing name and distance in KM
        for (City city : locations) {
            // Calculate distance between current current iteration of city and user's city
            long double distanceFromUserCity = calcDistance(locations[index1].latitude(), locations[index1].longitude(), city.latitude(), city.longitude());
            
            // Dont add user's city
            if (distanceFromUserCity != 0) {
                pairs.emplace_back(city.name(), distanceFromUserCity);
            }
        }
        
        // Sort by distance in ascending order
        sort(pairs.begin(), pairs.end(), compare);
        
        cout << endl;
        
        // Display the first (closest) seven cites
        cout << "Closest cities: " << endl;
        for (auto pair = pairs.begin(); pair != pairs.begin() + 7; ++pair) {
            cout <<
            pair -> first <<
            ": " <<
            right <<
            setw(25.0 - (pair -> first.length())) <<
            pair -> second <<
            " kilometers    " <<
            right <<
            setw(15) <<
            kmToMiles(pair -> second) <<
            " miles" <<
            endl;
        }
        
        cout << endl;
        
        // Display the last (furthest) seven cites
        cout << "Furthest cities: " << endl;
        for (auto pair = pairs.end() - 7; pair != pairs.end(); ++pair) {
            cout <<
            pair -> first <<
            ": " <<
            right <<
            setw(25.0 - (pair -> first.length())) <<
            pair -> second <<
            " kilometers    " <<
            right <<
            setw(15) <<
            kmToMiles(pair -> second) <<
            " miles" <<
            endl;
        }
        cout << endl << endl;
    }

    
    return 0;
}
