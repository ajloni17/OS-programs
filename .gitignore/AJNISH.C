#include<stdio.h>

int n=3;int m=3;int i=0;int j;

int Resource_Available[3]={3,2,2};

int Resource_Allocated[][3]={{0,0,1},{3,2,0},{2,1,1}};

int Process_Maximum_Need[][3]={{8,4,3},{6,2,0},{3,3,3}};

int Process_Current_Need[3][3];

int Safety_Sequence[3];

bool Finish[3]={false,false,false};

int *RAv,*RAl,*PMx,*PNd;

void Display_Table();

int Check_Algo(int,int *);

int Request_Algo(int,int *);

int Safety_Algo(int,int *,bool *);

void Calculate_Need();

int Create_Safe_Sequence();

void Display_Safety_Sequence();


int main(){

	printf("This is Banker's algorithm created by Deepanshu Raghuvanshi \n");

	Calculate_Need();

	Display_Table();

	int *R,a[3],p;

	printf("Enter any of the following Process: 0, 1, 2\n");scanf("%d",&p);

	printf("Enter the Requested Resources for the Respective Process as P1,P2 and P3: ");

	scanf("%d",a);scanf("%d",a+1);scanf("%d",a+2);

	R=a;

	printf("For Process P%d checking Request\n",p);

	Check_Algo(p,R);

	Display_Table();}

int Check_Algo(int pid,int *R){

	if(Request_Algo(pid,R)==1)Display_Table();

	else{

		printf("Request Not Satisfied\n");

		return 0;

	}

	printf("Now Checking Safety\n");

	if(Create_Safe_Sequence()!=0)Display_Safety_Sequence();

	else printf("Safe Sequence is not Possible\n");

}

int Request_Algo(int pid,int *R){

	RAv=Resource_Available;

	RAl=Resource_Allocated[pid];

	PNd=Process_Current_Need[pid];

	for(i=0;i<m;i++){

		if(*(R+i)>*(PNd+i))return 0;

		if(*(R+i)>*(RAv+i))return 0;

	}

	printf("Request is possible!\n");

	for(i=0;i<m;i++){

		*(RAl+i)+=*(R+i);

		*(RAv+i)-=*(R+i);

		*(PNd+i)-=*(R+i);

	}

	return 1;

}

bool Safety_Algo(int pid){

	printf("Possible Process to Run: P%d\n",pid);

	RAv=Resource_Available;

	RAl=Resource_Allocated[pid];

	for(i=0;i<3;i++){

		*(RAv+i)+=*(RAl+i);

		*(RAl+i)=0;

		*(PNd+i)=0;

	}

	return true;

}

int Create_Safe_Sequence(){

	int *W=Resource_Available,flag;

	int *Seq=Safety_Sequence,k=0,g=0;

	bool *F=Finish;

	for(i=0;i<10;i++){

		k=i%3;

		if(*(F+k)==true)continue;

		PNd=Process_Current_Need[k];

		flag=1;

		printf("Need:");

		for(j=0;j<3;j++){

			printf(" %d",*(PNd+j));

			if(*(PNd+j)>*(W+j))flag=0;

		}

		printf("\n");

		if(flag==1){

			*(F+k)=Safety_Algo(k);

			*(Seq+(g++))=k;

			Display_Table();		

		}

		else *(F+k)=false;

		if(*(F)&*(F+1)&*(F+2)==true)return 1;

	}

	return 0;

}

void Display_Safety_Sequence(){

	int *Seq=Safety_Sequence,i;

	printf("Safety Sequence:");

	printf("<");for(i=0;i<3;i++)printf("%d,",*(Seq+i));printf(">\n");

}

void Calculate_Need(){

	int pid,i,j;

	for(pid=0;pid<n;pid++){

		PNd=Process_Current_Need[pid];

		RAl=Resource_Allocated[pid];

		PMx=Process_Maximum_Need[pid];

		for(i=0;i<m;i++){

			*(PNd+i)=*(PMx+i)-*(RAl+i);

		}

	}

}

void Display_Table(){

	int i,j;

	printf("\nProcess\tMaximum\t\tAllocated\tNeed\t\tAvailable\n");

  	for(j=0;j<n;j++){

		RAl=Resource_Allocated[j];

		RAv=Resource_Available;

		PMx=Process_Maximum_Need[j];

		PNd=Process_Current_Need[j];

		printf("P%d\t",j);

		for(i=0;i<m;i++){

			printf("%d ",*(PMx+i));}

		printf("\t\t");

		for(i=0;i<m;i++){

			printf("%d ",*(RAl+i));}

		printf("\t\t");

		for(i=0;i<m;i++){

			printf("%d ",*(PNd+i));}

		printf("\t\t");

		printf("R%d: %d ",j,*(RAv+j));

		printf("\n");}

	printf("\n");}
