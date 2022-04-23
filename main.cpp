#include "io.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

#define SONG_NAME_LENGTH 100

using namespace std;

list<string> songsToSave;
list<string> all_songs;

typedef struct sing_arguments{
    string song_name;
}sing_arguments;

void sing(string song);
void saveMissingSong(string song);

int main()
{
    all_songs = get_all_songs();

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
        string a;
        for(;;)
        {
            read(p[0], &a, SONG_NAME_LENGTH);
            if (a != "killProcess")
            {
                sing(a);
            }
            else break;
        }
        //close(*p[0]);
        cout << "Closing the stage" << endl;
    }

    else 
    {
        for (int i = 0; i < numberOfPeopleToSing; i++)
        {
            cout << "Which song would you like to sing?" << endl;
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
                cout << "We don't have this song right now, would you like to try with another? [y,n]" << endl;
                char anotherSongFlag;
                cin >> anotherSongFlag;
                cin.ignore();
                if (anotherSongFlag == 'y')
                {
                    i--;
                    continue;
                }
                cout << "Hope to see you soon, bye!" << endl;
            }
        }
        write(p[1], "killProcess", SONG_NAME_LENGTH);
        saveSongs(songsToSave);
        //close(p[1]);
        
    }
    int status;
    while ((wait(&status)) > 0);
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
    cout << "Now singing: " << song << endl;
    sleep(3);
    cout << "Singer is done!" << endl;
}

