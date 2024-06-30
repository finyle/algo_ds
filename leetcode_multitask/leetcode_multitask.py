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
import time
from typing import Callable
from collections import deque

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

class FooBar:
    def __init__(self, n:int):
        self.n = n 
        self.LockFoo = Lock()
        self.LockBar = Lock()
        self.LockBar.acquire()
    def foo(self, printFoo: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.LockFoo.acquire()  # foo 获得锁
            printFoo()
            self.LockBar.release()  # bar 释放锁

    def bar(self, printBar: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.LockBar.acquire()  # bar 获得锁
            printBar()
            self.LockFoo.release()  # foo 释放锁

# 6种方法： Semaphore CountDownLatch Thread.yield Locksupport  ReentrantLock+condition
class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n + 1
        self.Zero = Semaphore(1)
        self.Even = Semaphore(0)
        self.Odd = Semaphore(0)

    # printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n):
            self.Zero.acquire()
            printNumber(0)
            if i % 2 == 1:
                self.Odd.release()
            else:
                self.Even.release()

    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n):
            if i % 2 == 0:
                self.Even.acquire()
                printNumber(i)
                self.Zero.release()

    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n):
            if i % 2 == 1:
                self.Odd.acquire()
                printNumber(i)
                self.Zero.release()

class H2O:
    def __init__(self):
        self.semaH = Semaphore(2)
        self.semaO = Semaphore(1)
        self.lock = Lock()

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.semaH.acquire()
        releaseHydrogen()
        self.lock.acquire()
        if self.semaH._value == 0 and self.semaO._value == 0:
            self.semaH.release()
            self.semaH.release()
            self.semaO.release()
        self.lock.release()

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.semaO.acquire()
        releaseOxygen()
        self.lock.acquire()
        if self.semaH._value == 0 and self.semaO._value == 0:
            self.semaH.release()
            self.semaH.release()
            self.semaO.release()
        self.lock.release()

class BoundedBlockingQueue():

# 3种方法： semaphore synchronized lock+condition

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.en = Semaphore(capacity)
        self.de = Semaphore(0)
        self.queue = deque()
        self.n = 0

    def size(self) -> int:
        return self.n

    def enqueue(self, element: int) -> None: # 队首添加元素
        self.n += 1
        self.en.acquire()
        self.queue.appendleft(element)
        self.de.release()

    def dequeue(self) -> int: # 队尾去除元素
        self.n -= 1
        self.de.acquire()
        val = self.queue.pop()
        self.en.release()
        return val
    
class FizzBuzz:
    def __init__(self, n: int):
        self.n = n
        self.sem_fizz = Semaphore(0)
        self.sem_buzz = Semaphore(0)
        self.sem_fibu = Semaphore(0)
        self.sem_num = Semaphore(1)
    # printFizz() outputs "fizz"
    def fizz(self, printFizz: 'Callable[[], None]') -> None:
        for i in range(1, self.n+1):
            if i % 3 == 0 and i % 5 != 0:
                self.sem_fizz.acquire()
                printFizz()
                self.sem_num.release()
    # printBuzz() outputs "buzz"
    def buzz(self, printBuzz: 'Callable[[], None]') -> None:
        for i in range(1, self.n+1):
            if i % 3 != 0 and i % 5 == 0:
                self.sem_buzz.acquire()
                printBuzz()
                self.sem_num.release()
    # printFizzBuzz() outputs "fizzbuzz"
    def fizzbuzz(self, printFizzBuzz: 'Callable[[], None]') -> None:
        for i in range(1, self.n+1):
            if i % 3 == 0 and i % 5 == 0:
                self.sem_fibu.acquire()
                printFizzBuzz()
                self.sem_num.release()
    # printNumber(x) outputs "x", where x is an integer.
    def number(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n+1):
            self.sem_num.acquire()
            if i % 3 == 0 and i % 5 == 0:
                self.sem_fibu.release()
            elif i % 3 == 0:
                self.sem_fizz.release()
            elif i % 5 == 0:
                self.sem_buzz.release()
            else:
                printNumber(i)
                self.sem_num.release()

forkslock = Lock()
forks = [1] * 5
class DiningPhilosophers:
    # call the functions directly to execute, for example, eat()
    def wantsToEat(self,
                   philosopher: int,
                   pickLeftFork: 'Callable[[], None]',
                   pickRightFork: 'Callable[[], None]',
                   eat: 'Callable[[], None]',
                   putLeftFork: 'Callable[[], None]',
                   putRightFork: 'Callable[[], None]') -> None:
        leftforkid = 4 if philosopher - 1 < 0 else philosopher - 1
        rightforkid = philosopher
        iseat = False
        while not iseat:
            if forkslock.acquire(False):
                if forks[leftforkid] and forks[rightforkid]:
                    forks[leftforkid] = 0
                    forks[rightforkid] = 0
                    # print(philosopher,'pickup')
                    forkslock.release()
                    pickLeftFork()
                    pickRightFork()
                    # print(philosopher,'eat')
                    eat()
                    iseat = True
                    putLeftFork()
                    forks[leftforkid] = 1
                    putRightFork()
                    forks[rightforkid] = 1
                    # print(philosopher,'eatdone')
                else:
                    forkslock.release()
                    time.sleep(0.001)

    class Solution:
    
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
# 1242. 给你一个初始地址 startUrl 和一个 HTML 解析器接口 HtmlParser，请你实现一个 多线程的网页爬虫，用于获取与 startUrl 有 相同主机名 的所有链接。
#
# 以 任意 顺序返回爬虫获取的路径。
#
# 爬虫应该遵循：
#
# 从 startUrl 开始
# 调用 HtmlParser.getUrls(url) 从指定网页路径获得的所有路径。
# 不要抓取相同的链接两次。
# 仅浏览与 startUrl 相同主机名 的链接。
#
#
# 如上图所示，主机名是 example.org 。简单起见，你可以假设所有链接都采用 http 协议，并且没有指定 端口号。举个例子，链接 http://leetcode.com/problems 和链接 http://leetcode.com/contest 属于同一个 主机名， 而 http://example.org/test 与 http://example.com/abc 并不属于同一个 主机名。
#
# HtmlParser 的接口定义如下：
#
# interface HtmlParser {
# // Return a list of all urls from a webpage of given url.
# // This is a blocking call, that means it will do HTTP request and return when this request is finished.
# public List<String> getUrls(String url);
# }
# 注意一点，getUrls(String url) 模拟执行一个HTTP的请求。 你可以将它当做一个阻塞式的方法，直到请求结束。 getUrls(String url) 保证会在 15ms 内返回所有的路径。 单线程的方案会超过时间限制，你能用多线程方案做的更好吗？
#
# 对于问题所需的功能，下面提供了两个例子。为了方便自定义测试，你可以声明三个变量 urls，edges 和 startUrl。但要注意你只能在代码中访问 startUrl，并不能直接访问 urls 和 edges。
#
# 拓展问题：
#
# 假设我们要要抓取 10000 个节点和 10 亿个路径。并且在每个节点部署相同的的软件。软件可以发现所有的节点。我们必须尽可能减少机器之间的通讯，并确保每个节点负载均衡。你将如何设计这个网页爬虫？
# 如果有一个节点发生故障不工作该怎么办？
# 如何确认爬虫任务已经完成？


# 4中实现方式：自定义Thread； 线程池； 线程安全容器；BFS自定义线程池

# 输入：
# urls = [
#   "http://news.yahoo.com",
#   "http://news.yahoo.com/news",
#   "http://news.yahoo.com/news/topics/",
#   "http://news.google.com",
#   "http://news.yahoo.com/us"
# ]
# edges = [[2,0],[2,1],[3,2],[3,1],[0,4]]
# startUrl = "http://news.yahoo.com/news/topics/"

# 输出：[
#   "http://news.yahoo.com",
#   "http://news.yahoo.com/news",
#   "http://news.yahoo.com/news/topics/",
#   "http://news.yahoo.com/us"
# ]
#

import collections
import queue
import threading
from typing import List
from urllib.parse import urlsplit

class Solution:
    def __init__(self):
        self.queue = collections.deque()

    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        domain = urlsplit(startUrl).netloc
        request_queue = queue.Queue() # 多生产者，多消费者， 线程安全队列
        result_queue = queue.Queue()
        request_queue.put(startUrl)

        for _ in range(5): # 启动线程
            thread = threading.Thread(target=self._run, args=(domain, htmlParser, request_queue, result_queue))
            thread.daemon = True
            thread.start()
        running = 1
        visited = {startUrl}

        while running: # url去重，避免重复爬取
            for url in result_queue.get():
                if url not in visited:
                    visited.add(url)
                    request_queue.put(url)
                    running += 1
            running -= 1
        return list(visited)

    def _run(self, domain, htmlParser, request_queue, result_queue): # 多线程处理函数
        while True:
            now_url = request_queue.get()
            next_url_lst = []
            for next_url in htmlParser.getUrls(now_url):
                if domain == urlsplit(next_url).netloc:
                    next_url_lst.append(next_url)
            result_queue.put(next_url_lst)

class HtmlParser:
    def getUrl(self, url:str) -> List[str]: # 模拟执行http请求，返回所有与url关联的urls
        ans = []
        ans.append(url.split("."))
        return ans

class TrafficLight:
    def __init__(self):
        self.lock = Lock()
        self.now = 1

    def carArrived(
            self,
            carId: int, # 车id
            roadId: int, # 道路id， 两条路十字交叉
            direction: int, # 车的朝向id， 4个方向
            turnGreen: 'Callable[[], None]', # 调用绿灯函数，将当前道路等变绿
            crossCar: 'Callable[[], None]' # 调用通车函数，使车通过路口
    ):
        self.lock.acquire()
        if self.now == roadId:
            crossCar()
        else:
            self.now = roadId
            turnGreen()
            crossCar()
        self.lock.release()


if __name__ == '__main__':
    # f = Foo()
    # def printFirst(): print(1)
    # def printSecond(): print(2)
    # def printThird(): print(3)
    # Thread(target = f.first, args = [printFirst]).start()
    # Thread(target = f.third, args = [printThird]).start()
    # Thread(target = f.second, args = [printSecond]).start()

    # f2 = FooBar(100)
    # def printFoo(): print("foo")
    # def printBar(): print("bar")
    # Thread(target=f2.foo, args = [printFoo]).start()
    # Thread(target=f2.bar, args = [printBar]).start()

    # z = ZeroEvenOdd(100)
    # def printNumber(n: int): print(n)
    # Thread(target = z.zero, args = [printNumber]).start()
    # Thread(target = z.even, args = [printNumber]).start()
    # Thread(target = z.odd, args = [printNumber]).start()

    # h = H2O()
    # def releaseHydrogen(): print("H")
    # def releaseOxygen(): print("O")
    # Thread(target = h.hydrogen, args = [releaseHydrogen]).start()
    # Thread(target = h.oxygen, args = [releaseOxygen]).start()

    # c = BoundedBlockingQueue(2)
    # Thread(target=c.enqueue, args = [1]).start()
    # # Thread(target = c.dequeue).start()
    # print(c.size())

    # fb = FizzBuzz(15)
    # def printNumber(n:int): print(n)
    # def printFizz(): print('fizz')
    # def printBuzz(): print('buzz')
    # def printFizzBuzz(): print('fizzbuzz')
    # Thread(target = fb.fizz, args = [printFizz]).start()
    # Thread(target = fb.buzz, args = [printBuzz]).start()
    # Thread(target = fb.fizzbuzz, args = [printFizzBuzz]).start()
    # Thread(target = fb.number, args = [printNumber]).start()

    # d = DiningPhilosophers()
    # def pickLeftFork(): print([None, 1, 1])
    # def pickLeftFork(): print([None, 1, 1])
    # def pickLeftFork(): print([None, 1, 1])
    # def pickLeftFork(): print([None, 1, 1])
    # Thread(target = d.wantsToEat, args = [1, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork]).start()
    # Thread(target = d.wantsToEat, args = [1, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork]).start()
    # Thread(target = d.wantsToEat, args = [1, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork]).start()
    # Thread(target = d.wantsToEat, args = [1, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork]).start()
    # Thread(target = d.wantsToEat, args = [1, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork]).start()

    # s = Solution()
    # p = HtmlParser()
    # print(s.crawl(s, p))

    t = TrafficLight()
    def turnGreen(): print("turnGreen")
    def crossCar(): print("crossCar")
    Thread(target=t.carArrived, args = [turnGreen, crossCar])