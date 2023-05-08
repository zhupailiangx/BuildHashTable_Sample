# queue在linux 和Windows上的不同

## 引言
在实验Normals_Estimation算法过程中，**fixed_radius_index.h**文件99行给出q_的初始化方式为
```bash
sycl::queue q_ 
```

测试发现，这样的初始化方式在Linux和Windows上代码性能有很大差异。所以，写下本示例，首先对比
```bash
sycl::queue q_和q_ = dpct::get_default_queue()
```
在Linux和Windows上的性能差异，然后测试最新驱动版本和设置SYCL_ENABLE_DEFAULT_CONTEXTS=1在windows上面的表现，希望对接下来的工作有所帮助。


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
     
### 测试结果
对于两种队列初始化方法，我们分别在Linux和windows做了五次循环测试，第一次循环和后面循环的关系可以查看下面的表格.
<table border=0 cellpadding=0 cellspacing=0 width=902 style='border-collapse:
 collapse;table-layout:fixed;width:676pt'>
 <col width=64 style='width:48pt'>
 <col width=115 style='mso-width-source:userset;mso-width-alt:4205;width:86pt'>
 <col width=304 style='mso-width-source:userset;mso-width-alt:11117;width:228pt'>
 <col width=115 style='mso-width-source:userset;mso-width-alt:4205;width:86pt'>
 <col width=304 style='mso-width-source:userset;mso-width-alt:11117;width:228pt'>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl65 width=64 style='height:30.0pt;width:48pt'>Loop</td>
  <td colspan=2 class=xl66 width=419 style='border-left:none;width:314pt'>Linux</td>
  <td colspan=2 class=xl66 width=419 style='border-left:none;width:314pt'>Windows</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 style='height:15.0pt;border-top:none;border-left:
  none'>sycl::queue q_</td>
  <td class=xl67 style='border-top:none;border-left:none'>sycl::queue
  q_=dpct::get_default_queue()</td>
  <td class=xl67 style='border-top:none;border-left:none'>sycl::queue q_</td>
  <td class=xl67 style='border-top:none;border-left:none'>sycl::queue
  q_=dpct::get_default_queue()</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>1</td>
  <td class=xl66 style='border-top:none;border-left:none'>64ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>60ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>141ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>123ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>2</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>137ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>2ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>3</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>127ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>1ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>4</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>122ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>2ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>5</td>
  <td class=xl66 style='border-top:none;border-left:none'>6ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>125ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>1ms</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=115 style='width:86pt'></td>
  <td width=304 style='width:228pt'></td>
  <td width=115 style='width:86pt'></td>
  <td width=304 style='width:228pt'></td>
 </tr>
 <![endif]>
</table>
也可以在下面查看，和表格统计结果一致.

#### Linux 上测试结果
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
#### Windows上测试结果

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
### 驱动测试
当前版本驱动和最新版本驱动测试对比如下：
<div style="text-align: center;">
<table border=0  cellpadding=0 cellspacing=0 width=586 style='border-collapse:
 collapse;table-layout:fixed;width:440pt'>
 <col width=64 span=2 style='width:48pt'>
 <col width=197 style='mso-width-source:userset;mso-width-alt:7204;width:148pt'>
 <col width=64 style='width:48pt'>
 <col width=197 style='mso-width-source:userset;mso-width-alt:7204;width:148pt'>
 <tr height=20 style='height:15.0pt'>
  <td colspan=5 height=20 class=xl66 width=586 align="center" style='height:15.0pt;width:440pt;margin:0 auto'>Build
  hash table</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl65 style='height:30.0pt;border-top:none'>Loop</td>
  <td colspan=2 class=xl66 style='border-left:none'>Driver GFX_Win_101.4146</td>
  <td colspan=2 class=xl66 style='border-left:none'>Driver GFX_Win_101.4255</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 style='height:15.0pt;border-top:none;border-left:
  none'>sycl::queue q_</td>
  <td class=xl67 style='border-top:none;border-left:none'>sycl::queue q_=dpct::get_default_queue()</td>
  <td class=xl67 style='border-top:none;border-left:none'>sycl::queue q_</td>
  <td class=xl67 style='border-top:none;border-left:none'>sycl::queue q_=dpct::get_default_queue()</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 align=right style='height:15.0pt;border-top:none'>1</td>
  <td class=xl67 style='border-top:none;border-left:none'>103ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>96ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>101ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>94ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 align=right style='height:15.0pt;border-top:none'>2</td>
  <td class=xl67 style='border-top:none;border-left:none'>100ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>96ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 align=right style='height:15.0pt;border-top:none'>3</td>
  <td class=xl67 style='border-top:none;border-left:none'>94ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>94ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 align=right style='height:15.0pt;border-top:none'>4</td>
  <td class=xl67 style='border-top:none;border-left:none'>94ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>95ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 align=right style='height:15.0pt;border-top:none'>5</td>
  <td class=xl67 style='border-top:none;border-left:none'>94ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>94ms</td>
  <td class=xl67 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=197 style='width:148pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=197 style='width:148pt'></td>
 </tr>
 <![endif]>
</table>

</body>


### 属性设置
测试环境属性设置SYCL_ENABLE_DEFAULT_CONTEXTS=1.
在 SYCL 运行时启用（‘1’）或禁用（‘0’）默认平台上下文的创建。每个平台的默认上下文包含平台中的所有设备。在 Linux 上默认启用，在 Windows 上禁用。
此扩展还修改了队列构造函数的行为。队列将不再在构建时创建新的上下文。相反，他们将使用设备平台的默认上下文。
<table border=0 cellpadding=0 cellspacing=0 width=517 style='border-collapse:
 collapse;table-layout:fixed;width:388pt'>
 <col width=64 style='width:48pt'>
 <col width=97 span=2 style='mso-width-source:userset;mso-width-alt:3547;
 width:73pt'>
 <col width=64 style='width:48pt'>
 <col width=195 style='mso-width-source:userset;mso-width-alt:7131;width:146pt'>
 <tr height=20 style='height:15.0pt'>
  <td colspan=5 height=20 class=xl65 width=517 align="center" style='height:15.0pt;width:388pt'>Build
  Hash Table on Windows</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl65 style='height:30.0pt;border-top:none'>Loop</td>
  <td colspan=2 class=xl67 style='border-right:.5pt solid black;border-left:
  none'>default</td>
  <td colspan=2 class=xl65 style='border-left:none'>SYCL_ENABLE_DEFAULT_CONTEXTS=1</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 style='height:15.0pt;border-top:none;border-left:
  none'>sycl::queue q_</td>
  <td class=xl66 style='border-top:none;border-left:none'>sycl::queue q_</td>
  <td class=xl66 style='border-top:none;border-left:none'>sycl::queu<span
  style='display:none'>e q_</span></td>
  <td class=xl66 style='border-top:none;border-left:none'>sycl::queue q_</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>1</td>
  <td class=xl66 style='border-top:none;border-left:none'>102ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>95ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>108ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>94ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>2</td>
  <td class=xl66 style='border-top:none;border-left:none'>96ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>3</td>
  <td class=xl66 style='border-top:none;border-left:none'>95ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>4</td>
  <td class=xl66 style='border-top:none;border-left:none'>95ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>9ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>5</td>
  <td class=xl66 style='border-top:none;border-left:none'>96ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>9ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl66 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=97 style='width:73pt'></td>
  <td width=97 style='width:73pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=195 style='width:146pt'></td>
 </tr>
 <![endif]>
</table>


## 总结
本示例对比了sycl::queue q_和q_ = dpct::get_default_queue()对建立哈希表的性能影响，前者需要先返回默认设备，之后再创建一个queue,后者直接返回当前设备的默认队列。结果表明 <br />
(1) Linux 两种方式都能提高性能，而Windows只有在q_ = dpct::get_default_queue()才能提高性能. <br />
(2) 最新版本驱动不能提高windows Normals_Estimation上的性能. <br />
(3) 设置 SYCL_ENABLE_DEFAULT_CONTEXTS=1可以提高windows 上Normals_Estimation 性能. <br />
所以，我们需要把fixed_radius_index.h文件99行给出q_的初始化方式修改成**sycl::queue q_ = dpct::get_default_queue()**,或者环境设置**SYCL_ENABLE_DEFAULT_CONTEXTS=1**，这样Windows 和Linux上Normals_Estimation就有了差不多的性能.

