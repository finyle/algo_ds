package main

import (
	"fmt"
)

/*
https://go.dev/doc/effective_go#concurrency
shared by communicating
goroutines
channel
channels of channels
parallelization
*/

/*
https://zhuanlan.zhihu.com/p/680188944
创建并发任务
基于chan 进行数据传输和同步
使用互斥锁保护共享资源
*/

/*
CSP（Communicating Sequential Processes）和GMP（Goroutine Multiplexing Pattern 或者有时指的是 Golang Scheduler and Process Model）是两个不同的概念，在Go语言中分别代表着不同的层面和技术思想。

CSP（Communicating Sequential Processes）：
CSP是一种并发编程模型，最初由Tony Hoare提出，主张通过进程间的通信来组织并发行为，而不是通过共享内存。在Go语言中，CSP的概念体现在goroutines（轻量级线程）和channels（通道）的设计上。Goroutines可以通过通道发送和接收数据来进行同步和通信，这样可以有效地解决并发场景下的数据竞争等问题。

GMP（Goroutine Multiplexing Pattern）：
这个术语可能并不是标准的Go语言文献中使用的官方概念，但这里我们可以理解为Golang中的并发调度模式或者Goroutine与操作系统的交互方式。Go语言的运行时环境提供了一个高效的Goroutine调度器（GMP的一部分），它可以将大量的Goroutines映射到少量的操作系统线程上，并通过M:N调度模型来高效利用CPU资源。调度器负责在Goroutine之间切换上下文，当一个Goroutine阻塞（例如等待I/O操作或channel通信）时，调度器会自动切换至另一个就绪的Goroutine执行，从而实现并发执行的效果。

总结来说，CSP是Go语言实现并发模型的理念基础，它指导了goroutines和channels的设计；而GMP则是Go语言在实现层面如何调度和管理这些goroutines的具体机制。两者结合构成了Go语言简洁而强大的并发编程特性。
*/

/*
在学习 Go 语言的 GMP 调度器之前，原以为 GMP 底层原理较为复杂，要花很多时间和精力才能掌握，亲自下场学习之后，才发现其实并不复杂，只需三个多小时就足够：先花半个多小时，学习下刘丹冰Aceld 的 B 站讲解视频《Golang深入理解GPM模型》，然后花两个小时，结合《Go语言设计和实现》6.5节调度器的内容阅读下相关源码，最后，可以快速看看 GoLang-Scheduling In Go 前两篇文章的中译版，这样可以较快掌握 GMP 调度器的设计思想。当然，如果希望理解的更加透彻，还需要仔细钻研几遍源码，并学习其他各种资料，尤其是 Go 开发者的文章，最好能够输出一篇文章，以加深头脑中神经元的连接和对事情本质的理解，本文就是这一学习思路的结果，希望能帮助到感兴趣的同学。
本文的代码基于 Go1.18.1 版本，跟 Go1.14 版本的调度器的主要逻辑相比，依然没有大的变化，目前看到的改动是调度循环的 runtime.findrunnable() 函数，抽取了多个逻辑封装成了新的方法，比如 M 从 其他 P 上偷取 G 的 runtime.stealWork()。0. 结论先给出整篇文章的结论和大纲，便于大家获取重点：\
1. 为了解决 Go 早期多线程 M 对应多协程 G 调度器的全局锁、中心化状态带来的锁竞争导致的性能下降等问题，Go 开发者引入了处理器 P 结构，形成了当前经典的 GMP 调度模型；\
2. Go 调度器是指：运行时在用户态提供的多个函数组成的一种机制，目的是高效地调度 G 到 M上去执行；\
3. Go 调度器的核心思想是：尽可能复用线程 M，避免频繁的线程创建和销毁；利用多核并行能力，限制同时运行（不包含阻塞）的 M 线程数 等于 CPU 的核心数目； Work Stealing 任务窃取机制，M 可以从其他 M 绑定的 P 的运行队列偷取 G 执行；Hand Off 交接机制，为了提高效率，M 阻塞时，会将 M 上 P 的运行队列交给其他 M 执行；基于协作的抢占机制，为了保证公平性和防止 Goroutine 饥饿问题，Go 程序会保证每个 G 运行 10ms 就让出 M，交给其他 G 去执行，这个 G 运行 10ms 就让出 M 的机制，是由单独的系统监控线程通过 retake() 函数给当前的 G 发送抢占信号实现的，如果所在的 P 没有陷入系统调用且没有满，让出的 G 优先进入本地 P 队列，否则进入全局队列；；基于信号的真抢占机制，Go1.14 引入了基于信号的抢占式调度机制，解决了 GC 垃圾回收和栈扫描时无法被抢占的问题；\
4. 由于数据局部性，新创建的 G 优先放入本地队列，在本地队列满了时，会将本地队列的一半 G 和新创建的 G 打乱顺序，一起放入全局队列；本地队列如果一直没有满，也不用担心，全局队列的 G 永远会有 1/61 的机会被获取到，调度循环中，优先从本地队列获取 G 执行，不过每隔61次，就会直接从全局队列获取，至于为啥是 61 次，Dmitry 的视频讲解了，就是要一个既不大又不小的数，而且不能跟其他的常见的2的幂次方的数如 64 或 48 重合；\
5. M 优先执行其所绑定的 P 的本地运行队列中的 G，如果本地队列没有 G，则会从全局队列获取，为了提高效率和负载均衡，会从全局队列获取多个 G，而不是只取一个，个数是自己应该从全局队列中承担的，globrunqsize / nprocs + 1；同样，当全局队列没有时，会从其他 M 的 P 上偷取 G 来运行，偷取的个数通常是其他 P 运行队列的一半；\
6. G 在运行时中的状态可以简化成三种：等待中_Gwaiting、可运行_Grunnable、运行中_Grunning，运行期间大部分情况是在这三种状态间来回切换；\
7. M 的状态可以简化为只有两种：自旋和非自旋；自旋状态，表示 M 绑定了 P 又没有获取 G；非自旋状态，表示正在执行 Go 代码中，或正在进入系统调用，或空闲；\8.
P 结构体中最重要的，是持有一个可运行 G 的长度为 256 的本地环形队列，可以通过 CAS 的方式无锁访问，跟需要加锁访问的全局队列 schedt.runq 相对应；\
9. 调度器的启动逻辑是：初始化 g0 和 m0，并将二者互相绑定， m0 是程序启动后的初始线程，g0 是 m0 线程的系统栈代表的 G 结构体，负责普通 G 在 M 上的调度切换 --> runtime.schedinit()：负责M、P 的初始化过程，分别调用runtime.mcommoninit() 初始化 M 的全局队列allm 、调用 runtime.procresize() 初始化全局 P 队列 allp --> runtime.newproc()：负责获取空闲的 G 或创建新的 G --> runtime.mstart() 启动调度循环；；\
10. 调度器的循环逻辑是：运行函数 schedule() --> 通过 runtime.globrunqget() 从全局队列、通过 runtime.runqget() 从 P 本地队列、 runtime.findrunnable 从各个地方，获取一个可执行的 G --> 调用 runtime.execute() 执行 G --> 调用 runtime.gogo() 在汇编代码层面上真正执行G --> 调用 runtime.goexit0() 执行 G 的清理工作，重新将 G 加入 P 的空闲队列 --> 调用 runtime.schedule() 进入下一次调度循环。
*/

/*
GC 相关的代码在runtime/mgc.go文件下。通过注释介绍我们可以知道 GC 一共分为4个阶段：
sweep termination（清理终止） 会触发 STW ，所有的 P（处理器） 都会进入 safe-point（安全点）；清理未被清理的 span ，不知道什么是 span 的同学可以看看我的：详解Go中内存分配源码实现 https://www.luozhiyun.com/archives/434；
the mark phase（标记阶段） 将 _GCoff GC 状态 改成  _GCmark，开启 Write Barrier （写入屏障）、mutator  assists（协助线程），将根对象入队；恢复程序执行，mark workers（标记进程）和 mutator  assists（协助线程）会开始并发标记内存中的对象。对于任何指针写入和新的指针值，都会被写屏障覆盖，而所有新创建的对象都会被直接标记成黑色；GC 执行根节点的标记，这包括扫描所有的栈、全局对象以及不在堆中的运行时数据结构。扫描goroutine 栈绘导致 goroutine 停止，并对栈上找到的所有指针加置灰，然后继续执行 goroutine。GC 在遍历灰色对象队列的时候，会将灰色对象变成黑色，并将该对象指向的对象置灰；GC 会使用分布式终止算法（distributed termination algorithm）来检测何时不再有根标记作业或灰色对象，如果没有了 GC 会转为mark termination（标记终止）；
mark termination（标记终止） STW，然后将 GC 阶段转为 _GCmarktermination,关闭 GC 工作线程以及 mutator  assists（协助线程）；执行清理，如 flush mcache；
the sweep phase（清理阶段） 将 GC 状态转变至 _GCoff，初始化清理状态并关闭 Write Barrier（写入屏障）；恢复程序执行，从此开始新创建的对象都是白色的；后台并发清理所有的内存管理单元
*/
type FooBar struct {
	n       int
	fooChan chan bool // 用于 Foo 完成后通知 Bar
	//barChan chan bool // 用于 Bar 完成后通知 Foo
}

func NewFooBar(n int) *FooBar {
	fb := &FooBar{
		n:       n,
		fooChan: make(chan bool, 1), // 缓冲为 1 以避免初始的阻塞
		//barChan: make(chan bool),
	}
	fb.fooChan <- true
	return fb
}

func (fb *FooBar) Foo(printFoo func()) {
	for i := 0; i < fb.n; i++ {
		<-fb.fooChan // 等待通知
		printFoo()
		//fb.barChan <- true // 通知 Bar
		fb.fooChan <- true
	}
}

func (fb *FooBar) Bar(printBar func()) {
	for i := 0; i < fb.n; i++ {
		//<-fb.barChan // 等待通知
		<-fb.fooChan
		printBar()
		fb.fooChan <- true // 通知 Foo
	}
}

func printFoo() { fmt.Println("foo") }
func printBar() { fmt.Println("bar") }

func main() {
	f := NewFooBar(10)
	go f.Bar(printBar)
	go f.Foo(printFoo)
	//fmt.Println("hi")
}
