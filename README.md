# queue在linux 和Windows上的不同

## 引言
在实验Normals_Estimation算法过程中，发现Linux和Windows上queue不同初始化方式，对代码性能有很大影响。所以，写下本示例，对比q_选择默认队列和q_ = dpct::get_default_queue()的性能差异，希望对接下来的工作有所帮助。


### 在Linux系统上
* 安装oneapi(2023.0.0)
* 打开BuildHashTable_Sample,找到BuildHashTable_Sample.cpp所在的文件夹
* source /opt/intel/oneapi/setvars.sh
* dpcpp BuildHashTable_Sample.cpp -o BuildHashTable_Sample
* ./BuildHashTable_Sample

### 在 Windows 系统上
* 安装oneapi(2023.0.0)

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




