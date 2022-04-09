#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "io.h"
using namespace std;

int main()
{
    list<string> all_songs = get_all_songs();
    list<string> songsToSave;
    cout << "Welcome to the Karaoke Club" << endl;

    int numberOfPeopleToSing = rand() % 4 +1;
    for(int i=0; i< numberOfPeopleToSing; i++){
        cout<<"Which song would you like to sing?"<<endl;
        string choice;
        getline(cin, choice);
        if (listContains(all_songs, choice))
        {
            pid_t processId = fork();
            if (processId == 0)
            {
                cout<<"Now singing: "<<choice<<endl;
                sleep(10);
                cout<<"Singer is done!"<<endl;
                break;
            }
            else if(processId > 1) continue;
            else{
                throw "Forking failed";
            }
        }
        else{
            songsToSave.push_back(choice);
            
            cout<<"We don't have this song right now, would you like to try with another? [y,n]"<<endl;
            char choice;
            cin>>choice;
            cin.ignore();
            if (choice=='y')
            {
                i--;
                continue;
            }
            cout<<"Hope to see you soon, bye!"<<endl;
        }
        
    }

    int status=0;
    while(wait(&status)>0);
    saveSongs(songsToSave);
    return 0;
}


//get the number of people to sing
//in a loop, ask for the song of each one
    //if u have it -> child singing thread (add sleep timeout of 10 seconds)
    //if u dont, add it to the list and ask for another one

//save the songs you don't have
//wait for the children threads and exit wait()
