#include<stdio.h>
#include<stdlib.h>

#define MAP_ROW 20//定义行数； 
#define MAX_len 20//定义蛇的最大长度； 

int snackX[MAX_len]={1,2,3,4};//记录蛇身的初始X坐标； 
int snackY[MAX_len]={1,1,1,1};//记录蛇身的初始Y坐标； 
int run=1;//判断游戏是否继续进行； 
int slen=4;//记录蛇的初始长度； 
int x;//记录蛇在x上移动的距离； 
int y;//记录蛇在y上移动的距离；
char map[20][21]={//初始地图； 
	"********************",
	"*XXXH              *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"*                  *",
	"********************"
};

void print_map(void);//打印地图；
void map_snack(int x,int y);//在地图上画出蛇移动后的图案；
void list_snack(int x,int y);//将蛇身的坐标改变为移动后的坐标； 
void snack_move(char c); //蛇的移动 ：通过调用 map_snack和list_snack实现；
 
int main(){
	char c;
	print_map();
	while(run!=0){
		c=getchar();
		snack_move(c);
		print_map();
	}
	printf("game is over");
}

void print_map(void){//打印地图； 
	system("cls");
	for(int i=0;i<MAP_ROW;++i){
		printf("%s\n",map[i]);
	}
}
void map_snack(int x,int y){//在地图上画出蛇移动后的图案； 
	map[snackY[0]][snackX[0]]=' ';//擦去尾巴； 
	map[snackY[slen-1]+y][snackX[slen-1]+x]='H';//在下一个位置生成头部； 
	map[snackY[slen-1]][snackX[slen-1]]='X';//原来头部位置生成身体； 
}
void list_snack(int x,int y){//将蛇身的坐标改变为移动后的坐标； 
		for(int i=1;i<slen;++i){//将蛇身的坐标整体后移一位，留出头部； 
		snackX[i-1]=snackX[i];
		snackY[i-1]=snackY[i];
		}
		snackY[slen-1]+=y;
		snackX[slen-1]+=x;//将新的头部所在坐标赋予留出的头部； 
}
void snack_move(char c){//蛇的移动 ：通过调用 map_snack和list_snack实现； 
	switch (c){
		case 'w':case 'W':
			if(map[snackY[slen-1]-1][snackX[slen-1]]=='*'||map[snackY[slen-1]-1][snackX[slen-1]]=='X')run=0;//判断游戏是否结束； 
			else {
				x=0;y=-1;//将方向字符转化为坐标移动； 
				map_snack(x,y);
				list_snack(x,y);
			};
			break;
		case 's':case 'S':
			if(map[snackY[slen-1]+1][snackX[slen-1]]=='*'||map[snackY[slen-1]+1][snackX[slen-1]]=='X')run=0;
			else {
				x=0,y=1;
				map_snack(x,y);
				list_snack(x,y);
			};
			break;
		case 'd':case 'D':
			if(map[snackY[slen-1]][snackX[slen-1]+1]=='*'||map[snackY[slen-1]][snackX[slen-1]+1]=='X')run=0;
			else {
				x=1,y=0;
				map_snack(x,y);
				list_snack(x,y);
			};
			break;
		case 'a':case 'A':
			if(map[snackY[slen-1]][snackX[slen-1]-1]=='*'||map[snackY[slen-1]][snackX[slen-1]-1]=='X')run=0;
			else {
				x=-1,y=0;
				map_snack(x,y);
				list_snack(x,y);
			}
			break;
	}
}

