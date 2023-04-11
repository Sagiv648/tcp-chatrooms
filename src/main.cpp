#include "../include/routines.hpp"
#include "../include/utils.hpp"
#include <sys/epoll.h>




//High level overview and steps of implementation for the app:

//1) The listener thread accepts the descriptor of the client,
// creates the pollfd structures for the fd and stores it in a vector.

//2) The manager (or another thread, depending on the behavior of poll) thread uses the poll() API to poll for incoming data,
// if data arrives the manager reads the message's header to know from the client
// the room he sent the message in and then passes the message to the respective Group class object.

//3) The respective Group class object enqueues the message for delivery.

//4) The workers begin dequeue the messages from the queues of the Group class objects
// and send them to the clients within the respective Group class object's current clients.






pthread_t listener;
pthread_t manager;

pthread_t workers[WORKERS_COUNT];
int socketFD;
sockaddr_in addr;
pthread_attr_t attr;

int main(){
    std::vector<int> x = std::vector<int>();
    
    socketFD = setupServer(addr);
    if(socketFD == -1)
        exit(EXIT_FAILURE);
    
    int detached = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(detached != 0)
        exit(EXIT_FAILURE);

    int listen = pthread_create(&listener,&attr,listenRoutine,NULL);
    if(listen != 0)
        exit(EXIT_FAILURE);
        
    
    for(int i = 0; i < WORKERS_COUNT; i++)
    {
        int work = pthread_create(&workers[i],&attr,workRoutine,NULL);
        if(work != 0)
            exit(EXIT_FAILURE);
    }
    printf("we run?\n");
    while (1)
    {
        //server operator shell
    }
    
    return 0;
}
