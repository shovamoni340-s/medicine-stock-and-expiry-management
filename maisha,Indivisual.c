#include <stdio.h>
#include <string.h>

char code[6][10]={"MED01","MED02","MED03","MED04","MED05","MED06"};
char name[6][30]={"Oral Saline","Paracetamol","Insulin","Amoxicillin","Antacid","Cetirizine"};
int stock[6]={120,300,60,200,250,180};
int daily_req[6]={35,40,12,25,18,15};
int min_stock[6]={80,100,50,80,60,50};
int days_to_expiry[6]={45,120,30,20,15,90};
int ess[6]={3,2,3,3,1,2};
int cov[6];
char cond[6][30];
int pri[6];
int n=6;

void calc(int i){
if(daily_req[i]>0)
cov[i]=stock[i]/daily_req[i];
else
cov[i]=999;

int ls=0,er=0;
if(stock[i]<min_stock[i]) ls=1;
if(days_to_expiry[i]<=30) er=1;

if(ls==1&&er==1){
strcpy(cond[i],"Critical Condition");
pri[i]=100;
}
else if(ls==1){
if(ess[i]==3){ strcpy(cond[i],"Urgent Reorder"); pri[i]=80; }
else{ strcpy(cond[i],"Reorder Required"); pri[i]=60; }
}
else if(er==1){ strcpy(cond[i],"Expiry Attention"); pri[i]=70; }
else{ strcpy(cond[i],"Sufficient Stock"); pri[i]=10; }

pri[i]=pri[i]+(100-cov[i]);
}

void show(){
int i;
printf("\n%-8s %-15s %-8s %-10s %-10s %-20s %-8s\n","Code","Name","Stock","Coverage","Expiry","Condition","Priority");
printf("---------\n");
for(i=0;i<n;i++){
printf("%-8s %-15s %-8d %-10d %-10d %-20s %-8d\n",code[i],name[i],stock[i],cov[i],days_to_expiry[i],cond[i],pri[i]);
}
}

void srch(){
char c[10];
int i,f=0;
printf("\nEnter Medicine Code to Search: ");
scanf("%s",c);
for(i=0;i<n;i++){
if(strcmp(code[i],c)==0){
printf("Found: %s | Stock: %d | Expiry: %d days | Condition: %s\n",name[i],stock[i],days_to_expiry[i],cond[i]);
f=1;
break;
}
}
if(f==0) printf("Medicine Not Found!\n");
}

void upd(){
char c[10];
int i,ch,q,f=0;
printf("\nEnter Code: ");
scanf("%s",c);
for(i=0;i<n;i++){
if(strcmp(code[i],c)==0){
f=1;
printf("1. Add Stock  2. Issue Stock: ");
scanf("%d",&ch);
printf("Quantity: ");
scanf("%d",&q);
switch(ch){
case 1:
stock[i]=stock[i]+q;
break;
case 2:
if(q<=stock[i]) stock[i]=stock[i]-q;
else printf("Stock cannot be negative!\n");
break;
}
calc(i);
break;
}
}
if(f==0) printf("Medicine Not Found!\n");
}

void srt(){
int i,j;
char tc[10],tn[30],tco[30];
int a,b,d,e,g,h,k;
for(i=0;i<n-1;i++){
for(j=0;j<n-i-1;j++){
if(pri[j]<pri[j+1]){
strcpy(tc,code[j]); strcpy(code[j],code[j+1]); strcpy(code[j+1],tc);
strcpy(tn,name[j]); strcpy(name[j],name[j+1]); strcpy(name[j+1],tn);
strcpy(tco,cond[j]); strcpy(cond[j],cond[j+1]); strcpy(cond[j+1],tco);
a=stock[j]; stock[j]=stock[j+1]; stock[j+1]=a;
b=daily_req[j]; daily_req[j]=daily_req[j+1]; daily_req[j+1]=b;
d=min_stock[j]; min_stock[j]=min_stock[j+1]; min_stock[j+1]=d;
e=days_to_expiry[j]; days_to_expiry[j]=days_to_expiry[j+1]; days_to_expiry[j+1]=e;
g=ess[j]; ess[j]=ess[j+1]; ess[j+1]=g;
h=cov[j]; cov[j]=cov[j+1]; cov[j+1]=h;
k=pri[j]; pri[j]=pri[j+1]; pri[j+1]=k;
}
}
}
printf("Sorted successfully!\n");
show();
}

void sv(){
int i;
FILE *fp=fopen("report.txt","w");
if(!fp) return;
for(i=0;i<n;i++){
fprintf(fp,"%s %s %d %s %d\n",code[i],name[i],stock[i],cond[i],pri[i]);
}
fclose(fp);
printf("Saved to report.txt!\n");
}

int main(){
int ch,i;
void (*menu[5])();
menu[0]=show;
menu[1]=srch;
menu[2]=upd;
menu[3]=srt;
menu[4]=sv;

for(i=0;i<n;i++) calc(i);

while(1){
printf("\n1. Show Report\n2. Search\n3. Update Stock\n4. Sort Priority\n5. Save File\n6. Exit\nChoice: ");
scanf("%d",&ch);
if(ch>=1&&ch<=5) menu[ch-1]();
else if(ch==6) break;
else printf("Invalid option!\n");
}
return 0;
}
