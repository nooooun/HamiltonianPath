#ifndef HAMILTONIANPATH_GRAPH_H
#define HAMILTONIANPATH_GRAPH_H

#endif //HAMILTONIANPATH_GRAPH_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{
    string point;
    vector<string>pos;
    Node*next;
    Node*prev;
    Node(string val, vector<string>&temp){
        point = val;
        next = nullptr;
        prev = nullptr;
        for(int i = 0;i < temp.size();i++){
            pos.push_back(temp[i]);
        }
    }
};

class Graph {
private:
    Node *head;
    Node *tail;
public:
    Graph() : head(nullptr), tail(nullptr) {}

    void add(Node &val) {
        Node *newNode = new Node(val);
        if (!head) {
            head = newNode;
            tail = head;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    friend ostream &operator<<(ostream &OS, Graph &g) {
        Node *currNode = g.head;
        while (currNode != nullptr) {
            OS << "Point: " << currNode->point << endl;
            OS << "Possible ways from point: " << endl;
            for (int i = 0; i < currNode->pos.size(); ++i) {
                OS << currNode->pos[i] << endl;
            }
            OS << endl;
            currNode = currNode->next;
        }
        delete[]currNode;
        return OS;
    }

    Node*getHead(){
        return head;
    }

    void createGraph(){
        vector<string>ways;
        string name;
        string way;
        do{
            cout << "Enter point(enter 'end' to end): ";
            cin >> name;
            if(name == "end"){
                continue;
            }
            do{
                cout << "Enter way from " << name << "(enter 'end' to end): ";
                cin >> way;
                if(way == "end"){
                    continue;
                }
                ways.push_back(way);
            }while(way != "end");
            Node newNode(name, ways);
            add(newNode);
            ways.clear();
        }while(name != "end");
    }

    Node* findNode(const string& nodeName){
        Node*temp = head;
        while(temp != nullptr){
            if(temp->point == nodeName){
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void HamiltonianRecursion(Node* current, Node* dest, vector<string>&path, vector<Node*>&visited, vector<string>&hamiltonianPath, int size){
        path.push_back(current->point);
        visited.push_back(current);

        if(path.size() == size and current->point == dest->point){
            hamiltonianPath = path;
            return;
        }

        for(auto a : current->pos){
            Node*newNode = findNode(a);
            if(newNode != nullptr and find(visited.begin(), visited.end(), newNode) == visited.end()){
                HamiltonianRecursion(newNode, dest, path, visited, hamiltonianPath, size);
            }
        }
        path.pop_back();
        visited.erase(find(visited.begin(), visited.end(), current));
    }
    vector<string> HamiltonialPath(string start, string finish){
        vector<string>path;
        vector<string>hamiltonianPath;
        vector<Node*>visited;
        Node* current = findNode(start);
        Node* dest = findNode(finish);
        int size = 0;
        Node*temp = head;
        while(temp != nullptr){
            size++;
            temp = temp->next;
        }
        HamiltonianRecursion(current, dest, path, visited, hamiltonianPath, size);
        return hamiltonianPath;
    }

    void PrintHamiltonianPath(){
        bool Hamilton = false;
        string start, finish;
        vector<string>path;
        createGraph();
        cout << "Enter starter point: ";
        cin >> start;
        cout << "Enter finish point: ";
        cin >> finish;
        path = HamiltonialPath(start, finish);
        if(path.size() != 0){
            Hamilton = true;
        }
        if(Hamilton){
            cout << "Hamiltonian path: ";
            for(auto a : path){
                cout << a;
            }
            cout << endl;
        }
        else{
            cout << "Hamiltonian path didn't found" << endl;
        }
    }
    void PrintAll() {
        bool Hamilton = false;
        vector<string> path;
        createGraph();
        Node *temp1 = getHead();
        Node *temp2 = getHead();
        while (temp1 != nullptr) {
            while (temp2 != nullptr) {
                if (temp1->point == temp2->point) {
                    temp2 = temp2->next;
                    continue;
                }
                path = HamiltonialPath(temp1->point, temp2->point);
                if (path.size() != 0) {
                    Hamilton = true;
                }
                if (Hamilton) {
                    cout << "Hamiltonian path from " << temp1->point << " to " << temp2->point << ": ";
                    for (auto a: path) {
                        cout << a;
                    }
                    cout << endl;
                } else {
                    cout << "There is no Hamiltonian path from " << temp1->point << " to " << temp2->point << endl;
                }
                temp2 = temp2->next;
                if (temp2 == nullptr) {
                    temp2 = getHead();
                    temp1 = temp1->next;
                }
            }
        }
    }
};
