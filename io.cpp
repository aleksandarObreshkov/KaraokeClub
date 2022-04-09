#include "io.h"
using namespace std;

const string DJ_FILE_NAME = "dj.txt";

list<string> get_all_songs() {
    fstream fileReader;
    fileReader.open(DJ_FILE_NAME, ios::in);
    if (!fileReader.is_open())
    {
        throw "No DJ songs file available";
    }

    list<string> dj_songs;
    string data_read = "initLoop";
    while(!data_read.empty()){
        getline(fileReader, data_read);
        dj_songs.push_back(data_read);
    }

    fileReader.close();
    return dj_songs;
}