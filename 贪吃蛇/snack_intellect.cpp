#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

#define MAP_ROW 20//定义行数； 
#define MAX_len 20//定义蛇的最大长度； 

int snackX[MAX_len]={1,2,3,4};//记录蛇身的初始X坐标； 
int snackY[MAX_len]={1,1,1,1};//记录蛇身的初始Y坐标； 
int run=1;//判断游戏是否继续进行； 
int slen=4;//记录蛇的初始长度； 
int x;//记录蛇在x上移动的距离； 
int y;//记录蛇在y上移动的距离；
int foodX=5;//记录食物X位置 
int foodY=1;/记录食物Y位置 
int food=0;//判断蛇的下一次移动是否遇到食物；
int Xd=0;//记录蛇头X方向； 
int Yd=0; //记录蛇头Y方向； 
int time=0;//记录矫正次数； 
char map[20][21]={//初始地图； 
	"********************",
	"*XXXH$             *",
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
void food_eat(void);//生成食物； 
char whereGoNext(int Hx,int Hy,int Fx,int Fy);
int main(){
	print_map();
	char c;
	while(run!=0){
		sleep(1);
		c=whereGoNext(snackX[slen-1],snackY[slen-1],foodX,foodY);
		snack_move(c);
		print_map();
		if(slen==MAX_len){
			printf("you win!!!");
			break;
		}
		printf("%d,%d==%d,%d",foodX,foodY,snackX[slen-1],snackY[slen-1]);
	}
	if(slen!=MAX_len)printf("game is over!!!");
}


char headturn(int distanceX,int distanceY){//定义蛇头运动方向； 
	if(snackX[slen-1]==snackX[slen-2]){
			if(distanceX>0){
				Xd=1;
			}
			else if(distanceX<0){
				Xd=-1;
			}
			else if(distanceX==0){
				if(distanceY<0)Yd=-1;
				else if(distanceY>0)Yd=1;
			} 
		}
	else if(snackY[slen-1]==snackY[slen-2]){
			if(distanceY>0){
				Yd=1;
			}
			else if(distanceY<0){
				Yd=-1;
			}
			else if(distanceY==0){
				if(distanceX<0)Xd=-1;
				else if(distanceX>0)Xd=1;
			} 
		}
}
int ndeath(int Xd,int Yd){//判断蛇头下一次运动是否会死亡； 
	int ndea=1;
	if(Xd==0&&Yd==0);
	else {
		if(map[snackY[slen-1]+Yd][snackX[slen-1]+Xd]=='X')ndea=0;
	}
	if(ndea==1)time=1;
	return ndea;
}
void headcorrect(int time){//矫正蛇头方向，使其不死； 
	if(time%3!=0||time==0){
		if(Xd==0){
			if(Yd==-1)Yd=1;
			else if(Yd==1)Yd=-1;
		}
		else if(Yd==0){
			if(Xd==1)Xd=-1;
			else if(Xd==-1)Xd=1;
		}
	}
	else {
		Xd=1;//如果一定会死，那就死吧； 
	} 
}
char whereGoNext(int Hx,int Hy,int Fx,int Fy){
	int distanceX=Fx-Hx;
	int distanceY=Fy-Hy;
	if(ndeath(Xd,Yd)!=0){//判断是否会死，不会则以蛇头返回的正确方向移动； 
		if(Xd!=0){
			if(Xd==1){
				if(distanceX-1==0){
					Xd=0;//到达指定位置，将下一次方向置为零，等待 headturn(distanceX,distanceY)返回下个正确方向； 
				}
				return 'd';
			}
			if(Xd==-1){
				if(distanceX+1==0){
					Xd=0;
					}
				return 'a';
			}
		}
		else if(Yd!=0){
			if(Yd==1){
				if(distanceY-1==0){
					Yd=0;
				}
				return 's';
			}
			if(Yd==-1){
				if(distanceY+1==0){
					Yd=0;
				}
				return 'w';
			}
		}
		else if(Xd==0&&Yd==0){//方向为零时，返回下一个正确方向； 
			char c=headturn(distanceX,distanceY);
			return c;
		}
	}
	else{//如果下一个移动会死亡，矫正，三次矫正仍不行则死亡； 
		headcorrect(time);
		++time;//矫正次数； 
	}
}
void print_map(void){//打印地图； 
	system("cls");
	for(int i=0;i<MAP_ROW;++i){
		printf("%s\n",map[i]);
	}
}
void map_snack(int x,int y){//在地图上画出蛇移动后的图案； 
	if(food==0||slen==MAX_len){//蛇未遇到食物，或身体达到最长。 
		map[snackY[0]][snackX[0]]=' ';//擦去尾巴；
	}
	map[snackY[slen-1]+y][snackX[slen-1]+x]='H';//在下一个位置生成头部；
	map[snackY[slen-1]][snackX[slen-1]]='X'; //原来头部位置生成身体；
}
void list_snack(int x,int y){//将蛇身的坐标改变为移动后的坐标； 
	if(food==0||slen==MAX_len){//蛇未遇到食物，或身体达到最长，只进行移动； 
		for(int i=1;i<slen;++i){//将蛇身的坐标整体后移一位，留出头部；
		snackX[i-1]=snackX[i];
		snackY[i-1]=snackY[i];
		}
		snackY[slen-1]+=y;
		snackX[slen-1]+=x;//将新的头部所在坐标赋予留出的头部； 
	}
	else if(slen<MAX_len&&food!=0){//蛇身维达最长，遇到食物，吃掉并伸长一节身体； 
			snackY[slen]=snackY[slen-1]+y;
			snackX[slen]=snackX[slen-1]+x;
			++slen;
			food_eat();//蛇吃掉食物，在地图上随机生成新食物，当蛇达最长后不再生成； 
		}
	food=0;
	
}
void snack_move(char c){//蛇的移动 ：通过调用 map_snack和list_snack实现； 
	switch (c){
		case 'w':case 'W':
			if(map[snackY[slen-1]-1][snackX[slen-1]]=='*'||map[snackY[slen-1]-1][snackX[slen-1]]=='X')run=0;//判断游戏是否结束； 
			else {
				x=0;y=-1;//将方向字符转化为坐标移动； 
				if(map[snackY[slen-1]+y][snackX[slen-1]+x]=='$')food=1;//判断是否遇到食物； 
				map_snack(x,y);
				list_snack(x,y);
			};
			break;
		case 's':case 'S':
			if(map[snackY[slen-1]+1][snackX[slen-1]]=='*'||map[snackY[slen-1]+1][snackX[slen-1]]=='X')run=0;
			else {
				x=0,y=1;
				if(map[snackY[slen-1]+y][snackX[slen-1]+x]=='$')food=1;
				map_snack(x,y);
				list_snack(x,y);
			};
			break;
		case 'd':case 'D':
			if(map[snackY[slen-1]][snackX[slen-1]+1]=='*'||map[snackY[slen-1]][snackX[slen-1]+1]=='X')run=0;
			else {
				x=1,y=0;
				if(map[snackY[slen-1]+y][snackX[slen-1]+x]=='$')food=1;
				map_snack(x,y);
				list_snack(x,y);
			}
			break;
		case 'a':case 'A':
			if(map[snackY[slen-1]][snackX[slen-1]-1]=='*'||map[snackY[slen-1]][snackX[slen-1]-1]=='X')run=0;
			else {
				x=-1,y=0;
				if(map[snackY[slen-1]+y][snackX[slen-1]+x]=='$')food=1;
				map_snack(x,y);
				list_snack(x,y);
			}
			break;
	}
}
void food_eat()//生成食物
{
	foodX = rand() % 20 + 1;
	foodY = rand() % 20 + 1;
	while (map[foodY][foodX] != ' ') {
		foodX = rand() % 20 + 1;
		foodY = rand() % 20 + 1;
	}//如果食物没有在空白处生成就再生成一次
	map[foodY][foodX] = '$';
}
