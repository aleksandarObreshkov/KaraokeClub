#include "io.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

typedef struct sing_arguments{
    string song_name;
}sing_arguments;

void* sing(void* args);

void* logic(void* params){
    list<string> all_songs = get_all_songs();
    list<string> songsToSave;
    cout << "Welcome to the Karaoke Club" << endl;

    int numberOfPeopleToSing = rand() % 4 + 1;
    for (int i = 0; i < numberOfPeopleToSing; i++)
    {
        cout << "Which song would you like to sing?" << endl;
        string choice;
        getline(cin, choice);
        if (listContains(all_songs, choice))
        {
            pthread_t singer_thread;
            sing_arguments args;
            args.song_name = choice;
            pthread_create(&singer_thread, NULL, sing, (void *)&args);
            pthread_join(singer_thread, NULL);
        }
        else
        {
            songsToSave.push_back(choice);
            cout << "We don't have this song right now, would you like to try with another? [y,n]" << endl;
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'y')
            {
                i--;
                continue;
            }
            cout << "Hope to see you soon, bye!" << endl;
        }
    }

    int status = 0;
    while (wait(&status) > 0);
    saveSongs(songsToSave);
}

void* sing(void* params){
    sing_arguments* args = (sing_arguments*)params;
    cout << "Now singing: " << args->song_name << endl;
    sleep(10);
    cout << "Singer is done!" << endl;
}

int main()
{

    pthread_t parent;
    pthread_create(&parent, NULL, logic, NULL);
    pthread_join(parent, NULL);
    
    return 0;
}


