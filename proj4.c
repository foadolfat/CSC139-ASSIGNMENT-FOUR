#include <stdio.h>
#include <stdlib.h>

FILE* input;
int n, numOfPages, numOfFrames, requests;
int* frame;
int frameFree=0;
int unload=0;
int pageFaults=0;
int j=0;
int timer=0;

void lru(){
 printf("LRU\n");
 int on[numOfFrames]; 

 while(fscanf(input, "%d", &n)==1){
  int exists=0;
  int i=0;
  while(i<numOfFrames){
   if(frame[i]==n){
    printf("Page %d already in Frame %d\n", n, i);
    on[i]=timer;
    exists=1;
   }
   i++;
  }
  if(exists==0){
   pageFaults++;
   if(frameFree<numOfFrames){
    frame[frameFree]=n;
    on[frameFree]=timer;
    printf("Page %d loaded into Frame %d\n", n, frameFree);
    frameFree++;
   }else{
    int min=on[0];
    int index=0;
    int k;
    for(k=0; k<numOfFrames; k++){
     if(on[k]<min){
      min=on[k];
      index=k;
     }
    }
    printf("Page %d unloaded from Frame %d, Page %d loaded into frame %d\n", frame[index], index, n, index);
    frame[index]=n;
    on[index]=timer;
   }
  }
  timer++;
 }
 printf("%d page faults\n", pageFaults);
}

void clock(){
 printf("CLOCK\n");
 int ref[numOfFrames];
 
 while(j<requests){
  fscanf(input, "%d", &n);
  int exists=0;
  int i=0;
  while(i<numOfFrames){
   if(frame[i]==n){
    printf("Page %d already in Frame %d\n", n, i);
    exists=1;
    ref[i]=1;
   }
   i++;
  }
  if(exists==0){
   pageFaults++;
   if(frameFree<numOfFrames){
    frame[frameFree]=n;
    printf("Page %d loaded into Frame %d\n", n, frameFree);
    frameFree++;
   }else{
    while(ref[unload]==1){
     ref[unload]=0;
     unload=(unload+1)%numOfFrames;
    }     
    printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d \n", frame[unload], unload, n, unload);
    frame[unload]=n;
    unload=(unload+1)%numOfFrames;
   } 
  }
  j++;
 }
 printf("%d page faults\n", pageFaults);
}

int main(int arg, char* argv[]){ 
 input = fopen(argv[1], "r");
 
 fscanf(input, "%d", &numOfPages);
 fscanf(input, "%d", &numOfFrames);
 fscanf(input, "%d", &requests);
 
 frame = (int*)malloc(numOfFrames*sizeof(int));
 if(strcmp(argv[2], "CLOCK")==0){
  clock();
 }else if(strcmp(argv[2], "LRU")==0){
  lru();
 }else{
  printf("Invalid option\nUsage: ./proj4 <INPUT FILE NAME> <LRU | CLOCK>\n");
 }

}
