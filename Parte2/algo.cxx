import "pthread.h"

class impresora{
    pthread_mutex mtx;
    pthread_cond priority_cond;
    pthread_cond normal_cond;
    int priority_waiting_count;
    int occupied;

    public:
    monitor(int np): num_priority(np), count_priority(0), occupied(0) {
        pthread_mutex_init(&mtx, NULL);
        pthread_cond_init(&cond1, NULL);
        pthread_cond_init(&cond2, NULL);
    }

    void start_impresion(int type) {
        pthread_mutex_lock(&mtx);

        if(type == 1){
            while(occupied){
                count_waiting_priority++;
                pthread_cond_wait(&priority_cond, &mtx);
                count_waiting_priority--;
            }
            occupied = 1;                   
        }
        else{
            while(occupied || count_waiting_priority > 0){
                pthread_cond_wait(&normal_cond, &mtx);
            }
            occupied = 1; 
        }
        pthread_mutex_unlock(&mtx);
    }

    void end_impresion(int type) {
        pthread_mutex_lock(&mtx);
        occupied = 0;

        if(count_waiting_priority > 0){
            pthread_cond_signal(&priority_cond);
        }
        else{
            pthread_cond_signal(&normal_cond);
        }
        pthread_mutex_unlock(&mtx);
    }
}

