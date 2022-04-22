#include "io.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <mutex>

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SONGS_FIFO "songs_fifo"

using namespace std;

mutex mtx;


list<string> songsToSave;
list<string> all_songs;
list<pthread_t*> singers;

typedef struct sing_arguments{
    string song_name;
}sing_arguments;

void* sing(void* args);
void* logic(void* args);
void saveMissingSong(string song);
void handleThreadCreation(string song);

int main()
{
    all_songs = get_all_songs();

    cout << "Welcome to the Karaoke Club" << endl;

    int numberOfPeopleToSing = rand() % 4 + 1;
    mkfifo(SONGS_FIFO, 0666);

    int processId = fork();
    if (processId == 0)
    {
        //read a song name from the fifo file
        //sleep the thread for a certain amount of time
        int songsPipe = open(SONGS_FIFO, O_RDWR);
        for (;;)
        {
            string a;
            read(songsPipe, &a, sizeof(a));
            if (a == "kill")
            {
                break;
            }
            if (a!="")
            {
                cout << a << endl;
            }
            
        }
        
    }

    else 
    {
        //ask for a song name
        //if its there, write it to the FIFO file
        int songsPipe = open(SONGS_FIFO, O_RDWR);
        string a;
        cin>>a;
        write(songsPipe, &a, sizeof(a));
        
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

void* sing(void* params){
    mtx.lock();
    sing_arguments* args = (sing_arguments*)params;
    cout << "Now singing: " << args->song_name << endl;
    sleep(10);
    cout << "Singer is done!" << endl;
    mtx.unlock();
}


// for (int i = 0; i < numberOfPeopleToSing; i++)
        // {
        //     cout << "Which song would you like to sing?" << endl;
        //     string temp;
        //     getline(cin, temp);
        //     string choice = trimAndLower(temp);
        //     if (listContains(all_songs, choice))
        //     {
        //         pthread_t singer_thread;
        //         //singers.push_back(&singer_thread);
        //         sing_arguments args;
        //         args.song_name = choice;
        //         // the thread being created is different every time, but its saved in the same address, same for the struct
        //         pthread_create(&singer_thread, NULL, sing, &args);
        //         pthread_join(singer_thread, NULL);
        //     }
        //     else
        //     {
        //         saveMissingSong(choice);
        //         cout << "We don't have this song right now, would you like to try with another? [y,n]" << endl;
        //         char anotherSongFlag;
        //         cin >> anotherSongFlag;
        //         cin.ignore();
        //         if (anotherSongFlag == 'y')
        //         {
        //             i--;
        //             continue;
        //         }
        //         cout << "Hope to see you soon, bye!" << endl;
        //     }
        // }

        // saveSongs(songsToSave);
