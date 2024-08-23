# 并发编程：
# 内置 multithreading, multiprocess
# 内置 asyncio
import asyncio
# leetcode 样例：
# 按序打印： 三个线程分别调用同一个实例的三个方法，顺序执行
# python 提供的并发原语： 互斥， 同步
## condition, lock, semaphore, event, barrier, queue,
from threading import Thread, Lock, RLock, Condition, Semaphore, Event, Barrier
from multiprocessing import Process, Lock, RLock, Condition, Semaphore, Event, Barrier, Queue
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
class Foo:
    def __init__(self):
        self.firstJobDone = Lock()
        self.secondJobDone = Lock()
        self.firstJobDone.acquire()
        self.secondJobDone.acquire()
    def first(self, printFirst: 'Callable[[], None]') -> None:
        printFirst()
        self.firstJobDone.release()
    def second(self, printSecond: 'Callable[[], None]') -> None:
        with self.firstJobDone:
            printSecond()
            self.secondJobDone.release()
    def third(self, printThird: 'Callable[[], None]') -> None:
        with self.secondJobDone:
            printThird()
def printFirst():
    print("1")
def printSecond():
    print("2")
def printThird():
    print(3)
class Foo_condition:
    def __init__(self):
        self.c = Condition()
        self.t = 0
    def first(self, printF: 'Callable[[], None]') -> None:
        self.res(0, printF)
    def second(self, printS: 'Callable[[], None]') -> None:
        self.res(1, printS)
    def third(self, printT: 'Callable[[], None]') -> None:
        self.res(2, printT)
    def res(self, val:int, func: 'Callable[[], None]') -> None:
        with self.c:
            self.c.wait_for(lambda :val == self.t)
            func()
            self.t += 1
            self.c.notify_all()

# python 协程 async & await
class Foo_async:
    def __init__(self):
        self.c = Condition()
        self.t = 0
    async def first(self, printF: 'Callable[[], None]') -> None:
        await self.res(0, printF)
    async def second(self, printS: 'Callable[[], None]') -> None:
        await self.res(1, printS)
    async def third(self, printT: 'Callable[[], None]') -> None:
        await self.res(2, printT)
    async def res(self, val:int, func: 'Callable[[], None]') -> None:
        with self.c:
            self.c.wait_for(lambda :val == self.t)
            func()
            self.t += 1
            self.c.notify_all()

async def printF():
    await print(1)
async def printS():
    await print(2)
async def printT():
    await print(3)

# 交替打印
# 打印0，奇偶数
# h20生成
# 优先阻塞队列
# 交替打印字符串
# 哲学家进餐
# 多线程网络爬虫
# 红绿灯模拟

# Java 并发编程实战样例: 分工 互斥 同步
# juc: 并发工具： Lock_Condition, Atomic
#      并行框架： Future, CompletableFuture, CompletionService, ForkJoinPool
# thrid-party: Guava, Dubbo(Netty), Disruptor, Hikaricp


# Go 并发编程实战样例
# sync: 并发工具： Lock, Cond, Map;
# go + chan: csp并发模型
# third-party: etcd, grpc-go
# csp concurrency pattern golang implement part of this
# gpm goroutine-processor-machine schedule model 


# cs149 并行计算样例
# simple task: 分形计算, sqrt, saxpy (ispc)
# compute graph task: custom executorPool (std::concurrency)
# cuda: saxpy, prefix_sum, circle_render (cuda.h)
# page-rank, bfs (图算法处理) (omp.h) #pragma

# 并发安全的容器
# trie, skiplist, b+tree, map, queue

# 并发io模型
# asyncio, netty, aio


# 内置 future 异步编程模型


if __name__ == '__main__':
    f = Foo()
    Thread(target = f.first, args = [printFirst]).start()
    Thread(target = f.third, args = [printThird]).start()
    Thread(target = f.second, args = [printSecond]).start()

    # Process(target = f.first, args = [printFirst]).start()
    # Process(target = f.third, args = [printThird]).start()
    # Process(target = f.second, args = [printSecond]).start()

    # with ThreadPoolExecutor(max_workers=3) as e:
    #     e.map(f.first, [printFirst])
    #     e.map(f.third, [printThird])
    #     e.map(f.second, [printSecond])

    # with ProcessPoolExecutor(max_workers=3) as e:
    #     e.map(f.first, [printFirst])
    #     e.map(f.third, [printThird])
    #     e.map(f.second, [printSecond])

    # 协程
    # f_a = Foo_async()
    # loop = asyncio.get_event_loop()
    # loop.run_until_complete(f_a.first(printFirst))
    # loop.run_until_complete(f_a.second(printSecond))
    # loop.run_until_complete(f_a.third(printThird))
    # loop.close()
    # t1.start()
    # t3.start()
    # t2.start()