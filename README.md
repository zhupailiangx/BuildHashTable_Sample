# Different ways of initializing queue on Linux and Windows
## Introduction
In the process of experiment Normals_Estimation, we found that in the file **fixed_radius_index.h** line 99, the initialization method of q_ is 
```bash
sycl::queue q_ 
```
However,after testing, it is found that the code performance of such an initialization method is very different on Linux and Windows.
So, write this example and first compare the performance difference between 
```bash
sycl::queue q_ and q_ = dpct::get_default_queue()
```
in building hash tables on Linux and Windows. Then, test SYCL_ENABLE_DEFAULT_CONTEXTS=1 and latest driver, hoping to help the next work.

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

### Test results
For the two queue initialization methods, we did five loop tests on Linux and Windows respectively. The relationship between the first loop and the subsequent loops can be viewed in the table below.

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
  <td class=xl66 style='border-top:none;border-left:none'>131ms</td>
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
  <td class=xl66 style='border-top:none;border-left:none'>127ms</td>
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

### Comparison of different driver versions on Windows
The driver version may be affected. We have added the experiment of the latest driver version. The following is the experimental comparison between the current driver version and the latest driver version
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


### Set Target Properties

The following is a comparison of setting and not setting the attribute SYCL_ENABLE_DEFAULT_CONTEXTS=1.
Enable (‘1’) or disable (‘0’) creation of default platform contexts in SYCL runtime. The default context for each platform contains all devices in the platform. Refer to Platform Default Contexts extension to learn more. Enabled by default on Linux and disabled on Windows.This extension also modifies the behavior of queue constructors. Queues will no longer create a new context upon construction. Instead, they will use the default context from the device’s platform.

<table border=0 cellpadding=0 cellspacing=0 width=813 style='border-collapse:
 collapse;table-layout:fixed;width:611pt'>
 <col width=64 style='width:48pt'>
 <col width=97 style='mso-width-source:userset;mso-width-alt:3547;width:73pt'>
 <col width=274 style='mso-width-source:userset;mso-width-alt:10020;width:206pt'>
 <col width=97 style='mso-width-source:userset;mso-width-alt:3547;width:73pt'>
 <col width=281 style='mso-width-source:userset;mso-width-alt:10276;width:211pt'>
 <tr height=20 style='height:15.0pt'>
  <td colspan=5 height=20 class=xl66 width=813 align="center" style='height:15.0pt;width:611pt'>Build
  Hash Table on Windows</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl66 style='height:30.0pt;border-top:none'>Loop</td>
  <td colspan=2 class=xl67 style='border-right:.5pt solid black;border-left:
  none'> </td>
  <td colspan=2 class=xl66 style='border-left:none'>SYCL_ENABLE_DEFAULT_CONTEXTS=1</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none;border-left:
  none'>sycl::queue q_</td>
  <td class=xl65 style='border-top:none;border-left:none'>sycl::queue
  q_=dpct::get_default_queue()</td>
  <td class=xl65 style='border-top:none;border-left:none'>sycl::queue q_</td>
  <td class=xl65 style='border-top:none;border-left:none'>sycl::queue
  q_=dpct::get_default_queue()</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 align=right style='height:15.0pt;border-top:none'>1</td>
  <td class=xl65 style='border-top:none;border-left:none'>102ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>95ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>108ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>94ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 align=right style='height:15.0pt;border-top:none'>2</td>
  <td class=xl65 style='border-top:none;border-left:none'>96ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 align=right style='height:15.0pt;border-top:none'>3</td>
  <td class=xl65 style='border-top:none;border-left:none'>95ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 align=right style='height:15.0pt;border-top:none'>4</td>
  <td class=xl65 style='border-top:none;border-left:none'>95ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>9ms</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 align=right style='height:15.0pt;border-top:none'>5</td>
  <td class=xl65 style='border-top:none;border-left:none'>96ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>9ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>7ms</td>
  <td class=xl65 style='border-top:none;border-left:none'>8ms</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=97 style='width:73pt'></td>
  <td width=274 style='width:206pt'></td>
  <td width=97 style='width:73pt'></td>
  <td width=281 style='width:211pt'></td>
 </tr>
 <![endif]>
</table>


## Summary
 This sample compares the performance impact of sycl::queue q_ and q_ = dpct::get_default_queue() on the establishment of a hash table. The former needs to return the default device first, and then create a queue, and the latter directly returns the default queue of the current device. The results show <br />
(1)  Both methods can improve performance on Linux systems, while Windows can only improve performance when **q_ = dpct::get_default_queue()**. <br />
(2) The latest version of the driver does not improve performance on Windows Normals_Estimation.<br />
(3) Setting **SYCL_ENABLE_DEFAULT_CONTEXTS=1** can improve the performance of Normals_Estimation on windows.<br />
Therefore, we need to modify the initialization method of q_ given in line 99 of the fixed_radius_index.h file to **sycl::queue q_ = dpct::get_default_queue()**, or the environment setting **SYCL_ENABLE_DEFAULT_CONTEXTS=1**, so that the Normals_Estimation on Windows and Linux is almost the same performance.


