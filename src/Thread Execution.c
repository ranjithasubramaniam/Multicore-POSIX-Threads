#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
typedef struct _stage_t {
pthread_mutex_t m;
pthread_cond_t avail ; //Input data for this stage available ?
pthread_cond_t ready ; //Level ready for new data ?
int data_ready ; // != 0 , if current data is available
long data ; //Data
pthread_t thread ; //Thread_ID
struct _stage_t * next ;
} stage_t ;

typedef struct _pipe_t {
pthread_mutex_t m;
stage_t * head , * tail ; // First and last stage of the pipeline
int stages ; // Number of pipeline stages
int active ; // Number of active data elements
} pipe_t ;

int pipe_send ( stage_t * stage , long data ) { // Level and data to be passed
pthread_mutex_lock (& stage -> m);
{
    while ( stage -> data_ready ) // Wait for data consumption
        pthread_cond_wait (& stage -> ready , & stage ->m);
    stage -> data = data ;
    stage -> data_ready = 1;
    pthread_cond_signal (& stage -> avail );
}
pthread_mutex_unlock (& stage ->m);
}

void *pipe_stage ( void *arg )
{
    stage_t *stage = ( stage_t *) arg ;
    pthread_mutex_lock (&stage -> m) ;
    {
        while (1)
        {
            while (!stage -> data_ready ) // Wait for data
                pthread_cond_wait (&stage -> avail , & stage ->m);
            // Process data and pass it to successor stage
            pipe_send ( stage -> next , ( stage -> data + 1) );
            stage -> data_ready = 0; // Processing complete
            pthread_cond_signal (& stage -> ready );
        }
    }
    pthread_mutex_unlock (&stage -> m) ; // Never reached
}




int pipe_create ( pipe_t *pipe , int stages )  // to create the pipeline
{
    stage_t **link = & pipe -> head ;
    pthread_mutex_init (& pipe ->m , NULL );
    pipe -> stages = stages ; pipe -> active = 0;
    // Create stages + 1 stages , last stage for the result
    for ( int pi = 0; pi <= stages ; pi ++)
    {
        stage_t * new_stage = ( stage_t *) malloc ( sizeof ( stage_t ));
        pthread_mutex_init (& new_stage ->m , NULL );
        pthread_cond_init (& new_stage -> avail , NULL );
        pthread_cond_init (& new_stage -> ready , NULL );
        new_stage -> data_ready = 0;
        * link = new_stage ; // Setup of a linked list
        link = & new_stage -> next ;
    }
    *link = (stage_t*) NULL ;
    pipe -> tail = new_stage;
    // Create a thread for each stage except the last one
    for (stage_t * st = pipe_head; st -> next ; st = st -> next )
    	pthread_create (& st->thread , NULL , pipe_stage , st );
}

int pipe_start ( pipe_t * pipe , long v )
{
    pthread_mutex_lock (& pipe -> m );
    {
        pipe -> active ++;
    }
    pthread_mutex_unlock (& pipe -> m );
    pipe_send ( pipe -> head , v );
}
int pipe_result ( pipe_t * pipe , long * result )
{
    stage_t * tail = pipe -> tail ;
    int empty = 0;
    pthread_mutex_lock (& pipe -> m ) ;
    if ( pipe -> active <= 0)
        empty = 1;
    else
        pipe -> active --; // Pipeline empty : don 't remove , otherwise : remove
    pthread_mutex_unlock (& pipe -> m ) ;
    if ( empty ) return 0;
    pthread_mutex_lock (& tail ->m ) ;
    while (! tail -> data_ready ) // Wait for data
        pthread_cond_wait (& tail -> avail , & tail -> m);
    * result = tail -> data ;
    tail -> data_ready = 0;
    pthread_cond_signal (& tail -> ready );
    pthread_mutex_unlock (& tail -> m ) ;
    return 1;
}

int main ( int argc , char * argv [])
{
    pipe_t pipe ; // creating an object to the structure pipe_t
    long value , result ;
    char line [128];
    pipe_create (& pipe , 10) ; // pass the object and number of stages to the function
    // Program termination only in case of a parsing error or EOF
    while ( fgets ( line , sizeof ( line ) , stdin ) )
    {
        if (!* line ) continue ; // Ignore empty inputs
        if (! strcmp ( line , " = " ) )
        {
            if ( pipe_result (& pipe , & result ) )
                printf ( " % d \ n " , result ) ;
            else
                printf ( " ERROR :  Pipe  empty \ n " ) ;
        }
        else
        {
            if ( sscanf ( line , " %ld " , &value ) < 1)
                printf ( " ERROR :  Not  an  int \ n " ) ;
            else
                pipe_start (& pipe , value ) ;
        }
    }
    return 0;
}
*/
