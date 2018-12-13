#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

#define MAP_ROW 20//���������� 
#define MAX_len 20//�����ߵ���󳤶ȣ� 

int snackX[MAX_len]={1,2,3,4};//��¼����ĳ�ʼX���ꣻ 
int snackY[MAX_len]={1,1,1,1};//��¼����ĳ�ʼY���ꣻ 
int run=1;//�ж���Ϸ�Ƿ�������У� 
int slen=4;//��¼�ߵĳ�ʼ���ȣ� 
int x;//��¼����x���ƶ��ľ��룻 
int y;//��¼����y���ƶ��ľ��룻
int foodX=5;//��¼ʳ��Xλ�� 
int foodY=1;/��¼ʳ��Yλ�� 
int food=0;//�ж��ߵ���һ���ƶ��Ƿ�����ʳ�
int Xd=0;//��¼��ͷX���� 
int Yd=0; //��¼��ͷY���� 
int time=0;//��¼���������� 
char map[20][21]={//��ʼ��ͼ�� 
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

void print_map(void);//��ӡ��ͼ��
void map_snack(int x,int y);//�ڵ�ͼ�ϻ������ƶ����ͼ����
void list_snack(int x,int y);//�����������ı�Ϊ�ƶ�������ꣻ 
void snack_move(char c); //�ߵ��ƶ� ��ͨ������ map_snack��list_snackʵ�֣�
void food_eat(void);//����ʳ� 
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


char headturn(int distanceX,int distanceY){//������ͷ�˶����� 
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
int ndeath(int Xd,int Yd){//�ж���ͷ��һ���˶��Ƿ�������� 
	int ndea=1;
	if(Xd==0&&Yd==0);
	else {
		if(map[snackY[slen-1]+Yd][snackX[slen-1]+Xd]=='X')ndea=0;
	}
	if(ndea==1)time=1;
	return ndea;
}
void headcorrect(int time){//������ͷ����ʹ�䲻���� 
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
		Xd=1;//���һ���������Ǿ����ɣ� 
	} 
}
char whereGoNext(int Hx,int Hy,int Fx,int Fy){
	int distanceX=Fx-Hx;
	int distanceY=Fy-Hy;
	if(ndeath(Xd,Yd)!=0){//�ж��Ƿ����������������ͷ���ص���ȷ�����ƶ��� 
		if(Xd!=0){
			if(Xd==1){
				if(distanceX-1==0){
					Xd=0;//����ָ��λ�ã�����һ�η�����Ϊ�㣬�ȴ� headturn(distanceX,distanceY)�����¸���ȷ���� 
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
		else if(Xd==0&&Yd==0){//����Ϊ��ʱ��������һ����ȷ���� 
			char c=headturn(distanceX,distanceY);
			return c;
		}
	}
	else{//�����һ���ƶ������������������ν����Բ����������� 
		headcorrect(time);
		++time;//���������� 
	}
}
void print_map(void){//��ӡ��ͼ�� 
	system("cls");
	for(int i=0;i<MAP_ROW;++i){
		printf("%s\n",map[i]);
	}
}
void map_snack(int x,int y){//�ڵ�ͼ�ϻ������ƶ����ͼ���� 
	if(food==0||slen==MAX_len){//��δ����ʳ�������ﵽ��� 
		map[snackY[0]][snackX[0]]=' ';//��ȥβ�ͣ�
	}
	map[snackY[slen-1]+y][snackX[slen-1]+x]='H';//����һ��λ������ͷ����
	map[snackY[slen-1]][snackX[slen-1]]='X'; //ԭ��ͷ��λ���������壻
}
void list_snack(int x,int y){//�����������ı�Ϊ�ƶ�������ꣻ 
	if(food==0||slen==MAX_len){//��δ����ʳ�������ﵽ���ֻ�����ƶ��� 
		for(int i=1;i<slen;++i){//������������������һλ������ͷ����
		snackX[i-1]=snackX[i];
		snackY[i-1]=snackY[i];
		}
		snackY[slen-1]+=y;
		snackX[slen-1]+=x;//���µ�ͷ���������긳��������ͷ���� 
	}
	else if(slen<MAX_len&&food!=0){//����ά���������ʳ��Ե����쳤һ�����壻 
			snackY[slen]=snackY[slen-1]+y;
			snackX[slen]=snackX[slen-1]+x;
			++slen;
			food_eat();//�߳Ե�ʳ��ڵ�ͼ�����������ʳ����ߴ���������ɣ� 
		}
	food=0;
	
}
void snack_move(char c){//�ߵ��ƶ� ��ͨ������ map_snack��list_snackʵ�֣� 
	switch (c){
		case 'w':case 'W':
			if(map[snackY[slen-1]-1][snackX[slen-1]]=='*'||map[snackY[slen-1]-1][snackX[slen-1]]=='X')run=0;//�ж���Ϸ�Ƿ������ 
			else {
				x=0;y=-1;//�������ַ�ת��Ϊ�����ƶ��� 
				if(map[snackY[slen-1]+y][snackX[slen-1]+x]=='$')food=1;//�ж��Ƿ�����ʳ� 
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
void food_eat()//����ʳ��
{
	foodX = rand() % 20 + 1;
	foodY = rand() % 20 + 1;
	while (map[foodY][foodX] != ' ') {
		foodX = rand() % 20 + 1;
		foodY = rand() % 20 + 1;
	}//���ʳ��û���ڿհ״����ɾ�������һ��
	map[foodY][foodX] = '$';
}
