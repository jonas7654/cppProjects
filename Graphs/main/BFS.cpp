#include <algorithm>
#include <iostream>
#include <array>
#include <queue>
#include <list>
#include <tuple>
#include <utility>

const int N = 10;
using E_List = std::array<std::list<int>, N>;


void printEList(const E_List& eList) {
    for (int i = 0; i < N; ++i) {
        std::cout << "List " << i << ": ";
        for (const int& value : eList[i]) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

std::tuple<std::array<int, N>, std::array<int, N>, std::array<int,N>> BFS(E_List G, int v) { 

  std::tuple<std::array<int, N>, std::array<int, N>, std::array<int,N>> results;
  std::queue<int> Q;
  std::array<int, N> resultList;
  std::array<int, N> parent;
  std::array<int, N> layer;
  std::fill(parent.begin(), parent.end(), -1); // -1 => not visited
  // BFS ausführen


  int index = 0;
  Q.push(v);
  layer[v] = 0;
  parent[v] = v;
  
  while(!Q.empty()) {
    v = Q.front();
    Q.pop();
    
      resultList[index++] = v;

      for(int neighbour : G[v]) {
          if (parent[neighbour] == -1) {
          Q.push(neighbour);
          parent[neighbour] = v;
          layer[neighbour] = layer[v] + 1;
        }
      }
  }

  results = std::make_tuple(resultList, parent, layer);
  return results;
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
    G[5].push_back(6);

    // Node 6 connections
    G[6].push_back(5);

    // Node 7 connections
    G[7].push_back(5);  // 
    G[7].push_back(8);
    // Node 8 connections
    G[8].push_back(9);
    G[8].push_back(5);
    G[8].push_back(7);
    
    // Node 9
    G[9].push_back(8);

    printEList(G);

    auto result = BFS(G,0);

    std::cout << "Pre Order: ";
    for (int i = 0; i < N; i++) {
        std::cout << std::get<0>(result)[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Predecessors: ";
    for (int i = 0; i < N; i++) {
        std::cout << std::get<1>(result)[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Levels: ";
    for (int i = 0; i < N; i++) {
        std::cout << std::get<2>(result)[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

