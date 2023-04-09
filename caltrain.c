#include <pthread.h>
#include "caltrain.h"
#include "stdio.h"


void station_init(struct station *station){
    station->available_seats = 0;
    station->waiting_passenger = 0;
    station->departed_passengers = 0;
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->Wait_till_arrive, NULL);
    pthread_cond_init(&station->can_leave, NULL);

}

void station_load_train(struct station *station, int count){
    pthread_mutex_lock(&station->mutex);
    station->available_seats = count;
    if(station->available_seats != 0 && station->waiting_passenger != 0) {
        pthread_cond_broadcast(&station->Wait_till_arrive);
        pthread_cond_wait(&station->can_leave, &station->mutex);
    }
    station->available_seats = 0;
    pthread_mutex_unlock(&station->mutex);
}

void station_wait_for_train(struct station *station){
    pthread_mutex_lock(&station->mutex);
    station->waiting_passenger++;
    while(station->available_seats == 0 || station->waiting_passenger == 0){
        pthread_cond_wait(&station->Wait_till_arrive, &station->mutex);
    }
    station->available_seats--;
    station-> waiting_passenger--;
    station->departed_passengers++;
    pthread_mutex_unlock(&station->mutex);
}

void station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->mutex);
    if((station->departed_passengers) != 0 )
        station->departed_passengers--;
    if(station->departed_passengers == 0 &&
       (station->available_seats== 0 || station->waiting_passenger == 0))
        pthread_cond_signal(&station->can_leave);
    pthread_mutex_unlock(&station->mutex);
}