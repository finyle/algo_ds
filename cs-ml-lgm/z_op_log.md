# debug 环境：
# windows10 + clion + minGW 
#### 1. 下载三方依赖 eigen(矩阵库) fast_double_parser(参数解析) fmt(字符串格式) compute()
# external_libs: compute, eigen, fast_double_parser, fmt 
#### 2. 执行src/main 配置入参： 配置文件路径； 及配置文件中的数据文件的相对路径修改
# run/debug config: program arguments: config="examples\\regression\\train.conf"
# 修改train.conf 中的 data路径地址： examples\\regression\\train.data
#### 3. pip install --no-binary lightgbm lightgbm

# cmakelists.txt: 

****************************************************************

# src： 
# 主干流程： main -> application -> boosting, metric, objective -> treelearner
# contrib: cuda GPU接口； io 数据读写接口； network 分布式计算网络接口
# swig: python-cpp 桥接API 


# trace：
## app.initTrain -> (parserConfig, loadData) init_obj, init_model
## init_objFunc -> objective_fun.init -> objectiveFunction.init -> obj策略 重载init实现 (rank_obj.RankXENDCG arxiv2021)
## init_model -> boosting.init -> gbdt.init -> treelearner.create -> linear.init&train (coef 并行计算) arxiv2017

## app.train -> boosting.train -> gbdt.train -> trainOneIter -> boosting(自定义损失函数，gradient 并行复制)， bagging处理， 实例化Tree(gradients, learning rate, update score)

## app.predict -> Predictor.init 任务类型判断：KRefitTree (TextReader实例化， 并行处理 stringToArray， 初始化objective_fun, boosting, 构造gbdt.refitTree) -> 并行处理treeLearn.init & fitByExistingTree -> linnearTreeLearner.calculateLinear 并行计算linear model coef

# ##########################################################
# 数据结构定义：
# Application -> Dataset, Metric, Boosting, ObjectiveFunc
# Metric.Eval 指标计算 -> GBDT(gbdt 算法实现类)

# 流程：Application.initTrain()
## Boosting 策略 gbdt, dart, goss, rf
## Objective 策略 regression, regression_l1, quantile, huber, fair, poisson, binary, lambdarank, rank_xendcy, multiclass, cross_entrogy, mape, gamma, tweedie, custom
## loadData() std::chrono(计时)加载训练数据 -> 实例化 Predictor -> 同步数据分区中的random seed -> 实例化 DataLoader -> load_file， save_binary_file -> 实例化 Metric -> 加载valid数据 -> metric.init(valid_data) | vector.shrink_to_fit裁剪元素长度
## 初始化 objective.init 虚函数
## 初始化 boosting.init 虚函数 -> 重载 GBDT.init() -> 载入model配置 && 实例化 TreeLearner
## 添加 valid_data 到 Boosting

# 流程： Application.train() 

# Metric 策略

# ######################
# GBDT -> Tree TreeLearner， ScoreUpdater， SampleStrategy， (Metric, ObjectiveFunc, Config)
# 流程： GBDT.init()
## 读取配置文件，设置模型参数
## 加载split_file
## 实例化ObjectiveFunc -> 实例化采样策略：SampleStrategy -> Hessian变换 -> 实例化TreeLearner(init, setForcedSplit) -> checkForcedSplitFeatures()叶节点分裂特征索引限制 -> ResetGradientBuffers() 为bagging操作创建缓存

###  并行计算： refitTree -> predict; trainOneIter -> train

# ######################
# TreeLearner(工厂模式) -> LinearTreeLearner, SerialTreeLearner, FeatureParallelTreeLearner, SerialTreeLearner, VotingParallelTreeLearner,

# LinearTreeLearner 调用： init
## init： 并行计算线性模型参数(model coef)，二维vector存储
## train -> BeforeTrain ->实例化Tree -> GetLeafMap -> CalculateLinear: 并行计算 matrix model coef 参考论文： calculate coefficients using the method described in Eq 3 of https://arxiv.org/pdf/1802.05640.pdf


# #######################
# ObjectiveFunc

# RankingObjective: 参考论文实现： arxiv.org/abs/1911.09798


# #######################
# Network -> Linkers， BruckMap 




