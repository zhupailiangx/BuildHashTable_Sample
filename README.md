# Different init queue value on Linux and Windows
## Introduction
In the process of experiment Normals_Estimation, we found that in the file fixed_radius_index.h line 99, the initialization method of q_ is 
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
* Open BuildHashTable_Sample and find BuildHashTable_Sample.cpp
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
This example compares the performance impact of sycl::queue q_ and q_ = dpct::get_default_queue() on the establishment of a hash table. The result shows that we need to change the initialization method of q_ given in line 99 of the fixed_radius_index.h file to sycl ::queue q_ = dpct::get_default_queue(), so that Normals_Estimation has similar performance on Windows and Linux.

# Chinese Version

# queue在linux 和Windows上的不同

## 引言
在实验Normals_Estimation算法过程中，fixed_radius_index.h文件99行给出q_的初始化方式为
```bash
sycl::queue q_ 
```

测试发现，这样的初始化方式在Linux和Windows上代码性能有很大差异。所以，写下本示例，对比
```bash
sycl::queue q_和q_ = dpct::get_default_queue()
```
在Linux和Windows上的性能差异，希望对接下来的工作有所帮助。


### 在Linux系统上
* 安装oneapi(2023.0.0)
* 打开BuildHashTable_Sample,找到BuildHashTable_Sample.cpp所在的文件夹
* source /opt/intel/oneapi/setvars.sh
* dpcpp BuildHashTable_Sample.cpp -o BuildHashTable_Sample
* ./BuildHashTable_Sample

### 在 Windows 系统上
* 安装oneapi(2023.0.0) 和 Visual Studio

#### Visual Studio IDE
* 打开 Visual Studio
* 选择菜单 "File > Open > Project/Solution",找到"BuildHashTable_Sample"文件夹和选择"BuildHashTable_Sample.sln"
* 检查包含目录是否包含dpct文件路径
* 选择菜单 "Project > Build" ，然后执行代码
     


### Linux 上测试结果
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
### Windows上测试结果

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
## 总结
本示例对比了sycl::queue q_和q_ = dpct::get_default_queue()对建立哈希表的性能影响，结果表明，我们需要把fixed_radius_index.h文件99行给出q_的初始化方式修改成sycl::queue q_ = dpct::get_default_queue(),这样Windows 和Linux上Normals_Estimation就有了差不多的性能。



