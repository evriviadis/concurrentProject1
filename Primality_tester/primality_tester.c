#include "library.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*This is main. It assigns jobs to all threads created,
and tells them when it's time to finish.*/
int main(int argc, char* argv[]) {
    if(argc != 2){
        printf("Wrong number of args\n");
        return(-1);
    }

    int /* file_dir, i = 0, result, read=0, number,  */input;
    /* char *buffer; */
    int N = atoi(argv[1]), found_available_thread;
    thread_infoT** threads = (thread_infoT**) malloc(sizeof(thread_infoT*) * N);

    // Create and initialize threads
    for(int i = 0; i < N; i++){
        threads[i] = (thread_infoT*) malloc(sizeof(thread_infoT));
        
        threads[i]->finished = 0;
        threads[i]->available = 1;
        threads[i]->given_work = 0;
        threads[i]->terminate = 0;
        threads[i]->number_to_check = 0;
        
        if (pthread_create(&(threads[i]->thread_id), NULL, worker, threads[i]) != 0) {
            perror("Failed to create thread:");
            return 1;
        }
    }

/*  ///////////////////////////  ILOPOIHSH ME ANAGNOSI APO ARXEIO (lathos me bugs)///////////////////////////



    buffer = (char *)malloc(sizeof(char));
    file_dir = open(argv[2], O_RDONLY);

    while(1){
        result = my_read(file_dir, &buffer[i], 1, &read);
        //if(!result){
        //    perror("my_read");
        //    break;
        //}

        if(buffer[i] == '\0'){
            printf("brikame to telos tou file\n\n");
            close(file_dir);
            free(buffer);
            break;
            /////////   ME AYTO TON TROPO DEN DIABAZEI TO TELEYTAIO NUMBER FIX IT!!!  ////////////
        }
        
        if((buffer[i] == '\n') || (buffer[i] == ' ')){
            i = 0;
            number = atoi(buffer);

            //check the number
            found_available_thread = 0;
            while (!found_available_thread) {
                for (int j = 0; j < N; j++) {
                    if (threads[j]->available) {
                        threads[j]->number_to_check = number; // give input to the thread first! 
                        threads[j]->given_work = 1;          // and then start processing.
                        found_available_thread = 1;
                        break;
                    }
                }
            }
            buffer = (char *)realloc(buffer, sizeof(char));
        }else{
            i++;
            buffer = (char *)realloc(buffer,(i+1)*sizeof(char));
        }
    }
 */

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

    //Get input data and assign work to the threads
    printf("Enter integers (Ctrl+D to stop):\n");
    while (scanf("%d", &input) != EOF) {
        // loop to search until we find available thread
        found_available_thread = 0;
        while (!found_available_thread) {
            for (int i = 0; i < N; i++) {
                if(threads[i]->available){
                    threads[i]->number_to_check = input; // give input to the thread first! 
                    threads[i]->given_work = 1;          // and then start processing.
                    found_available_thread = 1;
                    threads[i]->available = 0;   
                    break;
                }
            }
        }
    }
    
    // After EOF wait for workers to finish their job
    for(int i = 0; i < N; i++){   
        if(threads[i]->available && !threads[i]->given_work){
            threads[i]->terminate = 1;
        }else{
            i--;
        }
    }

    //Free workers' memory and destroy them
    for(int i = 0; i < N; i++){
        if(threads[i]->finished){
            free(threads[i]);
        }else{
            i--;
        }
    }

    free(threads);
    return 0;
}
