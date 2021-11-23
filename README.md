# 项目介绍
欢乐斗地主残局AI

# 编译
使用G++编译器
## Linux
编译命令
```
g++ -std=c++11 *.cpp -o ddz
```
运行
```
./ddz
```
## Windows

编译命令
```
g++ -std=c++11 *.cpp -o ddz.exe
```
运行
```
.\ddz.exe
```

# 使用方法
## 输入双方初始手牌
输入己方的手牌，不区分大小写，不含空格（大王: Y, 小王: X, A: A, K: K, Q: Q, J: J, 10: 0）
```
Input Your Cards:
```
输入对方的手牌，要求同上
```
Input Oppo Cards:
```

## 显示必胜和方案/必败
### 必胜和方案
```
[Win] (LianDui, AA)  (LianDui, 22)
```
方案之间用空格隔开，方案是一个二元组，第一个分量是牌型，第二个分量是牌序列
### 必败
```
[Lose]
```
必败则不给出方案

## 输入每一轮的出牌
己方出牌，要求同输入初始手牌，空输入表示不要
```
Your OnePlay:
```
对方出牌，要求同上
```
Oppo OnePlay:
```

# 示例
## 输入双方初始手牌
![#](./example/1.jpg)
```
Input Your Cards: KQJ9555443
Input Oppo Cards: YXKQJ0866643
```
## 显示必胜和方案/必败
![#](./example/2.jpg)
```
>                 <
>-----------------<
[Win] (FeiJi2, 55544) 
```
## 输入每一轮的出牌
![#](./example/3.jpg)
```
Your OnePlay: 55544
Oppo OnePlay: YX
================
Your Cards: KQJ93
Oppo Cards: KQJ0866643
```

## 如此循环
直到一方牌出完
![#](./example/4.jpg)
```
> <
>-<
[Win] (Empty) 
Your OnePlay:    
Oppo OnePlay: 6663
================
Your Cards: KQJ93
Oppo Cards: KQJ084
......
```