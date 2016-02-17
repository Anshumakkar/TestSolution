#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



typedef struct Data{
int Row;
int Col;
int Len;
}Data;


typedef struct Queue{
Data* array;
int rear;
int front;
}Queue;


bool isQueueEmpty(Queue *q){
    return (q->front==q->rear)?true:false;
}

void enQueue(Queue *q,Data dt){

q->rear++;
q->array[q->rear]=dt;
}


Data deQueue(Queue *q){
    Data dt={0,0,0};
    if(isQueueEmpty(q)){
        return dt;
    }
    q->front++;
    dt=q->array[q->front];
    return dt;
}

Queue * createQueue(int num){
    Queue *q=(Queue*)calloc(1,sizeof(Queue));
    q->front=-1;
    q->rear=-1;
    q->array=(Data*)calloc(num,sizeof(Data));
    return q;
}

int Calculate(int arr[5][6],int sRow,int sCol,int rows,int cols,int len){


    int counter=0;
    int **visited=NULL;
    int i=0,j=0;
    Queue *q=createQueue(30);

    visited=(int**)calloc(5,sizeof(int*));
    for(i=0;i<5;i++){
        visited[i]=(int*)calloc(6,sizeof(int));
    }

    for(i=0;i<5;i++,printf("\n")){
        for(j=0;j<6;j++){
            printf(" %d ",arr[i][j]);
        }
    }

   if(len==0||(arr[sRow][sCol]==0)){
       printf("\n return 0");
        return 0;
    }

    /**Enqueue first element **/
    Data dt={sRow,sCol,len-1};
    enQueue(q,dt);
    counter++;
    visited[sRow][sCol]=1;

    while(!isQueueEmpty(q)){
        Data rt=deQueue(q);
        int row=rt.Row;
        int col=rt.Col;
        int length=rt.Len;

        /** Check left **/
        if((col-1>=0)&&length>0 && visited[row][col-1]==0 && (arr[row][col]&8)&& (arr[row][col-1]&2)){
            Data dt={row,col-1,length-1};
            enQueue(q,dt);
            counter++;
            visited[row][col-1]=1;
        }
        /**Check Right */
        if((col+1<cols)&&length>0 && visited[row][col+1]==0 && (arr[row][col]&2)&& (arr[row][col+1]&8)){
            Data dt={row,col+1,length-1};
            enQueue(q,dt);
            counter++;
            visited[row][col+1]=1;
        }
        /**Check Top */
        if((row-1>=0)&&length>0 && visited[row-1][col]==0 && (arr[row][col]&1)&& (arr[row-1][col+1]&4)){
            Data dt={row-1,col,length-1};
            enQueue(q,dt);
            counter++;
            visited[row-1][col]=1;
        }
        /**Check Bottom */
        if((row+1<rows)&&length>0 && visited[row+1][col]==0 && (arr[row][col]&4)&& (arr[row+1][col+1]&1)){
            Data dt={row+1,col,length-1};
            enQueue(q,dt);
            counter++;
            visited[row+1][col]=1;
        }
    }
    printf("\ncounter=%d",counter);
    return counter;




}


int main(){
    int arr[5][6]={{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};

    Calculate(arr,2,2,5,6,3);
    return 0;
}
