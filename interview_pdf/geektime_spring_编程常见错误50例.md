# https://time.geekbang.org/column/intro/100077001?utm_campaign=geektime_search&utm_content=geektime_search&utm_medium=geektime_search&utm_source=geektime_search&utm_term=geektime_search&tab=catalog
# Spring 编程常见错误50

# Spring Core
### 1. Spring Bean 定义常见错误
#### 隐式扫描不到 Bean 的定义
#### 定义的 Bean 缺少隐式依赖
#### 原型 Bean 被固定

### 2. 依赖注入常见错误
#### 过多赠予，无所适从
#### 显式引用 Bean 时首字母忽略大小写
#### 引用内部类的 Bean 遗忘类名

#### @Value 没有注入预期的值
#### 错乱的注入集合

### 4. 生命周期常见错误
#### 构造器内抛空指针异常
#### 意外触发 shutdown 方法

### 5. Spring AOP 常见错误
#### this 调用的当前类方法无法被拦截
#### 直接访问被拦截类的属性抛空指针异常

#### this 调用的当前类方法无法被拦截
#### 直接访问被拦截类的属性抛空指针异常

### 7. Spring 事件常见错误
#### 试图处理并不会抛出的事件
#### 监听事件的体系不对
#### 部分事件监听器失效


# Spring Web
# 一个HTTP请求的处理过程
### 9.  Spring Web URL 解析常见错误
#### 当 @PathVariable 遇到 /
#### 错误使用 @RequestParam、@PathVarible 等注解
#### 未考虑参数是否可选

### 10. Spring Web Header 解析常见错误
#### 接受 Header 使用错 Map 类型
#### 错认为 Header 名称首字母可以一直忽略大小写
#### 试图在 Controller 中随意自定义 CONTENT_TYPE 等

### 11. Spring Web Body 转化常见错误
#### No converter found for return value of type
#### 变动地返回 Body
#### Required request body is missing

### 12. Spring Web 参数验证常见错误
#### 对象参数校验失效
#### 嵌套校验失效
#### 误解校验执行

### 13. Spring Web 过滤器使用常见错误
#### @WebFilter 过滤器无法被自动注入
#### Filter 中不小心多次执行 doFilter()

#### @WebFilter 过滤器使用 @Order 无效
#### 过滤器被多次执行

### 15. Spring Security 常见错误
#### 遗忘 PasswordEncoder
#### ROLE_ 前缀与角色

### 16.  Spring Exception 常见错误
#### 小心过滤器异常
#### 特殊的 404 异常

# Spring 补充

### 18. Spring Data 常见错误
#### 注意读与取的一致性
#### 默认值的错误
#### 冗余的 Session

### 19. Spring 事务常见错误(22,23)
#### unchecked 异常与事务回滚
#### 试图给 private 方法添加事务

#### 嵌套事务回滚错误
#### 多数据源间切换之谜

### 21. Spring Rest Template 常见错误
#### 参数类型是 MultiValueMap
#### 当 URL 中含有特殊字符
#### 小心多次 URL Encoder

### 22. Spring Test 常见错误
#### 资源文件扫描不到
#### 容易出错的 Mock

# Spring 编程错误根源