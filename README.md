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

The following is a comparison of setting and not setting the attribute A=b

<table border=0 cellpadding=0 cellspacing=0 width=517 style='border-collapse:
 collapse;table-layout:fixed;width:388pt'>
 <col width=64 style='width:48pt'>
 <col width=97 span=2 style='mso-width-source:userset;mso-width-alt:3547;
 width:73pt'>
 <col width=64 style='width:48pt'>
 <col width=195 style='mso-width-source:userset;mso-width-alt:7131;width:146pt'>
 <tr height=20 style='height:15.0pt'>
  <td colspan=5 height=20 class=xl65 width=517 style='height:15.0pt;width:388pt'>Build
  Hash Table</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl65 style='height:30.0pt;border-top:none'>LOOP</td>
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


## Summary
$~~~~~~~~$ This sample compares the performance impact of sycl::queue q_ and q_ = dpct::get_default_queue() on the establishment of a hash table. The former needs to return the default device first, and then create a queue, and the latter directly returns the default queue of the current device. The results show that both methods of Linux can improve performance, while Windows can only improve performance when **q_ = dpct::get_default_queue()**.At the same time, the latest driver board version does not significantly improve performance. Therefore, we need to modify the initialization method of q_ given in line 99 of the **fixed_radius_index.h** file to **sycl: :queue q_ = dpct::get_default_queue()**, so that Normals_Estimation has similar performance on Windows and Linux.



