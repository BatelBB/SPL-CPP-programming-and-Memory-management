#include <iostream>
#include "Session.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    Session sess(argv[1]);
    sess.simulate();

    json js = sess.writeJson();
    ofstream o("output.json");
    o << js << endl;
    
    return 0;
}


