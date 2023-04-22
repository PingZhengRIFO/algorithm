#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <math.h>
using namespace std;
#define N 10
#define INFINITE 999999999
#define MYTYPE double

struct _point
{
int x;
int y;
} point[N];

struct _edge
{
int from;
int to;
MYTYPE cost;
} edge[N*N];

MYTYPE inw[N]; //最小入边
int vis[N]; //是否被访问
int idx[N]; //由当前图到重构图的映射
int pre[N]; //前驱顶点
MYTYPE Directed_MST(int root, int NV, int NE)
{
    MYTYPE ret=0;

    while (1) //开始迭代过程
    {
    //1.确定最小入边集
    for(int i=0; i<NV; ++i) inw[i]=INFINITE;
    for (int i=0; i<NE; ++i)
    {
        int from=edge[i].from;
        int to=edge[i].to;
        if (from != to && edge[i].cost < inw[to]) //from!=to忽略自环
        {
            inw[to]=edge[i].cost;
            pre[to]=from;
        }
    }
    //检查是否有不可达点
    for (int i=0; i<NV; ++i)
    {
        if(i==root) continue; //除根之外
        if(inw[i]==INFINITE) return -1; //有不可达顶点，不可能生成最小树形图，退出
    }

    //2.找环
    for (int i=0; i<NV; ++i)
    {
        vis[i]=-1;
        idx[i]=-1;
    }

    int newidx=0;
    inw[root]=0;
    for (int i=0; i<NV; ++i) //有两个作用：计算最小入边集的权值和；检查是否有环，如果有，重新对点进行编号
    {
        ret+=inw[i];
        int v=i;
        while (vis[v]!=i && idx[v]==-1 && v!=root) 
        //由v回溯。能回到根，即最后v==root，那么肯定不在环里；回不到根，v!=root，v有可能在环里，也有可能不在（回溯到一个环然后出不去了，同样也到不了根）。
        //若v在环里，则环上所有点的id[]值会被重新标号，不再是-1；若是后一种情况，它前驱的环上的点的id[]已被修改为非-1，不能通过“id[v]==-1”这个条件的检查。
        {
            vis[v] = i;
            v = pre[v];
        }
        if (v!=root && idx[v]==-1) //两个条件保证了：1.在环上2.这环没被处理过
        {
        //下面把环上所有的点的标号设置为同一个
            for (int u=pre[v]; u!=v; u=pre[u])
            {
                idx[u]=newidx;
            }
            idx[v]=newidx;
            ++newidx;
        }
    }
    if(newidx==0) break; //无环，ret就是答案，跳出迭代
    for (int i=0; i<NV; ++i)
    {
        if(idx[i]==-1) idx[i]=newidx++; //给环外的点继续编号
    }

    //3.重新构图，准备下一次迭代
    for (int i=0; i<NE; ++i)
    {
        int to=edge[i].to;
        edge[i].from=idx[edge[i].from];
        edge[i].to=idx[edge[i].to];
        if(edge[i].from!=edge[i].to)
        {
             edge[i].cost -= inw[to];
            //放弃最小边（如果放弃是因为它在环里）所需要付出的代价，就是增量。这些增量又构成了一张新图，下一轮迭代处理这张新图。
				/*注意：
				Here's the tricky part！还记得算法本身是怎样做的吗？求出环上每个点若放弃最小入边所产生的增量，形成一个增量集合，选择集合中最小的增量。
				这里把环上的所有点都标成同一个序号，看成一个点，下一次迭代过程的第一步就是求这个“点”入边的最小权值，实际上求的就是环上所有点增量集合的最小值，也就是最小增量！
				*/
        }
    }

    //为下一轮迭代赋初值
    NV=newidx;
    root=idx[root];
    }
    return ret;
}

MYTYPE calcdist(int point_a, int point_b)
{
MYTYPE delta_x=(MYTYPE)(point[point_a].x - point[point_b].x);
MYTYPE delta_y=(MYTYPE)(point[point_a].y - point[point_b].y);
return sqrt(delta_x*delta_x + delta_y*delta_y);
}

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("D:\\out.txt", "w", stdout);

    int n, m, x, y, from, to;
    MYTYPE ans;

    while (scanf("%d", &n) != EOF)
    {
        scanf("%d", &m);

        for (int i=0; i<n; ++i) //n个顶点
        {
        scanf("%d%d", &x, &y);
        point[i].x=x;
        point[i].y=y;
        }

        for (int i=0; i<m; ++i) //m个边
        {
            scanf("%d%d", &from, &to);
            edge[i].from=from-1;
            edge[i].to=to-1;
            edge[i].cost=calcdist(from-1, to-1);
        }

        ans=Directed_MST(0, n, m);

        if (ans==-1) printf("NO\n");
        else printf("%.2f\n", ans);
    }

return 0;
}
