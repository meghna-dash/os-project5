#include <unistd.h>
#include <types.h>
#include <kern/unistd.h>
#include <kern/errno.h>
#include <lib.h>
#include <addrspace.h>
#include <thread.h>
#include <curthread.h>
#include <vm.h>
#include <vfs.h>
#include <test.h>

/*
 * fork duplicates the currently running process. The two copies are identical,
 * except that one (the "new" one, or "child"), has a new, unique process id,
 * and in the other (the "parent") the process id is unchanged.
 *
 * The process id must be greater than 0.
 *
 * The two processes do not share memory or open file tables; this state is
 * copied into the new process, and subsequent modification in one process does
 * not affect the other.
 *
 * However, the file handle objects the file tables point to are shared, so,
 * for instance, calls to lseek in one process can affect the other.
 */

pid_t
fork(void);

/*
 * fork duplicates the currently running process. The two copies are identical,
 * except that one (the "new" one, or "child"), has a new, unique process id,
 * and in the other (the "parent") the process id is unchanged.
 */
 int fork(struct trapframe *tf, int *ret){
   // create child process
  	child = thread_create(curthread -> t_name);

    KASSERT(curthread != NULL);
    KASSERT(tf != NULL);

    // Check if user has allowance for a new process.
    // If not, return error code EAGAIN	Too many processes already exist.
    if (num_total_processes >= allowed_processes) {
      return EAGAIN;
    }

    // Allocate memory to child process using kmalloc.
    child -> t_stack = kmalloc(STACK_SIZE);
    // Return error code ENOMEM	if sufficient virtual memory for the new process
    // was not available.
  	if (child -> t_stack == NULL) {
  		kfree(child -> t_name);
  		kfree(child);
  		return ENOMEM;
  	}

    child -> t_pcb = curthread -> t_pcb;

    // copy trapframe onto new thread and make the new thread runnable
    md_initpcb(&child -> t_pcb, child -> t_stack, tf, 0, md_forkentry);

    // Create a new process id for the child processs.
    pid = p_new -> p_pid;
    // The process id must be greater than 0.
    if (getpid(child) < 1 || getpid(child) == NULL) {
      return -1;
    }

    // On error, no new process is created, fork only returns once, returning -1,
    // and errno is set according to the error encountered.
    if (err) {
      return errno(err);
    }

    // In the parent process, the process id of the new child process is returned.
    if (getpid(child) != NULL) {
      return getpid(child);
    }

    // In the child process, 0 is returned.
    return 0;
 }
