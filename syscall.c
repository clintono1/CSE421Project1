#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "filesys/filesys.h"
#include "threads/vaddr.h"
#include "userprog/process.h"
#include "devices/shutdown.h"
/*
function return values placed in eax register
each system call argument takes up 4 bytes on stack
*/

static void halt(void);
static void exit(int status); //exit used to return -1 on error
static int get_arg(int * esp, int buffer);
static int get_user(const uint8_t *uaddr);
static bool put_user(uint8_t *udst, uint8_t byte);
static bool valid_string(void * s);
static void valid_pointer(char *c,unsigned int size);
static void valid_buffer(void* buffer, unsigned size);
static void valid_size(void* vaddr, unsigned size);
static void is_valid(char *c, unsigned int size);
static void syscall_handler (struct intr_frame *);
void
syscall_init (void) 
{

  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

}
/* Reads a byte at user virtual address UADDR.
UADDR must be below PHYS_BASE.
Returns the byte value if successful, -1 if a segfault
occurred. */
static int
get_user (const uint8_t *uaddr)
{
   int result;
   asm ("movl $1f, %0; movzbl %1, %0; 1:"
      : "=&a" (result) : "m" (*uaddr));
   return result;
}

/* Writes BYTE to user address UDST.
UDST must be below PHYS_BASE.
Returns true if successful, false if a segfault occurred. */
static bool
put_user (uint8_t *udst, uint8_t byte)
{
   int error_code;
   asm ("movl $1f, %0; movb %b2, %1; 1:"
      : "=&a" (error_code), "=m" (*udst) : "q" (byte));
   return error_code != -1;
}
/*
get and put user from piazza post394
*/

//check to see if its pointer to virtual address exits with -1 if not
static void is_valid(char *c, unsigned int size){
if(c==NULL||!is_user_vaddr(c)||get_user(c)==-1;
exit(-1);
int i;
while(i<size){
if(c+i==NULL||!is_user_vaddr(c+i)||get_ser(c+i)==-1){
exit(-1);
}
i=i+1;
}
}
/*
static void valid_buffer(const void* buffer, unsigned size){

}
*/

static void valid_size(const void* vaddr,unsigned size){
if (vaddr==NULL) thread_exit();
if(!is_user_vaddr(vaddr) || !is_user_vaddr(size+vaddr)) exit(-1);
}

/*
pass arguments into syscall exits if address is invalid
*/
static int get_arg(int *esp, int buffer){
if(!is_user_vaddr(buffer+esp)) exit(-1);
return *(esp+buffer);


}
/*
system call handler FSM
*/
static void
syscall_handler (struct intr_frame *f UNUSED) 
{
// cast converts current stack pointer to int
int *esp=(int *)f->esp;
int sys_call;
int arg1;
int arg2;
int arg3;
sys_call=*(int)f->esp;
//valid_pointer();
//valid_buffer();
//struct thread *t;
//switches stack pointer
if(get_user(esp)==-1 || get_user(esp+1)==-1||get_user(esp+2)==-1||get_user(esp+3)==-1){
exit(-1);
}
switch(sys_call){

case halt:
shutdown_power_off();
break;


case exit:
arg1=get_arg(esp,1);
exit(arg1);
break;

case exec:
arg1=get_arg(esp,1);
f->eax=create(esp);
break;

case wait:
arg1=get_arg(esp,1);
f->eax=wait(esp);
break;

case create:
arg1=get_arg(esp,1);
arg2=get_arg(esp,2);
f->eax=create(esp);

break;

case remove:
arg1=get_arg(esp,1);
filesys_remove(arg1);
f->eax=remove(esp);
break;

case open:
arg1=get_arg(esp,1);
f->eax=open(esp);
break;

case filesize:
arg1=get_arg(esp,1);
f->eax=filesize(esp);
break;

case read:
arg1=get_arg(esp,1);
arg2=get_arg(esp,2);
arg3=get_arg(esp,3);
f->eax=read(esp);
break;

case write:
arg1=get_arg(esp,1);
arg2=get_arg(esp,2);
arg3=get_arg(esp,3);
f->eax=write(esp);
break;

case seek:
arg1=get_arg(esp,1);
arg2=get_arg(esp,2);
f->eax=seek(esp);
break;

case tell:
arg1=get_arg(esp,1);
f->eax=tell(esp);
break;

case close:
f->eax=close(esp);
break;

default: exit(-1);
break;
}
}




/*
System CAll Helper Functions
*/


static void halt (void){
  shutdown_power_off();
}

static void exit (int status){
printf ("Exiting, status: ", status);
thread_exit(status);

}





static int wait(void* esp){
int pid=get_arg(esp,1);
int status=process_wait(pid);
return status;
}




/*system call create
checks for null arguments*/
static bool create(void *esp){
const char * file=get_arg(esp,1);
unsigned int size=get
bool created=filesys_create(file,size);
return status;
}

static bool remove(void *esp){
const char * file = get_arg(esp,1);
is_valid(name,255);
bool status;
status=filesys_remove(file);
return status;
}


static int open(void *esp){
const char * file = get_arg(esp,1);
is_valid(file,255);
}
//unfinished
static int filesize(void *esp){
int fd=get_arg(esp,1);
}

static int write(void *esp){
int fd=get_arg(esp,0);
const void* buffer=get_arg(esp,1);
unsigned int size(esp,2);
is_valid(buffer,size);
}
//unfinished
static void seek(void * esp){
int fd=get_arg(esp,1)l
unsigned position = get_arg(esp,1);

}
//unfinished
static void close(void * esp){
int fd=get_arg(esp,0);
file_close();


/*
pid_t exec (const char *cmd_line){
return process_execute (cmd_line);
}
*/
/*int wait (pid_t pid){
  return process_wait(pid);
}

bool create (const char *file, unsigned initial_size){
return filesys_create(file, initial_size);

}

bool remove (const char *file) {
return filesys_remove(file);
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
/*
unsigned tell (int fd) {

}

void close (int fd) {

}
/*
