# cs 相关课程
## mit: 操作系统， 分布式系统
## stanford: 计算机网络， 编译器， 并行计算
## cmu: 数据库

---
## mit 6.828 操作系统
### 1. op_log
```
0. wsl + c99 + qemu + win; xv6类unxi的教学os， jos基于xv6的实验原型；
** xv6 重新下载： https://github.com/xv6.git
** wsl 中通过makefile 编译出镜像文件，复制到windows启动： qemu-system-i386 -m 512 -drive file xv6.img,index=0,media=disk,format=raw -drive file fs.img,index=1,media=disk,format=raw (注意qemu启动镜像文件时的必要参数)
** gdb 模式，参考makefile文件，本地配置配置gdb环境后，启动参数加gdb 相关配置
1. no handout, https://pdos.csail.mit.edu/6.828/2018/schedule.html
1. lab/makefile 实验部分
2. vx6 + qemu  教学用os
3. c 语言系统编程常见错误： 自定义函数与系统调用内置函数重名：
** warning: conflicting types for built-in function： 编译是加上-fno-builtin或者-fno-builtin-FUNCTION 选项
** cast from pointer to integer of different size
** note: in expansion of macro ‘V2P’
** undefined reference to `kinit1'
下载qemu for windows; 重写xv6/makefile,实现基于wsl调用qumu for widnows (exp: bash: cmd.exe /C 'calc.exe')

4. 基于 python 实现 test
5. 依赖： inc + lib
```
### 2. handouts
```
lib 1-6: 
0. c prime
1. bootstrap                        boot
2. memory management(rom)           kern
3. user environment(process)        user
4. multitask (cpu)                  kern
5. fs file system (disk)            fs
6. net net driver (net card)        net

hw 1-12:
boot, shell, system calls, page allocation, cpu alarm, locks, uthreads, barrier, big files, crash, mmap
```
---
## mit 6.824 分布式系统
介绍分布式系统的抽象定义及部分具体实现，设计内容：容错，复制，一致性 (fault tolerance, replication, consistency)
### 1. op_log
```
0. golang 无三方包依赖， 导入自定义包：go mod init MyProject; import "MyProject/?" 基于plugin的二进制调用 & go_test

1. 基于 go-test 实现 test
```
### 2. handouts
```
1. map-reduce word-count 并行计算的经典例子：词频计数：
2. raft 协议实现， init; getState； raft节点集群基于时间戳确保所有节点的备份一致
3. key-value 基于server的键值服务实现： put, get, del, logMerge基于快照的日志合并
4. shared, replica groups: 分片间的状态同步： shared master 主分片负责同步所有节点状态
```
---
## cs143 编译器
### 1. op_log
```
0. wsl + cpp14, makefile 编译，复制到 wsl 中执行 make， 实现基于mips的编译器，一次执行二进制文件：
1. 实现基于cool 语言的编译器： 词法分析， 解析器， 语义分析， 代码生成4部分
3. 基于 make 实现 test
4. 实现编译器的前端(flex, bison, semant) + 后端(cgen); 可执行文件 并用脚本打包 shell 实现命令行参数解析，实现基于mips平台的编译器
```
### 2. handouts
```
1. cool 语言编译工具coolc 仅支持 i686 架构； 编译为在mips机器可识别的字节码并执行, apt install spim
2. apt install flex (assign2) lexer， 在cool.flex 中实现正则表达式，模式，行为
3. apt install  bison (assign3) parser， 在 cool.y 中实现 bison 功能：关键字匹配
4. semant (语义分析： 语法规则检测)， 在 semant.cc 实现抽象语法树生成
5. cgen (生成机器码) 在 cgen.cc 实现mips平台代码生成 (.s 文件)
```

## cs144 计算机网络
### op_log
```
0. wsl + cpp14
1. apt install libpcap-dev && apt install libpthread-stubs0-dev, 依赖libpcap
2. spone.util.buffer.cc 文件中缺少头文件： out_of_range是一个进程文件。 
   外文名 out_of_range 使用条件 使用时须包含头文件 #include<stdexcept>
3. 基于 lib-sponge 库，网络帧定义 + socket(send&revc) + 网络接口 + ip路由， 实现自定义的 tcp 协议栈， 并基于该协议栈实现简易的网络应用
4. 在apps 中 lab7 构建简单的网络应用，基于自定义协议栈的网络库

5. 基于 cmake 实现 cpp test
```
### 2. handouts
```
1. byte_stream
2. stream_reassembler
3. wrapping_integers
4. tcp recv&send&conn
5. net interface 
6. ip router
7. apps 
### simple internet application
### tcp 协议： 流装配； tcp receiver, sender, connection
### network interface
### IP 路由
### 实现网络基础设置infra with all component
```


## cs149 cpp 并行计算 parallel compute
### 1. op_log
```

```
### 2. handouts
```
1. fractal generation; sqrt; saxpy: 分形图片生成， 开平方， 线性方程组计算
2. build a task execution lib(synchronous bulk task launch | support execution of task graphs) 并行任务框架
3. a simple cuda render： 基于cuda的图片渲染
4. bfs & page-rank(graph processing)
```
--- 

## cmu15-445/645 bustub 数据库
### 1. op_log
```
0. wsl + cpp17
1. 依赖： libs: argparse, linenoise, libpg_query(命令行参数输入); googletest(测试框架); libfort(命令行表结构展示)； murmur3(hash); utf8proc(字符编码)
1.  error: catching polymorphic type ‘class bustub::TransactionAbortException’ by value [-Werror=catch-value=]
   33 |   } catch (TransactionAbortException e) { 
    多态异常只能通过 引用 或 指针捕获 &e || *e
2. 没有 handout， https://15445.courses.cs.cmu.edu/spring2023/assignments.html
3. cpp prime + bustub(buffer pool mangager, B+ tree index, query execution, concurrency control)

4. 基于 google-test 实现各组件的测试; build + cmake
5. tools: tools/shell， 实现简易 commandline sql
```
### 2. handouts
```
0. Trie (cow, thread safe, put get del), code foomat(make lint); memory leak
1. LRUKReplacer(evit, setEvitable, remove, size, recordAccess) BufferPoolManager(fetchPage, unpinPage, flushPage, newPage, delPage, flushAllPages) Basic&Read&WritePageGuard 页面替换算法， 并行io优化
2. B+Tree page(internel page, leaf page);  insert,search(single value); del; leaf scan; concurrent index 死锁检测， segfault
3. method executor(scan, insert, update, del); aggregation&join; sort limit executor, topN optimization 基于index的查询， 多连接查询，剪枝优化 column pruning， system catalog, 索引更新
4. lockManger(table lock, row lock), deadlcok detection(addEdge, hasCycle), ConcurretQuery(commit, abort); 查询下推预测， index pruning
```
