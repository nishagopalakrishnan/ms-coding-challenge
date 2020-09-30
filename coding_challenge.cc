#include <string>
#include <fstream>
#include <vector>
#include <utility>    // std::pair
#include <stdexcept>  // std::runtime_error
#include <sstream>    // std::stringstream
#include <iostream>  
#include <stdlib.h>
#include <algorithm>  // sort
#include <iomanip>    // setprecision
#include "gtest/gtest.h" // Google test frame work.
#include <cmath>
#include <math.h>

using namespace std;

long double earthRadius= 6378.137;
vector <pair<long double, std::string> > resultFoodTruck;


/**
   Function to convert degree into radians

   @param[in]   degree  Latitude or longitude in degree.
*/
long double toRadians(const long double degree) 
{ 
    return (degree * ((M_PI)/100)); 
} 


/**
   Calculate the distance between two co-ordinates
   given in terms of latitude and longitude.

   @param[in] lat1      Latitude of the food truck.
   @paran[in] long1     Longitude of the food truck.
   @param[in] custlat   Latitude of the customer.
   @param[in] custlong  Longitude of the customer.
*/
long double computeDistance(long double lat1, long double long1,
		            long double custLat, long double custLong)  
{
    long double distInKms;

    // Convert from degrees to radian.	
    lat1= toRadians(lat1); 
    long1= toRadians(long1); 
    custLat= toRadians(custLat); 
    custLong= toRadians(custLong);
      
    // Apply the Haversine Formula 
    long double dlong= custLong - long1; 
    long double dlat= custLat - lat1; 
  
    distInKms= pow(sin(dlat / 2), 2) +  
               cos(lat1) * cos(custLat) *  
               pow(sin(dlong / 2), 2); 
  
    distInKms= 2 * asin(sqrt(distInKms)); 
  
    return (distInKms * earthRadius); 
} 


/**
   Read the csv file containing information of all the
   Food trucks in the region and compute the distance
   between customer and foodtrucks.

   @param[in] fileName  Path name with information about Food Trucks.
   @param[in] userLat   Latitude of user in degrees.
   @param[in] userLong  Longitude of user in degrees.
*/
void computeTrucksCloseBy(std::string fileName, long double userLat, long double userLong)
{
    std::ifstream dataFile(fileName);

    if (!dataFile.is_open())
      return;

    std::string line;
    std::string val1, val2;

    // Ignore the column names by reading the first line..
    if (dataFile.good())
      std::getline(dataFile, line);

    // Read food truck data.
    while (std::getline(dataFile, line))
    {
        std::stringstream ss(line);
        std::string truckName;
        unsigned int colId= 1;
	long double lat, longt, dist;
        
	// Scan until you get the 15th column information.
	while(colId!= 15 && std::getline(ss, val1, ','))
	{
	  // Save the food truck name for display later.
	  if (colId == 2)
	    truckName.assign(val1);
	  colId++;

        }		

	// Fetch the latitude and longitude information.
	std::getline(ss, val1, ',');
	std::getline(ss, val2, ',');

	lat= atof(val1.c_str());
	longt= atof(val2.c_str());

        // Find the distance and update the result vector.
	dist= computeDistance(lat, longt, userLat, userLong);
        resultFoodTruck.push_back(make_pair(dist, truckName));
	
     }

     // Sort in ascending order based on the distance.
     sort(resultFoodTruck.begin(), resultFoodTruck.end());
     dataFile.close();
}


/**
    Dispaly the closest no of trucks specified by customer.

    @param[in] noOfTrucks   Number of trucks to be displayed.
*/
void displayFoodTrucksCloseBy(unsigned int noOfTrucks)
{
  cout << noOfTrucks << " food trucks close by are: \n";
  cout << "-----------------------------------------------------------------\n";
  cout << setprecision(2) << fixed;
  for (int i=0; i < noOfTrucks; i++)
  {
    cout << resultFoodTruck[i].second << " is at a distance of " << resultFoodTruck[i].first << "kms\n";
    cout << "----------------------------------------------------------------\n";
  }

}

/**
   Validate the Latitude and longitude supplied.

   @param[in]  lat     Latitude.
   @param[in]  longt   Longitude.
*/
bool validateLatLong(long double lat, long double longt)
{
  if (!(isfinite(lat) && (abs(lat)>= -90) && (abs(lat) <=90)))
    return true;

  if (!(isfinite(lat) && (abs(lat)>= -180) && (abs(lat) <=180)))
    return true;

  return false;
}


/**
   Find the food truck close to the customer.

   @param[in] noOfTrucks    Number of Trucks to display.
   @param[in] userLat       Latitude of customer.
   @param[in] userLong      Longitude of customer.
   @param[in] regionData    Path the data file.

*/
void findFoodTrucks(unsigned int noOfTrucks, long double userLat,
		   long double userLong, std::string regionData)
{
   if (validateLatLong(userLat, userLong))
     return;
     
   computeTrucksCloseBy(regionData, userLat, userLong);
   displayFoodTrucksCloseBy(noOfTrucks);

}


// Unit Tests.
TEST (displayFoodTrucks, invalidLatLongt)
{
  // Arrange
  long double userlat=100, userlong= 182;
  unsigned int noOfTrucks= 0;

  // Act
  findFoodTrucks(noOfTrucks, userlat, userlong, "../Mobile_Food_Facility_Permit.csv");


  // Check
  ASSERT_TRUE(resultFoodTruck.size() == 0);
}



TEST (displayFoodTrucks, noDataFile)
{
  // Arrange
  long double userlat=37.73363804110, userlong= -122.109595796246;
  unsigned int noOfTrucks= 0;

  // Act
  findFoodTrucks(noOfTrucks, userlat, userlong, "../Mobile_Food_Facility");


  // Check
  ASSERT_TRUE(resultFoodTruck.size() == 0);
}


TEST (displayFoodTrucks, closestFoodTruck)
{
  // Arrange
  long double userlat=37.73363804110, userlong= -122.109595796246;
  unsigned int noOfTrucks= 1;

  // Act
  findFoodTrucks(noOfTrucks, userlat, userlong, "../Mobile_Food_Facility_Permit.csv");


  // Check
  ASSERT_TRUE(resultFoodTruck.size() > 0);
}


TEST (displayFoodTrucks, fiveFoodTrucks)
{
  // Arrange
  long double userlat=37.73363804110, userlong= -122.109595796246;
  unsigned int noOfTrucks= 5;

  // Act
  findFoodTrucks(noOfTrucks, userlat, userlong, "../Mobile_Food_Facility_Permit.csv");


  // Check
  ASSERT_TRUE(resultFoodTruck.size() > 0);

}

TEST (displayFoodTrucks, tenFoodTrucks)
{
  // Arrange
  long double userlat=37.73363804110, userlong= -122.109595796246;
  unsigned int noOfTrucks= 10;

  // Act
  findFoodTrucks(noOfTrucks, userlat, userlong, "../Mobile_Food_Facility_Permit.csv");


  // Check
  ASSERT_TRUE(resultFoodTruck.size() > 0);
}


int main()
{
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
