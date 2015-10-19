#include<iostream>
#include<stdio.h>
#include<stdlib.h>

struct ipsubnet{
    int subnet[4];
    int mask[4];
    int counter = 0;
};

class IPstat{
private:

    int i=0,j=0,listsize=0;//listsize用来计算IP的个数
    FILE *fp;//用于文件操作
public:
    void getIP(int val[][4]);// 读取IP.txt取得IP
    void getSubnet(struct ipsubnet *val);//读取subnet.txt取得子网号和子网掩码
    void match(int ip[][4],struct ipsubnet *val);//将IP和子网掩码进行&运算并和子网号匹配
    void output(struct ipsubnet *val);//将匹配的结果输出到result.txt

};

void IPstat::getIP(int val[][4]){
    fp = fopen("e:/Dev c++/IP.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%d.%d.%d.%d\n",&val[i][0],&val[i][1],&val[i][2],&val[i][3]);
        i++;
        listsize++;
    }
    fclose(fp);
}

void IPstat::getSubnet(struct ipsubnet *val){
    fp = fopen("e:/Dev c++/subnet.txt","r");
    i = 0;
    while(!feof(fp)){
        fscanf(fp,"%d.%d.%d.%d\t%d.%d.%d.%d\n",&val[i].subnet[0],&val[i].subnet[1],&val[i].subnet[2],&val[i].subnet[3],&val[i].mask[0],&val[i].mask[1],&val[i].mask[2],&val[i].mask[3]);
        i++;
    }
    fclose(fp);
}

void IPstat::match(int ip[][4],struct ipsubnet *val){
    int temp[100][4];
    int a;
    for(i=i-1;i>=0;i--){
        for(j=0;j<4;j++){
            temp[i][j] =ip[i][j]&val[i].mask[j];
        }
    }

    for(i=0;i<listsize;i++){
        for(j=0;j<listsize;j++){
            for(a=0;a<4;a++){
            if(temp[j][a]!=val[i].subnet[a])
                break;
            else if(a==3)
                val[i].counter++;
            }
        }
    }


}

void IPstat::output(struct ipsubnet *val){

    i = 0;
    fp = fopen("e:/Dev c++/result.txt","w");
    while(i<listsize){
        fprintf(fp,"%d.%d.%d.%d\t%d\n",val[i].subnet[0],val[i].subnet[1],val[i].subnet[2],val[i].subnet[3],val[i].counter);
        i++;
    }
    fclose(fp);

}

int main(){
    struct ipsubnet sub[100],*subp;
    int ips[100][4];
    int (*ip)[4]=ips;
    subp = sub;
    IPstat ipcomp;
    ipcomp.getIP(ip);
    ipcomp.getSubnet(subp);

    ipcomp.match(ip,subp);
    ipcomp.output(subp);
    return 0;
}
