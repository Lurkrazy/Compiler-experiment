
#include"stdio.h"
#include"ctype.h"
#include"string.h"
#define init_size 1000
#define ERROR 0;
#define OK 1;
#define incre_size 10
#define M 50
#define N 80
typedef struct{
	int num;
	char word[20];
}list;
list *list_word,*list_list,*list_p1;
char code[M][N];
int readm=0,readn=0;
int lreadm=0,lreadn=0;
int maxline=0,word_num=0,word_p=0;
init();
readcode();
isoldword(char word[]);
char getch();
getsym();
outlist();
insert_list(int num,char word[]);



main(){
int i,j;
//clrscr();
init();
readcode();
/*
for(i=0;i<maxline;i++)
	for(j=0;j<strlen(code[i]);j++)
		printf("%c",getch());
*/
i=0;
while(getysm());
/*
outlist();
*/
}

init(){
	FILE *fp;
	list *p;
	char *k;
	list_word=(list *)malloc(sizeof(list)*34);
	list_list=(list *)malloc(sizeof(list)*init_size);
	list_p1=list_list;
	p=list_word;
	if(list_word){
		if((fp=fopen("data.txt","r"))==NULL){
			printf("can not open file data.txt");
			return ERROR;
		}
		while(fgets(p->word,20,fp)!=NULL){
			word_num++;
			p->num=word_num;
			k=strchr(p->word,'\n');
			if(k) *k=0;
			p++;
		}
		p--;
		p->num+=2;
		close(fp);
		return OK;


	}
	else{
		printf("memory is pool\n");
		return ERROR;
	}
}
outlist(){
	list *p;
	int i=0;
	FILE *fp;
	p=list_list;
	fp=fopen("out.txt","w+");
	while(i<word_p){
		printf("%d,%s\n",p->num,p->word);
		fprintf(fp,"%d\t%s\n",p->num,p->word);
		p++;
		i++;
	}
	fclose(fp);
	return OK;


}
readcode(){
	FILE *fp;
	int i=0;
	if((fp=fopen("code.txt","r"))==NULL)
		return ERROR;
	while(fgets(code[i],N,fp)!=NULL){
		i++;
	}
	code[i-1][strlen(code[i-1])]='\n';
	maxline=i;
	fclose(fp);
	return OK;

}
char getch(){
	int i,j,tempm;
	i=readm;
	lreadm=i;
	j=readn;
	lreadn=j;
	if(readm<M&&readn<N){
		tempm=strlen(code[readm]);
		if(code[readm][readn]!='\n'){
				lreadm=readm;
				i=readm;
				lreadn=readn++;
				return code[i][j];
		}
		else{
			lreadm=readm;
			readm++;
			lreadn=readn;
			readn=0;
			return ' ';
		}
		return code[i][j];
	}
	else
	return ERROR;

}
getysm(){
	char ch;
	int n;
	int val;
	char str[20];
	ch=getch();

	while(ch==' '&&readm<M){
		ch=getch();
	}
	n=0;
	if(ch=='\x0')
	return 0;
	if(isalpha(ch)){
		while(isalpha(ch)){
			while(n<20&&isalnum(ch)){
			str[n]=ch;
			n++;
			ch=getch();
			}
		str[n]='\0';
		if(ch!=' '){
			readm=lreadm;
			readn=lreadn;
		}
		}
		n=isoldword(str);
		if(n){
			printf("%d\t%s\n",n,str);
			insert_list(n,str);
			return 1;
		}
		else{
			printf("34\t%s\n",str);
			insert_list(34,str);
			return 1;
		}
	}
	else if(isdigit(ch)){
	       val=0;
	       while(isdigit(ch)){
			 str[val]=ch;
			 val++;
			 ch=getch();
	       }
	       str[val]='\0';
	       readm=lreadm;
	       readn=lreadn;
		insert_list(33,str);
		printf("33\t%s\n",str);
	       return 1;

	}
	else if(isdbchar(ch)){
	    str[0]=ch;
	    ch=getch();
	    if(ch=='>'||ch=='='){
		str[1]=ch; str[2]='\0';
		n=isoldword(str);
		if(n==0)
			printf("lines %d error in compiling unknow character %s\n",readm+1,str);
			/*printf("%s,%d\n",str,n); */
		else{
			insert_list(n,str);
			printf("%d\t%s\n",n,str);
		}
		return 1;
	    }
	    else {
		readm=lreadm;
		readn=lreadn;
		str[1]='\0';
		n=isoldword(str);
		if(n==0)
			printf("lines %d error in compiling unknow character %s\n",readm+1,str);
			/*printf("%d,%c\n",n,str[0]);*/
		else{
			insert_list(n,str);
			printf("%d\t%s\n",n,str);
		}
		return 1;
	    }


	}
	else{
		str[0]=ch;
		str[1]='\0';
		n=isoldword(str);
		if(n==0)
			printf("liness %d error in compiling unknow character %s\n",readm+1,str);

		else{
			insert_list(n,str);
			printf("%d\t%s\n",n,str);
		}
		return 1;
	}
	return 0;


}
isoldword(char word[]){
	list *p1;
	int i=1;
	p1=list_word;
	while(i<=word_num){
		if(strcmp(p1->word,word)==0)
		return p1->num;
		p1++;
		i++;

	}
	return 0;

}
isdbchar(char c){
	char array_c[]={'<','>',':','\/'};
	int i;
	for(i=0;i<4;i++){
		if(c==array_c[i])
			break;
	}
	if(i==4)
	return 0;
	else
	return 1;
}
insert_list(int num,char word[]){
	int i;
	list *kk=list_list;
	for(i=0;i<word_p;i++){
	if(strcmp(kk->word,word)==0)
	return 0;
	kk++;
	}
	list_p1->num=num;
	strcpy(list_p1->word,word);
	list_p1++;
	word_p++;
	/*printf("%d,%s",num,word);*/
}