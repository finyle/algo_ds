<<<<<<< HEAD
# python 原生 socket 实现 简单的tcp c-s 结构
# python 内置 http， 实现简单的http c-s 结构: 命令行工具： python -m http.server 
# python 内置 request, 实现简单的 http client
# python 三方库 websocket 实现 websocket 协议，需要加载源码自定打包安装

# 基于协程池 和 ws 的爬虫
 


# 基于requests 库的http post 请求构造
import base64
import datetime
import hmac
import json
import time
import timeit
from threading import Thread

import requests
import websocket


def http_request_construct(url: str):
    # RESTful API:
    base_url = ""
    endpoint = ""
    url = ""

    # api 请求授权， key-secret
    gemini_api_key = ""
    gemini_api_secret = "".encode()

    # 幂等性校验参数
    payload_nonce = str(datetime.datetime.now())

    # payload 请求头 载荷构造
    payload = {

    }

    # payload 编码, 请求签名构造
    encoded_payload = json.dump(payload).encode()
    b64 = base64.b64encode(encoded_payload)
    signature = hmac.new()

    # 请求头构造
    request_headers = {

    }

    # 发起请求
    response = requests.post(url,
                  data = None,
                  header = request_headers)

    new_order = response.json()
    print(new_order)

def get_orderbook():
    order = requests.get("")
    print(order)


def on_message(ws, message):
    print("Received: " + message)
def on_open(ws):
    # 线程运行函数
    def gao():
        # 往服务器依次发送 0-4，每次发送完休息 0.1 秒
        for i in range(5):
            time.sleep(0.01)
            msg = "{0}".format(i)
            ws.send(msg)
            print('Sent: ' + msg)
        # 休息 1 秒用于接受服务器回复的消息
        time.sleep(1)

        # 关闭 Websocket 的连接
        ws.close()
        print("Websocket closed")

    Thread(target=gao).start()

# echo.websocket.org; 官方端口；被墙
def ws_main():
    ws = websocket.WebSocketApp("ws://echo.websocket.org/",
                                on_message = on_message,
                                on_open = on_open)
    # tear_down()
    ws.run_forever()


def time_compare():
    latency = timeit.timit('')
    print('latency is {} ms'.format(latency * 1000))

# 基于ws的爬虫： 返回响应数据结构定义
class OrderBook:
    def __init__(self):
        pass
    def insert(self):
        pass
    def sort_and_slice(self):
        pass
    def get(self):
        return

class Crawler:
    def __init__(self):
        pass
    # 对爬取的数据进行处理，写入本地文件 & 数据库
    def on_message(self):
        pass
if __name__ == '__main__':
=======
# python 原生 socket 实现 简单的tcp c-s 结构
# python 内置 http， 实现简单的http c-s 结构: 命令行工具： python -m http.server 
# python 内置 request, 实现简单的 http client
# python 三方库 websocket 实现 websocket 协议，需要加载源码自定打包安装

# 基于协程池 和 ws 的爬虫
 


# 基于requests 库的http post 请求构造
import base64
import datetime
import hmac
import json
import time
import timeit
from threading import Thread

import requests
import websocket


def http_request_construct(url: str):
    # RESTful API:
    base_url = ""
    endpoint = ""
    url = ""

    # api 请求授权， key-secret
    gemini_api_key = ""
    gemini_api_secret = "".encode()

    # 幂等性校验参数
    payload_nonce = str(datetime.datetime.now())

    # payload 请求头 载荷构造
    payload = {

    }

    # payload 编码, 请求签名构造
    encoded_payload = json.dump(payload).encode()
    b64 = base64.b64encode(encoded_payload)
    signature = hmac.new()

    # 请求头构造
    request_headers = {

    }

    # 发起请求
    response = requests.post(url,
                  data = None,
                  header = request_headers)

    new_order = response.json()
    print(new_order)

def get_orderbook():
    order = requests.get("")
    print(order)


def on_message(ws, message):
    print("Received: " + message)
def on_open(ws):
    # 线程运行函数
    def gao():
        # 往服务器依次发送 0-4，每次发送完休息 0.1 秒
        for i in range(5):
            time.sleep(0.01)
            msg = "{0}".format(i)
            ws.send(msg)
            print('Sent: ' + msg)
        # 休息 1 秒用于接受服务器回复的消息
        time.sleep(1)

        # 关闭 Websocket 的连接
        ws.close()
        print("Websocket closed")

    Thread(target=gao).start()

# echo.websocket.org; 官方端口；被墙
def ws_main():
    ws = websocket.WebSocketApp("ws://echo.websocket.org/",
                                on_message = on_message,
                                on_open = on_open)
    # tear_down()
    ws.run_forever()


def time_compare():
    latency = timeit.timit('')
    print('latency is {} ms'.format(latency * 1000))

# 基于ws的爬虫： 返回响应数据结构定义
class OrderBook:
    def __init__(self):
        pass
    def insert(self):
        pass
    def sort_and_slice(self):
        pass
    def get(self):
        return

class Crawler:
    def __init__(self):
        pass
    # 对爬取的数据进行处理，写入本地文件 & 数据库
    def on_message(self):
        pass
if __name__ == '__main__':
>>>>>>> d2cf9d11bdcb024015f36837ba48c64d5f38c888
    ws_main()