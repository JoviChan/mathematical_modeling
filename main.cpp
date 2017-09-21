#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <iomanip>
#include "roadMap.h"

using namespace std;

roadMap testMap;
map<string, string> deletedF;
map<string, vector<string>> nearZCount;

void display() {
    testMap.drawPoints();
    testMap.drawLines();
    glFlush();
}

void displayNearest() {
    testMap.drawPoints();
    testMap.dijkstra(testMap.getNode("D1"));
    map<string, string> D1Path = testMap.getPath();
    map<double, string> D1nearF = testMap.getNearestF();
    int count = 0;
    for (auto &near : D1nearF) {
        if (count >= 12)
            break;
        if (count < 6)
            deletedF[near.second] = "c0" + to_string(count + 1);
        else if (count < 9)
            deletedF[near.second] = "B0" + to_string(count - 5);
        else
            deletedF[near.second] = "A0" + to_string(count - 8);
        //cout << near.second << " " << near.first << endl;
        stack<string> revPath;
        string temp = near.second;
        while (temp != "D1" && temp != "") {
            revPath.push(temp);
            temp = D1Path[temp];
        }
        string pathResult = "D1";
        string prev = "D1";
        while (!revPath.empty()) {
            string cur = (string)revPath.top();
            testMap.drawLine(testMap.getNode(prev), testMap.getNode(cur), 1, count * 0.08, (12 - count) * 0.08);
            pathResult += " " + cur;
            revPath.pop();
            prev = cur;
        }
        cout << deletedF[near.second] << " " << pathResult << endl;
        count++;
    }

    testMap.dijkstra(testMap.getNode("D2"));
    map<string, string> D2Path = testMap.getPath();
    map<double, string> D2nearF = testMap.getNearestF();
    count = 0;
    for (auto &near : D2nearF) {
        if (count >= 12)
            break;
        if (count < 6)
            deletedF[near.second] = "c0" + to_string(count + 7);
        else if (count < 9)
            deletedF[near.second] = "B0" + to_string(count - 2);
        else
            deletedF[near.second] = "A0" + to_string(count - 5);
        //cout << near.second << " " << near.first << endl;
        stack<string> revPath;
        string temp = near.second;
        while (temp != "D2" && temp != "") {
            revPath.push(temp);
            temp = D2Path[temp];
        }
        string pathResult = "D2";
        string prev = "D2";
        while (!revPath.empty()) {
            string cur = (string)revPath.top();
            testMap.drawLine(testMap.getNode(prev), testMap.getNode(cur), 1, count * 0.08, (12 - count) * 0.08);
            pathResult += " " + cur;
            revPath.pop();
            prev = cur;
        }
        cout << deletedF[near.second] << " " << pathResult << endl;
        count++;
    }
    glFlush();
    cout << endl;
}

void displaySecondPart() {
    testMap.drawPoints();
    for (auto &car : deletedF) {
        stack<string> revPath;
        testMap.dijkstra(testMap.getNode(car.first));
        map<string, string> Path = testMap.getPath();
        map<double, string> nearZ = testMap.getNearestZ();
        string pathResult = car.first;
        string prev = car.first;
        string temp;
        temp = nearZ.begin()->second;
        nearZCount[temp].push_back(car.second);
        int count = temp[temp.size() - 1] - 48;
        while (temp != car.first && temp != "") {
            revPath.push(temp);
            temp = Path[temp];
        }
        //cout << car.second << endl;
        while (!revPath.empty()) {
            string cur = (string)revPath.top();
            testMap.drawLine(testMap.getNode(prev), testMap.getNode(cur), count / 6, count * 0.15, (7 - count) * 0.15);
            pathResult += " " + cur;
            revPath.pop();
            prev = cur;
        }
        cout << car.second << " " << pathResult << endl;
    }
    glFlush();
    cout << endl;
}

void displayThirdPart() {
    testMap.drawPoints();
    for (auto &near : nearZCount) {
        sort(near.second.begin(), near.second.end(), greater<string>());
        for (int i = 0; i < near.second.size(); i++) {
            testMap.dijkstra(testMap.getNode(near.first));
            map<string, string> path = testMap.getPath();
            map<double, string> nearF = testMap.getNearestF();
            for (auto &nf : nearF) {
                if (deletedF.find(nf.second) != deletedF.end())
                    continue;
                deletedF[nf.second] = near.second[i];
                //cout << nf.second << " " << nf.first << endl;
                stack<string> revPath;
                string temp = nf.second;
                while (temp != near.first && temp != "") {
                    revPath.push(temp);
                    temp = path[temp];
                }
                string pathResult = near.first;
                int count = near.first[near.first.size() - 1] - 48;
                string prev = near.first;
                while (!revPath.empty()) {
                    string cur = (string)revPath.top();
                    testMap.drawLine(testMap.getNode(prev), testMap.getNode(cur), count / 6, count * 0.15, (7 - count) * 0.15);
                    pathResult += " " + cur;
                    revPath.pop();
                    prev = cur;
                }
                cout << near.second[i] << " " << pathResult << endl;
                break;
            }
        }
    }
    glFlush();
}



int main(int argc, char* argv[]) {
    ifstream pointsFile("/Users/v/Desktop/jianmo/code/points.csv");
    string line;

    while (getline(pointsFile, line)) {
        if (line.size() == 0 || line == ",,")
            continue;
        if (line[line.size() - 1] == '\r')
            line = line.substr(0, line.size() - 1);
        string id = line.substr(0, line.find(','));
        if (id == "")
            continue;
        line = line.substr(line.find(',') + 1);
        int x = atoi(line.substr(0, line.find(',')).c_str());
        int y = atoi(line.substr(line.find(',') + 1).c_str());
        node temp(id, x, y);
        testMap.addNode(temp);
    }

    pointsFile.close();

    ifstream sRoadFile("/Users/v/Desktop/jianmo/code/singleRoads.csv");

    while (getline(sRoadFile, line)) {
        if (line.size() == 0 || line == ",,")
            continue;
        if (line[line.size() - 1] == '\r')
            line = line.substr(0, line.size() - 1);
        string parent = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        while (line != "") {
            string child = line.substr(0, line.find(','));
            if (child == "") {
                if (line.find(',') == string::npos)
                    break;
                line = line.substr(line.find(',') + 1);
                continue;
            }
            testMap.addRoad(parent, child);
            testMap.addRelation(parent + child, true, true);
            if (line.find(',') == string::npos) {
                testMap.addRoad(parent, line);
                break;
            }
            line = line.substr(line.find(',') + 1);
        }

    }
    sRoadFile.close();

    ifstream dRoadFile("/Users/v/Desktop/jianmo/code/doubleRoads.csv");

    while (getline(dRoadFile, line)) {
        if (line.size() == 0 || line == ",,")
            continue;
        if (line[line.size() - 1] == '\r')
            line = line.substr(0, line.size() - 1);
        string parent = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        while (line != "") {
            string child = line.substr(0, line.find(','));
            if (child == "") {
                if (line.find(',') == string::npos)
                    break;
                line = line.substr(line.find(',') + 1);
                continue;
            }
            testMap.addRoad(parent, child);
            testMap.addRelation(parent + child, false, true);
            if (line.find(',') == string::npos) {
                testMap.addRoad(parent, line);
                break;
            }
            line = line.substr(line.find(',') + 1);
        }

    }
    dRoadFile.close();

    ifstream resultFile("/Users/v/Desktop/jianmo/code/result.txt");
    map<string, vector<string>> result;
    map<string, int> progress;
    double maxTime = 0.0;
    while (getline(resultFile, line)) {
        if (line == "")
            continue;
        if (line[line.size() - 1] == '\r')
            line = line.substr(0, line.size() - 1);
        string carId = line.substr(0, line.find(' '));
        line = line.substr(line.find(' ') + 1);
        while (line != "") {
            string child = line.substr(0, line.find(' '));
            if (child == "") {
                if (line.find(' ') == string::npos)
                    break;
                line = line.substr(line.find(' ') + 1);
                continue;
            }
            if (result.find(carId) == result.end() || (*(result[carId].end() - 1) != child))
                result[carId].push_back(child);
            if (line.find(' ') == string::npos) {
                break;
            }
            line = line.substr(line.find(' ') + 1);
        }
    }
    resultFile.close();
    for (auto &re : result) {
        cout << setiosflags(ios::fixed);
        cout << re.first;
        double time = 0.0;
        string preChild = "";
        int count = 0;
        for (auto &child : re.second) {
            cout << "," << child;
            if (preChild == "") {
                cout << "," << setprecision(1) << time;
            }
            else {
                double distance = testMap.distance(preChild, child);
                double speed;
                string key = preChild + child;
                if (!testMap.isSinglePath(key)) {
                    if (re.first[0] == 'A')
                        speed = 70;
                    else if (re.first[0] == 'B')
                        speed = 60;
                    else
                        speed = 50;
                }
                else {
                    if (re.first[0] == 'A')
                        speed = 45;
                    else if (re.first[0] == 'B')
                        speed = 35;
                    else
                        speed = 30;
                }
                time += (distance / speed) * 60.0;
                cout << "," << setprecision(1) << time;
                if (child[0] == 'F') {
                    progress[re.first] = count;
                    if (time > maxTime)
                        maxTime = time;
                    break;
                }
                cout << "," << setprecision(1) << time;
                count++;
            }
            preChild = child;
        }
        cout << endl;
    }
    double maxTime2 = 0.0;
    for (auto &re : result) {
        cout << setiosflags(ios::fixed);
        //cout << re.first;
        double time = maxTime;
        for (int i = progress[re.first] + 1; i < re.second.size(); i++) {
            if (i == progress[re.first] + 1) {
                cout << setprecision(1) << time;
            }
            else {
                cout << "," << re.second[i];
                double distance = testMap.distance(re.second[i-1], re.second[i]);
                double speed;
                string key = re.second[i-1] + re.second[i];
                if (!testMap.isSinglePath(key)) {
                    if (re.first[0] == 'A')
                        speed = 70;
                    else if (re.first[0] == 'B')
                        speed = 60;
                    else
                        speed = 50;
                }
                else {
                    if (re.first[0] == 'A')
                        speed = 45;
                    else if (re.first[0] == 'B')
                        speed = 35;
                    else
                        speed = 30;
                }
                time += (distance / speed) * 60.0;
                cout << "," << setprecision(1) << time;
                if (re.second[i][0] == 'Z')
                    time += 10;
                if (re.second[i][0] == 'F') {
                    cout << "," << "466.8";
                    break;
                }

                cout << "," << setprecision(1) << time;
            }
        }
        cout << endl;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("graph");
    glMatrixMode(GL_PROJECTION);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 150.0);
    glutDisplayFunc(display);


    glutCreateWindow("graph2");
    glMatrixMode(GL_PROJECTION);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 150.0);
    glutDisplayFunc(displayNearest);

    glutCreateWindow("graph3");
    glMatrixMode(GL_PROJECTION);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 150.0);
    glutDisplayFunc(displaySecondPart);

    glutCreateWindow("graph4");
    glMatrixMode(GL_PROJECTION);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 150.0);
    glutDisplayFunc(displayThirdPart);

    glutMainLoop();
    return 0;
}