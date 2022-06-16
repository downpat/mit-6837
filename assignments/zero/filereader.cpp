#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<string> splitOnSlashes(string slashDelimited) {
    size_t firstSlashPos, secondSlashPos;
    vector<string> stringVec;

    //Get slash positions
    firstSlashPos = slashDelimited.find('/');
    secondSlashPos = slashDelimited.find('/', firstSlashPos + 1);
    
    //Get split strings
    stringVec.push_back(slashDelimited.substr(0, firstSlashPos));
    stringVec.push_back(slashDelimited.substr(firstSlashPos + 1, secondSlashPos - firstSlashPos - 1));
    stringVec.push_back(slashDelimited.substr(secondSlashPos + 1, string::npos));

    return stringVec;
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
            vector<string> faceAtts1 = splitOnSlashes(val1);
            cout << "\t\tvertex: " << faceAtts1[0] << endl;
            cout << "\t\t?:" << faceAtts1[1] << endl;
            cout << "\t\tnormal: " << faceAtts1[2] << endl;
            cout << "\ttriplet2: " << val2 << endl;
            vector<string> faceAtts2 = splitOnSlashes(val2);
            cout << "\t\tvertex: " << faceAtts2[0] << endl;
            cout << "\t\t?:" << faceAtts2[1] << endl;
            cout << "\t\tnormal: " << faceAtts2[2] << endl;
            cout << "\ttriplet3: " << val3 << endl;
            vector<string> faceAtts3 = splitOnSlashes(val3);
            cout << "\t\tvertex: " << faceAtts3[0] << endl;
            cout << "\t\t?:" << faceAtts3[1] << endl;
            cout << "\t\tnormal: " << faceAtts3[2] << endl;
        }
    }
}
