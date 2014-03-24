/*
 * Pipe FS header file for OSM exam at DIKU 2014.
 *
 * You may need to modify this file.
 */

#include "kernel/kmalloc.h"
#include "kernel/assert.h"
#include "vm/pagepool.h"
#include "drivers/gbd.h"
#include "fs/vfs.h"
#include "fs/pipe.h"
#include "lib/libc.h"

/*A pipe pseudo file*/
typedef struct{
  //name of pipe file
  char name[VFS_NAME_LENGTH];
  // buffer to store content of file
  char buffer[PIPE_BUFFER_LEN];
  // if 1 the pipe is not in use, if 0 it is
  int free;
} pipe_t;


/* Data structure for use internally in pipefs. We allocate space for this
 * dynamically during initialization */
typedef struct {
  semaphore_t *lock;
  //arry of pipes
  pipe_t pipes[MAX_PIPE_NUMBER];
  /* Define any data you may need  here. */
} pipefs_t;


/***********************************
 * fs_t function implementations
 ***********************************/

/* Initialize pipefs. We allocate one page of dynamic memory for the
 * fs_t and pipefs_t structures.  Note that, in contrast to other
 * filesystems, we take no disk parameter.  You may want to extend
 * this function. */
fs_t *pipe_init(void)
{
    uint32_t addr;
    fs_t *fs;
    pipefs_t *pipefs;
    semaphore_t *sem;
    int i, ret;

    /* check semaphore availability before memory allocation */
    sem = semaphore_create(1);
    if (sem == NULL) {
        kprintf("pipe_init: could not create a new semaphore.\n");
        return NULL;
    }

    addr = pagepool_get_phys_page();
    if(addr == 0) {
        semaphore_destroy(sem);
        kprintf("pipe_init: could not allocate memory.\n");
        return NULL;
    }
    addr = ADDR_PHYS_TO_KERNEL(addr);      /* transform to vm address */

    /* Assert that one page is enough */
    KERNEL_ASSERT(PAGE_SIZE >= (sizeof(pipefs_t)+sizeof(fs_t)));

    /* fs_t, pipefs_t and all required structure will most likely fit
       in one page, so obtain addresses for each structure and buffer
       inside the allocated memory page. */
    fs  = (fs_t *)addr;
    pipefs = (pipefs_t *)(addr + sizeof(fs_t));

    /* save semaphore to the pipefs_t */
    pipefs->lock = sem;

    fs->internal = (void *)pipefs;

    /* We always have this name. */
    stringcopy(fs->volume_name, "pipe", VFS_NAME_LENGTH);

    fs->unmount   = pipe_unmount;
    fs->open      = pipe_open;
    fs->close     = pipe_close;
    fs->create    = pipe_create;
    fs->remove    = pipe_remove;
    fs->read      = pipe_read;
    fs->write     = pipe_write;
    fs->getfree   = pipe_getfree;
    fs->filecount = pipe_filecount;
    fs->file      = pipe_file;

    ret = vfs_mount(fs, "pipe");

    KERNEL_ASSERT(ret == 0);
    
    kprintf("pipe INIT start\n");

    //get semaphore?
    semaphore_P(pipefs->lock);

    //initialize all pipes in pipefs
    for(i = 0; i < MAX_PIPE_NUMBER; i++){
      // initially every pipe is free
      pipefs->pipes[i].free = 1;
    }
    semaphore_V(pipefs->lock);

    return fs;
}

/* You have to implement the following functions.  Some of them may
   just return an error.  You have to carefully consider what to do.*/

int pipe_unmount(fs_t *fs)
{
    fs=fs;
    return VFS_NOT_SUPPORTED;
}

int pipe_open(fs_t *fs, char *filename)
{
  kprintf("From open filename is %s\n",filename);
  int i, fid = -1;
  //get internal pipefs
  pipefs_t *pipefs = fs->internal;
  // get the semaphore before reading
  semaphore_P(pipefs->lock);

  for(i = 0; i< MAX_PIPE_NUMBER; i++){
    if(pipefs->pipes[i].free){
      if(!stringcmp(pipefs->pipes[i].name,filename) ){//they are equal
	fid = i;
	pipefs->pipes[i].free = 0;
	break;	
      }
    }
  }
  //release, since we are done reading now
  semaphore_V(pipefs->lock);
  
  if(fid == -1){// we didn't find the fid
    return VFS_NOT_FOUND;
  }

  return fid;

}

int pipe_close(fs_t *fs, int fileid)
{
    fs = fs; fileid = fileid;
    return VFS_NOT_SUPPORTED;
}

int pipe_create(fs_t *fs, char *filename, int size)
{
  kprintf("In create, filename is %s\n", filename);
  
  // the size of the file is constant atm
  size=size;
   int i;
  //get internal pipefs
  pipefs_t *pipefs = fs->internal;
  //get semaphore for the table
  semaphore_P(pipefs->lock);

  for(i=0;i< MAX_PIPE_NUMBER; i++){
    //get the first free pipe
    if(pipefs->pipes[i].free){
      //save file name, filename len is the same as VFS
      stringcopy(pipefs->pipes[i].name, filename, VFS_NAME_LENGTH);
      kprintf("name is set to %s\n", pipefs->pipes[i].name);
      break;
    }
  }
  if (i >= MAX_PIPE_NUMBER){
    return VFS_LIMIT;    
  }

  semaphore_V(pipefs->lock);
  return 0;
}

int pipe_remove(fs_t *fs, char *filename)
{
    fs=fs; filename=filename;
    return VFS_NOT_SUPPORTED;
}

int pipe_read(fs_t *fs, int fileid, void *buffer, int bufsize, int offset)
{
  int size;
  //get internal pipefs
  pipefs_t *pipefs = fs->internal;
  // get the semaphore before reading
  semaphore_P(pipefs->lock);

  //get the max size to read
  size = MIN(bufsize, PIPE_BUFFER_LEN - offset);  
  if(size <= 0){
    semaphore_V(pipefs->lock);
    return PIPE_NEGATIVE_SIZE;
  }
  
  // get the max size between bufsize and 
  stringcopy(buffer, pipefs->pipes[fileid].buffer + offset,size);  

  //release, since we are done reading now
  semaphore_V(pipefs->lock);
  //todo find a way to count bytes read
  return 0;
}

int pipe_write(fs_t *fs, int fileid, void *buffer, int datasize, int offset)
{
  int size;
  //get internal pipefs
  pipefs_t *pipefs = fs->internal;
  // get the semaphore before reading
  semaphore_P(pipefs->lock);
  
  size = MIN(datasize,PIPE_BUFFER_LEN - offset);

  if(size <= 0){
    semaphore_V(pipefs->lock);
    return PIPE_NEGATIVE_SIZE;
  }
  stringcopy(pipefs->pipes[fileid].buffer + offset, buffer, size);  
  //release, since we are done reading now
  semaphore_V(pipefs->lock);
  //todo find a way to count bytes read
  return 0;
}

int pipe_getfree(fs_t *fs)
{
    fs=fs;
    return VFS_NOT_SUPPORTED;
}

int pipe_filecount(fs_t *fs, char *dirname)
{
    fs=fs; dirname=dirname;
    return VFS_NOT_SUPPORTED;
}

int pipe_file(fs_t *fs, char *dirname, int idx, char *buffer)
{
    fs=fs; dirname=dirname; idx=idx; buffer=buffer;
    return VFS_NOT_SUPPORTED;
}
