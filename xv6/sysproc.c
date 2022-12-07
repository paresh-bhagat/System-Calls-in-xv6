#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "sys/ipc.h"

extern int trace;
extern int system_call_count[27];
extern char system_call_name[27][20];

extern void send_message();
extern void receive_message();

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//print system call with count

int
sys_print_count(void)
{ 

  for(int i=97 ; i<=122 ; i++)
  {
  	for(int j=0; j<=26; j++)
  	{
    		if( system_call_count[j] != 0 && system_call_name[j][0]==i )
     			cprintf("sys_%s %d\n", system_call_name[j], system_call_count[j]);
  	}
  }
  
  return 0;
}

//toggle state

int
sys_toggle(void)
{
  if(trace==0)
    trace = 1;
  else
    trace = 0;
  for(int i=0; i<=26 ; i++)
    system_call_count[i] = 0;
  return 0;
}

//add

int
sys_add(void)
{
    int a,b;
    argint(0,&a);
    argint(1,&b);
    return a+b;
}

//ps

int
sys_ps(void)
{
    return ps();
}

int
sys_send(void)
{
  int sender_id, receiver_id; 
  char *message;

  if(argstr(2, &message) < 0){
    return -1;
  }

  if(argint(0, &sender_id) < 0){
    return -1;
  }
  if(argint(1, &receiver_id) < 0){
    return -1;
  }
  
  send_message(sender_id,receiver_id, message);

  return 0;
}

int sys_recv(void)
{  
  char *message;
 
  if(argstr(0, &message) < 0){
    return -1;
  }
  
  receive_message(message);
  return 0;
}
