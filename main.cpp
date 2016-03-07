//  ����ƥ���㷨 
//  �����ʽΪ����һ��Ϊ������N��֮��ÿ�����������ָ�ʽ 
//      M x MΪ�ַ���M��,xΪһ������ʾMalloc ��СΪx�Ŀռ䡣 
//      F p x FΪ�ַ�"F"��ʾ��P��XΪһ��������ʾ�ͷ�Mem[P~P+X]�Ĵ�СΪX�Ŀռ䡣 
//  ÿ��������еĿռ��  
#include <iostream> 
#include <cstdio> 
#include <list> 
using namespace std; 
 
const int TOTAL_MEM=200; 
 
unsigned char Mem[TOTAL_MEM];//�ڴ�� 
  
struct MemBlock{//�ڴ��,start��end�ֱ��ʾ�������ڴ���е��±����䣬����ҿ��� 
    int start,end;                      
    MemBlock(int a=0,int b=0):start(a),end(b){} 
};  
list<MemBlock> freeList;//�����ڴ����� 
  
unsigned char* memMalloc(int size)//�����ڴ棬������뵽�򷵻��ڴ��ͷָ�롣ʧ���򷵻��㡣 
{ 
    list<MemBlock>::iterator itr=freeList.begin(); 
    for(itr;itr!=freeList.end();itr++){//������������ 
        if ((*itr).end-(*itr).start >= size){//�ɹ��ҵ���һ����ʵĿռ䡣 
            unsigned char* header = Mem+(*itr).start;//��¼�ҵ���ͷָ�롣 
            (*itr).start += size;//�޸Ŀ����ڴ��������Ϣ 
            if( (*itr).end == (*itr).start){//�����÷����꣬ɾ������������䡣 
                freeList.erase(itr); 
            } 
            return header;//����ָ�롣 
        } 
    } 
    return 0;//ʧ�ܣ�����0; 
}
 
void memFree(unsigned char *header,int size){//�ͷŴ�*P ��ʼ��һ���ڴ� 
    list<MemBlock>::iterator itr=freeList.begin(); 
	int start=header-Mem; 
    for(itr;itr!=freeList.end();itr++) 
		if ((*itr).start>=start){//Ѱ�Ҳ���λ�� 
        if (start+size<(*itr).start) 
            freeList.insert(itr, MemBlock(start,size));//�����ڴ�ε��б��б� 
        else (*itr).start=start;//���ϲ������ڴ�� 
        break; 
    }      
} 

void output(){//���ʣ��ռ� 
    static int step=0; 
    printf("step %d\n",step); 
    list<MemBlock>::iterator itr=freeList.begin(); 
    for(itr;itr!=freeList.end();itr++){
        if((*itr).start<TOTAL_MEM) printf("[%d,%d)\n",(*itr).start,(*itr).end); 
    } 
    step++; 
} 

int main(int argc, const char * argv[]) { 
    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout); 
    freeList.push_back(MemBlock(0,TOTAL_MEM));
    freeList.push_back(MemBlock(TOTAL_MEM+1,TOTAL_MEM+1)); 
    int N; 
    scanf("%d\n",&N); 
    for (int i=0;i<N;i++){ 
        char ch; 
        scanf("%c",&ch); 
        if (ch=='M'){ 
            int x;scanf("%d\n",&x); 
            unsigned char *P=memMalloc(x); 
            output(); 
        }else{ 
            int x,y; 
            scanf("%d%d\n",&x,&y); 
            memFree(Mem+x,y); 
            output(); 
    	} 
	} 
	return 0; 
} 

