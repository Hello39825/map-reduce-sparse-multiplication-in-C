#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define size1 100//taking input for Dpart where the element stored row wise
#define size2 100//size of key value pair string;
#define sizenum 10 // size of integer for string conversion .
#define max_size 1000//size for the no of mapped string.
#define matsize 50 // matrix will be 50 x 50
struct term
{
    int row;
    int col;
    int val;

};

struct Matrix
{
    int **M;
    int r;
    int c;
};

typedef struct Matrix Matrix;
int COL;
int ROW;




void create_mat( Matrix *Mat)
{
    printf("Enter the no of row and column: ");
    scanf("%d%d",&Mat->r,&Mat->c);

    Mat->M = malloc(sizeof(int *)*(Mat->r));

    int i;
    for(i=0;i<Mat->r;i++)
    {
        Mat->M[i]=malloc(sizeof(int)*Mat->c);
    }
}

void GetMat( Matrix *Mat)
{
    int i,j;
    printf("Enter the input in normal matrix form\n");
    for(i=0;i<Mat->r;i++)
    {
        for(j=0;j<Mat->c;j++)
            scanf("%d",&Mat->M[i][j]);

    }
}

void addstr(char str1[],char str2[])
{
    int i,j;
    i=strlen(str1);
    for(j=0;j<=strlen(str2);j++)
        str1[i++]=str2[j];
}

FILE *D;

void combine(Matrix A,Matrix B)
{
    ROW=A.r;
    COL=B.c;
    if(A.c!=B.r)
    {
        printf("multiplication not possible");
        exit(0);
    }
    int i,j;
     FILE *fp;
   fp= fopen("file1.txt","w");

   for(i=0;i<A.r;i++)
    {
        char str1[100];
        char str2[100];
        str1[0]='\0';
        str2[0]='\0';
        char line[100];
        line[0]='\0';

        addstr(str1,"A,");
        char num[5];
        itoa(i,num,10);
        addstr(str1,num);
        addstr(str1,",");


        for(j=0;j<A.c;j++)
        {
            if(A.M[i][j]==0)
                continue;
            else
            {
                char nt[5],np[5];
                itoa(j,nt,10);
                addstr(str1,nt);
                itoa(A.M[i][j],np,10);
                addstr(str2,np);
                if(j!=A.c-1)
                {
                    addstr(str2,",");
                    addstr(str1,",");
                }


            }

        }

       addstr(line,str1);
       addstr(line,"\t");
       addstr(line,str2);

       fprintf(fp,"%s\n",line);


    }
    fclose(fp);


//  for matrix b
fp= fopen("file2.txt","w");


    for(i=0;i<B.r;i++)
    {
        char str1[100];
        char str2[100];
        str1[0]='\0';
        str2[0]='\0';
        char line[100];
        line[0]='\0';

        addstr(str1,"B,");
        char num[5];
        itoa(i,num,10);
        addstr(str1,num);
        addstr(str1,",");


        for(j=0;j<B.c;j++)
        {
            if(B.M[i][j]==0)
                continue;
            else
            {
                char nt[5],np[5];
                itoa(j,nt,10);
                addstr(str1,nt);
                itoa(B.M[i][j],np,10);
                addstr(str2,np);
                if(j!=B.c-1)
                {
                   addstr(str2,",");
                   addstr(str1,",") ;
                }


            }

        }

       addstr(line,str1);
       addstr(line,"\t");
       addstr(line,str2);

       fprintf(fp,"%s\n",line);


    }

    fclose(fp);

//    joining the files


    D=fopen("D.txt","w");

    char ch;
    fp=fopen("file1.txt","r+");
    while((ch=getc(fp))!=EOF)
    {
        fprintf(D,"%c",ch);

    }

    FILE *ff;
   ff=fopen("file2.txt","r+");
    while((ch=getc(ff))!=EOF)
    {
        fprintf(D,"%c",ch);

    }

    fclose(D);
    fclose(fp);
    fclose(ff);


}
char** split_string(char* text, char delim) {

    char** result = malloc(1*sizeof(char*));
    int size = 1;

    char* temp = strtok(text, &delim);
    *result = temp;

    while(temp != NULL) {
        size++;
        result = realloc(result,size*sizeof(char*));
        temp = strtok(NULL, &delim);
        result[size-1] = temp;
    }

    return result;
}

void map()
{

    int n=0;
    char ch;
    FILE *fp;
    fp=fopen("D.txt","r");
    FILE *ff;
    ff=fopen("Dpart.txt","w");

    while((ch=getc(fp))!=EOF)
    {
        if(ch=='\n')
            n++;
    }
    fclose(fp);
    fp=fopen("D.txt","r");
    int i;
    for(i=0;i<n;i++)
    {
        char line[size1];
        int j=0;
        while(((ch=getc(fp))!='\n'))
            line[j++]=ch;
        line[j]='\0';
        char **str;
        str=split_string(line,'\t');
        char **str1;
        char **str2;
        str1=split_string(str[0],',');
        str2=split_string(str[1],',');


        if(strcmp(str1[0],"A")==0)
        {
           int m,n;

           for(m=0;m<COL;m++)
           {



               for(n=0;str2[n]!=NULL;n++)
               {
                    char key[size2];
                    char value[size2];
                    key[0]='\0';
                    value[0]='\0';

                   addstr(key,str1[1]);
                   addstr(key,",");
                   char conv[sizenum];
                   itoa(m,conv,10);
                   addstr(key,conv);

                   addstr(value,"A");
                   addstr(value,",");
                   addstr(value,str1[n+2]);
                   addstr(value,",");
                   addstr(value,str2[n]);
                   fprintf(ff,"%s\t%s\n",key,value);


               }

           }

        }

        if(strcmp(str1[0],"B")==0)
        {
           int o,p;

           for(o=0;o<ROW;o++)
           {



               for(p=0;str2[p]!=NULL;p++)
               {
                    char key[size2];
                    char value[size2];
                    key[0]='\0';
                    value[0]='\0';
                    char conv[sizenum];

                   itoa(o,conv,10);
                   addstr(key,conv);
                   addstr(key,",");
                   addstr(key,str1[p+2]);
                   addstr(value,"B");
                   addstr(value,",");
                   addstr(value,str1[1]);
                   addstr(value,",");
                   addstr(value,str2[p]);
                   fprintf(ff,"%s\t%s\n",key,value);


               }

           }

        }

    }
    fprintf(ff,"END");
    fclose(ff);


}



void reduce()
{

    FILE *fp,*ff;
    fp=fopen("Dpart.txt","r");

    char list[size1];
    fgets(list,size1,fp);
    char *item[max_size];
    int i=0;
    while(strcmp(list,"END"))
    {
        item[i]=malloc(sizeof(char)*(strlen(list)+1));
        strcpy(item[i++],list);
        fgets(list,size1,fp);


    }
    fclose(fp);
    item[i]=NULL;
    fp=fopen("Dpart.txt","w");

    i=0;
    while(item[i]!=NULL)
    {
        i++;
    }
    int lenght=i;
    int j;
    for(i=0;i<lenght-1;i++)
    {
        for(j=1+i;j<lenght;j++)
        {
            if(strncmp(item[i],item[j],6)>0)
            {
                char temp[size1];
                strcpy(temp,item[i]);
                strcpy(item[i],item[j]);
                strcpy(item[j],temp);
            }
        }
    }
    i=0;
    while(item[i]!=NULL)
    {
        fprintf(fp,"%s",item[i]);
        i++;
    }
    fprintf(fp,"END");
    fclose(fp);
    char line[size1];
    fp=fopen("Dpart.txt","r");
    fp=fopen("Dpart.txt","r");
    ff=fopen("result.txt","w");
    int flag=0;
    char check[size1];
    char **pair;
    char **value;
    fgets(line,size1,fp);
    while(strcmp(line,"END"))
    {
        int arr1[matsize]={0};
        int arr2[matsize]={0};

        pair=split_string(line,'\t');
        strcpy(check,pair[0]);
        do
        {
            char line1[size1];
            char **value1;
            flag=0;
            value=split_string(pair[1],',');

            if(strcmp(value[0],"A")==0)
                arr1[atoi(value[1])]=atoi(value[2]);
            else if(strcmp(value[0],"B")==0)
                arr2[atoi(value[1])]=atoi(value[2]);
            fgets(line,30,fp);

            strcpy(line1,line);
            value1=split_string(line1,'\t');


            if(strcmp(check,value1[0])==0)
                flag=1;




        }while(flag&&(strcmp(line,"END")));










    if(!flag)
        {
            int xx,result=0,aij,bjk;
            for(xx=0;xx<COL;xx++)
            {
                aij=(arr1[xx]!=0)?arr1[xx]:0;
                bjk=(arr2[xx]!=0)?arr2[xx]:0;
                result=result+aij*bjk;

            }
            if(result)
            fprintf(ff,"%s,%d\n",check,result);
        }

    }
    fprintf(ff,"END");

    fclose(ff);
    fclose(fp);

}



void filetosparse(struct term sparse[])
{

    sparse[0].row=ROW;
    sparse[0].col=COL;
    FILE *fp;
    int i=1;
    char line[size1];
    char **pair;
    fp=fopen("result.txt","r");
    fgets(line,size1,fp);
    while(strcasecmp(line,"END"))
    {
        pair=split_string(line,',');
        sparse[i].row=atoi(pair[0]);
        sparse[i].col=atoi(pair[1]);
        sparse[i].val=atoi(pair[2]);
        i++;


        fgets(line,size1,fp);
    }
    sparse[0].val=i-1;
    printf("Your result is \n row col value:\n");

fclose(fp);
}



void disp(struct term sparse[])
{   printf("\n\n output in normal form \n");
    int i,j,k=1;
    for(i=0;i<sparse[0].row;i++)
    {
        for(j=0;j<+sparse[0].col;j++)
        {
            if(sparse[k].row==i&&sparse[k].col==j)
            {
                printf("%4d  ",sparse[k].val);
                k++;
            }
            else
                printf("   0");

        }
        printf("\n\n");
    }
}




void spdisp(struct term sparse[])
{
    int i,j;
    printf("\n\nrow col val");
    for(i=0;i<=sparse[0].val;i++)
    {
        printf("\n%3d %3d %3d",sparse[i].row,sparse[i].col,sparse[i].val);
        if(i==0)
            printf("\n");

    }

}

int main()
{

    Matrix Mat1,Mat2;
    struct term sparse[1000];
    printf("Matrix 1\n");
    create_mat(&Mat1);
    GetMat(&Mat1);
    printf("Matrix 2\n");
    create_mat(&Mat2);
    GetMat(&Mat2);
    combine(Mat1,Mat2);


    map();
    reduce();
    filetosparse(sparse);
    spdisp(sparse);
    disp(sparse);



}

