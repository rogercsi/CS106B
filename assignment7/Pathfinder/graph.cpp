//
//  graph.cpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 14/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//


#include <fstream>
#include <sstream>
#include <stack>
#include <unordered_set>
#include "graph.hpp"
#include "pqueue.hpp"

using namespace std;

// default ctor
Graph::Graph()
: g({}) { }


// ctor from input filestream
Graph::Graph(ifstream &infile)
: g({}) {
    string str = "";
    while (getline(infile, str)) {
        if (str == "NODES") {
            // read all the nodes
            while (getline(infile, str)) {
                if (str == "ARCS") {
                    break;
                } else {
                    stringstream input(str);
                    string node_name;
                    input >> node_name;
                    g[node_name] = make_shared<GNode>(node_name);
                }
            }
        }
        if (str == "ARCS") {
            // read all the arcs
            while (getline(infile, str)) {
                stringstream input(str);
                string node1, node2;
                double weight;
                input >> node1 >> node2 >> weight;
                // add two edges
                g.at(node1)->edges.push_back(GEdge(weight, g.at(node1), g.at(node2)));
                g.at(node2)->edges.push_back(GEdge(weight, g.at(node2), g.at(node1)));
            }
        }
    }
}


// prints the graph to stdout
void Graph::printGraph() const {
    for (auto node : g) {
        node.second->printNode();
        cout << endl;
    }
}


// implements Dijkstra algorithm to find the shortest path between two nodes
// returns a pair of distance and a stack representing a path
pair<double, stack<shared_ptr<GNode>>> Graph::dijkstra(const string &src, const string &target) const {
    // create map of distances, a stack to keep an optimal path and a set to keep track of enqueued nodes
    unordered_map<string, double> distances{};
    unordered_map<string, string> prev{};
    stack<shared_ptr<GNode>> path;
    unordered_set<string> visited_nodes{}, enq_nodes{};
    
    // set distance to source to 0, to all other nodes to infinity
    for (auto node : g) {
        distances[node.first] = 999999999999.99;
        prev[node.first] = "";
    }
    distances[src] = 0.0;
    
    // create priority queue
    PQueue<shared_ptr<GNode>, double> pq((less<double>()));
    pq.enqueue(make_shared<GNode>(*g.at(src)), 0.0);
    enq_nodes.insert(g.at(src)->name);
    
    while (!pq.isEmpty()) {
        auto v = pq.dequeueMax();
        visited_nodes.insert(v->name);
        if (v->name == target)
            break;
        for (auto edge : v->edges) {
            auto org_ptr = edge.origin.lock();
            auto dest_ptr = edge.dest.lock();
            if (visited_nodes.find(dest_ptr->name) == visited_nodes.end()) {
                auto alt = distances.at(v->name) + edge.weight;
                if (alt < distances.at(dest_ptr->name)) {
                    distances.at(dest_ptr->name) = alt;
                    prev[dest_ptr->name] = v->name;
                    if (enq_nodes.find(dest_ptr->name) == enq_nodes.end()) {
                        pq.enqueue(make_shared<GNode>(*dest_ptr), alt);
                        enq_nodes.insert(dest_ptr->name);
                    }
                }
            }
        }
    }
    
    // construct the path
    path.push(make_shared<GNode>(*g.at(target)));
    auto i_str = prev.at(target);
    while (i_str != "") {
        path.push(make_shared<GNode>(*g.at(i_str)));
        i_str = prev.at(i_str);
    }
    
    return make_pair(distances.at(target), path);
}


// kruskal algorithm - minimal spanning tree
// returns vector of shared pointers to graph edges that form the min spanning tree
vector<shared_ptr<GEdge>> Graph::kruskal() const {
    // vector to store results
    vector<shared_ptr<GEdge>> result;
    
    // create two helper maps - from node names to id's and from id's to vector of node names
    unordered_map<string, int> name_to_id{};
    unordered_map<int, vector<string>> id_to_names{};
    int id_counter = 0;
    
    // put all edges to PQueue, populate helper maps
    PQueue<shared_ptr<GEdge>, double> pq((less<double>()));
    for (auto elt : g) {
        for (auto edge : elt.second->edges) {
            pq.enqueue(make_shared<GEdge>(edge), edge.weight);
        }
        name_to_id[elt.first] = id_counter;
        id_to_names[id_counter] = { elt.first };
        ++id_counter;
    }
    
    // main section
    while (!pq.isEmpty()) {
        auto edge_ptr = pq.dequeueMax();
        auto org_ptr = edge_ptr->origin.lock();
        auto dest_ptr = edge_ptr->dest.lock();
        // if different id's of origin and destination, two nodes belong to different sets
        int origin_old_id = name_to_id.at(org_ptr->name);
        int dest_old_id   = name_to_id.at(dest_ptr->name);
        if (origin_old_id != dest_old_id) {
            // add to resulting vector
            result.push_back(edge_ptr);
            
            // get new id
            ++id_counter;
            
            // create new vector for new id
            id_to_names[id_counter] = {};
            
            // assign to both vectors of nodes new id, populate new_vec
            for (auto node_name : id_to_names.at(origin_old_id)) {
                name_to_id.at(node_name) = id_counter;
                id_to_names.at(id_counter).push_back(node_name);
            }
            for (auto node_name : id_to_names.at(dest_old_id)) {
                name_to_id.at(node_name) = id_counter;
                id_to_names.at(id_counter).push_back(node_name);
            }
            
            // get rid of old values
            id_to_names.erase(origin_old_id);
            id_to_names.erase(dest_old_id);
        }
    }
    
    return result;
}