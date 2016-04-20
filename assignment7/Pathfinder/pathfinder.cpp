//
//  pathfinder.cpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 16/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "pathfinder.hpp"

using namespace std;


// routine for loading new data file
void Pathfinder::loadFile() {
    
    while (true) {
        string file_path = "";
        cout << "Enter graph data filename or absolute path [RETURN to exit]: ";
        if (!getline(cin, file_path)) {
            if (cin.eof()) {
                cout << endl;
                loaded = false;
                return;
            }
        } else {
            // user hit return - exit
            if (file_path.length() == 0) {
                break;
            } else {
                ifstream infile;
                infile.open(file_path);
                if (infile.good()) {
                    graph_ptr = make_unique<Graph>(infile);
                    loaded = true;
                    cout << "File loaded successfully" << endl << endl;
                    return;
                } else {
                    cout << "Error opening the file, try again." << endl;
                    cin.ignore(10000, '\n');
                }
            }
        }
    }
}


// main loop
void Pathfinder::start() {
    cout << "PATHFINDER" << endl << endl;
    loadFile();
    while (loaded) {
        string user_choice;
        cout << "Your options:" << endl
        << "1. Print the graph" << endl
        << "2. Load other data file" << endl
        << "3. Find shortest path" << endl
        << "4. Compute minimal spanning tree" << endl
        << "5. Quit" << endl
        << "Choose your option (1-5): ";
        getline(cin, user_choice);
        cout << endl;
        if (user_choice == "1" || user_choice == "2" || user_choice == "3" || user_choice == "4" || user_choice == "5") {
            switch (stoi(user_choice)) {
                case 1:
                    graph_ptr->printGraph();
                    cout << endl;
                    break;
                case 2:
                    loadFile();
                    cout << endl;
                    break;
                case 3:
                    cout << "Shortest path" << endl;
                    shortestPath();
                    break;
                case 4:
                    cout << "Min spanning tree" << endl;
                    minSpanningTree();
                    break;
                case 5:
                    cout << "Bye!" << endl;
                    loaded = false;
                    return;
                default:
                    cout << "Choose 1-5" << endl;
                    break;
            }
            
        } else {
            if (cin.eof()) {
                cout << endl;
                return;
            }
            cout << "Choose 1-5, please" << endl << endl;
        }
    }
}


// shortest path wrapper
void Pathfinder::shortestPath() {
    string src, dest;
    while (true) {
        cout << "Please, choose the source node: ";
        getline(cin, src);
        if (graph_ptr->containsNode(src)) {
            break;
        } else {
            cout << "No such node in a given graph" << endl;
        }
    }
    while (true) {
        cout << "Please, choose the destination node: ";
        getline(cin, dest);
        if (graph_ptr->containsNode(dest)) {
            break;
        } else {
            cout << "No such node in a given graph" << endl;
        }
    }
    auto result = graph_ptr->dijkstra(src, dest);
    cout << "Shortest path between " << src << " and " << dest << " is: " << result.first << endl;
    cout << "The path is:" << endl;
    while (!result.second.empty()) {
        cout << result.second.top()->name << " ";
        result.second.pop();
    }
    cout << endl;
}


// min spanning tree wrapper
void Pathfinder::minSpanningTree() {
    cout << endl;
    auto min_tree = graph_ptr->kruskal();
    for (auto edge_ptr : min_tree) {
        edge_ptr->printEdge();
        cout << endl;
    }
    cout << endl;
}
