#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

//TID, PID, real-time priority and name (command)

//rcu_read_lock();
//rcu_read_unlock();
typedef struct mythread_struct{
   pid_t pid;
   pid_t tid;
   unsigned int rt_priority;
   char	comm[16];
} mythread_struct;


SYSCALL_DEFINE0(count_rt_threads){
  long count;
  struct task_struct *p;
  rcu_read_lock();
  count = 0;

  for_each_process(p){
    unsigned int rt_priority = p->rt_priority;
    if(rt_priority >=1 &&rt_priority <=99){
      count++;
    }
  }
  rcu_read_unlock();
  return count;
}

/*
SYSCALL_DEFINE2(list_rt_threads, void __user * user_buf, int, count){
  int counter;
  rcu_read_lock();
  counter = 0;

  mythread_struct* local_data = (mythread_struct*)kmalloc( sizeof(mythread_struct)*count, GFP_KERNEL  );
  struct task_struct *p;
  for_each_process(p){
    if(counter >=count){
      return counter;
    }
    unsigned int rt_priority = p->rt_priority;
    if(rt_priority >=1 &&rt_priority <=99){
      local_data[count].pid = p->tgid;
      local_data[count].tid = p->pid;
      local_data[count].rt_priority = p->rt_priority;
      strcpy(data_buf[count].comm, p->comm);
      counter++;
    }
  }

  copy_to_user (user_buf, local_data, sizeof(mythread_struct)*count);
  kfree(local_data);
  rcu_read_unlock();
  return counter;








}
*/
