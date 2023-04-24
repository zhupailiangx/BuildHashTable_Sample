# Different ways of initializing queue on Linux and Windows
## Introduction
In the process of experiment Normals_Estimation, we found that in the file **fixed_radius_index.h** line 99, the initialization method of q_ is 
```bash
sycl::queue q_ 
```
However,after testing, it is found that the code performance of such an initialization method is very different on Linux and Windows.
So, write this example and compare the performance difference between 
```bash
sycl::queue q_ and q_ = dpct::get_default_queue()
```
in building hash tables on Linux and Windows, hoping to help the next work.

### On Linux
* Install oneapi(2023.0.0)
* git clone https://github.com/zhupailiangx/BuildHashTable_Sample.git
* cd BuildHashTable_Sample/BuildHashTable_Sample
* source /opt/intel/oneapi/setvars.sh
* dpcpp BuildHashTable_Sample.cpp -o BuildHashTable_Sample
* ./BuildHashTable_Sample

### On Windows
* Install oneapi(2023.0.0) and  Visual Studio
#### Visual Studio IDE
* Open Visual Studio
* Select menu "File > Open > Project/Solution",find "BuildHashTable_Sample" folder and select "BuildHashTable_Sample.sln"
* Check if include directory contains dpct file path
* Select menu "Project > Build", then view the execution results
### Test results on Linux
```bash
  Test with default q_:

Loop = 1
 build hash table time=64ms
Loop = 2
 build hash table time=8ms
Loop = 3
 build hash table time=7ms
Loop = 4
 build hash table time=7ms
Loop = 5
 build hash table time=6ms

_____________________________________________

Test with q_ = dpct::get_default_queue():

Loop = 1
 build hash table time=60ms
Loop = 2
 build hash table time=7ms
Loop = 3
 build hash table time=7ms
Loop = 4
 build hash table time=7ms
Loop = 5
 build hash table time=7ms

```
### Test results on Windows
```bash
  Test with default q_:

Loop = 1
 build hash table time=141ms
Loop = 2
 build hash table time=137ms
Loop = 3
 build hash table time=127ms
Loop = 4
 build hash table time=122ms
Loop = 5
 build hash table time=125ms

_____________________________________________

Test with q_ = dpct::get_default_queue():

Loop = 1
 build hash table time=123ms
Loop = 2
 build hash table time=2ms
Loop = 3
 build hash table time=1ms
Loop = 4
 build hash table time=2ms
Loop = 5
 build hash table time=1ms

```
## Summary
       This example compares the performance impact of sycl::queue q_ and q_ = dpct::get_default_queue() on the establishment of a hash table. The former needs to return the default device first, and then create a queue, and the latter directly returns the default queue of the current device. The result shows that we need to change the initialization method of q_ given in line 99 of the **fixed_radius_index.h** file to **sycl ::queue q_ = dpct::get_default_queue()**, so that Normals_Estimation has similar performance on Windows and Linux.




