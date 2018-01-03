#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 21
typedef struct st_s *st_t;
typedef struct graph{
    int **madj;
    int nv;
}graph_t;
struct st_s{
    char **v;
    int nmax;
    int n;
};
graph_t *readF(char *fn,st_t *st);
st_t st_init(int maxN);
int st_find_add(st_t t,char *str);
int st_find(st_t t,char *str);
int st_add(st_t t,char *str);
graph_t *graph_init(int nv);
void graph_insert_edge(graph_t *g,int x,int y,int w);
void graph_write(graph_t *g,st_t t);
void regular(graph_t *g);
int main(int argc,char *argv[])
{
    graph_t *g;
    st_t st;
    g=NULL;
    st=NULL;
    if(argc!=2){
        printf("error in CL args.\n");
        exit(0);
    }
    g=readF(argv[1],&st);
    graph_write(g,st);
    regular(g);
    return 0;
}
graph_t *readF(char *fn,st_t *st){
    FILE *fp;
    int w,id1,id2;
    char src[MAXL],dst[MAXL];
    graph_t *g;
    g=NULL;
    *st=st_init(1);
    fp=fopen(fn,"r");
    if(fp==NULL){
        printf("error in file opening.\n");
        exit(0);
    }
    while(fscanf(fp,"%s %d %s",src,&w,dst)==3){
        id1=st_find_add(*st,src);
        id2=st_find_add(*st,dst);
    }
    fclose(fp);
    fp=fopen(fn,"r");
    g=graph_init((*st)->n);
    while(fscanf(fp,"%s %d %s",src,&w,dst)==3){
        id1=st_find(*st,src);
        id2=st_find(*st,dst);
        graph_insert_edge(g,id1,id2,w);
    }
    fclose(fp);
    return g;
}
st_t st_init(int maxN){
    st_t st;
    st=calloc(1,sizeof(* st));
    if(st==NULL){
        printf("error in allocation");
        exit(0);
    }
    st->n=0;
    st->nmax=maxN;
    st->v=(char **)malloc(maxN*sizeof(char *));
    if(st->v==NULL){
        printf("error in allocation");
        exit(0);
    }
    return st;
}
int st_find_add(st_t t,char *str){
    int id;
    id=st_find(t,str);
    if(id==-1){
        return (st_add(t,str));
    }
    return id;
}
int st_find(st_t t,char *str){
    int i;
    for(i=0;i<t->n;i++){
        if(!strcmp(str,t->v[i])){
            return i;
        }
    }
    return -1;
}
int st_add(st_t t,char *str){
    int i=t->n;
    if(t->n==t->nmax){
        t->nmax=2*t->nmax;
        t->v=realloc(t->v,t->nmax*sizeof(char *));
    }
    t->v[i]=strdup(str);
    t->n++;
    return i;
}
graph_t *graph_init(int nv){
    graph_t *g;
    int i;
    g=(graph_t *)malloc(1*sizeof(graph_t));
    g->nv=nv;
    g->madj=(int **)calloc(nv,sizeof(int *));
    for(i=0;i<nv;i++){
        g->madj[i]=(int *)calloc(nv,sizeof(int));
    }
    return g;
}
void graph_insert_edge(graph_t *g,int x,int y,int w){
    g->madj[x][y]=w;
    return;
}
void graph_write(graph_t *g,st_t t){
    int i,j;
    int nv=g->nv;
    printf("Number of vertexes:%d\n",nv);
    for(i=0;i<nv;i++){
        for(j=0;j<nv;j++){
            printf("%d ",g->madj[i][j]);
        }
        printf("\n");
    }
    return;
}
void regular(graph_t *g){
    int i,j,in,out,nv,inf,outf,reg=1;
    in=0;
    out=0;
    nv=g->nv;
    for(i=0;i<nv;i++){
        if((g->madj[0][i])!=0)
            in++;
    }
    for(i=0;i<nv;i++){
        if((g->madj[i][0])!=0)
            out++;
    }
    if(in!=out){
        //printf("Its not a regular graph.\n");
        reg=0;
    }
    for(i=0;i<nv;i++){
        inf=0;
        for(j=0;j<nv;j++){
            if(g->madj[i][j]!=0)
                inf++;
        }
        if(in!=inf){
                reg=0;
        }
    }
    for(i=0;i<nv;i++){
        inf=0;
        for(j=0;j<nv;j++){
            if(g->madj[j][i]!=0)
                outf++;
        }
        if(outf!=out){
                reg=0;
        }
    }
    if(reg==0){
        printf("Its not a regular graph.\n");
    }
    return;

}
