lab1
1. rom bios: gdb si(步进)查看 bios加载
2. boot loader: 
   3. 在0x7c00 (boot sector的加载地址)打断点，trace boot.S; 比较boot/boot.S和obj/boot/boot.S的区别
   4. trace main.c 中的bootmain(), 查看每次redsect的地址是否相同
   load kernel: 
      5. 理解 c 中的pointer
      6. 修改boot/Makefrag 中的link address(0x7c00)，重新编译，查看错误
      7. gdb x(x/Nx ADDR) 打印在addr的n个单词的内存地址；重启机器,在0x00100000处检测8个单词;再查看bootloader 加载 kernel的地址 是否相同
3. 在 kern/entry.S 中的 movl %eax, %cr0 处打断点
   4. 找到在obj/kern/kernel.asm中的test_backtrace()函数，断点调试
   5. debuginfo_eip 中的 __STAB_*来自 kern/kernel.ld 中的 __STAB_*

lab2 (内存管理: 两部分(kernel使用物理内存分配器实现内存的分配回收，维护数据结构记录那些内存被回收，分配，共享))
相关文件(inc/memlayout.h; kern/pmap.c & pmap.h & kclock.h & kclock.c), 特别注意 memlayout.h & pmap.h || inc/mmu.h
1. physical mem: 实现kern/pmap.c 中的5个函数： boot_alloc, mem_init, page_init, page_alloc, page_free 
2. virtual mem: gdb 只允许通过虚拟地址访问qemu的内存； qemu monitor命令 xp 可以 inspect 物理地址; 在启动qemu的cmd中ctrl-a c && xp, 在gdb中键入x
   3. page table 页表管理： 实现kern/pmap.c 中的5个函数： pgdir_walk(), boot_map_region(), page_lookup(), page_remove(), page_insert()
4. kernel address space： 完成 kern/pmap.c 中mem_init()在调用完 check_page()后的内容


lab3 (创建受保护的用户进程空间，增强kernel用以跟踪用户进程，创建于给单独的用户进程，向其中加载如一个程序镜像并启动 & 内核处理来自进程的系统调用并捕获任何由它造成的异常)
相关文件：
inc/ evn.h          进程结构定义
     trap.h         trap
     syscall.h      进程至kernel的系统调用    
     lib.h          进程 support lib
kern/ evn           kernel中的进程结构定义
      trap          trap
      syscall       kernel私有的系统调用
      trapentry.S   entry-point 控制trap的汇编
lib/  Makefrag       构建进程库的makefile参数   
      entry.S        进程的汇编 entry-point
      libmain.c      entry.S的启动入口
      syscall        进程的panic实现
      console        进程的console实现 putchar, getchar
      exit           进程的exit实现   
      panic          进程的panic实现
user/ *
进程与异常捕获
1. 修改kern/pmap.c中的mem_init() 
2. 完成kern/env.c 中的6个函数： env_init, env_setup_vm, region_alloc, load_icode, env_create, env_run 
3. 修改 trapentry.S 和 trap.c 实现trap

page fault, breakpoint exceptions and syscall
4. 修改 trap_dispatch() 
5. 编辑 kern/trapentry.S, kern/trap.c 处理内核中的异常 
6. 修改 lib/libmain.c和 lib/exit.c 让其在破坏进程时被kernel监控到
7. 修改 kern/trap.c syscall.c



lab4 (多进程支持3部分：
    a.round-robin调度算法,添加基础的系统调用(创建销毁进程，分配映射内存);)
    b.实现类unix风格的fork 允许进程复制
    c.实现进程进间通信(实现同步)
相关文件: 
kern/cpu 
     mpconfig
     lapic
     