# Team Proposal

## Leading Question 

For our project we have decided to use the OpenFlights dataset and plant to do the following:

* Find the optimal flight path between two airports.
  * The optimal path with the least connecting flights.
  * The optimal path with shortest distance.

* Find the most optimal traversal that visits every airport in the world with least repetition.

* Find the most important airport in each country, based on the number of links to the airport. 

If time permits:

* We would also like to visualize all optimal flight paths to Chicago from every other state on a USA map.

* We would also like to visualize the significance of major airports across the world by graphing the major airports in every country on a world map. We also plan to use color/size on the graphed points to compare the major airports in every country in the world. 


## Dataset Acquisition and Processing

* OpenFlights Dataset

### Data acquisition:
We will use the following datasets taken from OpenFlights.

* Airports: The airports dataset will provide us with the following information about each airport:

  * ID 
  * IATA/ICAO code
  * Name
  * City
  * Country
  * Latitude
  * Longitude
  * Altitude

* Routes: This routes dataset will tell us the following information for each route:

  * The Airline ID and IATA/ICAO code
  * Source Airport
  * Source Airport ID 
  * Destination Airport
  * Destination Airport ID

We will only be needing these datasets and the listed fields of the datasets to build our graph. 

With this data we will be able to construct a weighted directed graph with a set of vertices and edges such that the airports represent the vertices and the routes represent the edges of the graph. 

In particular, we will implement the graph to use an adjacency list for each vertex. The graph itself will contain an unordered map of vertices and an edge list. The vertices map will contain the ID of an airport as the key and a pointer to that Airport as value. The Airport class will internally store a vector with routes that point to the corresponding route in the edge list.

### Processing the data:

* The airprorts will represent the vertices of the graph. We will create a class for airports that will contain the data about its ID, its location i.e. latitude, longitude, altitude, its name, the city and country it is situated in, the number of airlines flying into and from that airport, and a vector of route pointers that contain that airport. 

* The routes will represent the graph edges. We will create a class for routes that will store the distance as the weight of the edge. It will also store the source and destination airports pointers and their IATA/ICAO codes.

* The 2-letter IATA or 3-letter ICAO codes will represent the id or keys of the airports.

* The latitude and longitude of airports will be stored in radians to simplify calculations for distance. We will use the Haversine formula to find the distance between two coordinates.

* Our graph class will contain a hash map that maps an airport ID to the airport pointer. This will allow us to quickly move around the grpah.

* We will also store a hash map that stores the keys as cities name and values as a vector of airports situated within that city. This can allow us to quickly access all of the airports in a particular city and will be useful for solving problems.

* We may want to store additional data as we see fit. 

## Graph Algorithms

We will be implementing the following algorithms and traversals with the graph.

* BFS: Breadth First Search Traversal - We will use BFS to traverse through all airports that have fligth connections (represented by nodes), with a given root airport. 

  * The BFS traversal can help us find the path between two airports with least connecting flights while the Dijsktra's algorithm can find the shortest path by taking into consideration the distance between airports.
  
  * We will find a path that starts from one airport and visits all other airports with the minimum repetition.

  * Input:
    - A graph of airports and routes. 
    - A start airport.

  * Output:
    - We will traverse through the graph and save the result into a file using a specific delimiter. 
    - We will also output the resulting path as a vector of airports.

  * Complexity:
    - O(|V| + |E|) where |V| = number of airports, |E| = number of routes.

* Dijkstra's Algorithm - This will help us find the shortest path between two airports. 

  * Input: 
    - A graph with airports as the vertices and routes as edges.
    - The start airport
    - The destination airport 

  * Output: 
    - The shortest path between the start and destination airport. It will be represented by a vector of airports.

  * Complexity: O(|E| + |V|log|V|) where |E| = number of edges and |V| = number of vertices in the graph. 
    - For our project, the number of edges is the same as the number of routes and the number of vertices is the same as the number of airports. 

  Note. 

  * The OpenFlights dataset has around 67663 routes between 3321 airports as of June 2014.

  * The airports will be represented by their respective 2-letter IATA or 3-letter ICAO code. The user must enter the correct code for the airport to the program to run the algorithm.

  * We will use the distance between airports as the weight of the edge. The distances will be computed by using the latitude and longtitude of the airports provided by the dataset. Thus, the airports will be stored in a priority queue by the magnitude of their distance from the current airport.

  * Page Rank: 

    * We will use this algorithm to find the most important airport in each country in the world.

    * We will rank the airports by placing the ones with more connections above the others.

    * Input:
      - A graph of airports and routes.

    * Output:
      - A list containing pairs of country and airport, which is the most important for that country.

    * Complexity: O(|V|+|E|)


## Timeline
* Finalizing specific project details and loading the dataset from csv files - one week (by 15th November)
* Represent the model with a Airport and Route, and initialise a graph with the data- one week (by 20th November)
* Run the required algorithms on the graph - two weeks (6th December)
* Generate PNG Image of flight path on a world map, work on final touches - one week (by 13th december)

(In the last 2 weeks, we will also allocate time to work on our final presentaion)

# Team Members
* Aarya Bhatia: @aaryab2
* Ananyaa Tanwar: @atanwar2
* Samiksha Arora: @arora21
