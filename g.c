#define H5FILE_NAME        "g.h5"
#define GROUP_BASENAME "/group_"

#include "hdf5.h"
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

int
main (void)
{
  char* group_name = NULL;  
  hid_t fid = -1;
  hid_t* obj_id_list = NULL;
  int i = 0;
  int num_group = INT_MAX - 1;
  int temp_num_group = INT_MAX - 1;
  int group_digit = 0;
  
  while(temp_num_group != 0) {
    group_digit++;
    temp_num_group /= 10;
  }
  printf("malloc()\n");
  group_name = malloc((group_digit+1)+sizeof(GROUP_BASENAME));
  if (group_name == NULL) {
    printf("malloc() failed\n");
    return -1;
  }
  
  obj_id_list = (hid_t*)calloc(num_group, sizeof(hid_t));
  if (obj_id_list == NULL) {
    printf("calloc() failed\n");
    return -1;
  }
  

    
  fid = H5Fcreate(H5FILE_NAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  
  if(fid < 0) {
    printf("Cannot create HDF5 file %s, at line %d\n", H5FILE_NAME, __LINE__);
    return -1;
  }
  
  for(i=0;i< num_group;i++) {
    sprintf(group_name, GROUP_BASENAME "%d", i);  
    if((obj_id_list[i]=H5Gcreate(fid, group_name,
                                 H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT))<0) {
      printf("Cannot create the group, at line %d\n", __LINE__);
      return -1;      
    }
  }
  free(obj_id_list);
  free(group_name);  
  return 0;
}
