#### lightGBM
#### 概览：
本质： grediant bootsing model
实现： 集成算法 梯度计算
特性： 分层设计易扩展， #pargma cpp并行计算, cuda GPU计算支持
用途： 基于梯度的集成决策树算法库(支持分布式训练)

#### 对比 scikit-learn-gbdt, xgboost 

最佳分裂点查找算法： histogram-based 
高效的稀疏空间优化算法：(goss) gradient-based on one-side sampling
(https://papers.nips.cc/paper_files/paper/2017/file/6449f44a102fde848669bdd9eb6b76fa-Paper.pdf)LightGBM: A Highly Efficient Gradient Boosting
Decision Tree

cuda GPU硬件加速支持

分布式训练支持

集成算法库的分层设计： 
支持更多的 集成模型 gbdt rf dart
支持更多的 obj function： 二分 多分 rank(https://arxiv.org/abs/1911.09798) An Alternative Cross Entropy Loss for Learning-to-Rank
支持更多的 loss function： 
支持更多的 treeLearner：  matrix model coef parallel compute(https://arxiv.org/pdf/1802.05640.pdf)Gradient Boosting with Piece-Wise Linear Regression Trees

# ######################## 点(领域知识) 抽象->实现 (设计模式(reactor) -> 应用协议(tcp) -> 编码细节(锁 内存))
#### 集成算法库模型的分层设计
#### train -> predict (拟合->生成) 

#### 集成算法：boosting bagging randomForest
#### loss function
#### objective funciton
#### 决策树 tree learner

#### cpu并行计算 #pragma parallel
#### gpu并行计算 cuda
#### malloc 内存分配回收
#### 中间模型存档 (checkpoint)

#### net 分布式训练支持

#### Python api (swig) 
#### C api

# ######################## 线(模型训练 预测(生成))
#### 源码包文件 编译 概览
编译：
    下载三方依赖 eigen(矩阵库) fast_double_parser(参数解析) fmt(字符串格式) compute
    cpp cmakelists build 编译成exe
    pip insatll . 编译算法库为.dll动态连接调用 并通过Python API调用
使用exp:    
    执行src/main 配置入参： 配置文件路径； 及配置文件中的数据文件的相对路径修改
    run/debug config: program arguments: config="examples\\regression\\train.conf"
    修改train.conf 中的 data路径地址： examples\\regression\\train.data
包结构：

#### 主干流程： 
main -> application(train or predict) -> boosting, metric, objective -> treelearner -> model-to-file or out-predict-result

#### 应用初始化
parseConfig, loadData 
init_objfunc 
init_model

#### train


#### predict