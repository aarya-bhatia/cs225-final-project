# Week 1
Nov 1 - Nov 8

* Made team contract and proposald. 
* We discussed about the algorithms to implement for the project and chose BFS, Dijkstra's and Page Rank. 
* We added the dataset csv files to the res folder. 
* We setup the makefile and test cases with a basic program.

# Week 2
Nov 8 - Nov 15

* Set up the classes for Graph,Airport,Route
* Created Logger to write to file
* Made utility functions to parse csv files correctly. We had to write our parse functions so that we could filter string from quotations and trim whitespaces.
* Began testing file io functions.
* Loaded datasets into graph.
* Testing graph for success in loading the datasets. 

# Week 3 
Nov 15 - Nov 22

* We wrote a function to do a bfs traversal of the entire graph and find the number of strongly connected components.
* Created a test suite to test our algorithms on a simple graph with a few vertices and edges.
* Created a traversal class to implement bfs on the graph. Finds the path between two airports in the graph with the least connecting flights. 

# Week 4
Nov 22 - 29

* Implemented function to compute distance between two latitude and longitutdes and used this to initialise edge weights.
* Implements dijkstra algorithm and tested on graph.
* Redesgined model with templated classes on separate branch. Then, merged with main branch. 
* Put the code for loading datasets in GraphBuilder namespace.
* Added helper functions to help with testing such as finding the path length of the path.
* Updated test suites and made them more thorough. We need to ensure path length by BFS >= path length by Dijkstra.
* We confirm BFS and Dijkstra are returning the correct path.

# Week 5
Nov 29 - Dec 6
* Implemented and tested strongly connected components algorithm
* Continue work on page rank
* We ran strongly connected components algorithm on our airport graph.
    * We found out that there were 9 components with multiple airports but 4470 components with single airport. 
    * The biggest cluster of airports has 3354 airports where each of those airports is reachable by another.
* Put the code for SCC in a new class.
* Implemented a condense graph function that uses the strongly connected components. It picks one element to be the 
representative for each component and creates a new graph with this strategy. Since all vertices in a component are
reachable by any other vertex in that component, they essentailly represent one vertex.
* Saved the output of strongly connected components and condensed graph in file using Logger class.

# Week 6
Dec 6 - Dec 13
* Started working on the GOALS.MD and RESULTS.MD for Final Presentation.
* Updated README.MD.
* Finished Page Rank. 
* Tested page rank on the graph to find the Top 100 Airports of the world.
* Fixed bugs in page rank. Use N as degree if vertex has degree 0 while evaluating the next iteration.
* Started working on PPT and adding content and images to GOALS/RESULTS.