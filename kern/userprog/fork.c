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

/*
 * The process id must be greater than 0.
 */

/* The two processes do not share memory or open file tables; this state is
 * copied into the new process, and subsequent modification in one process does
 * not affect the other.
 */

/* However, the file handle objects the file tables point to are shared, so,
 * for instance, calls to lseek in one process can affect the other.
 */

/* On success, fork returns twice, once in the parent process and once in the
 * child process. In the child process, 0 is returned. In the parent process,
 * the process id of the new child process is returned.
 */

/* On error, no new process is created, fork only returns once, returning -1,
 * and errno is set according to the error encountered.
 *
 * Error Codes:
 * EAGAIN	Too many processes already exist.
 * ENOMEM	Sufficient virtual memory for the new process was not available.
 */
