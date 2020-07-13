# 神经网络可视化

[![Build status](https://ci.appveyor.com/api/projects/status/im0xw2ni24hfnwp9/branch/master?svg=true)](https://ci.appveyor.com/project/smileandyxu/visualized-neural-networks/branch/master)

## 项目描述 ##

小组名称：神经网络

小组成员：徐正浩，梁洵，杨云皓

选题：神经网络可视化

### 项目管理 ###

版本控制：git, github

开发环境：QT 5.14.2

持续集成：appveyor

编程语言：C++17

框架结构：MVVM

文档编写：markdown

### 项目提出 ###

神经网络是目前热门的研究领域，大部分神经网络的实现较为抽象，难以清楚知道神经网络结构以及中间计算过程。因此我们希望通过对神经网络进行可视化处理，让用户能够直观地了解到所构建的神经网络结构以及中间计算过程，使其能够直观方便地调整神经网络结构与参数，方便学习其原理。

### 功能实现 ###

#### 绘图编辑

- 实现神经元移动、放置、连接、删除等

- 选择、修改神经元类型（是否带激活函数等）

- 手动编辑输入神经元值、连接权重

- 手动提供标准输出值

#### 计算显示

- 根据输入计算输出

- 根据网络输出和标准输出值误差链式求导

- 修改连接权重

#### 界面与功能展示

主界面

<img src=".\graph\主界面.png" style="zoom:67%;" />

神经元的的放置

选择神经元类型后，单击左键即可放置

<img src=".\graph\放置.png" style="zoom:67%;" />

神经元的连接与类型修改

左键选定神经元后，右键拖动至另一神经元松开即可连接，神经元类型将根据连接情况自行修改。

<img src=".\graph\连接与类型修改.png" style="zoom:67%;" />



神经元手动编辑

双击神经元或连接值，出现弹窗，进行编辑

<img src=".\graph\编辑.png" style="zoom:67%;" />

计算与反向传播

点击计算，选择正向计算或反向传播进行计算

<img src=".\graph\计算.png" style="zoom:67%;" />

## 具体实现

### 框架描述 ###

框架整体采用MVVM模式，将view层与model层分离，通过view model连接，实现多人协作。

#### App

绑定NetView，NetViewModel和NetModel的属性（Graph类）和Command&Notification。

#### View

完成神经网络的图形显示，并提供一系列交互按钮触发网络属性（拓扑结构，权值，输入输出值等），调用Command修改数据。

利用Graph提供的拓扑信息修改窗口内的图形数据（位置、显示数字、颜色等等）。

#### ViewModel

完成Command和Notification的参数沟通，把View装在Command中的参数解析成Model的方法类型。

#### Model

完成对Graph的包装（NetModel类）和属性修改，包括提供加点、加边、前馈计算、反向传播的函数实现。

将Graph作为属性通过App绑定传递给View进行显示。

#### Common

实现Graph类，提供基本操作。

### 实现过程 ###

#### 第一轮迭代 (TestCI)

实现MVVM框架；做出主窗口，实现神经元的放置，移动；部署持续集成

- [x] 主窗口显示 (NetView)
- [x] 工具栏编辑模式切换
- [x] 神经元放置
- [x] 神经元选择
- [x] 神经元移动
- [x] Appveyor CI

#### 第二轮迭代 (Addweights)

实现神经元的连接；优化显示

- [x] 神经元连接
- [x] 环路、重边检查
- [x] 差异显示不同类型神经元 (input, hidden, output)
- [x] 修复上轮Bug

#### 第三轮迭代 (Addvalue)

实现神经元值和连接权重、梯度等显示；手动编辑输入神经元值，连接权重功能

- [x] 显示神经元值
- [x] 显示边权和当前存储梯度
- [x] 提供弹窗修改神经元值 (NeuronView)
- [x] 提供弹窗修改边权 (WeightView)
- [x] 修复上轮Bug

#### 第四轮迭代 (Addcalcforward)

实现前向计算输出功能

- [x] 菜单提供计算按钮 (Forward)
- [x] 实现前馈计算并显示
- [x] 修复Bug (issue#10)

#### 第五轮迭代 (Addbackprop)

实现神经网络的梯度计算、反向传播与参数优化

- [x] 菜单提供梯度计算、反向传播、参数优化和一次性执行按钮
- [x] 实现梯度计算
- [x] 实现梯度反向传播
- [x] 实现参数更新

#### 第一阶段Release (v0.1.1)

更新文档；持续部署打包release

- [x] 更新文档
- [x] Appveyor CD

#### 第六轮迭代 (Adddelete)

实现神经元和连接的删除

- [x] 实现神经元删除
- [x] 实现连接有向边删除
- [x] 维护神经元类型
- [x] 修复和添加的冲突Bug

#### 第七轮迭代 (Addconfig)

添加一系列设置选项

- [x] 支持学习率设置
- [x] 支持神经元激活选择
- [x] 支持切换损失函数

#### 杂项

- [x] 支持一键多轮参数优化
- [x] 添加操作快捷键
- [x] 添加说明

### 计算实现 ###

根据图结构对神经元进行拓扑排序，再顺序计算各神经元上的值。

## 项目分工 ##

View：徐正浩

Model & ViewModel : 梁洵 杨云皓

