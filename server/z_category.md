# 应用层网络协议
## ssh (secure shell) 
### 2步连接： 客户端和服务端建立连接 & 用户和身份鉴权
```
# https://zhuanlan.zhihu.com/p/108161141
* 客户端联系服务端，双方沟通自己支持的 SSH 协议的版本，约定使用某个共同支持的版本。
* 服务端将自己的 Host Key 、加密方法和其他一些参数发给客户端。
* 客户端通过 Host Key 验证服务端身份，双方用服务端发来的参数和 Diffie-Hellman 算法生成 Session Key。
* 加密通道建立完成
--- 
* 客户端用 Private Key 生成签名向服务器发起登录请求。
* 服务端验证签名，检查自己有没有和这个签名匹配的 Public Key，如果有，则进入下一步。
* 服务端生成一串随机字符串，用 Public Key 加密后发送给客户端。
* 客户端用相应的 Private Key 解密这串字符串，再使用 MD5 hash 和 Session Key 加密该字符串，将结果发送给服务端。
* 服务端使用同样的 MD5 hash 和 Session Key 计算这串字符的加密结果，并和客户端发来的结果做比对，如果结果一样，则允许客户端登录。
---
* 总结： SSH 分为两大步，第一步是客户端和服务端建立连接，最终生成双方都一致的 Session Key。第二步使用 Authorized Key 进行登录，登录过程使用 Public/Private Key 验证身份。连接建立完成后，在通讯过程中使用 Session Key 对信息进行加密解密。

```

## ftp (file tranfer protocals), 和HTTP相比，FTP面向的直接是服务器的文件系统，并且具有维持状态的特点，在文件传输管理上，FTP更胜一筹。
### 模块架构：控制连接， 数据连接
### 数据传输模式： ASCII, 二进制模式
```
* FTP客户首先发起建立1个与FTP服务器端口号21之间的TCP控制连接, 指定TCP作为传输层协议
* 客户在建立的控制连接上获得身份认证
* 客户在建立的控制连接上发送命令来浏览远程主机的目录.
* 当服务器接收到1个文件传输命令时, 在服务器端口号20创建1个与客户 的TCP数据连接
* 1个文件传输后,服务器结束这个TCP数据连接
* .之后 再次传输，服务器创建第2个TCP与客户的数据连接来传输下一个文件.
** 特点：
* 控制连接: 带外发送控制信息（对比 HTTP 带内控制信息）
* FTP 服务器要维护用户状态信息: 当前目录, 先前的身份认证（对比HTTP的无状态连接）

```

# openssh-protable: ssh协议的开源实现 c
# filecxx: fileCentipede 跨平台的文件上传下载工具 cpp
```
文件蜈蚣是一个全能网络文件上传/下载器, BitTorrent客户端, WebDAV客户端, FTP客户端, 和SSH客户端.
它快速, 可定制, 用户友好, 多协议支持, 同时也包含了很多有用的辅助工具如: HTTP请求器, 文件合并工具, 编码/解码工具等.
和网页浏览器进行集成, 你可以从网页上下载音频和视频, 甚至是加密视频.
```


# filestash go + js
```
 A modern web client for SFTP, S3, FTP, WebDAV, Git, Minio, LDAP, CalDAV, CardDAV, Mysql, Backblaze, ...
```

# hiddify dart
```
一款基于 Sing-box 通用代理工具的跨平台代理客户端。Hiddify 提供了较全面的代理功能，例如自动选择节点、TUN 模式、使用远程配置文件等。Hiddify 无广告，并且代码开源。它为大家自由访问互联网提供了一个支持多种协议的、安全且私密的工具。类似 v2ray
```

# sftpgo
```
功能齐全且可高度配置的事件驱动文件传输解决方案。服务器协议：SFTP、HTTP/S、FTP/S、WebDAV。存储后端：本地文件系统、加密的本地文件系统，S3（兼容）对象存储，谷歌云存储，Azure Blob存储，其他SFTP服务器。

使用SFTPGo，您可以利用本地和云存储后端在内部或使用您已经熟悉的相同工具和流程与业务合作伙伴交换和存储文件。
```

# aria2
```
轻量级跨平台多源多协议支持下载器，下载速度只取决于带宽
```

# nginx 文件上传下载
```
nginx ftp 支持
Nginx 默认不支持 FTP 协议，但可以通过第三方模块如ngx_http_ftp_module实现简单的FTP功能。
http {
    server {
        listen 80;
        server_name your.server.com;
 
        location /ftp/ {
            # 启用 ngx_http_ftp_module 模块的 ftp 功能
            ftp_get $arg_url;
 
            # 设置输出文件的名称，默认为最后一个URI组件
            ftp_use_low_level_buffer on;
            sendfile on;
            sendfile_max_chunk 1m;
            aio on;
            output_buffers 1 1m;
 
            # 设置用于FTP连接的代理服务器
            proxy_set_header Host $ftp_host;
            proxy_set_header Proxy $scheme://$http_host$request_uri;
            proxy_set_header Connection close;
 
            # 设置FTP连接的超时时间
            ftp_connect_timeout 30s;
            ftp_read_timeout 60s;
 
            # 设置日志
            error_log /var/log/nginx/ftp_error.log;
            access_log /var/log/nginx/ftp_access.log;
        }
    }
}
```