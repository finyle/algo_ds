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
import collections
import queue
import threading
from typing import List
from urllib.parse import urlsplit

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
        self.semaO.acquire()

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.semaH.acquire()
        releaseHydrogen()
        self.lock.acquire()
        if self.semaH._value == 0:
            self.semaO.release()

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.semaO.acquire()
        releaseOxygen()
        self.semaH.release(2)

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
    cars = [1,3,5,2,4]; directions = [2,1,2,4,3]; arrivalTimes = [10,20,30,40,50]
    Thread(target=t.carArrived, args = [turnGreen, crossCar]).start()