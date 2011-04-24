#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 6

int workspace[ROWS][COLS]={
	{0,0,0,1,0,0},
	{0,0,0,1,0,0},
	{0,0,1,1,1,0},
	{0,0,0,0,0,0},
	{0,0,0,1,0,0},
};

int navigation[ROWS][COLS]={
	{-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1},
};


/*
   int navigation[ROWS][COLS]={
   {0,1,2,-1,6,7},
   {1,2,3,4,5,6},
   {2,3,-1,-1,-1,7},
   {3,4,5,-1,9,8},
   {4,5,6,-1,10,9},
   };
 */

int shortestpath[ROWS][COLS]={
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
};

//initially, no cells are visited
int visited[ROWS][COLS]={
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
};

void printworkspacematrix(void){
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			if(workspace[i][j]==1){
				printf("\e[37;41m %02d \e[m",workspace[i][j]);
			}else{
				printf("\e[37;44m %02d \e[m",workspace[i][j]);

			}
		//printf("%d ",workspace[i][j]);
		printf("\n");
	}
}

//print a colored matrix according to the values
void printnavigationmatrix(void){
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			if(navigation[i][j]==-1){
				printf("\e[37;41m %02d \e[m",navigation[i][j]);
			}else{
				if(shortestpath[i][j])
					printf("\e[37;42m %02d \e[m",navigation[i][j]);
				else
					printf("\e[37;44m %02d \e[m",navigation[i][j]);

			}
		//printf("%d ",navigation[i][j]);
		printf("\n");
	}
}

void printfunctionmatrix(void){
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			if(navigation[i][j]==-1){
				printf("\e[37;41m %02d \e[m",navigation[i][j]);
			}else{
				printf("\e[37;44m %02d \e[m",navigation[i][j]);

			}
		//printf("%d ",navigation[i][j]);
		printf("\n");
	}
}

int *getmin(int x, int y){
  	//the starting point is a path, so should be marked as one
        shortestpath[x][y]=1;
	//these are the alternatives exits from a single spot (east,west,south or north).
	int possibilities[4][2]={
		{x,y+1},
		{x,y-1},
		{x+1,y},
		{x-1,y},
	};
	//index of the possibility to be tested
	int index=0;
	
	//the minimum value is assigned for the maximum possible value for an integer(which is 4 bytes), so the first value of the reading become the minimum
	int minval=pow(2,8*4),minx=-1,miny=-1;

	do {
		int x=possibilities[index][0];
		int y=possibilities[index][1];

		//printf("testing %d,%d value %d\n ",x,y,navigation[x][y]);

		//if is a valid coordinate and the size is minimum, compared with the other possibilities.
		if(
				x>=0 && x<ROWS &&
				y>=0 && y<COLS &&
				navigation[x][y]<minval && 
				navigation[x][y]!=-1 
		  ){
			minval=navigation[x][y];
			minx=x;
			miny=y;
		}
		//go for the next possibility
		index++;
		//just for possibilities
	}while (index<4);
	//create an array to return the choosen coordinate
	int *val=(int *)malloc(sizeof(int)*2);
	val[0]=minx;
	val[1]=miny;
	//if found a minimum path, means that there is a path from the start to the goal
	if(minx!=-1){
		shortestpath[minx][miny]=1;	
	}

	return val;


}

//Fill up the shortest path matrix, which stores the shortest path for a given workspace
void fillshortestpath(int x,int y){

	//check whether the requested coordinates are outside the matrix dimension
	if(!(x<ROWS&&y<COLS)){
		fprintf(stderr,"ERROR! Your spot is not into the matrix boundaries buddy\n");
		exit(1);
	}

	//check wheter the requested coordinates are in a wall (somewhere where the robot cannot be)
	if(workspace[x][y]==1){
		fprintf(stderr,"ERROR! You cannot start from there buddy. This is an obstacle.\n");
		exit(1);
	}

	//runs through all individual steps (shortest individual cell)
	do {
		//given the x,y spot, returns the shortest exist (north,south,east or west)
		int *coord=getmin(x,y);
		x=coord[0];
		y=coord[1];
		free(coord);
		//fprintf(stderr,"min (%d,%d)..value %d\n",x,y,navigation[x][y]);
	}while(navigation[x][y]!=-1&&navigation[x][y]!=0);

	//check is any path was found from the start to the goal
	if(x==-1||y==-1){
		fprintf(stderr,"FAIL! No path, sorry buddy.\n");
		exit(1);
	}

}


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

	int x,y,sx,sy;

	printf("\n\nWelcome to pathfinder\n\n");

	printf("Instruction:\n");
	printf("x means the line number, and starts from 0 until %i:\n",ROWS-1);
	printf("y means the column number, and starts from 0 until %i:\n\n",COLS-1);
	
	printf("Your Workspace:\n");
	printworkspacematrix();

	printf("Choose the goal:\nx? ");
	scanf("%d",&x);
	printf("y? ");
	scanf("%d",&y);
	printf("\n");


	printf("Choose the start:\nx?");
	scanf("%d",&sx);
	printf("y?");
	scanf("%d",&sy);
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
	printf("Navigation:\n");
	//print the workspace matrix
	printfunctionmatrix(); 
	printf("Result of the Shortest search:\n");
	//fill the shortestpath matrix to decide which track take
	fillshortestpath(sx,sy);
	//print the navigation matrix
	printnavigationmatrix(); 

	return 1;
}
