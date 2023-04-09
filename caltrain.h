 #include <pthread.h>

struct station {
	// FILL ME IN
    pthread_cond_t can_leave ; // for train
    pthread_cond_t  Wait_till_arrive ; // foe passenger to wait till the train will come
    pthread_mutex_t mutex ;
    int available_seats  ;
    int waiting_passenger ;
    int departed_passengers ;

};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
