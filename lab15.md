# 字符游戏 - 智能蛇（2）
* 本次项目的任务是让蛇有一定的智能，能通过算法具有 “感知 - 决策 - 行动” 的能力。近一步，你可以做出华丽的字符界面，实现 人控蛇 与 智能蛇 抢食大战。
## 一、实验目的
* 了解 算法 与 “智能” 的关系
* 通过算法赋予蛇智能
* 了解 Linux IO 设计的控制
## 二、实验环境
* Linux Only. 你可以选择 Unbutu、Centos 等发行版。
* 建议编辑环境 Vim 或 Vscode, 编译 gcc
* 第一次使用 Linux，建议使用虚拟机。可以使用其他同学准备好的 Vbox 镜像

由于准备不充分，编者只能用 devc++ 来实现智能蛇；

### 2、智能蛇的程序框架

	输出字符矩阵
	WHILE not 游戏结束 DO
        wait(time)
		ch＝whereGoNext(Hx,Hy,Fx,Fy)
		CASE ch DO
		‘A’:左前进一步，break 
		‘D’:右前进一步，break    
		‘W’:上前进一步，break    
		‘S’:下前进一步，break    
		END CASE
		输出字符矩阵
	END WHILE
	输出 Game Over!!! 

具体代码实现：

```c:
int main(){
	print_map();//事先打印地图；
	char c;//定义字符变量c储存运动位置；
	while(run!=0){
		sleep(1);//限定每一秒循环一次；
		c=whereGoNext(snackX[slen-1],snackY[slen-1],foodX,foodY);//寻找下一个运动指令；
		snack_move(c);//依指令操纵蛇的运动；
		print_map();//打印运动后地图；
	}
	if(slen==MAX_len){//如果蛇身达最长则胜利；
			printf("you win!!!");
		}
	else printf("game is over!!!");//如果蛇身达未达最长则失败；
}
```
其中sleep函数类延时函数存在于库中
* 在VC中使用带上头文件
   * #include <windows.h>
（ Sleep函数存放头文件：WinBase.h）
* 在gcc编译器中，使用的头文件因gcc版本的不同而不同
   *  #include <unistd.h>
Sleep()单位为毫秒，sleep()单位为秒
* 如果需要更精确可以用usleep单位为微秒


sleep(1)表示延迟一秒；

### 时钟换算:
* 微秒，时间单位，符号us（英语：microsecond ）.
* 1微秒等于百万分之一秒（10的负6 次方秒）
* 0.000 001 微秒 = 1皮秒
* 0.001 微秒 = 1纳秒
* 1,000 微秒 = 1毫秒
* 1,000,000 微秒 = 1秒
* 1s = 1000ms
* 1ms = 1000μs
* 1μs = 1000ns
* 1ns = 1000ps
* 1秒(s) = 1000 毫秒(ms) = 1,000,000 微秒(μs) = 1,000,000,000 纳秒(ns) = 1,000,000,000,000 皮秒(ps)

whereGoNext(Hx,Hy,Fx,Fy)函数是蛇智能实现的原因，它会根据蛇与食物的坐标，返回规避障碍的路径；

### 具体代码实现：

```c
char whereGoNext(int Hx,int Hy,int Fx,int Fy){
	int distanceX=Fx-Hx;//定义蛇与食物的水平距离；
	int distanceY=Fy-Hy;//定义蛇与食物的垂直距离；
	if(map[snackY[slen-1]-1][snackX[slen-1]]=='X'&&(map[snackY[slen-1]+1][snackX[slen-1]]=='X'||map[snackY[slen-1]][snackX[slen-1]-1]=='X'))return 'd';//如果蛇的上边与左边或上边与下边或上下左均有身体则向右走；
	else if(map[snackY[slen-1]][snackX[slen-1]-1]=='X'&&(map[snackY[slen-1]][snackX[slen-1]+1]=='X'||map[snackY[slen-1]+1][snackX[slen-1]]=='X'))return 'w';//如果蛇的左边与右边或左边与下边或左右下均有身体则向上走；
	else {
	    if(snackX[slen-1]==snackX[slen-2]){//
		    if(distanceX>0)return 'd';
		    else if(distanceX<0)return 'a';
		    else if(distanceX==0){
			    if(distanceY<0)return 'w';
			    else return 's'; 
		    }
	    }
	    else if(snackY[slen-1]==snackY[slen-2]){//
		    if(distanceY>0)return 's';
		    else if(distanceY<0)return 'w';
		    else if(distanceY==0){
			if(distanceX>0)return 'd';
			else return 'a';
		    }
	    }
    }	
}
```
