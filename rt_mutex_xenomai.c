/*
 *
 * Filename: rt_mutex_xenomai.c                                                                           
 *                
 * Purposet: Test and demonstrate how to use real time mutex in Xenomai. 
 *                    
 * Date:     January 2013
 *
 * Comments: "Xenomai is a real-time development framework cooperating with the Linux kernel,
 * in order to provide a pervasive, interface-agnostic, hard real-time support
 * to user-space applications, seamlessly integrated into the GNU/Linux environment."
 * (source: www.xenomai.org)
 * This short program aims to demonstrate how to use real time mutex in Xenomai. 
 * It is tested on a ARM developement platform embedding a minimal linux system.
 * A RS-232 to USB cable allows to controle the board from the development computer.
 * The module is build using a cross-toolchaine created with Buildroot. 
 *     
 */

/*---- Includes ----*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

/*---- Xenomai includes ----*/

#include <rtdk.h>
#include <native/task.h>
#include <native/timer.h>
#include <native/mutex.h>


// Declare a mutex

static RT_MUTEX mutex; 

// task1 routine

void thread1 (void * unused)
{
	rt_printf("task1 starts\n");
	rt_printf("task1 is waiting for the mutex\n");
	rt_mutex_acquire(& mutex, TM_INFINITE); 
	rt_printf("task1 is doing some work ...\n");
	rt_timer_spin(1000000000LLU);
	rt_printf("task1 has finished its work\n"); 
	rt_printf("task1 release mutex\n"); 
	rt_mutex_release(& mutex);
	
	
}

// task2 routine

void thread2 (void * unused)
{
	rt_printf("task2 starts\n");
	rt_printf("task2 is waiting for the mutex\n");
	rt_mutex_acquire(& mutex, TM_INFINITE); 
	rt_printf("task2 is doing some work ...\n");
	rt_timer_spin(3000000000LLU);
	rt_printf("task2 has finished its work\n"); 	
	rt_printf("task1 release mutex\n"); 
	rt_mutex_release(& mutex);
}

int main(void)
{
	int err;
	RT_TASK task1, task2; 
	
	// To avoid page fault 

	mlockall(MCL_CURRENT|MCL_FUTURE);
	
	// To start rt print buffers 
	
	rt_print_auto_init(1);
	
	// Create mutex
 
	if((err = rt_mutex_create(& mutex, "rtXenoMutex")) != 0) 
	{
		fprintf(stderr, "rt_mutex_create: %s\n", strerror(-err));
		exit(EXIT_FAILURE);
	}
	
	// Create and start task1 

	if((err = rt_task_spawn(& task1, "task1", 0, 99, T_JOINABLE, thread1, NULL)) != 0) 
	{
		fprintf(stderr, "rt_task_spawn: %s\n", strerror(-err));
		exit(EXIT_FAILURE);
	}

	// Create and start task2

	if((err = rt_task_spawn(& task2, "task2", 0, 99, T_JOINABLE, thread2, NULL)) != 0) 
	{
		fprintf(stderr, "rt_task_spawn: %s\n", strerror(-err));
		exit(EXIT_FAILURE);
	}	
	
	rt_printf("Waiting the end of task1 and task2...\n");
	rt_taskjoin(& task1);
	rt_taskjoin(& task2);

	// Cleaning
 	
	rt_mutex_delete(& mutex); 	

	return 0;
}



/*
 * End of file     
 */



