#pragma once
#include<iostream>
#include<climits>
#include<vector>
#include<queue>
#include<cmath>
#include<map>
#include<set>

using namespace std;

template<typename T>
struct DijkstraOUT{
    int shortestDistance;
    map<T,T> predecessorTree;
};


template<typename T>
struct weightedGraph{
    
    map<T, set<pair<T,int>>> neighborList;

    weightedGraph(){}

    void addVertex(int value){
        neighborList[value] = {}; 
    }

    void addEdge(T x, T y, int weight){

        neighborList[x].insert(pair<T,int>(y,weight));
        neighborList[y].insert(pair<T,int>(x,weight));

    }

    void removeEdge(T x, T y){

       int weight = weightOfEdge(x,y);
       neighborList[x].erase(pair<T,int>(y,weight));
       neighborList[y].erase(pair<T,int>(x,weight));

    }

    void emptyGraph(){
        neighborList = {};
    }

    void printGraph(){

        cout << "Adjacency list:" << endl;
        
        for(auto i : neighborList){
            cout << i.first << ": ";
            for(auto neighbor : i.second) cout << "(" << neighbor.first << "," << neighbor.second << ");";
            cout << endl;
        }
    }

    void printEdges(){

        cout << "Edge list:" << endl;

        for(auto vertex : neighborList)
            if(!vertex.second.empty()) 
                for(auto neighbors : vertex.second)
                    cout << "("<< vertex.first << "," << neighbors.first << ") - weight = " << neighbors.second << endl;
                
        
    }

    int weightOfEdge(T x, T y){

        for(auto i : neighborList[x]){
            if(i.first == y) return i.second;
        }
        throw "Edge doesn't exist";

    }
   
    int shortestPathLength(T x, T y){

        map<T, int> shortestDistanceToVertex;

        for(auto vertex : neighborList){
            shortestDistanceToVertex[vertex.first] = INT_MAX;
        }
        shortestDistanceToVertex[x] = 0;

        for(auto v : neighborList){
            for(auto n : v.second){
                
                if(shortestDistanceToVertex[n.first] > shortestDistanceToVertex[v.first] + weightOfEdge(v.first,n.first)){
                    shortestDistanceToVertex[n.first] = shortestDistanceToVertex[v.first] + weightOfEdge(v.first,n.first);
                }
            
            }
        }

        return shortestDistanceToVertex[y];
    }

    bool BellmanFordNegativeCycle(){

        map<T, int> shortestDistanceToVertex;

        for(auto vertex : neighborList){
            shortestDistanceToVertex[vertex.first] = INT_MAX;
        }

        for(auto v : neighborList){
            for(auto n : v.second){
                
                if(shortestDistanceToVertex[n.first] > shortestDistanceToVertex[v.first] + weightOfEdge(v.first,n.first)){
                    shortestDistanceToVertex[n.first] = shortestDistanceToVertex[v.first] + weightOfEdge(v.first,n.first);
                }
               
            }
        }

        for(auto v : neighborList){
            for(auto n : v.second){
                
                if(shortestDistanceToVertex[n.first] > shortestDistanceToVertex[v.first] + weightOfEdge(v.first,n.first) && shortestDistanceToVertex[v.first] < 10000){
                    return true;
                }
            
            }
        }

        return false;

    }
    /*
    int Dijkstra(T s, T f){

        //initialize single source
        map<T, int> d;
        map<T,T> predecessor;

        for(auto v : neighborList){ 
            d[v.first] = 10000; 
            predecessor[v.first] = -1;
        }
        d[s] = 0;
        ///

        vector<T> S;
        priority_queue<T> Q;
        for(auto v : neighborList){ Q.push( -1 * v.first ); }

        while(!Q.empty()){
            
            T u = -1 * Q.top();
            Q.pop();

            S.push_back(u);
            
            for(auto neighbor : neighborList[u]){
                if(d[neighbor.first] > d[u] + weightOfEdge(u,neighbor.first)){
                    d[neighbor.first] = d[u] + weightOfEdge(u,neighbor.first);
                    predecessor[neighbor.first] = u;
                }
            }
        }

        return d[f];
    }*/


    DijkstraOUT<T> Dijkstra(T s, T f){

        //initialize single source
        map<T, int> d;
        map<T,T> predecessorTree;

        for(auto v : neighborList){ 
            d[v.first] = 10000; 
            predecessorTree[v.first] = -1;
        }
        d[s] = 0;
        ///

        vector<T> S;
        priority_queue<T> Q;
        for(auto v : neighborList){ Q.push( -1 * v.first ); }

        while(!Q.empty()){
            
            T u = -1 * Q.top();
            Q.pop();

            S.push_back(u);
            
            for(auto neighbor : neighborList[u]){
                if(d[neighbor.first] > d[u] + weightOfEdge(u,neighbor.first)){
                    d[neighbor.first] = d[u] + weightOfEdge(u,neighbor.first);
                    predecessorTree[neighbor.first] = u;
                }
            }
        }

        return {d[f], predecessorTree};
    }

};