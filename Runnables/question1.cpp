// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include <unordered_map>
// #include <cstdlib> 
// #include "../Algorithms/Dijkstra/Dijkstra.h" 
// using namespace std;

// int main() {
//     // std::cout << "Hello World";
//     const std::string filename = "USA-road-d.FLA.gr";
//     std::ifstream graphFile(filename);
//     if (!graphFile.is_open()) {
//         std::cerr << "Failed to open the graph file." << std::endl;
//         return 1;
//     }

//     std::string line;
//     bool readingEdges = false;
//     std::vector<std::vector<int> > adjacencyList;
//     std::vector<std::vector<int> > weightMap;

//     while (std::getline(graphFile, line)) {
//         if (line.empty()) {
//             continue; // Skip empty lines
//         }

//         if (line[0] == 'p') {
//             // This line contains information about the graph size
//             std::istringstream iss(line);
//             std::string token;
//             iss >> token; // Skip "p"
//             iss >> token; // Should be "sp"
//             int numVertices, numEdges;
//             iss >> numVertices >> numEdges;

//             // Initialize your graph data structure with the number of vertices
//             adjacencyList.resize(numVertices + 1); // Assuming 1-based indexing

//             readingEdges = true; // Start reading edges after this line
//         } else if (readingEdges) {
//             // This line contains an edge description
//             std::istringstream iss(line);
//             std::string token;
//             iss >> token; // Skip "a"
//             int source, target, weight;
//             iss >> source >> target >> weight;

//             // Add the edge to your graph data structure
//             adjacencyList[source].push_back(target); // Adjust for your graph representation

//             // If it's an undirected graph, you may want to add the reverse edge as well
//             // adjacencyList[target].push_back(source); 

//             // Store the weight in a separate data structure if needed
//             weightMap[source][target] = weight; 
//         }
//     }
//     int source=909, target=906;
//     cout<<weightMap[source][target];

//     // Close the graph file
//     graphFile.close();
//     return 0;
// }


#include <iostream>
#include <random>

#include "../Algorithms/Dijkstra/Dijkstra.h"

using namespace std;

int main() {
  // Load the Florida graph.
  Graph graph;
  graph.ReadDIMACS("florida.gr");

  // Initialize the random number generator.
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(0, graph.NumNodes() - 1);

  // Run Dijkstra's algorithm for 200 randomly selected source-destination pairs.
  int total_runtime = 0;
  for (int i = 0; i < 200; i++) {
    int source = dis(gen);
    int destination = dis(gen);

    // Start the timer.
    auto start = chrono::high_resolution_clock::now();

    // Run Dijkstra's algorithm.
    vector<int> path;
    int distance = graph.Dijkstra(source, destination, path);

    // Stop the timer.
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> runtime = end - start;
    total_runtime += runtime.count();

    // Print the results.
    cout << "Shortest path from " << source << " to " << destination << ": ";
    for (int node : path) {
      cout << node + 1 << " ";
    }
    cout << endl;
    cout << "Shortest path length: " << distance << endl;
  }

  // Print the total runtime.
  cout << "Total runtime in seconds for 200 random Dijkstra: " << total_runtime << endl;

  return 0;
}