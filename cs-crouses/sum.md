# #######################################
# cs 相关课程

## cs143 编译器
### op_log
```
cool 语言编译器 coolc, 依赖mips执行(oline版本：https://shawnzhong.github.io/JsSpim)， 依赖 flex， bison工具 ; makefile: make test
0. wsl + cpp14, makefile 编译，复制到 wsl 中执行make
1. 实现基于cool 语言的编译器： 词法分析， 解析器， 语义分析， 代码生成4部分
1. cool 语言编译工具coolc 仅支持 i686 架构； 编译为在mips机器可识别的字节码并执行, apt install spim
2. apt install flex (assign2) lexer
3. apt install  bison (assign3) parser
4. semant (语义分析： 语法规则检测)
5. cgen (生成机器码)
```
### lab0-4
```
0. 编译 test.cl 为 test.s 并在 mips上运行
1. 编辑 flex 文件 cool.flex(lexical analyzer) 通过regular expression, patterns, actions定义分词规则, 由flex库生成 cool-flex.cc源文件，再编译为分词器 lexer
2. 编辑 cool.y(parser) 构建抽象语法树 全局变量保存语法树根节点  由 bison库生成 cool-parse.cc 源文件再编译为 parser
3. 编辑 semant.cc  遍历语法树，解析语义，lca实现语法checker方法：semant
4. 编辑 cgen.cc 代码生成器的3个部分：构建继承图, 全局数据常量, spim指令;基于语义和目标码规则生成目标代码：cgen
```
---

## cs144 计算机网络
### op_log
```
TCP 协议栈实现(webget, tcpdump)
0. wsl + cpp14； makefile 脚本编译， 通过cmakelists指定编译静态库，不依赖三方库实现自动化测试 cd build && make check-lab0
1. apt install libpcap-dev && apt install libpthread-stubs0-dev
2. spone.util.buffer.cc 文件中缺少头文件： out_of_range是一个进程文件。 
   外文名 out_of_range 使用条件 使用时须包含头文件 #include<stdexcept>
3. 基于 lib-sponge 库，实现自定义的 tcp 协议栈： streamassemble, tcp recv&send&conn, net interface ,ip router 
```
### lab0-7
```
0. 网络数据包在内存中的结构： byte_stream
1. 网络数据包的拼接： stream_reassembler
2. fin, ack 确定收包数量，实现流控(flow control): tcp recv
3. clock 丢包检测，重发：tcp send
4. 实现特定规则确保不稳定的网络环境中实现可靠的数据传输：tcp connection
5. 链路层datagram 数据转化：network interface
6. 暂存链路层ip 并实现基于最大前缀的路由: ip router
7. webget(pthread), tcpdump(pcap)
```

## cs149 并行计算
### op_log
```
单机多核并行计算样例code snippets： simd执行向量化代码，ispc编译器； #pragma omp g++编译器指令； gpu并行计算(cada); 并行任务框架
0. 实验一需要 ispc 编译器; 实验三 需要 cuda-toolkit和GPU驱动; 试验四 需要下载图数据， makefile脚本
1. 多核CPU并行计算： ipsc 并行优化编译器， simd 向量化代码 mandelbrot(分形图片生成), vecintrin(向量化), mandelbrot(ispc), sqrt, saxpy
2. 并行计算框架： 异步任务创建执行， 图任务执行 asynchronized task, graph
3. GPU 并行计算：基于cuda(nvcc)的编程： 实现简易render(支持gpu加速) saxpy, scan, render
4. cpp 并行计算 #pragma omp parrlel 实现并行图遍历算法： page_rank, bfs
```

# ############################################
--- 

## cmu15-445/645 bustub 数据库
### op_log
```
仅实现buffer pool manager,B+树索引 页表, sql 查询执行，b+树并发支持,事务支持 大量使用cpp智能指针 迭代器
0. wsl + cpp17, 依赖三方库： googletest, linenoise, libpq_query; cmakelists构建项目; cd build && make check-tests
1.  error: catching polymorphic type ‘class bustub::TransactionAbortException’ by value [-Werror=catch-value=]
   33 |   } catch (TransactionAbortException e) { 
    多态异常只能通过 引用 或 指针捕获 &e || *e
2. 没有 handout， https://15445.courses.cs.cmu.edu/spring2023/assignments.html
3. cpp prime + bustub(buffer pool mangager, B+ tree index, query execution, concurrency control)
```
### lab0-4
```
0. 线程安全的： Trie (cow, thread safe, put get del), code foomat(make lint); memory leak
1. 内存池管理：BufferPoolManager(fetchPage, unpinPage, flushPage, newPage, delPage, flushAllPages); LRUKReplacer(evit, setEvitable, remove, size, recordAccess) Basic&Read&WritePageGuard 页面替换算法， 并行io优化
2. b+树 storage(索引 页(数据库最小存储单元) 表(磁盘上的物理表,表数据落盘))： B+Tree page(internel page, leaf page);  insert,search(single value); del; leaf scan; 
暂不支持索引数据落盘
3. sql语言解析并执行： method executor(scan, insert, update, del); aggregation&join; sort limit executor, topN optimization 基于index的查询， 多连接查询，剪枝优化 column pruning， system catalog, 索引更新
4. 数据库事务实现 锁管理器， 事务管理器： lockManger(table lock, row lock), deadlcok detection(addEdge, hasCycle), ConcurretQuery(begin, commit, abort); 查询下推预测， index pruning

```
# #############################################
---
## mit6.828 操作系统
### op_log
```
0. wsl + c99 + qemu + win; xv6类unxi的教学os， jos基于xv6的实验原型；
** xv6 重新下载： https://github.com/xv6.git
** wsl 中通过makefile 编译出镜像文件，复制到windows启动： qemu-system-i386 -m 512 -drive file=xv6.img,index=0,media=disk,format=raw -drive file=fs.img,index=1,media=disk,format=raw (注意qemu启动镜像文件时的必要参数)
** gdb 模式，参考makefile文件，本地配置配置gdb环境后，启动参数加gdb 相关配置
1. no handout, https://pdos.csail.mit.edu/6.828/2018/schedule.html
1. lab/makefile 实验部分
2. vx6 + qemu  教学用os
3. c 语言系统编程常见错误： 自定义函数与系统调用内置函数重名：
** warning: conflicting types for built-in function： 编译时加上-fno-builtin或者-fno-builtin-FUNCTION 选项
** cast from pointer to integer of different size
** note: in expansion of macro ‘V2P’
** undefined reference to `kinit1'
下载qemu for windows; 重写xv6/makefile,实现基于wsl调用qumu for widnows (exp: bash: cmd.exe /C 'calc.exe')
```
### lab0-6
```
0. c prime
1. debug 汇编 boot.S 理解os加载执行过程： boot.S 汇编实现os img加载: 
2. 内存管理：物理内存 & 虚拟内存：memory management(rom) pmap 页表初始化 分配 回收
3. 进程管理： user environment(process) env初始化 创建 运行 销毁 回收; trap中断 初始化 分配; syscall 系统调用
4. 多进程支持： kern： multiprocess (cpu) sched 调度; ((系统调用进程创建 销毁 分配内存,ipc))fork 允许进程复制; ipc 进程通信
5. 文件系统spawn :fs file system (disk) fs磁盘数据结构 bc blockcache ide server文件系统api
6. e1000网卡驱动+tcp协议栈，在os上实现文件传输： net net driver (net card) pci 网卡驱动初始化, net/input&output 网卡数据收发(系统调用) 
```
---

## mit6.824 分布式系统 os: 介绍分布式系统的抽象定义及部分具体实现，设计内容：容错，复制，一致性 (fault tolerance, replication, consistency)
### op_log
```
0. golang 无三方包依赖， 导入自定义包：go mod init MyProject; import "MyProject/?"
1. go标准库 支持 rpc， test 测试框架 无需makefile脚本
http://nil.csail.mit.edu/6.5840/2023/
http://nil.csail.mit.edu/6.5840/2023/papers/raft-extended.pdf

```
### lab1-4
```
1. map-reduce word-count 并行计算的经典例子：词频计数：word-count src/main shell 脚本执行测试
2. raft 协议实现，raft节点集群基于时间戳确保所有节点的备份一致；领导选举 日志 持久化 日志合并 appendLogEntry(), requestForVote(); 协议规则
3. client-server架构的k-v数据库: put, get, del, logMerge基于快照的日志合并
4. 基于raft协议为kv数据体提供分布式支持: 分片间的状态同步：shared master主分片负责同步所有节点状态
```