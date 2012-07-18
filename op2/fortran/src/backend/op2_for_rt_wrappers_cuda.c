#include <op_lib_core.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

void
op_get_dat (op_dat dat) {
  cudaMemcpy (dat->data, dat->data_d,
    dat->size * dat->set->size,cudaMemcpyDeviceToHost);

  cudaThreadSynchronize();
}

void
op_put_dat (op_dat dat) {
  cudaMemcpy (dat->data_d, dat->data,
    dat->size * dat->set->size,cudaMemcpyHostToDevice);

  cudaThreadSynchronize();
}
