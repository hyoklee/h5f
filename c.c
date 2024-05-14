#include <hdf5.h>
#include <stdio.h>

#define H5FILE_NAME "c.h5"
#define RANK        2

int
main(void)
{

    hid_t file;
    hid_t grp;
    hid_t dataset, dataspace;
    hid_t plist;

    herr_t  status;
    hsize_t dims[2];
    hsize_t cdims[2];

    int idx_f, idx_g;

    /*
     * Create a file.
     */
    file = H5Fcreate(H5FILE_NAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);


    /*
     * Create dataset "Compressed Data" in the group using absolute
     * name. Dataset creation property list is modified to use
     * GZIP compression with the compression effort set to 6.
     * Note that compression can be used only when dataset is chunked.
     */
    dims[0]   = 1000;
    dims[1]   = 1024;
    cdims[0]  = 1;
    cdims[1]  = 1024;
    dataspace = H5Screate_simple(RANK, dims, NULL);
    plist     = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_chunk(plist, 2, cdims);
    H5Pset_deflate(plist, 6);
    dataset =
        H5Dcreate2(file, "/Compressed_Data", H5T_NATIVE_INT, dataspace, H5P_DEFAULT, plist, H5P_DEFAULT);
    /*
     * Close the first dataset .
     */
    H5Sclose(dataspace);
    H5Dclose(dataset);
    H5Fclose(file);
}
