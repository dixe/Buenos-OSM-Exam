/*
 * Pipe FS header file for OSM exam at DIKU 2014.
 *
 * You may need to modify this file.
 */

#ifndef FS_PIPE_H
#define FS_PIPE_H

#define MAX_PIPE_NUMBER 12 // choosen to be the highest number still fitting in one page
#define PIPE_BUFFER_LEN 256
#define PIPE_NEGATIVE_SIZE -10
#define PIPE_NO_SEMAPHORE -11
#define PIPE_REMOVED -12
#define PIPE_WAIT_CYCLES 100

#include "fs/vfs.h"
#include "lib/libc.h"

fs_t *pipe_init(void);

int pipe_unmount(fs_t *fs);
int pipe_open(fs_t *fs, char *filename);
int pipe_close(fs_t *fs, int fileid);
int pipe_create(fs_t *fs, char *filename, int size);
int pipe_remove(fs_t *fs, char *filename);
int pipe_read(fs_t *fs, int fileid, void *buffer, int bufsize, int offset);
int pipe_write(fs_t *fs, int fileid, void *buffer, int datasize, int offset);
int pipe_getfree(fs_t *fs);
int pipe_filecount(fs_t *fs, char *dirname);
int pipe_file(fs_t *fs, char *dirname, int idx, char *buffer);

#endif
