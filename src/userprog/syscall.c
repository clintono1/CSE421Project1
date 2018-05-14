#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  
//Implement below methods into a switch-case/if condition on the system call
/* Either something like:
  if (system_call == SYS_HALT){
    halt();
  } else if (system_call == SYS_EXIT){
    .
    .
    .

--or--

  switch (system_call)
    case SYS_HALT:
      halt();
      break;
    case SYS_EXIT:
      .
      .
      .
  
Not sure which we think is best, though not much is affected performance-wise
*/
 
  thread_exit ();
}

void halt (void){
  shutdown_power_off();
}

void exit (int status){
  printf ("%s: exit(%d)\n", status);
  thread_exit(status);
}

pid_t exec (const char *cmd_line){

}

int wait (pid_t pid){
  return process_wait(pid);
}

bool create (const char *file, unsigned initial_size){

}

bool remove (const char *file) {

}

int open (const char *file) {

}

int filesize (int fd) {

}

int read (int fd, void *buffer, unsigned size) {

}

int write (int fd, const void *buffer, unsigned size) {

}

void seek (int fd, unsigned position) {

}

unsigned tell (int fd) {

}

void close (int fd) {

}
