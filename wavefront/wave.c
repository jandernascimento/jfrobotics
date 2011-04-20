#include <stdio.h>

#define ROWS 5
#define COLS 6

int workspace[ROWS][COLS]={
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
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

int *searchMin() {
  int *a;
  a = (int *)malloc(2*sizeof(int));
  int minx, miny;
  //first element is minimal. Compare all others
  //to this one to find the min step by step
  for (int i=0; i<ROWS; i++ ) 
    for (int j=0; j<COLS; j++ ) {
      if (visited[i][j] == 0 && navigation[i][j]!=-1) {
        minx = i;
        miny = j;
      }
    }

  for (int i=0; i<ROWS; i++ ) 
    for (int j=0; j<COLS; j++ ) {
      if (navigation[i][j] < navigation[minx][miny] && workspace[i][j]!=1
            && visited[i][j] == 0 && navigation[i][j] > -1)
        minx = i;
        miny = j;
    }

  a[0] = minx;
  a[1] = miny;
  return a;
}

void main(){

	navigation[x][y]=0;
	
	visited[x][y]=1;
	
	if((x-1)>0&&(x-1)<ROWS){
    if (workspace[x-1][y]!=1)
      navigation[x-1][y]=1;	
	}
	if((x+1)>0&&(x+1)<ROWS){
    if (workspace[x+1][y]!=1)
      navigation[x+1][y]=1;	
	}
	if((y+1)>0&&(y+1)<COLS){
    if (workspace[x][y+1]!=1)
      navigation[x][y+1]=1;	
	}
	if((y-1)>0&&(y-1)<COLS){
    if (workspace[x][y-1]!=1)
      navigation[x][y-1]=1;	
	}

	for(int i=0; i<ROWS; i++){
    for(int j=0; j<COLS; i++){
    //at first, we search all the grid to find the cell
    //with the min value. Store it.
		int *minElement=searchMin(i,j);
    if (minElement[0] = -2)
      continue;
    int xt = minElement[0];
    int yt = minElement[1];
    //delete this cell from the array of candidates
    visited[xt][yt]=1;
    //now, we calculate the distance for each neighbor;
    int current_val = navigation[xt][yt]+1;
    if((xt-1)>0&&(xt-1)<ROWS){
      if (workspace[xt-1][yt]!=1)
        navigation[xt-1][yt]=current_val;
    }
    if((xt+1)>0&&(xt+1)<ROWS){
      if (workspace[xt+1][yt]!=1)
        navigation[xt+1][yt]=current_val;
    }
    if((yt+1)>0&&(yt+1)<COLS){
      if (workspace[xt][yt+1]!=1)
        navigation[xt][yt+1]=current_val;
    }
    if((yt-1)>0&&(yt-1)<COLS){
      if (workspace[xt][yt-1]!=1)
        navigation[xt][yt-1]=current_val;	
    }
    }
	}		
	
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++)
      printf("%d ",navigation[i][j]);
    printf("\n");
  }

}
