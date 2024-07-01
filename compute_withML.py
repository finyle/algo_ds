
# scikit learn: knn, kmean, svm, linear-model 


# ##############################################

# 两个框架的主要计算逻辑部分 均为cpp 实现

# lightGBM

# objective_function:
# regression
# classification
# multi-class
# rank

# metric:

# linearTreeLearner:
# #parama parallel compute: coef计算 (X_T * H * X + lambda) ^ (-1) * (X_T * g)
## 调用矩阵计算库 engine， 实现并行矩阵运算

# 分布式计算：
# 提供net包， socket接口，用于并行计算时的数据通信
# 基于dask的分布式计算：


##################################################

# pytorch
# 框架应用 Python api:
## 网络模型定义： CustomModel(nn.Module): __init__(); forward();
## 损失函数： loss = nn.functional.cross_entropy(); 激活函数，损失函数均在
## 参数优化器： optim = optim.SGD & Adam

# 对应源码实现：
# Python接口相关： pytorch.torch.csrc.api.nn & optim

# 自动微分(单机版): pytorch.torch.csrc.autograd: 由 nn.Module._call 在模型实例化时自动执行前向传播
# 自动微分(分布式版): pytorch.torch.csrc.distributed.autograd
## context, engine, function, rpc

# onnx: open neural netmodel exchange(神经网络模型开放格式), 使得模型在支持该模式的环境中得以复用

# #########################################################
# 统计模型相关的指标计算：(公式)
# loss
# objetive function



#############################################################
# generate model 
# llama, tranformer

# whisper, chatts 

# pic style-transfer 

# search prune
# rl: gym, alpha-go, rl-card(doudizhu, chess, majiang, depu)
## multi-agent rl: star-craftII, DOTA2

