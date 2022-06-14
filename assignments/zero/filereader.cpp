#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void readFile() {
    cout << "Reading file..." << endl;
    ifstream objfile("sphere.obj");

    string line;

    while(getline(objfile, line)) {
        //cout << "Reading line..." << endl;
        istringstream isStream(line);
        
        string label;
        double val1, val2, val3;
        
        if(!(isStream >> label >> val1 >> val2 >> val3)) {
            continue;
        }

        if(label == "v") {
            cout << label << " line:" << endl;
            cout << "\t" << val1 << endl;
            cout << "\t" << val2 << endl;
            cout << "\t" << val3 << endl;
        }
    }
}
