#ifndef INIT_RAMFS
#define INIT_RAMFS

void ramfs_ls();
void ramfs_cat(char * filename);
int ramfs_load(char * filename, void * addr);

#endif