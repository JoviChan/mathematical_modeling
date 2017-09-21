//
// Created by jovichan on 2017/9/19.
//

#include "roadMap.h"

void roadMap::drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3f(0.0,0.0,0.5);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void roadMap::drawLine(node st, node en) {

    if (linkRelation[st.id + en.id].first) {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.5);
    }
    else {
        glLineWidth(4);
        glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
    }
    glVertex2f(st.x, st.y);
    glVertex2f(en.x, en.y);
    glEnd();
}

void roadMap::drawLine(node st, node en, double red, double green, double blue) {

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(red,green,blue);
    glVertex2f(st.x, st.y);
    glVertex2f(en.x, en.y);
    glEnd();
}

void roadMap::drawPoint(float x, float y) {
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.0,0.5,0.0);
    glVertex2f (x, y);
    glEnd();
}

void roadMap::drawPoint(node nd) {
    glPointSize(10);
    glBegin(GL_POINTS);
    if (nd.id[0] == 'F')
        glColor3f(0.0,1,0.0);
    else if (nd.id[0] == 'J')
        glColor3f(1.0,0.0,1.0);
    else if (nd.id[0] == 'Z')
        glColor3f(0.0,0.0,1);
    else
        glColor3f(0.5,0.5,0.5);
    glVertex2f (nd.x, nd.y);
    glEnd();
}

void roadMap::drawPoints() {
    for (auto it = this->allNodes.begin(); it != this->allNodes.end(); it++)
        drawPoint(it->second);
}

void roadMap::drawLines() {
    for (auto it = this->graph.begin(); it != this->graph.end(); it++) {
        for (auto nodeIt = it->second.begin(); nodeIt < it->second.end(); nodeIt++)
            drawLine(allNodes[it->first], allNodes[*nodeIt]);
    }
}

void roadMap::addNode(node nd) {
    this->allNodes[nd.id] = nd;
}
void roadMap::addRoad(node st, node en) {
    this->graph[st.id].push_back(en.id);
}

void roadMap::addRoad(string st, string en) {
    this->graph[st].push_back(en);
}

void roadMap::clearNode() {
    this->allNodes.clear();
}
void roadMap::clearRoad() {
    this->graph.clear();
}

void roadMap::addRelation(string key, bool isSingle, bool canVisit) {
    this->linkRelation[key] = {isSingle, canVisit};
}
void roadMap::changeRelation(string key, bool canVisit) {
    this->linkRelation[key].second = canVisit;
}

void roadMap::dijkstra(node start) {
    nearestF.clear();
    nearestZ.clear();
    path.clear();
    double inf=100000, min;
    string minId;
    map<string, bool> visited;
    for (auto &allNode : allNodes) {
        dis[allNode.first] = inf;
        visited[allNode.first] = false;
    }
    dis[start.id] = 0;
    visited[start.id] = true;
    for (auto it = graph[start.id].begin(); it < graph[start.id].end(); it++) {
        dis[*it] = distance(start.id, *it);
    }
    for (int i = 1; i < allNodes.size(); i++) {
        min = inf;
        for (auto &di : dis) {
            if(!visited[di.first] && di.second < min) {
                min = di.second;
                minId = di.first;
            }
        }
        if (minId[0] == 'F')
            nearestF[min] = minId;
        if (minId[0] == 'Z')
            nearestZ[min] = minId;
        visited[minId] = true;
        for (auto it = graph[minId].begin(); it < graph[minId].end(); it++) {
            double temp = distance(minId, *it);
            if (dis[*it] > min + temp) {
                path[*it] = minId;
                dis[*it] = min + temp;
            }
        }
    }
}

map<string, string> roadMap::getPath() {
    return path;
}

map<double, string> roadMap::getNearestF() {
    return nearestF;
}

map<double, string> roadMap::getNearestZ() {
    return nearestZ;
}

double roadMap::distance(node a, node b) {
    return sqrt(pow(double(a.x - b.x), 2) + pow(double(a.y - b.y), 2));
}

double roadMap::distance(string a, string b) {
    node aa = allNodes[a];
    node bb = allNodes[b];
    return distance(aa, bb);
}

node roadMap::getNode(string id) {
    return allNodes[id];
}

bool roadMap::isSinglePath(string key) {
    return linkRelation[key].first;
}