#include <hdf5.h>
#include <stdio.h>

#define DATASET_NAME "my_dataset"
#define CHUNK_SIZE 1024
#define NUM_CHUNKS 1000

int main(void) {
  hid_t file_id, dataset_id, dataspace_id, filespace_id;
  herr_t status;

  hsize_t dimsf[1] = {NUM_CHUNKS * CHUNK_SIZE};  // Dataset dimensions
  hsize_t chunk_dims[1] = {CHUNK_SIZE};         // Chunk dimensions
  hsize_t start[1], count[1];                   // Hyperslab for writing

  // Initialize data (replace with your data generation)
  int data[CHUNK_SIZE];
  for (int i = 0; i < CHUNK_SIZE; i++) {
    data[i] = i;  // Example data, replace with your logic
  }

  // Create a new HDF5 file
  file_id = H5Fcreate("k.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  if (file_id < 0) {
    printf("Error creating HDF5 file\n");
    return 1;
  }

  // Define the dataspace for the dataset
  dataspace_id = H5Screate_simple(1, dimsf, NULL);
  if (dataspace_id < 0) {
    printf("Error creating dataspace\n");
    H5Fclose(file_id);
    return 1;
  }

  // Define the hyperspace for the dataset chunks
  filespace_id = H5Screate_simple(1, chunk_dims, NULL);
  if (filespace_id < 0) {
    printf("Error creating filespace\n");
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
    return 1;
  }

  // Create chunked dataset
  dataset_id = H5Dcreate2(file_id, DATASET_NAME, H5T_STD_I32LE, dataspace_id,
                         H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dataset_id < 0) {
    printf("Error creating dataset\n");
    H5Sclose(dataspace_id);
    H5Sclose(filespace_id);
    H5Fclose(file_id);
    return 1;
  }

  // Loop through chunks and write data
  for (int i = 0; i < NUM_CHUNKS; i++) {
    start[0] = i * CHUNK_SIZE;
    count[0] = CHUNK_SIZE;
    H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, start, NULL, count, NULL);

    status = H5Dwrite(dataset_id, H5T_NATIVE_INT, filespace_id, dataspace_id,
                      H5P_DEFAULT, data);
    if (status < 0) {
      printf("Error writing data to chunk %d\n", i);
      H5Dclose(dataset_id);
      H5Sclose(dataspace_id);
      H5Sclose(filespace_id);
      H5Fclose(file_id);
      return 1;
    }
    else {
      H5Dflush(dataset_id);
    }
  }

  // Close resources
  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
  H5Sclose(filespace_id);
  H5Fclose(file_id);

  printf("Data written successfully to %s\n", "k.h5");
  return 0;
}
