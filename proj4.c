#include <stdio.h>
#include <stdlib.h>

int main(int arg, char* argv[]){
 FILE* input;
 int n;
 int numOfPages, numOfFrames, requests;
 int* frame;
  
 input = fopen(argv[1], "r");
 
 fscanf(input, "%d", &numOfPages);
 fscanf(input, "%d", &numOfFrames);
 fscanf(input, "%d", &requests);
 
 frame = (int*)malloc(numOfFrames*sizeof(int));
 if(strcmp(argv[2], "CLOCK")==0){
  printf("**CLOCK**\n");
  int frameFree=0;
  int pageToUnload=0;
  int pageFaults=0;
  int j=0;
  int ref[numOfFrames];
 
  while(j<requests){
   fscanf(input, "%d", &n);
   int flagExist=0;
   int i;
   for(i=0; i<numOfFrames; i++){
    if(frame[i]==n){
     printf("Page %d already in Frame %d\n", n, i);
     flagExist=1;
     ref[i]=1;
    }
   }
   if(flagExist==0){
    pageFaults++;
    if(frameFree<numOfFrames){
     frame[frameFree]=n;
     printf("Page %d loaded into Frame %d\n", n, frameFree);
     frameFree++;
    }else{
     while(ref[pageToUnload]==1){
      ref[pageToUnload]=0;
      pageToUnload=(pageToUnload+1)%numOfFrames;
     }     
     printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d \n", frame[pageToUnload], pageToUnload, n, pageToUnload);
     frame[pageToUnload]=n;
     pageToUnload=(pageToUnload+1)%numOfFrames;
    } 
   }
   j++;
  }
  printf("%d page faults\n", pageFaults);
 }else if(strcmp(argv[2], "LRU")==0){
  printf("**LRU**\n");
  int* usage = (int*)malloc(numOfFrames*sizeof(int));
  int frameFree=0;
  int pageFaults=0;
  int timer=0;
  int j=0;
  while(1==fscanf(input, "%d", &n)){
   int flagExist=0;
   int i;
   for(i=0; i<numOfFrames; i++){
    if(frame[i]==n){
     printf("Page %d already in Frame %d\n", n, i);
     usage[i]=timer;
     flagExist=1;
    }
   }
   if(flagExist==0){
    pageFaults++;
    if(frameFree<numOfFrames){
     frame[frameFree]=n;
     usage[frameFree]=timer;
     printf("Page %d loaded into Frame %d\n", n, frameFree);
     frameFree++;
    }else{
     int min=usage[0];
     int lIndex=0;
     int k;
     for(k=0; k<numOfFrames; k++){
      if(usage[k]<min){
       min=usage[k];
       lIndex=k;
      }
     }
     printf("Page %d unloaded from Frame %d, Page %d loaded into frame %d\n", frame[lIndex], lIndex, n, lIndex);
     frame[lIndex]=n;
     usage[lIndex]=timer;
    }
   }
   timer++;
  }
  printf("%d page faults\n", pageFaults);
 }else{
  printf("Invalid option\nUsage: ./proj4 <INPUT FILE NAME> <LRU | CLOCK>\n");
 }

}
