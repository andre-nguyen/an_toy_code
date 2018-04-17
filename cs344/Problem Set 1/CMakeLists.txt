############################################################################
# <summary> CMakeLists.txt for OpenCV and CUDA. </summary>
# <date>    2012-02-07          </date>
# <author>  Quan Tran Minh. edit by Johannes Kast, Michael Sarahan </author>
# <email>   quantm@unist.ac.kr  kast.jo@googlemail.com msarahan@gmail.com</email>
############################################################################
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)

link_libraries(${OpenCV_LIBS} )

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} "-Xcompiler -Wextra")
#set(CMAKE_CXX_FLAGS "-stdlib=libstdc++")
#set(CUDA_NVCC_FLAGS_DEBUG ${CUDA_NVCC_FLAGS_DEBUG} "-G")
#set(CUDA_NVCC_FLAGS "
#-ccbin /usr/bin/clang;
#-gencode;arch=compute_30,code=sm_30;
#-gencode;arch=compute_35,code=sm_35;
#-gencode;arch=compute_35,code=compute_35;
#-gencode;arch=compute_20,code=sm_20;
#-gencode;arch=compute_11,code=sm_11;
#-gencode;arch=compute_12,code=sm_12;
#-gencode;arch=compute_13,code=sm_13;")

# collect source files

file( GLOB  hdr *.hpp *.h )
file( GLOB  cu  *.cu)
SET (HW1_files main.cpp reference_calc.cpp compare.cpp)

CUDA_ADD_EXECUTABLE(HW1 ${HW1_files} ${hdr} ${cu})
