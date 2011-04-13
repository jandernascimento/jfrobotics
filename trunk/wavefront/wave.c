#include <stdio.h>

#define ROWS 5;
#define COLS 6;

int workspace[ROWS][COLS]={
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,1,1,1,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
};

int navigation[ROWS][COLS]={
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
};

int visited[ROWS][COLS]={
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
};

int x=0,y=0;
/*
void visit(int x, int y, int value){
	if(workspace[x][y]!=-1) return;
	
       visit(x,y+1,value+1);
       visit(x,y-1,value+1);
       visit(x+1,y+1,value+1);
       visit(x-1,y+1,value+1);
}
*/
void main(){

	navigation[x][y]=0;
	
	visited[x][y]=1;
	
	if((x-1)>0&&(x-1)<ROWS){
		navigation[x-1][y]=1;	
	}
	if((x+1)>0&&(x+1)<ROWS){
		navigation[x+1][y]=1;	
	}
	if((y+1)>0&&(y+1)<COLS){
		navigation[x][y+1]=1;	
	}
	if((y-1)>0&&(y-1)<COLS){
		navigation[x][y-1]=1;	
	}

	for(int i=1;i<(ROWS*COLS);i++){
		int minElement[2]=searchMin();	
	}		
	
	printf("test");

}
