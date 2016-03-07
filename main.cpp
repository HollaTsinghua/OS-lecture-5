//  最先匹配算法 
//  输入格式为，第一行为操作数N，之后每行输入有两种格式 
//      M x M为字符“M”,x为一整数表示Malloc 大小为x的空间。 
//      F p x F为字符"F"表示，P和X为一整数，表示释放Mem[P~P+X]的大小为X的空间。 
//  每次输出空闲的空间段  
#include <iostream> 
#include <cstdio> 
#include <list> 
using namespace std; 
 
const int TOTAL_MEM=200; 
 
unsigned char Mem[TOTAL_MEM];//内存池 
  
struct MemBlock{//内存块,start和end分别表示的是在内存池中的下标区间，左闭右开。 
    int start,end;                      
    MemBlock(int a=0,int b=0):start(a),end(b){} 
};  
list<MemBlock> freeList;//空闲内存链表 
  
unsigned char* memMalloc(int size)//申请内存，如果申请到则返回内存的头指针。失败则返回零。 
{ 
    list<MemBlock>::iterator itr=freeList.begin(); 
    for(itr;itr!=freeList.end();itr++){//遍历空闲链表。 
        if ((*itr).end-(*itr).start >= size){//成功找到第一块合适的空间。 
            unsigned char* header = Mem+(*itr).start;//记录找到的头指针。 
            (*itr).start += size;//修改空闲内存的区间信息 
            if( (*itr).end == (*itr).start){//若正好分配完，删除这个空闲区间。 
                freeList.erase(itr); 
            } 
            return header;//返回指针。 
        } 
    } 
    return 0;//失败，返回0; 
}
 
void memFree(unsigned char *header,int size){//释放从*P 开始的一段内存 
    list<MemBlock>::iterator itr=freeList.begin(); 
	int start=header-Mem; 
    for(itr;itr!=freeList.end();itr++) 
		if ((*itr).start>=start){//寻找插入位置 
        if (start+size<(*itr).start) 
            freeList.insert(itr, MemBlock(start,size));//插入内存段到列表列表 
        else (*itr).start=start;//向后合并两个内存段 
        break; 
    }      
} 

void output(){//输出剩余空间 
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

