# 基于 AT89C51 单片机的电梯显示面板设计

## 项目概述
本项目是基于 Proteus 仿真软件制作的一个简易的电梯上显示楼层信息的面板。

通过用户按楼层对应按键，面板会随着电梯的升降实时的显示当前得楼层位置。

## 电梯显示面板效果
![image](https://github.com/mz8023yt/elevator-display-panel/blob/master/Image/run.gif)

## 功能介绍
本项目使用 8 个按键模拟电梯中的楼层按键，这 8 个按键分别为：

- 7楼
- 6楼
- 5楼
- 4楼
- 3楼
- 2楼
- 1楼
- -1楼

通过按下对应楼层按键，电梯将运行到对应楼层。

## 使用方法
点击右上角 Clone or download --> Download ZIP，直接下载本项目。

或者点击上方的 releases 下载稳定的发布版本。

使用 Keil 5 打开 /Project/AT89C51.uvproj 文件即可浏览源码。

使用 Perteus 7 打开 /Circuit/elevator-display-panel.dsn 文件即可运行仿真文件。
