#include <algorithm>
#include <iostream>
#include <array>
#include <queue>
#include <list>
#include <sys/types.h>

const int N = 10;
using E_List = std::array<std::list<int>, N>;


void printEList(const E_List& eList) {
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << "List " << i << ": ";
        for (const int& value : eList[i]) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

std::list<int> BFS(E_List G, int v) {
  std::queue<int> Q;
  std::list<int> resultList;
  std::array<bool, N> markedNodes;
  std::fill(markedNodes.begin(), markedNodes.end(), false);

  // BFS ausführen
  Q.push(v);
  while(!Q.empty()) {
    v = Q.front();
    Q.pop();
    if (!markedNodes[v]) {
      markedNodes[v] = 1;
      resultList.push_back(v);
      
      for(int neighbour : G[v]) {
          Q.push(neighbour);
      }
    }
  }

  return resultList;
}




int main() {
 // Constructing a more complex graph
    E_List G;

    // Node 0 connections
    G[0].push_back(1);
    G[0].push_back(2);

    // Node 1 connections
    G[1].push_back(4);
    G[1].push_back(3);

    // Node 2 connections
    G[2].push_back(0);
    G[2].push_back(1);

    // Node 3 connections
    G[3].push_back(5);

    // Node 4 connections
    G[4].push_back(1);
    // Node 5 connections
    G[5].push_back(8);
    G[5].push_back(7);

    // Node 6 connections
    G[6].push_back(5);

    // Node 7 connections
    G[7].push_back(5);  // Node 4 connections
    G[7].push_back(8);
    // Node 8 connections
    G[8].push_back(9);
    G[8].push_back(5);
    G[8].push_back(7);
    
    // Node 9
    G[9].push_back(8);

    printEList(G);

    std::list<int> result = BFS(G, 0);

    for (const int& node : result) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}

