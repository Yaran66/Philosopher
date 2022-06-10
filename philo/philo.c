//
// Created by Aleksey Tvorogov on 12/05/2022.
//
#include "includes/philo.h"

int	mails = 0;
pthread_mutex_t	mutex;

void*	routine()
{
	for (int i = 0; i < 10000000; i++){
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
//	printf("Test from threads\n");
//	sleep(3);
//	printf("Ending threads\n");
	return(0);
}

//int main(int argc, char* argv[])
//{
//	pthread_t t1, t2;
//	pthread_mutex_init(&mutex, NULL);
//	pthread_create(&t1, NULL, &routine, NULL); // last NULL this is parameter
//	// for our function routine
//	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
//	{
//		return 1;
//	}
//	pthread_join(t1, NULL); // similar to wait
//	pthread_join(t2, NULL);
//	pthread_mutex_destroy(&mutex);
//	printf("Number of emails %d\n", mails);
//	return (0);
//}

int main()
{
	pthread_t th[20];
	int	i;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 20; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return 1;
		}
		printf("thread %d has started\n", i);
	}
	for (i = 0; i < 20; i++)
	{
		if (pthread_join(th[i], NULL) != 0){
			return 2;
		}
		printf("thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of emails %d\n", mails);
	return (0);
}

//void* roll_dice() {
//	int value = (rand() % 6) + 1;
//	int* result = malloc(sizeof(int));
//	*result = value;
//	// printf("%d\n", value);
//	printf("Thread result: %p\n", result);
//	return (void*) result;
//}
//
//int main() {
//	int* res;
//	srand(time(NULL));
//	pthread_t th;
//	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
//		return 1;
//	}
//	if (pthread_join(th, (void**) &res) != 0) {
//		return 2;
//	}
//	printf("Main res: %p\n", res);
//	printf("Result: %d\n", *res);
//	free(res);
//	return 0;
//}