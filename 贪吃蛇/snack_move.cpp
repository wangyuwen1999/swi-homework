#include<stdio.h>
#include<stdlib.h>

#define MAP_ROW 20//���������� 
#define MAX_len 20//�����ߵ���󳤶ȣ� 

int snackX[MAX_len]={1,2,3,4};//��¼����ĳ�ʼX���ꣻ 
int snackY[MAX_len]={1,1,1,1};//��¼����ĳ�ʼY���ꣻ 
int run=1;//�ж���Ϸ�Ƿ�������У� 
int slen=4;//��¼�ߵĳ�ʼ���ȣ� 
int x;//��¼����x���ƶ��ľ��룻 
int y;//��¼����y���ƶ��ľ��룻
char map[20][21]={//��ʼ��ͼ�� 
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

void print_map(void);//��ӡ��ͼ��
void map_snack(int x,int y);//�ڵ�ͼ�ϻ������ƶ����ͼ����
void list_snack(int x,int y);//�����������ı�Ϊ�ƶ�������ꣻ 
void snack_move(char c); //�ߵ��ƶ� ��ͨ������ map_snack��list_snackʵ�֣�
 
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

void print_map(void){//��ӡ��ͼ�� 
	system("cls");
	for(int i=0;i<MAP_ROW;++i){
		printf("%s\n",map[i]);
	}
}
void map_snack(int x,int y){//�ڵ�ͼ�ϻ������ƶ����ͼ���� 
	map[snackY[0]][snackX[0]]=' ';//��ȥβ�ͣ� 
	map[snackY[slen-1]+y][snackX[slen-1]+x]='H';//����һ��λ������ͷ���� 
	map[snackY[slen-1]][snackX[slen-1]]='X';//ԭ��ͷ��λ���������壻 
}
void list_snack(int x,int y){//�����������ı�Ϊ�ƶ�������ꣻ 
		for(int i=1;i<slen;++i){//������������������һλ������ͷ���� 
		snackX[i-1]=snackX[i];
		snackY[i-1]=snackY[i];
		}
		snackY[slen-1]+=y;
		snackX[slen-1]+=x;//���µ�ͷ���������긳��������ͷ���� 
}
void snack_move(char c){//�ߵ��ƶ� ��ͨ������ map_snack��list_snackʵ�֣� 
	switch (c){
		case 'w':case 'W':
			if(map[snackY[slen-1]-1][snackX[slen-1]]=='*'||map[snackY[slen-1]-1][snackX[slen-1]]=='X')run=0;//�ж���Ϸ�Ƿ������ 
			else {
				x=0;y=-1;//�������ַ�ת��Ϊ�����ƶ��� 
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

