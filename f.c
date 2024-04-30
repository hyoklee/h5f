#define FUSE_USE_VERSION 26

#include <fuse.h>

int h5f_close(int fid)
{
  return 0;
}

int h5f_create(char* name)
{
  return 0;
}

int main()
{
  int fid;
  char* name = "t.fs";
  
  fid = h5f_create(name);       /* call mkfs open */
  return h5f_close(fid);        /* call mkfs close */

}
  

