# ms-coding-challenge

List the food trucks within a proximity of "x" kms
from a given co-ordinates (latitude and longitude)
of a hungry customer.

## Installation

1) mkdir bin
2) cd bin 
3) cmake ..
4) make

## Usage

./codingChallenge.
[Runs all the tests]

## Tools Used

Programming Language: C++
          My experience has been in C mostly and to some extent C++. 
          Hence I have used C++.

Compiler: C++ 11

Editor: VIM

Compilation: CMake

Unit Testing framework:
          Google Unit test framework.

Platform:
       MAC OS.


## Notes

Design thoughts:
          On the first glance of a problem, I thought it will be easy to
          use Dijkstra's shortest path algorithm. Then I thought, I have
          to create the adjacency matrix after calculating the weights
          of each of the edges(customer to all food trucks). Hence ignored
          this appraoch.

          Next I thought about Euclidean algorithm. While reading more about
          that, I came across on why it won't work for distance on the sphere.

Design Implemented:

          While reading about Euclidean algorithm, I came across Haversine algorithm
          which is used for geo distance. Since this was more appropriate, I have used
          the Haversine alogrithm for calculating the distance between customer and
          various foodtrucks. Only the food trucks within the specifiedi maximum distance
          from the customer is displayed.

Design Alternatives:
         If I had some more time to gain expertise on application side programming,
         I would have loaded the data of food truck into a table and wrote a SQL
         query fitting the constraints of the problem description. I expect the performance
         to be better in comparison to the current solution designed.

         If I had front end knowledge, I could have plotted the data using a graphic interface
         which would have had more user appeal.

Implementation steps:

         a) Parse the CSV file to fetch the latitude and longitude of each of the food truck
            in the data file.
         b) Compute the distance between the food truck and customer using Haversine algorithm.
         c) Store the distance and food truck name in a vector in an ascending order based on
            distance.
         d) Based on the number of closest trucks requested by user, display the food truck
            name and distance.

Improvements:
         The code can be made modeled in a more object oriented way.


## Files
CMake Files:
      CMakeLists.txt
      CMakeLists.txt.in

DataFile:
     The data dump in CSV format provided for the challenge.


Code file:
     coding_challenge.cc


