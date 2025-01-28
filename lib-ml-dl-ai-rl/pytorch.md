### 框架应用 Python api:

#### 网络模型定义： CustomModel(nn.Module): __init__(); forward();
#### 损失函数： loss = nn.functional.cross_entropy(); 激活函数，损失函数均在
#### 参数优化器： optim = optim.SGD & Adam

```
# 网络模型定义
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1, 32, 3, 1)
        self.conv2 = nn.Conv2d(32, 64, 3, 1)
        self.dropout1 = nn.Dropout(0.25)
        self.dropout2 = nn.Dropout(0.5)
        self.fc1 = nn.Linear(9216, 128)
        self.fc2 = nn.Linear(128, 10)

    def forward(self, x):
        x = self.conv1(x)
        x = F.relu(x)
        x = self.conv2(x)
        x = F.relu(x)
        x = F.max_pool2d(x, 2)
        x = self.dropout1(x)
        x = torch.flatten(x, 1)
        x = self.fc1(x)
        x = F.relu(x)
        x = self.dropout2(x)
        x = self.fc2(x)
        output = F.log_softmax(x, dim=1)
        return output

# 数据加载
transform=transforms.Compose([toTensor(), Normalize()])
dataset=dataset.MINST("/data", transform)
# 模型加载
model = Net().to(devide)
# 参数优化： 
optimizer = optim.Adadelta(model.parameters())
schedule = StepLR(optimizer) 
# 迭代训练
for epch in range(epochs):
    train(model, data, optimizer)
    scheduler.step()
# 中间模型存档
torch.save(model.state.dic(),"cnn.pt")

# 训练
for batch, data in enumerate(train_loader):
    optimizer.zero_grad()                   # 优化初始化
    output=model(data)                      # 预测
    loss=F.nll_loss(output, target)         # 计算loss
    loss.backward()
    optimizer.step()                        # 优化步进
    print("train epoch {.0f}", loss.item())
```

# ##########################################################

#### 对应源码实现：
#### Python接口相关： pytorch.torch.csrc.api.nn & optim

#### 自动微分(单机版): pytorch.torch.csrc.autograd: 由 nn.Module._call 在模型实例化时自动执行前向传播
```
grad:

run_backward:

```


#### 自动微分(分布式版): pytorch.torch.csrc.distributed.autograd
#### context, engine, function, rpc

#### onnx: open neural netmodel exchange(神经网络模型开放格式), 使得模型在支持该模式的环境中得以复用

# ##############################################################
#### pytorch 算子（Operators）通常指的是进行各种数学运算和张量操作的函数
#### 基本算子 张量定义
#### 高级算子 矩阵乘法, 卷积
#### 自定义算子 使用torch.autograd.Function来创建自定义算子：
```
class MyReLU(torch.autograd.Function):
    @staticmethod
    def forward(ctx, input):
        ctx.save_for_backward(input)  # 保存输入以用于反向传播
        return input.clamp(min=0)

    @staticmethod
    def backward(ctx, grad_output):
        input, = ctx.saved_tensors
        grad_input = grad_output.clone()
        grad_input[input < 0] = 0
        return grad_input
# 使用自定义算子
relu = MyReLU.apply
output = relu(torch.tensor([-1.0, 2.0, -3.0]))
print(output)  # 输出: tensor([0., 2., 0.])
```
#### wavelet transform

对于性能要求极高的操作，你可能需要使用C++来扩展PyTorch，通过编写自定义的CUDA内核来实现：
编写C++/CUDA代码：创建一个C++文件，实现你的算子逻辑。
编译扩展：使用setuptools或torch.utils.cpp_extension来编译你的C++/CUDA代码。
在PyTorch中调用：导入编译后的模块，并像使用PyTorch的内置算子一样使用你的自定义算子。
这是一个高层次的概述，具体的实现细节会根据你的具体需求而有所不同。PyTorch的灵活性和强大的算子支持使其成为深度学习研究和开发的强大工具。

# ##############################################################
windows build：

* Windows:

#### Prerequisites

```bash
$ source <CONDA_INSTALL_DIR>\Scripts\activate.bat
$ conda create -y -n <CONDA_NAME>
$ conda activate <CONDA_NAME>
$ call "c:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
```

#### Get the PyTorch Source
```bash
git clone --recursive https://github.com/pytorch/pytorch  # 自行下载三方依赖, 配置github代理(watt toolkit)
cd pytorch
# if you are updating an existing checkout
git submodule sync
git submodule update --init --recursive
```

#### Install Dependencies

**Common**

```bash
conda install cmake ninja
# Run this command from the PyTorch directory after cloning the source code using the “Get the PyTorch Source“ section below
pip install -r requirements.txt -i  https://mirrors.aliyun.com/pypi/simple/ 
```

**On Windows**

```bash
pip install mkl-static mkl-include -i  https://mirrors.aliyun.com/pypi/simple/ 
# Add these packages if torch.distributed is needed.
# Distributed package support on Windows is a prototype feature and is subject to changes.
conda install -c conda-forge libuv=1.39
```

**On Windows**

If you want to build legacy python code, please refer to [Building on legacy code and CUDA](https://github.com/pytorch/pytorch/blob/main/CONTRIBUTING.md#building-on-legacy-code-and-cuda)

**CPU-only builds**

In this mode PyTorch computations will run on your CPU, not your GPU

```cmd
python setup.py develop
```