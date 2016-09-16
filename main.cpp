#include<iostream>
#include"stdio.h"
#include"conio.h"
#include"math.h"

using namespace std;

void writetocsv();                             //Function to write output to .csv file
int generate(int,int);                         //checks constraints

float shortest(float a,float b)                //function to find minimum in floyds algorithm
{
    return a<b?a:b;
}



int visited[5000],a,n=601,stop=0,totaldemand=0,ind[600];                  //Global declarations
int truckcount=0,pweight=1000,demands[1000],maxim;
static float dmat[5000][5000];
int DC=601,flag=0,x,y,skip[5000],skipall;
double ckm=0,minimum,overallkm=0,cost;
static string towrite[50][50];

int main()
{
int i,j,k,r,s,f,temp;                                              // local declarations


char str [80];

 int c=1;
  float fread;
  static float array[500000];

  FILE * pFile,*sFile;

  string stores[1000];


  int fin;


  sFile = fopen ("demand.txt","r");               //reading stores demands from file


  for(i=1;i<=600;i++)

 {

  fscanf (sFile, "%s %d",str,&fin);
demands[i]=fin;
stores[i]=str;

}


  fclose (sFile);


  pFile = fopen ("datatab.txt","r");              // reading distance matrix from file


  for(i=1;i<=601*601;i++)

 {

  fscanf (pFile, "%f", &fread);
array[i]=fread;


}


  fclose (pFile);
for(i=1;i<=601;i++)
  {for(j=1;j<=601;j++)
  {
      if(i==j)
  {
      dmat[i][j]=999;
      c++;
  }else
  {
      dmat[i][j]=array[c];
      c++;
  }

  }
  }

cout<<endl<<"Loading Tables and Computing Output..."<<endl;
cout<<"Please Wait..";

for(k=1;k<=n;k++)                                                  // applying Floyds algorithm (All Pairs Shortest Path)
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
{
if(i==j)
{
    dmat[i][j]=999;
}
else
 {dmat[i][j]=shortest(dmat[i][j],dmat[i][k]+dmat[k][j]);

}}



for(a=601;a>0;a--)
{
	truckcount++;

cout<<endl<<endl<<"Routing of Truck "<<truckcount<<endl;
cout<<"DC";
visited[DC]=1;
i=n;
ckm=0;
pweight=1000;
flag=0;stop=0;totaldemand=0;

for(f=1;f<=n;f++)
{

if(stop<20&&ckm<65)                                 //checking  maximum 20 stops and 65 km constraint
{
	minimum=999;maxim=0,temp=1;
for(j=1;j<n;j++)
{
if(dmat[i][j]<minimum&&visited[j]==0&&skip[j]==0)    //Finding next nearest store
	{
	minimum=dmat[i][j];
	//maxim=demands[j];
	x=i;
	y=j;
	}
}

if(generate(x,y))                                 //function to check the given constraints
{
	cout<<"-->"<<stores[y];
	cout<<"("<<dmat[x][y]<<")";
	visited[y]=1;skip[y]=1;
	i=y;totaldemand+=demands[y];
	towrite[truckcount][stop]=stores[y];
}
else
{
	skip[y]=1;

}
for(k=1;k<n;k++)
if(skip[k]==0)
{skipall=1;
 break;}

if(skipall==0)
break;

}
}
ckm=ckm+dmat[i][DC];
overallkm+=ckm;
cout<<"-->DC"<<endl;
cout<<"Totalcapacity= "<<totaldemand<<endl;
cout<<endl<<"KM travelled:"<<ckm<<endl<<endl;

for(r=1;r<=n;r++)
skip[r]=0;

for(s=1;s<n;s++)
{
if(visited[s]==0)
{flag=1;
break;}}

if(flag==0)break;

}

cost=((overallkm*30*365*3)+(20000*31*12*3));

cout<<endl<<"* Total number of trucks: "<<truckcount<<endl;
cout<<endl<<"* Total KM= "<<overallkm<<"  (Miles:"<<overallkm*5/8<<")"<<endl;
cout.precision(8);
cout<<endl<<"* Total cost for 3 years : "<<cost<<endl;
cout<<endl<<"Writing Output to CSV file..";
writetocsv();
cout<<endl<<endl<<"Writing Complete."<<endl<<endl;
//getch();
return 0;
}


int generate(int i,int j)
{
if(demands[j]<=pweight)                              //checking Truck capacity less than or equal to 1000
{

if(ckm+minimum<65-dmat[j][DC])                       //checking km<= 65
{
	stop++;
if((stop*5+(ckm+minimum)*1.5)<=(180-1.5*dmat[j][DC]))   //checking time constraint. less than 3hrs
 {      ckm=ckm+minimum;
	pweight=pweight-demands[j];
	return 1;
}
else    {
	stop--;
	return 0;
	}
}
else return 0;
}




	return 0;
}


void writetocsv()                    //Function to write trucks routing to CSV file
{
    int i,j;
    const char *str;
     FILE * csvFile;

    csvFile = fopen("Truckroute.csv","w");

    for(i=1;i<=truckcount;i++)
    fprintf(csvFile,"TRUCK %d,",i);
    fprintf(csvFile,"\n");
for(i=1;i<=20;i++)
{for(j=1;j<=truckcount;j++)
{
    str=towrite[j][i].c_str();
   fprintf (csvFile, "%s,",str);
}
   fprintf(csvFile,"\n");
}
   fclose (csvFile);
}



