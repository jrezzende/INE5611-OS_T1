#include "controller.c"

int main(int argc, char* argv[]) {
	int counters_amount = atoi(argv[1]);//quantidade e guichês vem por parâmetros quando executa
	
	pthread_t generator;//thread função que cria cidadãos
	pthread_create(&generator, NULL, citizen_generator, NULL);
	
	//cria e incializa três filas
	citizen_queue[0] = make_queue(citizen_queue[0]);
	citizen_queue[1] = make_queue(citizen_queue[1]);
	citizen_queue[2] = make_queue(citizen_queue[2]);
	
	printf("Total counters (guiches): %i\n", counters_amount);
	pthread_t threads[counters_amount];//crias as threads guichês
	int thread_success;
	
	for (int i = 0; i < counters_amount; i++) {//cria as threads guichês
		thread_success = pthread_create(&(threads[i]), NULL, counter_thread, NULL);
		
		if (thread_success != 0)
			printf("Error while creating thread");
	}
	
	for (int join = 0; join < counters_amount; join++)
		pthread_join(threads[join], NULL);
	
	return 0;
}
