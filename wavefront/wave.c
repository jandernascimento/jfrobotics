#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 6

int workspace[ROWS][COLS]={
{0,0,0,1,0,0},
{0,0,0,1,0,0},
{0,0,1,1,1,0},
{0,0,0,1,0,0},
{0,0,0,1,0,0},
};

int navigation[ROWS][COLS]={
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1},
};

//initially, no cells are visited
int visited[ROWS][COLS]={
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
{0,0,0,0,0,0},
};

//searches for a cell with the minimum value in navigation
//array (not counting '-1' of course)
int *searchMin() {
  int *a;
  a = (int *)malloc(2*sizeof(int));
  int minx, miny;
  bool if_break;
  if_break = false;
  
  //first cell which has not been yet visited 
  //has the minimum value.
  for (int i=0; i<ROWS; i++ ) {
    
    for (int j=0; j<COLS; j++ ) {
      if ((visited[i][j] == 0) && (navigation[i][j] != -1) 
          && workspace[i][j] != 1) {
        minx = i;
        miny = j;
        if_break = true;
        break;
      }
    }
    //cell is found. break.
    if (if_break)
      break;
  }

  //check if an unvisited cell with the minimal
  //value in navigation array is found
  bool found = false;
  
  //traverse all the grid and find
  for (int i=0; i<ROWS; i++ ) 
    for (int j=0; j<COLS; j++ ) {
      if (navigation[i][j] <= navigation[minx][miny] && navigation[i][j] >-1
          && (workspace[i][j]!=1) && (visited[i][j] == 0)) {
        minx = i;
        miny = j;
        found = true;
      }
    }

  if (!found) {
    a[0] = -2;
    a[1] = -2;
  }
  else {
    a[0] = minx;
    a[1] = miny;
  }

  return a;
}

int main(){

  int x,y;

  printf("Welcome!\nChoose a start position:\nx = ");
  scanf("%d",&x);
  printf("y = ");
  scanf("%d",&y);
  printf("\n");

  if (workspace[x][y] == 1) {
    printf("illegal start position\n");
    return 0;
  } 
  //navigation of the start point is 0
	navigation[x][y]=0;
	visited[x][y]=1;
	
  //put 1 for all the neighbors of the initial cell
	if((x-1)>=0){
    if (workspace[x-1][y]!=1)
      navigation[x-1][y]=1;	
	}
	if((x+1)<ROWS){
    if (workspace[x+1][y]!=1)
      navigation[x+1][y]=1;	
	}
	if((y-1)>=0){
    if (workspace[x][y-1]!=1)
      navigation[x][y-1]=1;	
	}
	if((y+1)<COLS){
    if (workspace[x][y+1]!=1)
      navigation[x][y+1]=1;	
	}

  int *minElement;
  minElement = (int *)malloc(2*sizeof(int));
  
  //main loop.
  //
	for(int i=0; i<ROWS; i++){
    for(int j=0; j<COLS; j++){
      //at first, we search all the grid to find the cell
      //with the min value. Store it if found.
      minElement = searchMin();
      
      if (minElement[0] == -2)
        break;
      int xt = minElement[0];
      int yt = minElement[1];
      
      //mark it as visited
      visited[xt][yt]=1;
      
      //now, we calculate the distance for each neighbor;
      //we rewrite the navigation value of each neigbor only
      //if it's closer to go there from current cell, or it's
      //not yet calculated and =-1
      int current_val = navigation[xt][yt]+1;
      //check for each neigbor
      if((xt-1)>=0 && workspace[xt-1][yt]!=1){
        if (navigation[xt-1][yt] > current_val || navigation[xt-1][yt] ==-1)
          navigation[xt-1][yt]=current_val;
      }
      if((xt+1)<ROWS && workspace[xt+1][yt]!=1){
        if (navigation[xt+1][yt] > current_val || navigation[xt+1][yt] ==-1)
          navigation[xt+1][yt]=current_val;
      }
      if((yt-1)>=0 && workspace[xt][yt-1]!=1){
        if (navigation[xt][yt-1] > current_val || navigation[xt][yt-1] ==-1)
          navigation[xt][yt-1]=current_val;	
      }
      if((yt+1)<COLS && workspace[xt][yt+1]!=1){
        if (navigation[xt][yt+1] > current_val || navigation[xt][yt+1] ==-1)
          navigation[xt][yt+1]=current_val;
      }
        
    }
    //it's time to stop the main loop 
    if (minElement[0] == -2)
      break;
	}		
	
  //display navigation array
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++)
      printf("%d ",navigation[i][j]);
    printf("\n");
  }
  
  return 1;
}
