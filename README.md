# Dining Philosophers Problem
Classic synchronization and concurrency challenge.

### philo - Philosophers with threads and mutexes.

## How to compile
```
make
```
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat

1. number_of_philosophers: The number of philosophers and also the number
of forks.

2. time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the sim-
ulation, they die.

3. time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.

4. time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

5. number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies
```
## Error handling and testing
1. Use valgrind to check for memory leaks.

2. Use helgrind to check for possible data races, destroyed locked mutexes and so on.

3. Simple parsing(INT MAX, non-numeric,  more or less arguments)
## Main structure
1. Check arguments.

2. Initialize philosophers, forks and mutexes.

3. Start threads

4. Main loop (eat, sleep, think, die).
## How I store data
I use two structures. One for storing main data, the other one for philosophers.
```
typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				must_eat;
	int				philo_finish;
	int				is_dead;
	int				*forks_state;
	pthread_mutex_t	write_dead;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	long			start_time;
	long			last_meal;
	long			time_passed;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;
```

## Terminology (Threads and Mutexes)
### 1. Threads
Definition - a single sequence stream within a process.

Explanation - a thread is like a mini-program inside a bigger program that lets different tasks happen at the same time, making things work faster and smoother.
```
#include <pthread.h>
pthread_t myThread;

void *myThreadFunction(void *arg) // This function should take a single void * argument and return a void *
{
    printf("Hello from the new thread!\n");
    return (NULL);
}

pthread_create(&myThread, NULL, myThreadFunction, NULL) // creates a new thread
// 1. A pointer to a pthread_t variable
// 2. Attributes for the new thread. If NULL is passed, default attributes are used
// 3. A pointer to the function that will be executed by the new thread. This function should take a single void * argument and return a void *
// 4. The argument passed to the function

pthread_join(myThread, NULL) // allows a thread to wait for the termination of another thread.
// 1. The thread ID of the thread you want to wait for
// 2.  A pointer to a location where the exit status of the joined thread can be stored

pthread_detach(myThread) // detach a thread to release resourses
```
### 2. Mutexes
Definition - a lock that prevents multiple threads from accessing the same shared resource simultaneously.

Explanation - The point of a mutex is to synchronize two threads. When you have two threads attempting to access a single resource, the general pattern is to have the first block of code attempting access to set the mutex before entering the code. When the second code block attempts access, it sees that the mutex is set and waits until the first block of code is complete (and unsets the mutex), then continues.
```
#include <pthread.h>

pthread_mutex_t myMutex;

pthread_mutex_init(&myMutex, NULL) // initialises the mutex
pthread_mutex_lock(&myMutex) // locks a mutex and makes sure that only one thread at a time can access a section protected by the mutex.
pthread_mutex_unlock(&myMutex) // unlocks the mutex
pthread_mutex_destroy(&myMutex) // destroys mutex to avoid resource leaks
```
### 3. Extra
```
void *memset(void *str, int c, size_t n) // copies the character c to the first n characters of the str

void *malloc(size_t size) // allocates memory

void free(void *ptr) // frees memory

int usleep(useconds_t microseconds) // delay in the execution of a program for a specified number of microseconds

int gettimeofday(struct timeval *tv, struct timezone *tz) // retrieves the current time of day and the timezone information
// 1. A pointer to a struct timeval that will be filled with the current time
// 2. A pointer to a struct timezone that will be filled with the timezone 
```
## Terminilogy (Processes and Semaphores)

### 1. Processes
```
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int kill(pid_t pid, int sig) // sends signals to processes (SIGTERM (termination), SIGKILL (forceful termination) ...)
// 1. pid: The process ID of the target process.
// 2. sig: The signal to send.

pid_t waitpid(pid_t pid, int *status, int options) // waits for the termination of a child process
// 1. pid: The process ID of the child process to wait for.
// 2. status: A pointer to an integer where the exit status of the child process will be stored.
// 3. options: Additional options to control the behavior of waitpid.

pid_t fork(void) //  creates a new process
```
### 2. Semaphores
```
#include <semaphore.h>

sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value) // opens a semaphore
// 1. name: A string representing the name of the semaphore. This name must start with a forward slash ("/") and should be unique within the system.
// 2. oflag: Flags that control the behavior of the function (O_CREAT (create the semaphore if it doesn't exist)).
// 3. mode: The permissions to set when creating a new semaphore.
// 4. value: The initial value of the semaphore.

int sem_close(sem_t *sem) // closes a semaphore
// 1. sem: A pointer to the semaphore structure returned by sem_open.

int sem_post(sem_t *sem) // increments the value of a semaphore.
// 1. sem: A pointer to the semaphore structure.

int sem_wait(sem_t *sem) // decrements the value of a semaphore.
// 1. sem: A pointer to the semaphore structure.

int sem_unlink(const char *name) // removes a semaphore from the system.
// 1. name: A string representing the name of the semaphore to be unlinked.
```
### 3. Extra
```
#include <stdlib.h>

void exit(int status) // terminates a program or a specific process
// 1. The exit status of the program. 0 - success, 1 - failure.
```
