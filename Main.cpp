#include <iostream>
#include "Session.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    //Session sess(argv[1]);
    //sess.simulate();

    std::ifstream ifs("config1.json");
    json jf = json::parse(ifs);
    size_t mSize = jf["graph"].size();

    cout << mSize;
    return 0;
}


