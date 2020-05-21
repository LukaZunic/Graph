#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<queue>
using namespace std;

template<typename T>
struct Graph{
    
    map<T,set<T>> neighborList;
    bool isDirected = false;

    map<T,bool> visited; // for dfs


    Graph(char is){
        if(is == 'D') isDirected = true; else if(is == 'U') isDirected = false;
    }

    void addVertex(int value){
        if(!neighborList.count(value))
            neighborList[value] = {}; 
    }

    void addEdge(int x, int y){
        if(isDirected){
            neighborList[x].insert(y);
        }else{
            neighborList[x].insert(y);
            neighborList[y].insert(x);
        }
    }

    void removeEdge(int x, int y){
        if(isDirected){
            neighborList[x].erase(y);
        }else{
            neighborList[x].erase(y);
            neighborList[y].erase(x);
        } 
    }

    vector<int> erased;

    void removeVertex(int x){

        vector<T> edg;

        erased.push_back(x);
          

        for(T n : this->neighborList[x]){
            edg.push_back(n);
        }
        for(auto i : edg){
            this->removeEdge(i,x);
            erased.push_back(i);
        }
        this->neighborList.erase(x);

    }


    void printGraph();
    void printEdges();

    void DFS(T s); 
    
    int numOfComponents(){
        int count = 0;
        for(auto i : this->neighborList){
            if(this->visited[i.first] == false){
                this->DFS(i.first);
                count++;
            }
        }
        this->visited.clear();
        return count;
    }

    bool isArticulationPoint(int point){
        
        int a,b;
        a = this->numOfComponents();
        this->removeVertex(point);
        b = this->numOfComponents();

        this->addVertex(erased[0]);

        for(int i = 1 ; i < erased.size(); i++){
            this->addEdge(erased[0], erased[i]);
        }
        
        return(b == a) ? false : true;
        
    }

    bool isBridge(int a, int b){

        if(this->neighborList[a].size() == this->neighborList[a].size() == 0){
            return true;
        }
        if(this->isArticulationPoint(a) && this->isArticulationPoint(b)){
            return true;
        }
        if( (this->isArticulationPoint(a) && this->neighborList[b].size() == 0) || (this->isArticulationPoint(b) && this->neighborList[a].size() == 0) ){
            return true;
        }
        

    }

};

template<class T>
void Graph<T>::printGraph(){
    cout << "Adjacency list:" << endl;
    for(auto i : neighborList){
        cout << i.first << ": ";
        for(auto neighbor : i.second) cout << neighbor << ",";
        cout << endl;
    }
}

template<class T>
void Graph<T>::printEdges(){
    cout << "Edge list:" << endl;
    for(auto v : neighborList){
        for(auto n : v.second){
            if(n > v.first && !isDirected){
                cout << "{" << v.first << "," << n << "}" << endl;
            }else if(isDirected){
                cout << "(" << v.first << "," << n << ")" << endl; 
            }  
        }
    }
}

template<class T>
void Graph<T>::DFS(T s){

    queue<T> Q;
    
    Q.push(s);

    for(auto v : this->neighborList){
        this->visited[v.first] = false;
    }
    this->visited[s] = true;

    T temp;
    while(!Q.empty()){
        temp = Q.front();
        Q.pop();
        

        for(auto i : this->neighborList[temp]){
            if(!this->visited[i]){
                Q.push(i);
                this->visited[i] = true;
            }
        }
    }   
}



