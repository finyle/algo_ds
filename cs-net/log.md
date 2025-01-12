#### 1. libsponge 依赖 linux 环境, 在 wsl中执行编译指令, 需要手动修改 libsponge 中的cmakelists (include_directories 手动设置依赖文件路径,三个文件夹中环形依赖)
```config
include_directories ("util")            
include_directories ("tcp_helpers")
include_directories ("./")
```
```bash
cd libsponge && mkdir build && cd build
cmake ..
make (make -j4(并行编译))
```

#### 2. 在build目录下执行 make check_wget||lab_1 完成自动化测试, wsl中手动创建build并执行cmake.. 没有测试相关配置(etc/ doctest), clion依据 cs-ComputerNest中的cmakelists配置生成的cmake-build-debug路径下可完成自动化测试
```config
cmake_minimum_required (VERSION 2.8.5)
cmake_policy (SET CMP0054 NEW)
project (Sponge)

include (etc/build_defs.cmake)
include (etc/build_type.cmake)
include (etc/cflags.cmake)

include (etc/doxygen.cmake)

include (etc/clang_format.cmake)
include (etc/clang_tidy.cmake)
include (etc/cppcheck.cmake)

include_directories ("${PROJECT_SOURCE_DIR}/libsponge/util")
include_directories ("${PROJECT_SOURCE_DIR}/libsponge/tcp_helpers")
include_directories ("${PROJECT_SOURCE_DIR}/libsponge")

add_subdirectory ("${PROJECT_SOURCE_DIR}/libsponge") 

add_subdirectory ("${PROJECT_SOURCE_DIR}/apps")

add_subdirectory ("${PROJECT_SOURCE_DIR}/tests")

add_subdirectory ("${PROJECT_SOURCE_DIR}/doctests")

include (etc/tests.cmake)
```

**********************************************************************************

#### 3. lab0: internet的简单使用： a. fetch a web page; b. send a e-mail; 
```shell
# telnet 协议实现： telnet "url" protocol(http,stmp)
```
```c
// 实现 apps/webget & libsponge/byte_stream(内存中的字节流结构)
```

TCP(transmission control) 使用不可靠的datagram传输可靠的byte_stream

#### 3. lab1: 数据流处理(整流) stream_reassembler (获取一节子字符串及其头节点在stream中的索引，并将子串按索引拼接到stream中)

#### 3. lab2: tcp_recv: inBound byteStream(告知发送者成功收到多少数据(ack) & 发送这当前允许发送更多字节?(flow control))
```c
// tcpRecv: 1.接收来自peer的segment 2.拼接segment 3.计算ack number和window size; 3.
```
#### 3. lab3: tcp_send: outBound byteStream(怀疑发送内容丢失? & 何时重新发送丢失内容) 
```c
//  tcpSend: 发送bunch tcpSegments, 每个seg包含来自stream中的子串首位标记syn,fin作为stream的起始点；sender跟踪这些数字直到收到ack; 
//           同时周期调用 tick 确定时间用以判断 segments 是否超时为收到ack
```
#### 3. lab4: tcp_conn (endpoint) (测试依赖 网络环境)
```c
// tcpConn 遵循的3个基础规则：
// 1. recv: 
// 2. send: 
// 3. time pass:
```
************************************************************************************

network interface: 连接网络传输datagrams与链路层 ethernet frame的桥梁
适配之前的tcp协议栈 & router使用网络接口间的route datagrams 实现路由定向

#### 3. lab5: network_interface (测试依赖 网络环境)
```c
// arp (address resolution protocol)
```

####    lab6: route
```c
// add_route: 记录ip 路由表  
// route_one_datagram : 实现最长前缀匹配
```

####    lab7: network_simulator & complete network
```bash
# 在netstimulator的基础上实现基于自定义协议栈的网络通信,文件传输
```


***************************************************************************************
#### apps: 

1. webget(依赖pthread 多线程下载文件) err: open: no such file or dirctory

2. tcpdump(依赖 pcap 抓包 ): err: no initiating capture: (null): socket: Address family not supported by protocol

3. tcp_benchmark: CPU-limited throughput                : 0.19 Gbit/s

4. network_simulator: datagrams route success

