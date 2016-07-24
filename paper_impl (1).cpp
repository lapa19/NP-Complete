#include<bits/stdc++.h>
#include<stack>
using namespace std;
int p[100],mat[100][100];
int edgeExists(int u,int v,int ind[])
{
    /*if((ind[u]>ind[v] && u<v) or (ind[u]<ind[v] && u>v))
    {
        return 1;
    }
    return 0;*/
    if(mat[u][v]==1)
        return 1;
    return 0;
}
int fmin(int visited[],int vnow,int arr[],int pind[],int ind[],int n)
{
    int i,flag=0;

    /*for(i=ind[vnow]-1; i>=1; i--)
    {
        if(visited[arr[i]] == 0 && edgeExists(vnow,arr[i],pind))
        {

            flag=1;
            return arr[i];

        }
    }
    if(flag==0)
    {
        for(i=ind[vnow]+1; i<=n; i++)
        {
            if(visited[arr[i]]==0 && edgeExists(vnow,arr[i],pind))
            {
                return arr[i];

            }
        }
    }*/
    /*int j;
    for(i=ind[vnow]-1,j=ind[vnow]+1;(i>=1 or j<=n);)
    {
       if(i>=1 && visited[arr[i]] == 0 && edgeExists(vnow,arr[i],pind))
           {
            return arr[i];

           }
       i--;
        if(j<=n && visited[arr[j]] == 0 && edgeExists(vnow,arr[j],pind))
          {
             return arr[j];

          }
       j++;
    }*/
    int ver=100000;
    for(i=1;i<=n;i++)
    {
       if(mat[vnow][i]==1 && visited[i]==0)
         {   //cout<<vnow<<" "<<i<<"\n";
             //cout<<"YES\n";
             ver=min(ver,i);
         }
    }
    //cout<<"ver = "<<ver<<'\n';
    return ver;
}
int* ModifiedDFS(int v,int n,int per[],int *k,int ind[])
{

    stack<int>s;
    *k=0;
    int pinv[n+1],line,vnow,vnext,ind2[n+1];

    int normal[n+1];
    int i,visited[n+1];
    for(i=1; i<=n; i++)
    {
        normal[i]=i;
        ind2[i]=i;
    }

    for(i=1; i<=n; i++)
    {
        visited[i]=0;
        pinv[i]=ind[ind[i]];
    }


    if(v==1)
    {
        line=1;
        vnow=1;
    }
    else
    {
        line=0;
        vnow=per[1];
    }
    visited[vnow]=1;

    s.push(vnow);

    p[*k]=vnow;
    int f;

    while(1)
    {
        f=0;
        for(i=1; i<=n; i++)
        {
            if(visited[i]==0)
            {
                f=1;
            }
        }
        if(f==0)
            break;
        if(line==0)
        {
            vnext=fmin(visited,vnow,normal,ind,ind2,n);

        }
        else
        {
            vnext=fmin(visited,vnow,per,ind,ind,n);

        }
        if(vnext==100000)
        {
            s.pop();
            vnow=s.top();
            *k=(*k)-1;
        }
        else
        {
            visited[vnext]=1;
            s.push(vnext);
            *k=(*k)+1;
            p[*k]=vnext;
            vnow=vnext;
        }

        line=(1+line)%2;
    }
    return p;
}
void bfs(int i,int n,int dist[],int ind[],int per[])
{
    int index,j;
    dist[i]=0;
    queue<int>q;
    int visited[n+1];
    for(j=0; j<=n; j++)
        visited[j]=0;

    q.push(i);
    visited[i]=1;
    while(!q.empty())
    {
        int i=q.front();

        q.pop();
        index=ind[i];
        for(j=1; j<=n; j++)
        {
            if(visited[per[j]]==0 && ((per[j]<i && ind[per[j]]>ind[i]) || (per[j]>i && ind[per[j]]<ind[i])))
            {
                dist[per[j]]=dist[i]+1;
                visited[per[j]]=1;
                q.push(per[j]);
            }
        }
    }
}
int main()
{
    int per[]= {-1,3,4,1,5,7,6,2};

    int n=7;

    int ind[n+1],i,j;
    int k,*p,*p1,*p2;
    int l,ll,v1,dist[n+1],maxlen=-1;
    for(i=1;i<=n;i++)
       {
         for(j=1;j<i;j++)
           {
             if(per[j]>per[i])
              {
                mat[per[i]][per[j]]=1;
                mat[per[j]][per[i]]=1;
              }
           }
       }

    for(i=1; i<=n; i++)
    {
        ind[per[i]]=i;
    }

    p1=ModifiedDFS(1,n,per,&k,ind);
    for(i=k; i>=0; i--)
        cout<<p1[i]<<" ";
    maxlen=max(maxlen,k+1);
        cout<<'\n';
    p2=ModifiedDFS(per[1],n,per,&k,ind);
    maxlen=max(maxlen,k+1);
    for(i=k; i>=0; i--)
        cout<<p2[i]<<" ";
    cout<<'\n';
    cout<<"Length of longest path :"<<maxlen<<'\n';

}
