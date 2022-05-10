# Goals

## Leading Question 

In this project, we wanted to explore the Open Flights dataset to gain insight into how air travel across nations is optimized. Our objective was to discover and analyze different factors that influence optimal flight paths. 

## Objectives

* Find an optimal flight route between any two airports based on two different metrics, which are as follows:
    * The optimal path based on the least number of connecting flights - found using a modified BFS traversal. 
    * The optimal path based on shortest distance - found using the Dijkstra's algorithm.
* Find the strongly connected components and build a condensed graph by shrinking each strongly connected component into a single component. 
* Find the most important airports using the Page Rank algorithm. The Page Rank provides a probability distribution of the likelihood of a person to visit each airport. 

## Dataset Overview

* OpenFlights Dataset

* We have chosen to use the [OpenFlights](https://openflights.org/data.html) dataset. 
* We used the Airports and Routes data from the OpenFlight dataset.
* Downloaded the files in the .csv format and saved them inside the res directory of our project.
* We get the following information from the Airports data:
    * Name of the airport
    * IATA code (3-letter)
    * ICAO code (4-letter)
    * City
    * Country
    * Latitude
    * Longitude
* We get the following information from the Routes data:
    * Source airport key
    * Destination airport key

## Data Processing

* The Airports dataset is used to create objects of type Airport which are used to create vertices of type Vertex&lt;std::string, Airport&gt;.
* The Routes dataset is used to create Edges of type Edge&lt;std::string&gt;.
* A graph of type Graph&lt;std::string, Airport&gt; is built using the vertices and edges defined above.  
* A GraphBuilder class is defined to handle the graph construction from the input files. The GraphBuilder class uses parsing functions pre-defined in the util namespace. 
* The parse_csv_line function splits each line into tokens separated by a comma. It skips the commas enclosed in quotes and also removes the quotes from a word. 
* The GraphBuilder initializes the three things - the vertices the edges, and the distances. 

* Graph:
   * A simple, directed and weighted graph is created after initializing the vertices, edges, and distances.
   * Vertices can be accessed in constant time since they are stored by a unordered_map from Key to Vertex pointer.
   * The adjacent edges can be accessed by our vertices in time proportional to the degree of the vertex. Only one vertex needs to store the pointer to the edge since vertices only store the outgoing edges. 
   * All our edge pointers are also maintained by the graph class for memory safety.


## Algorithms Overview

We implement the following algorithms on our graph: Breadth-first search, Dijkstra's Algorithm, Kosaraju's Strongly connected components algorithm, and Page Rank. The algorithms are described in more detail below.

## Breadth-First Search

The Breadth-First Search traversal is used to solve the problem of finding the shortest path between two airports with the least connecting flights. We do this by considering all costs of the edges to be equal to 1. So the shortest path will be the one with the least number of vertices. However, we can have many different BFS paths for our graph, it does not guarantee anything about the distances.

### Input

* source vertex key
* destination vertex key

### Output

* The BFS function is void. It only manipulates the data inside the vertices.
* The actual path is found by the path function. It is called using the same arguments given to BFS. The path function returns a vector of keys from the source to the destination vertex. These keys would be for the vertices visited in the path. 

* For invalid or non-existent path we return an empty vector.

### Complexity

* The complexity of BFS is O(V+E) where V = number of vertices and E = number of edges.

## Dijkstra's Algorithm

Dijkstra's algorithm is used to solve the problem of finding the shortest path by the distance between any two airports i.e vertices in the graph.

### Input

* Much like BFS, Dijkstra accepts the key to the source vertex and destination vertex.

### Output

* Dijkstra also changes the data of the vertices involved in the path. The path function follows up with Dijkstra to return the vector of keys with the actual path.
* For invalid or non-existent path we return an empty vector.

### Complexity

The complexity of Dijkstra is O(V+ElogV) where V = number of vertices and E = number of edges.

## Kosaraju's Algorithm

Kosaraju's Algorithm is used for finding the strongly connected components in a graph. We implement this algorithm in the SCC class defined in the file SCC.h. Kosaraju's algorithm is further used by the Condensation algorithm. This algorithm is implemented by the function SCC.

### Input

This algorithm accepts no parameters. Only during the initialization of an SCC instance, the constructor accepts the pointer to the graph we must work with. This graph is stored in the SCC class and used by the functions.

### Output

The SCC function finds and stores all the strongly connected components in the vector components in the SCC class. This can be accessed directly.

### Complexity

The complexity is O(V+E) where V = number of vertices and E = number of edges.

## Graph Condensation Algorithm

The graph condensation is a follow-up procedure for the SCC algorithm. It shrinks each strongly connected component into a single vertex identified by any one of the vertices of that component. All the edges are recreated between the condensed graph without creating duplicate edges. This function is implemented by the function build_condensed_graph in the SCC class. It uses the graph initialized with the constructor and strongly connected components found by the previous algorithm.  

### Input

No input.

### Output

The output is a graph of the same type as the original graph. The new graph is the condensed version of the graph.

### Complexity

The complexity is O(V+E) where V = number of vertices and E = number of edges.

## Page Rank

Page Rank algorithm is used to rank the vertices by their importance. The vertices store a rank variable that contains their final rank value. 

Our page rank implementation directly uses the definition of page rank. We sum up the value of page rank/degree for every vertex which has an edge to the current vertex. For this reason, we need an adjacency list for inbound edges. These are initialized at the start of the algorithm and stored directly in the vertices. The other thing to handle carefully is the case when a vertex has no outbound edges. In that case, its degree would be considered as N. Then, it would contribute 1/N times the current page rank, which would be smaller than other vertices as their degree << N.

### Input

The graph is provided as input to the constructor. The page rank function does not need arguments.

### Output

We print the 50 most popular airports in the world using page rank on the graph.

### Complexity

The worst-case complexity is O(k*V*E) where k is the number of iterations.

## Final Deliverables

* main
    * The makefile creates an executable called main in the project directory. The main program presents a command-line interface to test out the BFS and Dijkstra algorithm. It asks the user to enter the source and destination airport code. The code must be valid or there won't be output. Then it tries to find the path and print it to the console. The program repeats itself until it is terminated by pressing q or Control C.
* test
    * The test suit can be compiled with the help of the Makefile by the command 'make test'. It can be run with ./test. The program contains different test cases and also tests the other algorithms. For the SCC and Condensation algorithm, it creates an output file in the log directory. For Page Rank, we print the most popular airports onto the console and save the final state of the ranks to a file.

## Timeline
* Finalizing specific project details and loading the dataset from csv files - one week (by 15th November)
* Represent the model with an Airport and Route, and initialize a graph with the data- one week (by 20th November)
* Run the required algorithms on the graph - two weeks (6th December)
* Generate PNG Image of the flight path on a world map, work on final touches - one week (by 13th December)
