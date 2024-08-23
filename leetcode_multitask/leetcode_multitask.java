// 高性能限流器： Guava RateLimiter (40, 38)
// 0. 生产者-消费之 实现令牌桶： 并发环境下不能使用
// 1.令牌桶限流算法： 记录并动态计算下一令牌发放的时间 (未使用定时器)
// 2. Guava RateLimiter 扩展了标准的令牌桶算法，比如还能支持预热功能。对于按需加载的缓存来说，预热后缓存能支持 5 万 TPS 的并发，但是在预热前 5 万 TPS 的并发直接就把缓存击垮了，所以如果需要给该缓存限流，限流器也需要支持预热功能，在初始阶段，限制的流速 r 很小，但是动态增长的。预热功能的实现非常复杂，Guava 构建了一个积分函数来解决这个问题

// 高性能网络框架： Netty
// 1. 事件循环： 一个网络连接只会对应到一个 Java 线程： 对于一个网络连接的事件处理是单线程的，这样就避免了各种并发问题。
// 2. Netty 做了很多优化，例如优化了 ByteBuffer、支持零拷贝等等，和并发编程相关的就是它的线程模型了。Netty 的线程模型设计得很精巧，每个网络连接都关联到了一个线程上，这样做的好处是：对于一个网络连接，读写操作都是单线程执行的，从而避免了并发程序的各种问题。

// 高性能队列： Disruptor
// 0.  Java SDK 提供了 2 个有界队列：ArrayBlockingQueue 和 LinkedBlockingQueue，它们都是基于 ReentrantLock 实现的，在高并发场景下，锁的效率并不高，那有没有更好的替代品呢？有，今天我们就介绍一种性能更高的有界队列：Disruptor。
// 1. 程序局部性原理：内部的 RingBuffer 也是用数组实现的，但是这个数组中的所有元素在初始化时是一次性全部创建的，所以这些元素的内存地址大概率是连续的，相关的代码如下所示
//    在 Disruptor 中，生产者线程通过 publishEvent() 发布 Event 的时候，并不是创建一个新的 Event，而是通过 event.set() 方法修改 Event， 也就是说 RingBuffer 创建的 Event 是可以循环利用的，这样还能避免频繁创建、删除 Event 导致的频繁 GC 问题。
// 2. 避免伪共享：每个变量独占一个缓存行、不共享缓存行就可以了，具体技术是缓存行填充。比如想让 takeIndex 独占一个缓存行，可以在 takeIndex 的前后各填充 56 个字节，这样就一定能保证 takeIndex 独占一个缓存行
// 3. 无锁算法： ArrayBlockingQueue 是利用管程实现的，中规中矩，生产、消费操作都需要加锁，实现起来简单，但是性能并不十分理想。Disruptor 采用的是无锁算法，很复杂，但是核心无非是生产和消费两个操作。Disruptor 中最复杂的是入队操作，所以我们重点来看看入队操作是如何实现的。
// 对于入队操作，最关键的要求是不能覆盖没有消费的元素；对于出队操作，最关键的要求是不能读取没有写入的元素，所以 Disruptor 中也一定会维护类似出队索引和入队索引这样两个关键变量。Disruptor 中的 RingBuffer 维护了入队索引，但是并没有维护出队索引，这是因为在 Disruptor 中多个消费者可以同时消费，每个消费者都会有一个出队索引，所以 RingBuffer 的出队索引是所有消费者里面最小的那一个。

// 高性能数据库连接池： HiKariCP
// 0. 微观上 HiKariCP 程序编译出的字节码执行效率更高，站在字节码的角度去优化 Java 代码，HiKariCP 的作者对性能的执着可见一斑，不过遗憾的是他并没有详细解释都做了哪些优化。而宏观上主要是和两个数据结构有关，一个是 FastList，另一个是 ConcurrentBag。
// 1.  FastList 相对于 ArrayList 的一个优化点就是将 remove(Object element) 方法的查找顺序变成了逆序查找。除此之外，FastList 还有另一个优化点，是 get(int index) 方法没有对 index 参数进行越界检查，HiKariCP 能保证不会越界，所以不用每次都进行越界检查。
// 2. 实现一个数据库连接池，最简单的办法就是用两个阻塞队列来实现，一个用于保存空闲数据库连接的队列 idle，另一个用于保存忙碌数据库连接的队列 busy；获取连接时将空闲的数据库连接从 idle 队列移动到 busy 队列，而关闭连接时将数据库连接从 busy 移动到 idle。这种方案将并发问题委托给了阻塞队列
// 2.2. 最关键的属性有 4 个，分别是：用于存储所有的数据库连接的共享队列 sharedList、线程本地存储 threadList、等待数据库连接的线程数 waiters 以及分配数据库连接的工具 handoffQueue。其中，handoffQueue 用的是 Java SDK 提供的
// 2.2. FastList 适用于逆序删除场景；而 ConcurrentBag 通过 ThreadLocal 做一次预分配，避免直接竞争共享资源，非常适合池化资源的分配。

import com.sun.org.apache.bcel.internal.generic.PUSH;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.function.IntConsumer;

class exp_thread {
    public static void main(String[] args) {
        System.out.println(Thread.currentThread().getId());
        new Thread(() -> {
            Long tid = Thread.currentThread().getId();
            System.out.println("thread_id is " + tid);}).start();
        new Thread(() -> {
            Long tid = Thread.currentThread().getId();
            System.out.println("thread_id is " + tid);}).start();
        new Thread(() -> {
            Long tid = Thread.currentThread().getId();
            System.out.println("thread_id is " + tid);}).start();

    }
}

// diningPhilosphers
// 哲学家进餐： 死锁样例
class DiningPhilosphers {
    private ReentrantLock[] lockList = {
            new ReentrantLock(),
            new ReentrantLock(),
            new ReentrantLock(),
            new ReentrantLock(),
            new ReentrantLock(),
    };
    private Semaphore eatLimit = new Semaphore(4);
    public DiningPhilosphers() {}
    public void wantsToEat(int philosopher,
                           Runnable pickLeftFork,
                           Runnable pickRightFork,
                           Runnable eat,
                           Runnable putLeftFork,
                           Runnable putRightFork) throws InterruptedException {
        eatLimit.acquire();
        int rightFork = philosopher;
        int leftFork = (philosopher + 1) % 5;

        lockList[rightFork].lock();
        lockList[leftFork].lock();

        pickRightFork.run();
        pickLeftFork.run();

        eat.run();

        putRightFork.run();
        putLeftFork.run();

        lockList[rightFork].unlock();
        lockList[leftFork].unlock();

        eatLimit.release();
    }
}

// fizzbuzz
class FizzBuzz {
    private int n;
    private CyclicBarrier cyclicBarrier = new CyclicBarrier(4);
    public FizzBuzz(int n) {
        this.n = n;
    }
    public void fizz(Runnable printFizz) throws BrokenBarrierException, InterruptedException {
        for (int i = 0; i <= n; i++) {
            if (i % 3 == 0 && i % 5 != 0) printFizz.run();
            cyclicBarrier.await();
        }
    }
    public void buzz(Runnable printBuzz) throws BrokenBarrierException, InterruptedException {
        for (int i = 1; i <= n; i++) {
            if (i % 3 != 0 && i % 5 == 0) printBuzz.run();
            cyclicBarrier.await();
        }
    }
    public void fizzbuzz(Runnable printFizzBuzz) throws BrokenBarrierException, InterruptedException {
        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5 == 0) printFizzBuzz.run();
            cyclicBarrier.await();
        }
    }
    public void number(IntConsumer printNumber) throws BrokenBarrierException, InterruptedException {
        for (int i = 1; i <= n; i++) {
            if (i % 3 != 0 && i % 5 != 0) printNumber.accept(i);
            cyclicBarrier.await();
        }
    }
}

// h2o
class H20 {
    Semaphore H = new Semaphore(2);
    Semaphore O = new Semaphore(0);
    public H20() {}
    public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
        H.acquire(1);
        releaseHydrogen.run();
        O.release(1);
    }
    public void oxygen(Runnable releaseOxygen) throws InterruptedException {
        O.acquire(2);
        releaseOxygen.run();
        H.release(2);
    }
}

// zeroEvenOdd
class ZeroEvenOdd{
    private int n;
    private Semaphore zero = new Semaphore(1);
    private Semaphore even = new Semaphore(0);
    private Semaphore odd = new Semaphore(0);
    public ZeroEvenOdd(int n) {this.n = n;}
    public void zero(IntConsumer printNumber) throws InterruptedException {
        for (int i = 1; i <= n; i++) {
            zero.acquire();
            printNumber.accept(0);
            if (i % 2 == 0) even.release();
            else odd.release();
        }
    }
    public void even(IntConsumer printNumber) throws InterruptedException {
        for (int i = 2; i <= n; i++) {
            even.acquire();
            printNumber.accept(i);
            zero.release();
        }
    }
    public void odd(IntConsumer printNumber) throws InterruptedException {
        for (int i = 1; i <= n; i++) {
            odd.acquire();
            printNumber.accept(i);
            zero.release();
        }
    }
}

// foobar
// 交替打印
class FooBar {
    private int n;
    private Semaphore foo = new Semaphore(1);
    private Semaphore bar = new Semaphore(0);
    public FooBar(int n) {this.n = n;}
    public void foo(Runnable printFoo) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            foo.acquire();
            printFoo.run();
            bar.release();
        }
    }
    public void bar(Runnable printBar) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            bar.acquire();
            printBar.run();
            foo.release();
        }
    }
}

// traffic light
// 交通灯： 死锁样例
class trafficLight {
    public void carArrived() {

    }
}

// priority queue
// 并发安全的优先队列
class BoundBlockingQueue {
    private int n;
    public int size() {
        return n;
    }
    public void enqueue() {

    }
    public int dequeue() {
        int elm = 0;
        return elm;
    }
}

// multiprocessing web scrapy
// 基于多线程的网络爬虫，线程池创建
class webScrapy {
    public ArrayList<String> crwal() {
        ArrayList<String> arr = new ArrayList<>();
        return arr;
    }
    private void run() {

    }
}

// 烧水泡茶程序： 多线程样例： 线程池 -> 批处理，异步处理
// threadpool -> asyncio
// executor -> future -> completionService
class waterTea{
    // T1Task 需要执行的任务：
// 洗水壶、烧开水、泡茶
    static class T1Task implements Callable<String> {
        FutureTask<String> ft2;
        // T1 任务需要 T2 任务的 FutureTask
        T1Task(FutureTask<String> ft2){
            this.ft2 = ft2;
        }
        @Override
        public String call() throws Exception {
            System.out.println("T1: 洗水壶...");
            TimeUnit.SECONDS.sleep(1);

            System.out.println("T1: 烧开水...");
            TimeUnit.SECONDS.sleep(15);
            // 获取 T2 线程的茶叶
            String tf = ft2.get();
            System.out.println("T1: 拿到茶叶:"+tf);

            System.out.println("T1: 泡茶...");
            return " 上茶:" + tf;
        }
    }
    // T2Task 需要执行的任务:
// 洗茶壶、洗茶杯、拿茶叶
    static class T2Task implements Callable<String> {
        @Override
        public String call() throws Exception {
            System.out.println("T2: 洗茶壶...");
            TimeUnit.SECONDS.sleep(1);

            System.out.println("T2: 洗茶杯...");
            TimeUnit.SECONDS.sleep(2);

            System.out.println("T2: 拿茶叶...");
            TimeUnit.SECONDS.sleep(1);
            return " 龙井 ";
        }
    }

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        // 创建任务 T2 的 FutureTask
        FutureTask<String> ft2 = new FutureTask<>(new T2Task());
        // 创建任务 T1 的 FutureTask
        FutureTask<String> ft1 = new FutureTask<>(new T1Task(ft2));
        // 线程 T1 执行任务 ft1
        Thread T1 = new Thread(ft1);
        T1.start();
        // 线程 T2 执行任务 ft2
        Thread T2 = new Thread(ft2);
        T2.start();
        // 等待线程 T1 执行结果
        System.out.println(ft1.get());
    }
}

