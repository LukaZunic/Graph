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


    }

    void removeEdge(T x, T y){

       int weight = weightOfEdge(x,y);
       neighborList[x].erase(pair<T,int>(y,weight));

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

    int** Floyd_Warshall(){

        int numOfV = neighborList.size();
        int** matrix = new int*[numOfV];
      
        for(int i = 0; i < numOfV; i++){
            matrix[i] = new int[numOfV];
        }

        for(int i = 0; i < numOfV; i++){
            for(int j = 0; j < numOfV; j++){

                if(i == j) matrix[i][j] = 0;

                if(i != j){

                    try{
                        matrix[i][j] = weightOfEdge(i+1,j+1);
                    }catch(const char* err){
                        matrix[i][j] = 10000;
                    }

                }
            }
        }

        for(int k = 0 ; k < numOfV; k++){

            for(int i = 0; i < numOfV; i++){

                for(int j = 0; j < numOfV; j++){

                    if(matrix[i][j] > matrix[i][k] + matrix[k][j])
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
        
        return matrix;
    }




};