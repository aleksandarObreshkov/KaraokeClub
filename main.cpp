#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "io.h"
using namespace std;

int main()
{
    list<string> all_songs = get_all_songs();
    cout << "Welcome to the Karaoke Club" << endl;

    int numberOfPeopleToSing = rand() %4 +1;

    pid_t processId = fork();
    if (processId == 0)
    {
        cout << "Child";
        //add mutex around the cout<<"Now signing ..."
    }
    else {
        cout << "Parent"<<endl;
        //add mutex around the while() which reads the input for the song that will be sang
    }
    int status=0;
    while(wait(&status)>0);
    return 0;
}


//get the number of people to sing
//in a loop, ask for the song of each one
    //if u have it -> child singing thread (add sleep timeout of 10 seconds)
    //if u dont, add it to the list and ask for another one

//save the songs you don't have
//wait for the children threads and exit wait()
