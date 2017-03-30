#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include <unistd.h> 
#include<string.h>
#include <sstream>

using namespace std;
char filename[]="/proc/loadavg";
char filename2[]="/proc/meminfo";
char filename3[]="/proc/diskstats";
fstream fp;
void get_cpu(){
    char line[10];
    fp.open(filename,ios::in);//開啟檔案
    fp.getline(line, sizeof(line), ' ');
    int ans=atof(line)*100;
    printf("CPU Loading: %d\n", ans);
    fp.close();//關閉檔案
}
void get_mem(){
    float totalmem,freemem;
    char line2[2][128];
    fp.open(filename2,ios::in);//開啟檔案
    for (int i=0;i<=1;i++){
        fp.getline(line2[i], sizeof(line2), '\n');
    }
    string tot,free;
    tot=line2[0];
    free=line2[1];
    tot=tot.substr(17,7);
    free=free.substr(17,7);
    totalmem=atof(tot.c_str());
    freemem=atof(free.c_str());
    printf("Memory Usage: %1.0f/%1.0f MB (%f%%)\n", freemem,totalmem-freemem,freemem/(totalmem-freemem)*100);
    fp.close();//關閉檔案
}
void get_disk(double* ans){
    char line[26][128];
    double write,write2,read,read2;
    fp.open(filename3,ios::in);//開啟檔案
    for (int i=0;i<26;i++){
        fp.getline(line[i], sizeof(line), '\n');
    }
    string sub_str;
    string fin=line[25];
    stringstream ss(fin);
    for (int j=0;j<sizeof(line[25]);j++){
        getline(ss,sub_str,' ');
        if (j==14){
            ans[0]=atof(sub_str.c_str())/2048;
        }
        else if(j==18){
            ans[1]=atof(sub_str.c_str())/2048;
        }
    }
    fp.close();//關閉檔案
}
int main(){
    double ans[2];
    double ans2[2];
    get_cpu();
    get_mem();
    get_disk(ans);
    sleep(1);
    get_disk(ans2);
    printf("Disk Write speed: %f MB/S\n",ans2[1]-ans[1]);
    printf("Disk Read speed: %f MB/S\n",ans2[0]-ans[0]);
    return 0;
}
