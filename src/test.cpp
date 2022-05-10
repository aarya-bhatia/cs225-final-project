#include "../lib/acutest.hpp"
#include "Graph.h"
#include "GraphBuilder.h"
#include "PageRank.h"
#include "util.h"
#include "K.h"
#include "SCC.h"
#include "Logger.h"
#include <vector>
#include <stdlib.h> /* srand, rand */
#include <cstring>
#include <time.h>

void test_parse()
{
  std::vector<std::string> tokens = util::parse_line("1,\"AI127\",\"MAR 21\"");

  TEST_CHECK(tokens.size() == 3);

  TEST_CHECK(tokens[1].front() != '"');
  TEST_CHECK(tokens[1].back() != '"');
  TEST_CHECK(tokens[2].back() != '"');
  TEST_CHECK(tokens[2].back() != '"');

  TEST_CHECK(tokens[0] == "1");
  TEST_CHECK(tokens[1] == "AI127");
  TEST_CHECK(tokens[2] == "MAR 21");

  std::cout << util::to_string(tokens) << std::endl;

  tokens = util::parse_line("\"OurAirports\" 49,\"ORD\"");

  TEST_CHECK(tokens.size() == 2);
  TEST_CHECK(tokens[0] == "OurAirports 49");
  TEST_CHECK(tokens[1] == "ORD");

  std::cout << util::to_string(tokens) << std::endl;

  // Get tokens for example file
  std::vector<std::vector<std::string>> lines = util::parse_csv_file("res/names.csv");

  // Check if each line has equal number of columns
  for (size_t i = 0; i < lines.size() - 1; i++)
  {
    TEST_CASE_("%lu", i);
    TEST_CHECK(lines[i].size() == lines[i + 1].size());
  }

  TEST_CHECK(lines.size() == 3);
  TEST_CHECK(lines[0].size() == 2);
  TEST_CHECK(atoi(lines[0][0].c_str()) == 1);
  TEST_CHECK(lines[0][1] == "Aarya");
}

void test_big_graph()
{
  Graph<std::string, Airport> *g = GraphBuilder::build();

  TEST_CHECK(!g->edges.empty());
  TEST_CHECK(!g->vertices.empty());

  Edge<std::string> *r = g->edges.front();

  TEST_CHECK(g->has_vertex(r->source));
  TEST_CHECK(g->has_vertex(r->destination));

  Vertex<std::string, Airport> *u = g->vertices[r->source];
  Vertex<std::string, Airport> *v = g->vertices[r->destination];

  TEST_CHECK(u != nullptr);
  TEST_CHECK(v != nullptr);
  TEST_CHECK(u->is_adj(v));

  std::string src = "CMI";
  std::string dest = "SMF";

  g->bfs(src, dest);
  std::vector<std::string> path = g->path(src, dest); 
  std::cout << "Path(CMI,SMF): " << util::to_string(path) << std::endl;

  TEST_CHECK(g->has_vertex(src));
  TEST_CHECK(g->has_vertex(dest));
  TEST_CHECK(!g->vertices[src]->adj.empty());
  TEST_CHECK(!g->vertices[dest]->adj.empty());
  TEST_CHECK(!path.empty());
  TEST_CHECK(path.size() >= 2);
  TEST_CHECK(path.front() == src);
  TEST_CHECK(path.back() == dest);

  for (size_t i = 0; i < path.size() - 1; i++)
  {
    TEST_CASE_("Edge from %s to %s exists", path[i].c_str(), path[i + 1].c_str());
    TEST_CHECK(g->vertices[path[i]]->is_adj(g->vertices[path[i + 1]]));
  }

  g->dijkstra(src, dest);
  path = g->path(src, dest); 
  std::cout << "Dijkstra (CMI,SMF): " << util::to_string(path) << std::endl;

  delete g;
}

void test_scc_airports()
{
  Graph<std::string, Airport> *g = GraphBuilder::build();

  SCC<std::string, Airport> scc(g);
  scc.scc();

  std::vector<std::vector<std::string> > sccs = scc.get_components();

  size_t count = 0;
  size_t max_cluster = 0;

  Logger sccLogger("log/scc.txt");

  for(auto it = sccs.begin(); it != sccs.end(); it++)
  {
    sccLogger.print_line(util::to_string(*it));

    if((*it).size() > 1) 
    {
      count++;

      if(max_cluster < (*it).size())
      {
        max_cluster = (*it).size();
      }
    }
  }

  std::cout << "Total " << sccs.size() << " strongly connected components in airport graph." << std::endl;
  
  std::cout << count << " strongly connected components with more than one airport and " << (sccs.size() - count) << " components with single airports." << std::endl;

  std::cout << "The biggest cluster of airports contains " << max_cluster << " airports in it." << std::endl;

  Graph<std::string, Airport> *cg = scc.build_condensed_graph();

  Logger logger("log/condensed_graph.txt");

  for (auto it = cg->vertices.begin(); it != cg->vertices.end(); it++)
  {
    logger.print(it->first);
    logger.print("-> ");

    for (auto edgeItr = it->second->adj.begin(); edgeItr != it->second->adj.end(); edgeItr++)
    {
      logger.print((*edgeItr)->destination);
      logger.print(" ");
    }
    
    logger.print("\n");
  }

  delete cg;
  delete g;
}

void test_small_graph()
{
  Graph<char,int> g;

  g.create_vertex('A', 0);
  g.create_vertex('B', 0);
  g.create_vertex('C', 0);
  g.create_vertex('D', 0);
  g.create_vertex('E', 0);
  g.create_vertex('F', 0);

  Edge<char> *e1 = new Edge<char>('A', 'B');
  Edge<char> *e2 = new Edge<char>('A', 'C');
  Edge<char> *e3 = new Edge<char>('B', 'D');
  Edge<char> *e4 = new Edge<char>('B', 'E');
  Edge<char> *e5 = new Edge<char>('C', 'D');
  Edge<char> *e6 = new Edge<char>('C', 'E');
  Edge<char> *e7 = new Edge<char>('D', 'F');
  Edge<char> *e8 = new Edge<char>('E', 'F');

  e1->distance = 4;
  e2->distance = 2;
  e3->distance = 1;
  e4->distance = 4;
  e5->distance = 8;
  e6->distance = 7;
  e7->distance = 2;
  e8->distance = 2;

  g.vertices['A']->adj = std::list<Edge<char> *>{e1,e2};
  g.vertices['B']->adj = std::list<Edge<char> *>{e3,e4};
  g.vertices['C']->adj = std::list<Edge<char> *>{e5,e6};
  g.vertices['D']->adj = std::list<Edge<char> *>{e7};
  g.vertices['E']->adj = std::list<Edge<char> *>{e8};

  TEST_CHECK(g.vertices['A']->adj.front()->destination == 'B');
  TEST_CHECK(g.vertices['A']->adj.front()->source == 'A');
  TEST_CHECK(g.vertices['A']->adj.back()->destination == 'C');
  TEST_CHECK(g.vertices['A']->adj.back()->source == 'A');
  TEST_CHECK(g.vertices['B']->adj.front()->destination == 'D');
  TEST_CHECK(g.vertices['B']->adj.back()->destination == 'E');
  TEST_CHECK(g.vertices['C']->adj.front()->destination == 'D');
  TEST_CHECK(g.vertices['C']->adj.back()->destination == 'E');
  TEST_CHECK(g.vertices['D']->adj.front()->destination == 'F');
  TEST_CHECK(g.vertices['E']->adj.front()->destination == 'F');
  TEST_CHECK(g.vertices['A']->adj.size() == 2);
  TEST_CHECK(g.vertices['B']->adj.size() == 2);
  TEST_CHECK(g.vertices['C']->adj.size() == 2);
  TEST_CHECK(g.vertices['D']->adj.size() == 1);
  TEST_CHECK(g.vertices['E']->adj.size() == 1);
  TEST_CHECK(g.vertices['F']->adj.size() == 0);

  char src = 'A';
  char dest = 'F';
  
  g.bfs(src, dest);
  std::vector<char> bpath = g.path(src, dest); 
  std::cout << "BFS (A,F): " << util::to_string(bpath) << std::endl;
  
  std::vector<char> expected_path;

  TEST_CHECK(!bpath.empty());
  TEST_CHECK(bpath.front() == src);
  TEST_CHECK(bpath.back() == dest);

  expected_path= std::vector<char>{'A','B','D','F'};
  
  TEST_CHECK(bpath == expected_path);

  TEST_CHECK(g.vertices['A']->distance == 0);
  TEST_CHECK(g.vertices['B']->distance == 1);
  TEST_CHECK(g.vertices['C']->distance == 1);
  TEST_CHECK(g.vertices['D']->distance == 2);
  TEST_CHECK(g.vertices['E']->distance == 2);
  TEST_CHECK(g.vertices['F']->distance == 3);

  TEST_CHECK(g.vertices['A']->visited);
  TEST_CHECK(g.vertices['B']->visited);
  TEST_CHECK(g.vertices['C']->visited);
  TEST_CHECK(g.vertices['D']->visited);
  TEST_CHECK(g.vertices['E']->visited);
  TEST_CHECK(g.vertices['F']->visited);

  TEST_CHECK(g.vertices['A']->parent == nullptr);
  TEST_CHECK(g.vertices['B']->parent == g.vertices['A']);
  TEST_CHECK(g.vertices['C']->parent == g.vertices['A']);
  TEST_CHECK(g.vertices['D']->parent == g.vertices['B']);
  TEST_CHECK(g.vertices['E']->parent == g.vertices['B']);
  TEST_CHECK(g.vertices['F']->parent == g.vertices['D']);
  
  g.dijkstra(src, dest);
  std::vector<char> dpath = g.path(src, dest);
  std::cout << "Dijkstra (A,F): " << util::to_string(dpath) << std::endl;
  
  expected_path = std::vector<char>{'A','B','D','F'};
  TEST_CHECK(dpath == expected_path);

  TEST_CHECK_(g.path_length(bpath) >= g.path_length(dpath), "Length of path by BFS is not shorter than path by Dijkstra");

}

void test_scc()
{
  Graph<char, int> g;

  for(char c = 'A'; c <= 'F'; c++)
  {
    g.create_vertex(c, 0);
  }

  std::vector<std::vector<char> > edges{
    {'A','B'},
    {'B','C'},
    {'C','A'},
    {'B','D'},
    {'D','E'},
    {'E','F'},
    {'F','D'},
  };

  for(auto it = edges.begin(); it != edges.end(); it++)
  {
    g.create_edge((*it)[0],(*it)[1]);
  }

  Graph<char, int> *transpose = g.transpose();

  TEST_CHECK(transpose->vertices.size() == g.vertices.size());
  TEST_CHECK(transpose->edges.size() == g.edges.size());

  delete transpose;

  SCC<char, int> scc(&g);

  scc.scc();

  std::vector<std::vector<char> > sccs = scc.get_components();
  TEST_CHECK(sccs.size() == 2);

  for(auto it = sccs.begin(); it != sccs.end(); it++)
  {
    std::cout << util::to_string(*it) << std::endl;
  }

  Graph<char, int> *cg = scc.build_condensed_graph();

  std::cout << "Condensed Graph:\n";

  for(auto it = cg->vertices.begin(); it != cg->vertices.end(); it++)
  {
    std::cout << it->first << "-> ";
    for(auto edgeItr = it->second->adj.begin(); edgeItr != it->second->adj.end(); edgeItr++)
    {
      std::cout << (*edgeItr)->destination << " ";
    }
    std::cout << "\n";
  }

  delete cg;
}

void test_page_rank_big()
{
  Graph<std::string, Airport> *g = GraphBuilder::build();
  PageRank<std::string, Airport> page_rank(g);

  page_rank.solve();

  size_t top = 50;

  std::cout << "Top " << top << " Airports: " << std::endl;
  Logger log("log/page_rank_output.txt");

  std::vector<std::pair<float, std::string> > ranks = page_rank.get_ranks();

  // Write all to file and first 100 ranks to std out 
  for(size_t i = 0; i < ranks.size(); i++)
  {
    Vertex<std::string,Airport>*u = g->vertices[ranks[i].second];

    char line[100];
    sprintf(line, "%lu. %s, %s, %s: %f", i+1, u->key.c_str(), u->value.name.c_str(), u->value.city.c_str(), ranks[i].first);

    log.print_line(line);

    if(i < top) 
    {
      std::cout << std::string(line) << std::endl;
    }
  }

  delete g;
}

void test_page_rank()
{
  Graph<char, int> *g = new Graph<char, int>();

  g->create_vertex('A', 0);
  g->create_vertex('B', 0);
  g->create_vertex('C', 0);
  g->create_vertex('D', 0);

  g->create_edge('A', 'B');
  g->create_edge('A', 'C');
  g->create_edge('C', 'A');
  g->create_edge('B', 'D');
  g->create_edge('C', 'D');
  g->create_edge('D', 'C');

  PageRank<char, int> page_rank(g);

  page_rank.solve();
  page_rank.print();

  std::cout << "Page rank complete. " << std::endl;

  delete g;
}

TEST_LIST = {
  { "test_parse", test_parse },
  { "test_small_graph", test_small_graph },
  { "test_scc_airports", test_scc_airports },
  { "test_scc", test_scc },
  { "test_big_graph", test_big_graph },
  { "test_page_rank", test_page_rank },
  { "test_page_rank_big", test_page_rank_big },
  { nullptr, nullptr }
};
