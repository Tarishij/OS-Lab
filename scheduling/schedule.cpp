#include<bits/stdc++.h>
using namespace std;
struct process{
	int values[7];
};

void fcfs(process proc[],int no){

	int rt[no];
	int wt[no];
	int tat[no];
	int bt[no];
	for(int i=0;i<no;i++){
		bt[proc[i].values[0]-1]=proc[i].values[4]+proc[i].values[6];
	}
	queue<process> q;
	int time=proc[0].values[1];
	for(int i=0;i<no;i++)
	    q.push(proc[i]);
	    
		//response time=waiting time
	    
	for(int i=0;i<no;i++){
		rt[proc[i].values[0]-1]=time-proc[i].values[1];
		wt[proc[i].values[0]-1]=rt[proc[i].values[0]-1]+proc[i].values[5];
		time+=bt[proc[i].values[0]-1];
	}
	 //turn around time
	 
	 for(int i=0;i<no;i++){
		tat[proc[i].values[0]-1]=rt[proc[i].values[0]-1]+bt[proc[i].values[0]-1];
		
	}
	cout<<"Pid\tAT\tBT\tRT\tWT\tTAT"<<endl;
	for (int i=0;i<no;i++)
	cout<<proc[i].values[0]<<"\t"<<proc[i].values[1]<<"\t"<<bt[proc[i].values[0]-1]<<"\t"<<rt[proc[i].values[0]-1]<<"\t"<<wt[proc[i].values[0]-1]<<"\t"<<tat[proc[i].values[0]-1]<<endl;
    q.pop();
}

void sjf(process proc[],int no){
process p[no],tmp;
int bt[no];
	for(int i=0;i<no;i++){
		bt[proc[i].values[0]-1]=proc[i].values[4]+proc[i].values[6];
	}
	//copying in other process structure
	for(int i=0;i<no;i++)
	p[i]=proc[i];
	int min_burst;
	int time=p[0].values[1];
	for(int j=0;j<no;j++){
		
		min_burst=bt[p[j].values[0]-1];
		for(int k=j+1;k<no;k++){
			if(p[k].values[1]<=time && bt[p[k].values[0]-1]<min_burst){
				//schedule this process first:
				//thus swapping:
				tmp=p[k];
				p[k]=p[j];
				p[j]=tmp;
				min_burst=bt[p[j].values[0]-1];
			}
		}
		time+=bt[p[j].values[0]-1];
	}
	
	fcfs(p,no);
}

void priority_nonpre(process proc[],int no){
process p[no],tmp;
int bt[no];
	for(int i=0;i<no;i++){
		bt[proc[i].values[0]-1]=proc[i].values[4]+proc[i].values[6];
	}
	//copying in other process structure
	for(int i=0;i<no;i++)
	p[i]=proc[i];
	int min_priority;
	int time=p[0].values[1];
	for(int j=0;j<no;j++){
		
		min_priority=p[j].values[2];
		for(int k=j+1;k<no;k++){
			if(p[k].values[1]<=time && p[k].values[2]<min_priority){
				//schedule this process first:
				//thus swapping:
				tmp=p[k];
				p[k]=p[j];
				p[j]=tmp;
				min_priority=p[j].values[2];
		
			}
		}
		time+=bt[p[j].values[0]-1];
	}
	
	fcfs(p,no);
}
void roundrobin(process proc[],int no){
	
	int rt[no],tat[no];
	int time=0;
	int quant=1;
	int bt[no];
	for(int i=0;i<no;i++){
		bt[proc[i].values[0]-1]=proc[i].values[4]+proc[i].values[6];
	}
	//response time code will work only when quantum=1
	for( int i=0;i<no;i++){
		rt[proc[i].values[0]-1]=time-proc[i].values[1];
		time+=1;
	}
	process p[no];
	int wt[no];
	for(int i=0;i<no;i++)
	p[i]=proc[i];
	int remain=no;      //do until all the proces are done fully
	time=0;
	int count=0;    //to go in round robin fashion
	
	while(remain!=0){
		if(bt[p[count].values[0]-1]>quant){
			bt[p[count].values[0]-1]-=quant; 
			time+=quant;
		}
		else if(bt[p[count].values[0]-1]<=quant && bt[p[count].values[0]-1]!=0) {
			time+=bt[p[count].values[0]-1];
			bt[p[count].values[0]-1]=0;
			tat[count]=time-p[count].values[1];
			wt[count]=tat[count]-bt[p[count].values[0]-1]+p[count].values[5];
			remain--;
			
		}
		if(count==no-1)
		count=0;
		else if(p[count+1].values[1]<=time)
		count++;
		else
		count=0;
	}
	for(int i=0;i<no;i++){
		bt[proc[i].values[0]-1]=proc[i].values[4]+proc[i].values[6];
	}
	cout<<"Pid\tAT\tBT\tRT\tWT\tTAT"<<endl;
	for (int i=0;i<no;i++)
	cout<<proc[i].values[0]<<"\t"<<proc[i].values[1]<<"\t"<<bt[proc[i].values[0]-1]<<"\t"<<rt[proc[i].values[0]-1]<<"\t"<<wt[proc[i].values[0]-1]<<"\t"<<tat[proc[i].values[0]-1]<<endl;
    
	 
}
void lottery(process proc[],int no){
	//considering cpu generating the lottery ticket time as zero
	int time=0;
	int remain=no;
	int rt[no],wt[no],tat[no];
	process p[no];
	for(int i=0;i<no;i++)
	p[i]=proc[i];
	int count=0;
	int bt[no];
	for(int i=0;i<no;i++){
		bt[proc[i].values[0]-1]=proc[i].values[4]+proc[i].values[6];
	}
	int min[no],max[no];
	    min[0]=1;
	    for (int i=1;i<no;i++)
	    min[i]=min[i-1]+p[i-1].values[3];
	    max[0]=p[0].values[3];
	    for(int i=1;i<no;i++)
	    max[i]=min[i]+p[i].values[3]-1;
	    
	while(remain!=0){
		int gen=(rand()%100)+1;
	    count=0;
		while(count<no){
			if(  p[count].values[1]<=time &&p[count].values[3]!=0 && gen>=min[count] && gen <=max[count]){
				
				cout<<"generated: "<<gen<<endl;
				rt[p[count].values[0]-1]=time-p[count].values[1];
				wt[p[count].values[0]-1]=rt[p[count].values[0]-1]+p[count].values[5];
				p[count].values[3]=0;
				remain--;
				tat[p[count].values[0]-1]=rt[p[count].values[0]-1]+bt[p[count].values[0]-1];
				time+=bt[p[count].values[0]-1];
			}
		count++;
		
	}
	}
	cout<<"Pid\tAT\tBT\tSHARE\tRT\tWT\tTAT"<<endl;
	for (int i=0;i<no;i++)
	cout<<proc[i].values[0]<<"\t"<<proc[i].values[1]<<"\t"<<bt[p[i].values[0]-1]<<"\t"<<proc[i].values[3]<<"\t"<<rt[proc[i].values[0]-1]<<"\t"<<wt[proc[i].values[0]-1]<<"\t"<<tat[proc[i].values[0]-1]<<endl;
    
}
bool func(process v1,process v2){
	return (v1.values[1]<v2.values[1]);
}
int main(){
	fstream file;
	string file_name="process.txt";
	string word;
	file.open(file_name.c_str());
	file>>word;   //reading file char by char
	stringstream number(word); //to convert string to number
	int no_of_process;
	number>>no_of_process;
	
	process proc[no_of_process];
	int k=0,i=0;
	while(file>>word){
		if(word!="-1"){
			stringstream number(word);
			int x;
			
			number>>x;
			proc[k].values[i]=x;
			
			i++;
		}
		else{
			k++;
			i=0;
		}
	
	}
	//sort on basis of arrival time:
	sort(proc,proc+no_of_process,func);
	
	int f=0;
	do{
	cout<<"press 1:FCFS\npress 2:SJF\npress 3:Priority\npress 4:Round Robin\npress 5:Lottery Scheduling\npress 6:exit"<<endl;
	int ch;
	cin>>ch;
	switch(ch){
		case 1:
			fcfs(proc,no_of_process);
			break;
		case 2:
			sjf(proc,no_of_process);
			break;
		case 3:
			priority_nonpre(proc,no_of_process);
			break;
		case 4:
			roundrobin(proc,no_of_process);
			break;
		case 5:
			lottery(proc,no_of_process);
			break;
		case 6:
			f=1;
			break;
		
	}
	}while(f==0);
	
}
