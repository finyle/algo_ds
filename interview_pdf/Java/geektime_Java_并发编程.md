
# 并发理论基础
# 可见性，原子性和有序性问题：并发编程bug源头
# Java内存模型：看Java如何解决可见性和有序性问题
# 互斥锁：解决原子性问题
# 互斥锁：如何用一把锁保护多个资源
# 死锁怎么解决
# 用 “等待-通知”机制优化循环等待
# 安全性，活跃性以及性能问题
# 管程：并发编程的万能钥匙
# Java线程：Java线程的生命周期 & 
# Java线程：创建多少线程合适
# Java线程：为什么局部变量是线程安全的？
# 如何用面向对象思想写好并发程序
# 理论基础模块热点问题解答

# 并发工具类
# Lock 和 Condition： 隐藏在并发包中的管程
# Lock 和 Condition： Dubbo如何用管程实现异步转同步
# Semaphore： 如何快速实现一个限流器
# ReadWriteLock: 如何快速实现一个完备的缓存
# StampedLock： 有没有比读写锁更快的锁 (18, 20)
# CountDownLatch 和 CyclicBarrier： 如何让多线程步调一致
# 并发容器： 都有那些坑需要填
# 原子类： 无锁工具类的典范
# Executor 与线程池：如何创建正确的线程池
# Future： 如何用多线程实现最优的 "烧水泡茶" 程序
# CompletableFuture： 异步编程没那么难
# CompletionServie: 如何批量执行异步任务
# Fork/Join 单机版的MapReduce
# 并发工具类模块热点问题

# 并发设计模式
# Immutability 模式： 如何利用不变性解决并发问题 
# Copy-on-Write 模式： 不是延时策略的COW
# 线程本地存储模式： 没有共享，就没有伤害
# Guarde Suspension 模式: 等待唤醒机制的规范实现
# Balking模式： 在谈线程安全的单例模式
# Thread-Per-Message 模式： 最简单实用的分工方法
# Worker Thread模式： 如何避免重复创建线程
# 两阶段终止模式：如何优雅的终止线程
# 生产者-消费者模式： 用流水线思想提高效率
# 设计模式模块热点问题

# 案例分析
# 高性能限流器： Guava RateLimiter
```
```

# 高性能网络框架： Netty
```
```

# 高性能队列： Disruptor
```
```

# 高性能数据库连接池： HiKariCP
```
```

# 其他并发模型
# Actor模型： 面向对象原生的并发模型
# 软件事务内存： 借鉴数据库的并发经验
# 协程：更轻量级的线程
# CSP模型： Golang的主力队员

