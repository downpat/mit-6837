#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
using namespace std;

vector<int> faceTripletToVec(string faceTrip) {
    size_t firstSlashPos, secondSlashPos;

    //Get slash positions
    firstSlashPos = faceTrip.find('/');
    secondSlashPos = faceTrip.find('/', firstSlashPos + 1);
    
    //Get split strings
    string vertex = faceTrip.substr(0, firstSlashPos);
    string dunno = faceTrip.substr(
        firstSlashPos + 1,
        secondSlashPos - firstSlashPos - 1
    );
    string normal = faceTrip.substr(
        secondSlashPos + 1,
        string::npos
    );

    //Convert split strings to integers and add to final vector
    vector<int> intVec;
    intVec.push_back(stoi(vertex));
    intVec.push_back(stoi(dunno));
    intVec.push_back(stoi(normal));

    return intVec;
}

void printFaceVec(vector<int> face) {
    cout << "\t\tvertex: " << face[0] + 100 << "--" << typeid(face[0]).name() << endl;
    cout << "\t\t?:" << face[1] + 200 << "--" << typeid(face[1]).name() << endl;
    cout << "\t\tnormal: " << face[2] + 300 << "--" << typeid(face[2]).name() << endl;
}

void readFile() {
    cout << "Reading file..." << endl;
    ifstream objfile("sphere.obj");

    string line;

    while(getline(objfile, line)) {
        //cout << "Reading line..." << endl;
        istringstream isStream(line);
        
        string label;
        string val1, val2, val3;
        
        if(!(isStream >> label >> val1 >> val2 >> val3)) {
            continue;
        }

        if(label == "f") {
            cout << label << " line:" << endl;
            cout << "\ttriplet1: " << val1 << endl;
            vector<int> face1 = faceTripletToVec(val1);
            printFaceVec(face1);
            cout << "\ttriplet3: " << val2 << endl;
            vector<int> face2 = faceTripletToVec(val2);
            printFaceVec(face2);
            cout << "\ttriplet2: " << val3 << endl;
            vector<int> face3 = faceTripletToVec(val3);
            printFaceVec(face3);
        }
    }
}
