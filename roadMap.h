//
// Created by jovichan on 2017/9/19.
//

#ifndef CODE_DRAW_H
#define CODE_DRAW_H

#include <vector>
#include <string>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <map>

using namespace std;

struct node {
    string id;
    int x, y;
    node(string a, int b, int c) {
        this->id = a;
        this->x = b;
        this->y = c;
    }
    node(){}
    bool operator < (const node &i) const {return x == i.x;}
};




class roadMap {
public:
    void drawLine(float x1, float y1, float x2, float y2);
    void drawLine(node st, node en);
    void drawLine(node st, node en, double red, double green, double blue);
    void drawPoint(float x, float y);
    void drawPoint(node nd);
    void drawPoints();
    void drawLines();
    void addNode(node nd);
    void addRoad(node st, node en);
    void addRoad(string st, string en);
    void addRelation(string key, bool isSingle, bool isVisit);
    void changeRelation(string key, bool isVisit);
    void clearNode();
    void clearRoad();
    void dijkstra(node start);
    double distance(node a, node b);
    double distance(string a, string b);
    map<string, string> getPath();
    map<double, string> getNearestF();
    map<double, string> getNearestZ();
    bool isSinglePath(string key);
    node getNode(string id);

private:
    map<string, node> allNodes;
    map<string, vector<string>> graph;
    map<string, pair<bool, bool>> linkRelation;   //isSingle, canVisit
    map<string, string> path;
    map<string, double> dis;
    map<double, string> nearestF;
    map<double, string> nearestZ;
};
#endif //CODE_DRAW_H


