# 五子棋裁判-（附带简单测试用AI）

---

* 应用平台与编译环境
* 用法说明
* 鸣谢

---

## * 应用平台

windowsNT + MinGW（主要也只用到了g++和ar命令，所以linux平台的用户可以方便地修改Makefile文件来编译）

## * 用法说明

本裁判机默认使用15*15大小五子棋盘。  

使用 make.bat 批处理运行 ./tools 文件夹下的 make.exe 工具一键编译。如果使用其他的编译平台请自行修改 Makefile 文件。

编译完成后请将您的AI程序放置在根目录下，与编译好的 pve.exe 文件同目录。

打开 pve.exe 文件后，先输入每一步棋的间隔毫秒数，再分别输入先后手AI程序的文件名（不包括后缀.exe）。

文件夹中 old1.exe 和 old2.exe 文件为我提供的早期的AI程序供大家测试。

### 约定

棋盘文件存储在win环境变量 %temp% 下的 board.dat 中，原则上对AI只读不可写。 .dat 文件格式为：第一行两个整数 sizeOfBoard 和 whosePart 。 sizeOfBoard 代表棋盘大小，恒为15。 whosePart 代表轮到哪一方下棋，值为 1 代表接下来该先手方下棋， 值为 2 代表接下来该后手方下棋。

接下来是一个15行15列的矩阵，用空格和回车隔开。矩阵中 0 代表空位， 1 代表先手方下好的棋子， 2 代表后手方下好的棋子。

AI 程序应在读取完棋盘文件后，进行计算，并将EAX寄存器置为你要下的位置的坐标的编码（对于C/C++，请在主函数中 return 该值，或调用 exit() 并向该函数传入该值以结束程序）。位置坐标编码规则如下：以棋盘的左上角为0行0列，(行数*15+列数)得到最后整个程序的返回值。

## * 鸣谢

首先感谢提出要做这个话题和在这个约定之下分开做了一些工作并相互交流过的闫楠同学，以及同组的郭一挺同学，他们帮助我确认了这种约定的可行性并分析了优劣。还要感谢共同完成报告的其余四个小组成员。
