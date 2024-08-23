<<<<<<< HEAD
# 数组的载入，导出 numpy pandas (多为数组， Cython 加速)
# 科学计算 statisitic, scikit-learn, scipy 
# ml: lightGBM, pytorch 基于cpp的dll库调用
# pytroch 生态： dn模型的分布式部署，模型搭建, 模型的onnx， pretrained， 并行优化加速
# 矩阵相关计算(样例， 与性能无关)

# 1. 基于 pandas 的文件读取
# 调用 np.hstack()toifle();
# 参考： qlib.data.storage.file_storage.FileFeatureStorage.write()
#       __getitem__():
import abc
import struct

import numpy as np
import pandas as pd
def write_file(fileName: str):
    with open() as f:
        f.seek()
        struct.unpack()
        np.frombuffer(f.read)

def read_file(fileName):
    np.hstack().tofile()

    return pd.read_csv()


# 2. 策略：重新封装 pandas numpy：
## ops: element-wise pair-wise triple-wise, rolling, expanding, 利用 abc.ABC + 魔术方法，实现自定义内置运算符： data.base
## data: joblib 多进程特征计算: DatasetD.dataset()
### 整合 ops + data + cache = filter,

# 3. 缓存： data.cache:
## 内存缓存：memCache; cacheUtil(redis)
## 磁盘缓存： expressionCache， datasetCache， calendarCache， IndexManager

# 4. wrokflow: recorder_temp: 整合strategy(特征数据生成) + model 调用 backtest + risk_ayalysis(ic, ir, sharp, win_rate)
## task: manage, gen, utils 对运行任务进行管理： 派生，复用，监控， curd + monogoDB client
def strategy_api(strategy: str, values, n):
    if strategy == 'sma':   # 简单滑动平均
        return pd.Series(values).rolling(n).mean()
    if strategy == 'crossover':     # 判断是否交叉
        return values
class Strategy(metaclass=abc.ABCMeta):
    def __init__(self, broker, data):
        self._broker = broker
        pass
    def I(self) -> np.ndarray:
        pass
    @property
    def tick(self):
        return
    @property
    def data(self):
        return
    @abc.abstractmethod
    def init(self):
        pass
    @abc.abstractmethod
    def next(self):
        pass

    def buy(self):
        self._broker.buy()
    def sell(self):
        self._broker.sell()
class SmaCross(Strategy): # 简单滑动平均
    def init(self):
        pass
    def next(self):
        pass

# 3. 模拟交易 account + decision + exchange +  executor
## decision = strategy + position + report + signal
class ExchangeAPI:
    """
    """
    def __init__(self):
        pass
    def buy(self):
        pass
    def sell(self):
        pass
    def next(self):
        pass

# 4. 回测: 整合 Strategy + ExchangeAPI 生成(生成器)交易指令并执行: 下一次的决策来自上一次的结果，上一次的结果来自上上此的决策
## decison = straget(executor_result);
## executor_result = yield from executor(decision)
## straget.post_step(execute_result)
class Backtest:
    def __init__(self):
        pass
    def run(self):
        pass
    def _compute_result(self, broker):
        return

def main():

    print()



###################################################################
# instrucment-data access 
# memory: memory pool manager 
# disk: B+tree LSM serialize
# expr: dsl(sql), expr-engine(ops + eval)
# concurrency: distribution lock 


# workflow: (init_instance_byconfig <=> work-flow(task-flow bpmn))
# mlflow: monitor
# model save & load, model train, predict
# strategy load 
# signal backtest

# backtest(bt, zipline, trader)

# base-data: olchv 
# drived-data: ops with baseData, multiprocess compute and serialize(16hex)

# ml: train -> predict -> valid
=======
# 数组的载入，导出 numpy pandas (多为数组， Cython 加速)
# 科学计算 statisitic, scikit-learn, scipy 
# ml: lightGBM, pytorch 基于cpp的dll库调用
# pytroch 生态： dn模型的分布式部署，模型搭建, 模型的onnx， pretrained， 并行优化加速
# 矩阵相关计算(样例， 与性能无关)

# 1. 基于 pandas 的文件读取
# 调用 np.hstack()toifle();
# 参考： qlib.data.storage.file_storage.FileFeatureStorage.write()
#       __getitem__():
import abc
import struct

import numpy as np
import pandas as pd
def write_file(fileName: str):
    with open() as f:
        f.seek()
        struct.unpack()
        np.frombuffer(f.read)

def read_file(fileName):
    np.hstack().tofile()

    return pd.read_csv()


# 2. 策略：重新封装 pandas numpy：
## ops: element-wise pair-wise triple-wise, rolling, expanding, 利用 abc.ABC + 魔术方法，实现自定义内置运算符： data.base
## data: joblib 多进程特征计算: DatasetD.dataset()
### 整合 ops + data + cache = filter,

# 3. 缓存： data.cache:
## 内存缓存：memCache; cacheUtil(redis)
## 磁盘缓存： expressionCache， datasetCache， calendarCache， IndexManager

# 4. wrokflow: recorder_temp: 整合strategy(特征数据生成) + model 调用 backtest + risk_ayalysis(ic, ir, sharp, win_rate)
## task: manage, gen, utils 对运行任务进行管理： 派生，复用，监控， curd + monogoDB client
def strategy_api(strategy: str, values, n):
    if strategy == 'sma':   # 简单滑动平均
        return pd.Series(values).rolling(n).mean()
    if strategy == 'crossover':     # 判断是否交叉
        return values
class Strategy(metaclass=abc.ABCMeta):
    def __init__(self, broker, data):
        self._broker = broker
        pass
    def I(self) -> np.ndarray:
        pass
    @property
    def tick(self):
        return
    @property
    def data(self):
        return
    @abc.abstractmethod
    def init(self):
        pass
    @abc.abstractmethod
    def next(self):
        pass

    def buy(self):
        self._broker.buy()
    def sell(self):
        self._broker.sell()
class SmaCross(Strategy): # 简单滑动平均
    def init(self):
        pass
    def next(self):
        pass

# 3. 模拟交易 account + decision + exchange +  executor
## decision = strategy + position + report + signal
class ExchangeAPI:
    """
    """
    def __init__(self):
        pass
    def buy(self):
        pass
    def sell(self):
        pass
    def next(self):
        pass

# 4. 回测: 整合 Strategy + ExchangeAPI 生成(生成器)交易指令并执行: 下一次的决策来自上一次的结果，上一次的结果来自上上此的决策
## decison = straget(executor_result);
## executor_result = yield from executor(decision)
## straget.post_step(execute_result)
class Backtest:
    def __init__(self):
        pass
    def run(self):
        pass
    def _compute_result(self, broker):
        return

def main():

    print()



###################################################################
# instrucment-data access 
# memory: memory pool manager 
# disk: B+tree LSM serialize
# expr: dsl(sql), expr-engine(ops + eval)
# concurrency: distribution lock 


# workflow: (init_instance_byconfig <=> work-flow(task-flow bpmn))
# mlflow: monitor
# model save & load, model train, predict
# strategy load 
# signal backtest

# backtest(bt, zipline, trader)

# base-data: olchv 
# drived-data: ops with baseData, multiprocess compute and serialize(16hex)

# ml: train -> predict -> valid
>>>>>>> d2cf9d11bdcb024015f36837ba48c64d5f38c888
