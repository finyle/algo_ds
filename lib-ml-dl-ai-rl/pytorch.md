# 框架应用 Python api:

## 网络模型定义： CustomModel(nn.Module): __init__(); forward();
## 损失函数： loss = nn.functional.cross_entropy(); 激活函数，损失函数均在
## 参数优化器： optim = optim.SGD & Adam


# ##########################################################
# 对应源码实现：
# Python接口相关： pytorch.torch.csrc.api.nn & optim

# 自动微分(单机版): pytorch.torch.csrc.autograd: 由 nn.Module._call 在模型实例化时自动执行前向传播
# 自动微分(分布式版): pytorch.torch.csrc.distributed.autograd
## context, engine, function, rpc

# onnx: open neural netmodel exchange(神经网络模型开放格式), 使得模型在支持该模式的环境中得以复用