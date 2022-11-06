#include<cstdio>
#include<iostream>
#include<cstdlib>
using namespace std;
struct LinkNode{
	int data[4];
	LinkNode* NextLink;
	LinkNode* Before;
};
LinkNode* GenerateList(){
	LinkNode* ListHead=new LinkNode;
	LinkNode* TempLink1=new LinkNode;
	for(int num1=1;num1<=6;num1++){
		for(int num2=1;num2<=6;num2++){
			for(int num3=1;num3<=6;num3++){
				for(int num4=1;num4<=6;num4++){
					if(num1==1&&num2==1&&num3==1&&num4==1){
						LinkNode* Link=new LinkNode;
						Link->data[0]=num1;
						Link->data[1]=num2;
						Link->data[2]=num3;
						Link->data[3]=num4;
						ListHead=Link;
						TempLink1=Link;
						TempLink1->Before=NULL;
						TempLink1->NextLink=NULL;
					}/*else if(num1==6&&num2==6&&num3==6&&num4==6){
						LinkNode* Link=new LinkNode;
						Link->data[0]=num1;
						Link->data[1]=num2;
						Link->data[2]=num3;
						Link->data[3]=num4;
						TempLink1->NextLink=Link;
						Link->Before=TempLink1;
						TempLink1=TempLink1->NextLink;
						TempLink1->NextLink=NULL;
					}*/else{
						LinkNode* Link=new LinkNode;
						Link->data[0]=num1;
						Link->data[1]=num2;
						Link->data[2]=num3;
						Link->data[3]=num4;
						TempLink1->NextLink=Link;
						Link->Before=TempLink1;
						TempLink1=TempLink1->NextLink;
						TempLink1->NextLink=NULL;						
					}
					
					//如果是头部，那么不要让前面有东西 
				}
			}
		}
	}
	free((void*)TempLink1);
	return ListHead;
}
void Print(LinkNode* Head){
	LinkNode* Temp=new LinkNode;
	Temp=Head;
	//int j=0;
	cout<<"适应的配方有:"<<endl;
	while(Temp!=NULL){
	for(int i=0;i<4;i++){
		printf("%d",Temp->data[i]);
	}
	    printf("\n");
    	Temp=Temp->NextLink; 
    	//j++;
    }
    //printf("节点总数目：%d\n",j);
    free((void*)Temp);
}
LinkNode* Compare(LinkNode* Head,int CompareArray[4],int GlowStone,int RedStone){
    int TrueGlowStone=0;
    int TrueRedStone=0;
    int Compare1[4];
    int Compare2[4];
    LinkNode* CompareTempLink=new LinkNode;
    CompareTempLink=Head;
    /*对于每一个位置，如果尝试的配方与正确配方在该位置上有相同的物品，累加1份荧石粉，并将这两个物品标记为已配对。
	如果使用了Glowstone Accelerator，每次尝试会有一个触发了此判定的Reagent不被消耗。
    对于尝试配方（正确配方）中的每一个没有被标记为已配对的物品，如果正确配方（尝试配方）中有相同且没有被标记为已配对的物品，累加1份红石粉，
    并将这两个物品标记为已配对。如果使用了Redstone Accelerator，每次尝试会有一个触发了此判定的Reagent不被消耗。
    获得灰烬数量=4-（获得荧石粉数量+获得红石粉数量）。*/ 
	while(CompareTempLink!=NULL){
		TrueGlowStone=0;
		TrueRedStone=0;
		//先单独把两个要比较的数组拿出来，不能破坏链表里的内容，需要新开2个数组来比较，但是有点废内存了 
	    for(int i=0;i<4;i++){
	    	Compare1[i]=CompareArray[i];
	    	Compare2[i]=CompareTempLink->data[i];
		}
		//先去求萤石粉的数量 
		for(int i=0;i<4;i++){
			if(Compare1[i]==Compare2[i]){
				TrueGlowStone++;
				Compare1[i]=-1;
				Compare2[i]=-1;
			}
		}
		//再去求红石粉数量
		for(int i=0;i<4;i++){
			if(Compare1[i]==-1){
				continue;
			}
			for(int j=0;j<4;j++){
				if(Compare2[j]==-1){
					continue;
				}
				if(Compare1[i]==Compare2[j]){
					TrueRedStone++;
					Compare2[j]=-1;
					Compare1[i]=-1;
					/*比如5111和1555比较，红石应该是2个,5和后面第2个5,1和后面第一个1*/
				}
			}
		} 
		//printf("萤石数目：%d 红石数目：%d\n",TrueGlowStone,TrueRedStone); 
		
		if(TrueRedStone==RedStone&&TrueGlowStone==GlowStone){
			CompareTempLink=CompareTempLink->NextLink;
			//continue;
		}else{
			if(CompareTempLink->Before==NULL){
				Head=CompareTempLink->NextLink;
				LinkNode* freeNode=new LinkNode;
				freeNode=CompareTempLink;
				CompareTempLink=CompareTempLink->NextLink;
				CompareTempLink->Before=NULL;
				free(freeNode);
			}else if(CompareTempLink->Before!=NULL){
				CompareTempLink->Before->NextLink=CompareTempLink->NextLink;
				LinkNode* freeNode=new LinkNode;
				freeNode=CompareTempLink;
				if(CompareTempLink->NextLink!=NULL){
					CompareTempLink->NextLink->Before=CompareTempLink->Before;				
				}
				CompareTempLink=CompareTempLink->NextLink;
				free(freeNode);
			}
		}

	}
	return Head;
}
int main(){
	//GenerateLinkList
    //Print(Head);
    int CompareArray[4];
    int GlowStone;
    int RedStone;
    //读入物料和萤石和红石 
    while(true){
		cout<<"输入1启动计算程序，输入0退出计算程序"<<endl;
    	int judge=0;
    	scanf("%d",&judge);
    	if(judge==0){
    		break;
		}else if(judge==1){
		    LinkNode* Head=new LinkNode;
	        Head=GenerateList();
            while(Head->NextLink!=NULL){
    	    cout<<"请按照物料顺序，获取的萤石，获取的红石数目输入！"<<endl;
            for(int i=0;i<4;i++){
               scanf("%1d",&CompareArray[i]);
	        }
	        scanf("%1d",&GlowStone);
	        scanf("%1d",&RedStone);	
	        Head=Compare(Head,CompareArray,GlowStone,RedStone);
	        Print(Head);   	
            }
            cout<<"只有一种可能，运算结束"<<endl; 
            free(Head);
		}    	
	}
	return 0;
}
