/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 01/29/2018
* DESCRIPTION  : This program does a sorting to descending order from kernel to user space
                  using kmalloc
      
* HEADER FILES  : syssorter.h
****************************************************************/

#include "syssorter.h"

SYSCALL_DEFINE3(sorter ,unsigned long*, input_buffer,unsigned long, size, unsigned long*, output_buffer)
{

  unsigned long *buff;
  unsigned long outer_cnt,inner_cnt;
  unsigned long swap;

  printk(KERN_INFO "Logging syscall entry");
  printk(KERN_INFO "Size of buffer is: %ld", size);

  buff = kmalloc(size *sizeof(unsigned long), GFP_KERNEL);
  if(buff==NULL) //GFP_KERNEL- too make malloc sleep in kernel if memory is not available
  {
    printk(KERN_ALERT "memory allocation for buff has failed");
    return -EFAULT;
  }
  
  printk(KERN_INFO "Copying buffer from user to kernel space");

  if(copy_from_user(buff, input_buffer, size *sizeof(unsigned long)))
  {
    printk(KERN_ALERT "copy_from_user has failed");  
    return -EFAULT;
  }

  printk(KERN_INFO "Sorting input buffer using bubble sort algo");

  //This implements bubble sort algorithm

  for(outer_cnt=0;outer_cnt<(size-1);outer_cnt++)
  {
    for(inner_cnt=0;inner_cnt<(size-outer_cnt-1);inner_cnt++)
    {
      if(buff[inner_cnt]<buff[inner_cnt+1]) // sort in descending order
      {
        swap=buff[inner_cnt];
        buff[inner_cnt]=buff[inner_cnt+1];
        buff[inner_cnt+1]=swap;
      }
    }
  }

  printk(KERN_INFO "Bubble sort complete");

  printk(KERN_INFO "Copying sorted from kernel space to user space");
  if(copy_to_user(output_buffer, buff, size *sizeof(unsigned long)))
  {
    printk(KERN_ALERT "copy_to_user has failed");
    return -EFAULT;
  }

  printk(KERN_INFO "Freeing allocated memory using kfree");
  kfree(buff);
  printk(KERN_INFO "Logging syscall exit");

  return 0;
}
