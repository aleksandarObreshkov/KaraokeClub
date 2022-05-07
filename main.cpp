#include "io.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

#define SONG_NAME_LENGTH 50

using namespace std;

const string kill_command = "exit";
list<string> songsToSave;
list<string> all_songs;

typedef struct sing_arguments{
    string song_name;
}sing_arguments;

void sing(string song);
void saveMissingSong(string song);

int main()
{
    all_songs = getAllSongs();

    cout << "Welcome to the Karaoke Club" << endl;

    int numberOfPeopleToSing = rand() % 4 + 1;
    int p[2];
    if (pipe(p)<0)
    {
        cout << "Pipe unsuccessful"<<endl;
        exit(1);
    }

    pid_t processId = fork();
    if (processId == 0)
    {   
        while(true)
        {
            string a;
            read(p[0], &a, SONG_NAME_LENGTH);
            if (a.compare(kill_command)!=0)
            {
                sing(a);
            }
            else 
            {
                cout << "Stage: " <<"Closing..."<<endl;
                break;
            }
        }
    }

    else 
    {   
        for (int i = 0; i < numberOfPeopleToSing; i++)
        {
            cout << "DJ: " << "Which song would you like to sing?" << endl;
            string temp;
            getline(cin, temp);
            string choice = trimAndLower(temp);

            if (listContains(all_songs, choice))
            {
                write(p[1], &choice, SONG_NAME_LENGTH);
            }
            else
            {
                saveMissingSong(choice);
                cout << "DJ: " << "We don't have this song right now, would you like to try with another? [y,n]" << endl;
                char anotherSongFlag;
                cin >> anotherSongFlag;
                cin.ignore();
                if (anotherSongFlag == 'y')
                {
                    i--;
                    continue;
                }
                cout << "DJ: " << "Hope to see you soon, bye!" << endl;
            }
        }
        write(p[1], &kill_command, SONG_NAME_LENGTH);
        saveSongs(songsToSave);
        int status;
        cout << "DJ: "<<"Waiting for all performers to finish..." << endl;
        while ((wait(&status)) > 0);
        close(p[1]);
        close(p[0]);
    }
    
    return 0;
}

void saveMissingSong(string song){
    string result = trimAndLower(song);
    if (!listContains(songsToSave, result))
    {
        songsToSave.push_back(result);
    }
    
}

void sing(string song){
    cout << "Stage: " << "Now singing: " << song << endl;
    sleep(3);
    cout << "Stage: " << "Singer is done!" << endl;
}

