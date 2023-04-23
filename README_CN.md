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
* Install oneapi(2023.0.0)
* git clone https://github.com/zhupailiangx/BuildHashTable_Sample.git
* cd BuildHashTable_Sample/BuildHashTable_Sample
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

