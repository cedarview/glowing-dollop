#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char ch[1000]="iiiii";
	int i=10;
	FILE *fp=NULL;
	struct hello test;
	char hel[55]="haha,who are you?\n";
	fp=fopen("/home/darviw/桌面/hello/test/fopen/darv.txt","a+");
	
    fputs(hel,fp);
    rewind(fp);
	if(fp==NULL)
	{
		printf("wrong");
		exit(1);
	}
	memset(ch,0,sizeof(ch));
	//fgets(ch,255,(FILE*)fp);
	
	fread(ch,55,5,fp);//没有将指针重新指到头，而fread读取了275个字符，所以此次正确，但下次会读到空值	
	//fgets(ch,100,fp);
	//fscanf(fp, "%s", ch);
	printf("string: %s\n", ch);
	memset(ch,0,sizeof(ch));
	
	fgets(ch, 255, (FILE*)fp);//读到空值
   printf("3: %s\n", ch );
   //memset(ch,0,sizeof(ch));
   
   rewind(fp);//指回头部
   //逐行读取
   while(!feof(fp)){
	   fgets(ch, 255, (FILE*)fp);
	   printf("%d: %s\n", i,ch );
	   i++;
   }

	fclose(fp);
	fp=NULL;
	return 0;
}
