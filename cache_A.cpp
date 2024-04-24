#include "cachelab.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <getopt.h>
#include <unistd.h>
//typedef unsigned long long int mem_addr_t;
int h=0,v=0;
int hit=0,miss=0,eviction=0;
char filename[1<<7];
int S,E,B,s,b;

typedef struct{
    int valid;
    int tag;
    int time;
}cache_lines;  

cache_lines** cache = NULL;  





void cache_init()
{

        cache = (cache_lines**)malloc(sizeof(cache_lines*) * S); 
    for(int i = 0; i < S; ++i)
    {
        cache[i] = (cache_lines*)malloc(sizeof(cache_lines) * E);
        for(int j = 0; j < E; ++j)
        {
            cache[i][j].valid = 0;
            cache[i][j].tag = -1;
            cache[i][j].time = -1;
        }
    }
}

void cache_free(){
    for(int i=0;i<S;i++){
        free(cache[i]);
        
    }
    free(cache);
}
int LRU_index(int set){
    int maxtime=0,maxtime_index=0;
    for(int i=0;i<E;i++){
        if(i==0){
            maxtime=cache[set][i].time;
            continue;
        }
        else{
            if(cache[set][i].time>maxtime){
                maxtime=cache[set][i].time;
                maxtime_index=i;
            }
        }
    }
    return maxtime_index;
}



/*
int LRU_index_cache_S(){
    int maxtime=0,maxtime_index_S=0,maxtime_index_E=0;
    for(int i=0;i<S;i++){
        for(int j=0;j<E;j++){
            if(i==0&&j==0){
                maxtime=cache[i][j].time;
                continue;
            }
            else{
                if(cache[i][j].time>maxtime){
                    maxtime=cache[i][j].time;
                    maxtime_index_S=i;
                    maxtime_index_E=j;
                }
            }
        }
    }
    return maxtime_index_S;
}

int LRU_index_cache_E(){
    int maxtime=0,maxtime_index_S=0,maxtime_index_E=0;
    for(int i=0;i<S;i++){
        for(int j=0;j<E;j++){
            if(i==0&&j==0){
                maxtime=cache[i][j].time;
                continue;
            }
            else{
                if(cache[i][j].time>maxtime){
                    maxtime=cache[i][j].time;
                    maxtime_index_S=i;
                    maxtime_index_E=j;
                }
            }
        }
    }
    return maxtime_index_E;
}
*/


void update_time(){
    for(int i=0;i<S;i++){
        for(int j=0;j<E;j++){
            if(cache[i][j].valid==1){
                cache[i][j].time++;
            }
        }
    }
}

void set_empty_to_valid(int set,int index,int tag){
    cache[set][index].valid=1;
    cache[set][index].tag=tag;
    cache[set][index].time=0;
}

int if_hit(int set,int tag){
    for(int i=0;i<E;i++){
        if(cache[set][i].tag==tag&&cache[set][i].valid==1){
            return 1;
        }
    }
    return 0;
}

int find_hit(int set,int tag){
    //printf("taggg:%d",tag);
    for(int i=0;i<E;i++){
        //printf("&&");
        if(cache[set][i].tag==tag&&cache[set][i].valid==1){
            return i;
        }
    }
    return -1;
}

int if_empty(int set){
    for(int i=0;i<E;i++){
        // printf("valid:%d",cache_wset[i].valid);
        if(cache[set][i].valid==0){
            return 1;
        }
    }
    return 0;
}

int find_empty(int set){
    for(int i=0;i<E;i++){
        //printf("!");
        if(cache[set][i].valid==0){
            return i;
        }
    }
    return -1;
}
void update_all(unsigned int address){
    int tag=address>>(b+s);
    unsigned int temp=1<<31>>31;
    int set=(address>>b)&(temp>>(64-s));
    //printf("set:%dtag:%d",set,tag);
    int flag_hit=0;
    flag_hit=if_hit(set,tag);
    
    if(flag_hit){
        hit++;
        //printf("h\n");
        int hit_index=-1;
        hit_index=find_hit(set,tag);
        if(hit_index!=-1){
            cache[set][hit_index].time=0;
        }
        return;
    }
    
    int flag_empty=0;


    flag_empty=if_empty(set);
    //printf("%d",flag_empty);
    if(flag_empty){
        miss++;
        //printf("@");
        int empty_index=-1;
        empty_index=find_empty(set);
        set_empty_to_valid(set,empty_index,tag);
        return;
    }
    miss++;
    eviction++;
    //printf("e");
    int index=LRU_index(set);
    set_empty_to_valid(set,index,tag);

    //update_time();
    /*
    int flag_hit=0,hit_index=-1;
    for(int i=0;i<E;i++){
        if(cache[set][i].valid==0){
            continue;
        }
        if(cache[set][i].tag!=tag){
            continue;
        }
        else{
            flag_hit=1;
            hit_index=i;
            break;
        }
    }
    if(flag_hit==0){
        //miss
        miss++;
        int flag_empty=0,index_empty=-1;
        for(int i=0;i<E;i++){
            if(cache[set][i].valid==0){
                flag_empty=1;
                index_empty=i;
                break;
            }
            else{
                continue;
            }
        }
        if(flag_empty==0){
            eviction++;
            int maxtime=-1,index_maxtime_set=-1,index_maxtime_col=-1;
            for(int i=0;i<set;i++){
                for(int j=0;j<E;j++){
                    if(i==0&&j==0){
                        maxtime=cache[i][j].time;
                        index_maxtime_set=i;
                        index_maxtime_col=j;
                        continue;
                    }
                    else{
                        if(cache[i][j].time>maxtime){
                            maxtime=cache[i][j].time;
                            index_maxtime_set=i;
                            index_maxtime_col=j;
                        }
                    }
                }
            }
            cache[index_maxtime_set][index_maxtime_col].time=0;
            cache[index_maxtime_set][index_maxtime_col].tag=tag;
        }
        else{
            cache[set][index_empty].valid=1;
            cache[set][index_empty].time=0;
            cache[set][index_empty].tag=tag;
            return;
        }
    }
    else{
        //hit
        hit++;
        cache[set][hit_index].time=0;
        return;
    }
    */
}


void catch_files(){
    FILE* f=fopen(filename,"r");
    if(f==NULL){
        exit(-1);
    }
    char identifier;
    unsigned int address;
    int size;
    while(fscanf(f," %c  %x,%d",  &identifier, &address, &size)>0){
        if(identifier=='I'){
            continue;
        }
        if(identifier=='L'||identifier=='S'){
            update_all(address);
        }
        if(identifier=='M'){
            update_all(address);
            update_all(address);
        }
        update_time();
    }
    fclose(f);
}

int main(int argc,char* argv[])
{   
    int opt;
    E=0;E++;E--;
    b=0;b++;b--;
    s=0;s++;s--;
    h++;h--;
    v++;v--;
    /*
    FILE* f;
    f=fopen("/trace/yi.trace","r");
    */
    while(-1!=(opt=(getopt(argc,argv,"hvs:E:b:t:")))){
        switch(opt){
            case 'h':
                h=1;
                break;
            case 'v':
                v=1;
                break;
            case 's':
                s=atoi(optarg);
                break;
            case 'E':
                E=atoi(optarg);
                break;
            case 'b':
                b=atoi(optarg);
                break;
            case 't':
                strcpy(filename,optarg);
                break;
            default:
                break;
        }
    }
    S=1<<s;
    cache_init();
    //FILE* f=fopen(filename,"r");
    catch_files();
    cache_free();

    printSummary(hit, miss, eviction);
    hit=0;
    miss=0;
    eviction=0;
    return 0;
}