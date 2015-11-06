#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
	printf("\033c");
	printf("%s\n","Welcome to GPS data organizer by HMKRL.");
	int group;
	char prename[25],postname[26],*prenamep,*postnamep,id[10],*idp;
	FILE *inputfp,*youfp,*prefp,*postfp,*minfp;
	prenamep = &prename[0];
	postnamep = &postname[0];
	idp = &id[0];
	if (argc != 2)
	{
		printf("\n%s%s%s\n\n","usage:",argv[0]," (input file name)");
		exit(1);
	}
	else if((inputfp = fopen(argv[1],"r")) == NULL)
	{
		printf("\n%s\n\n","ERROR:input file not found");
		exit(1);
	}
	youfp = fopen("you.txt","r");
	minfp = fopen("min.txt","r");
	if(youfp == NULL)
	{
		printf("\n%s\n\n","ERROR:you.txt not found.");
		exit(1);
	}
	if(minfp == NULL)
	{
		printf("\n%s\n\n","ERROR:min.txt not found.");
		exit(1);
	}
	int date;
	printf("\n%s\n","Please input the date,format:mmdd");
	scanf("%d",&date);
	fscanf(youfp,"%d%s",&group,idp);
	sprintf(prenamep,"%02d_%9s_%04dpre.txt",group,idp,date);
	sprintf(postnamep,"%02d_%9s_%04dpost.txt",group,idp,date);
	prefp = fopen(prenamep,"w");
	postfp = fopen(postname,"w");
	
	char buffer[60],*bufferp = &buffer[0],nowh[3],nowm[3];
	int hour,min,hnow,mnow,hp = -1,mp = -1;
	while (fgets(bufferp,60,inputfp) != NULL)
	{
		fputs(bufferp,prefp);
	}
	fclose(prefp);
	fseek(inputfp,0,SEEK_SET);
	while(fgets(bufferp,60,inputfp) != NULL)
	{
		if(buffer[0] == 'D')
			continue;
		nowh[0] = buffer[41];
		nowh[1] = buffer[42];
		nowh[2] = '\0';
		nowm[0] = buffer[44];
		nowm[1] = buffer[45];
		nowm[2] = '\0';
		hnow = atoi(nowh);
		mnow = atoi(nowm);
		if(hnow == hp && mnow == mp)
			continue;
			buffer[41] = '\0';
		while(fscanf(minfp,"%d:%d",&hour,&min) != EOF && (hour != hnow || min != mnow))
		{
			fprintf(postfp,"%s%02d:%02d:00,0 fill\r\n",bufferp,hour,min);
		}
		fprintf(postfp,"%s%02d:%02d:00,0 get\r\n",bufferp,hour,min);
		hp = hnow;
		mp = mnow;
	}
	while(fscanf(minfp,"%d:%d",&hour,&min) != EOF)
	{
		fprintf(postfp,"%s%02d:%02d:00,0 fill\r\n",bufferp,hour,min);
	}
	printf("\n%s\n%s\n%s\n\n","Done!thanks for using this program","and welcome to our website","http://hmkrl.ddns.net/html");
	fclose(postfp);
	fclose(minfp);
	fclose(youfp);
	fclose(inputfp);

	return 0;
}
