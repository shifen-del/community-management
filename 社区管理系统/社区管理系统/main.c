#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define X 100      //社区工作者的人数
#define A 20    //娱乐设施数目

typedef struct community_worker{
    int no;
    char name[20];
    int work_year;
}C_W;


struct Node{
	int price;//住宅价格
	char id[50];//住宅编号
	char type[50];//房屋类型
	int is_used;
	struct Node *next,*fro;
};
struct Node *head=NULL,*tail=NULL;//链表头,尾
int Num=0;//总共多少个房屋
struct VIP
{
    char num[10];
    char name[10];
    char password[10];
    char house[10];
    struct VIP *nextp;
};

typedef struct VIP vip;
typedef vip* pvip;
void administrate();
void select();
void menu1();
void people();
void menu2();

void Vip_select(); //功能选择
pvip Vip_readfile(); //读取文件信息
void Vip_creat(); //新建会员
void Vip_save(); //将会员信息储存到文件
void Vip_search(); //查询会员
void Vip_modify(); //修改会员
void Vip_delet(); //删除会员

void worker_manage();
void begin(int D,C_W c_w[]);
void community_worker_Init(int D,C_W c_w[]);
void menu();
int RowOfFile(char fname[100]);
void Add(int *D,C_W c_w[]);
void renew(int D,C_W c_w[]);
int search(int D,C_W c_w[]);
void Modify(int D,C_W c_w[]);
void Delete(int *D,C_W c_w[]);

void creat_new(int price,char id[],char type[]);
void print_all();
struct Node * find_id();
struct Node * find_price(int x);
void change_value(char x[],int val);
void del(char x[]);
void init();
void update();
void beautiful_house();

int main()
{
    system("color 7D");
    administrate();
    select();
}

int Pass=123;

void administrate() //管理员登录
{
    int n=1;

    do
    {  int password;
        printf("\n\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|             欢迎进入小区管理系统               |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("请输入密码：");
        scanf("%d",&password);
        if(password==Pass)
        {
            printf("密码输入正确!\n");
            system("pause");
            n=0;
        }
        if(password!=Pass)
        {
            printf("密码输入错误，请重新输入！\n");
            system("cls");
        }
    }while(n==1);
}

void select()
{  int c;
    while(1)
    {

        menu1();
        scanf("%d",&c);
        switch(c)
       {
           case 1:beautiful_house();
            break;

           case 2:people();
            break;
            case 3:amusement();
            break;
           case 0:exit(0);
            break;
           default:printf("请重新输入数字！\n");
           system("pause\n");
           break;

        }

    }

}

void menu1()
{   system("cls");
    printf("\n\n");
        printf("\t\t|----------------小区管理系统--------------------|\n");
        printf("\t\t|        0   退出                                |\n");
        printf("\t\t|        1   房屋管理                            |\n");
        printf("\t\t|        2   人员管理                            |\n");
        printf("\t\t|        3   娱乐设施管理                        |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t请在(0-3)间做出你的选择: ");

}

void people()
{  system("cls");
   int t;
   menu2();
   scanf("%d",&t);
        switch(t)
       {
           case 1:Vip_select();
            break;
           case 2:worker_manage();
            break;
           case 0:return 0;
            break;
           default:printf("请重新输入数字！\n");
           system("pause\n");
           break;
        }

    system("cls");
}

void menu2()
{   system("cls");
    printf("\n\n");
        printf("\t\t|----------------人员管理系统--------------------|\n");
        printf("\t\t|        0   退出                                |\n");
        printf("\t\t|        1   住户管理                            |\n");
        printf("\t\t|        2   社区工作人员管理                    |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t请在(0-2)间做出你的选择: ");

}


void Vip_select() //功能选择
{
    int c;
    while(1)
    {

        Vip_menu();
        scanf("%d",&c);
        switch(c)
       {
           case 1:Vip_creat();
            break;
           case 2:Vip_search();
            break;
           case 3:Vip_delet();
            break;
           case 4:Vip_modify();
            break;
           case 0:return 0;
           default:printf("请重新输入数字！\n");
           system("pause\n");
           break;
        }
    }
    system("cls");
}


void Vip_menu() //功能菜单
{   system("cls");
    printf("\n\n");
        printf("\t\t|----------------住户管理系统--------------------|\n");
        printf("\t\t|        0   退出                                |\n");
        printf("\t\t|        1   新建会员                            |\n");
        printf("\t\t|        2   查询会员                            |\n");
        printf("\t\t|        3   删除会员                            |\n");
        printf("\t\t|        4   修改会员                            |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t请在(0-4)间做出你的选择: ");


}


pvip Vip_readfile() //读取文件并返回表头
{
    FILE *fp;
    pvip head=NULL;  //头指针
    pvip p1,p2;
    int i=0;  //记录节点数
    fp=fopen("Vip_list.txt","r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            p2=head;
            i++;
            p1=(pvip)malloc(sizeof(vip));
            fscanf(fp,"%s %s %s %s\n",p1->num,p1->name,p1->password,p1->house);
            if(i==1)
            {
                head=p1;   //头
            }
            else
            {
                while (p2->nextp!=NULL)
                    p2=p2->nextp;

                p2->nextp=p1;
            }
            p1->nextp=NULL;
        }
    }
    else
    {
        printf("不能打开文件");
    }
    fclose(fp);
    return head;
}

void Vip_creat() //新建会员
{
    pvip p1=Vip_readfile();
    pvip p2=(pvip)malloc(sizeof(vip));  //申请空间
    char num[10],name[10],password1[10],password2[10],house[10];
    system("cls");
    printf("       注册会员\n");
    printf("-----------------------\n");
    printf("请输入您的会员编号：\n");
    scanf("%s",num);
    while(p1!=NULL)
    {
        if(strcmp(num,p1->num)!=0) //防止编号相同
        {
            p1=p1->nextp;
        }
        else
        {
            printf("该编号已被占用，请重新输入！\n");
            memset(num,0,sizeof (num)); //把mun数组初始化0
            scanf("%s",num);
        }
    }
    printf("请输入您的会员名：\n");
    scanf("%s",name);
    printf("请输入您的密码：\n");
    scanf("%s",password1);
    printf("请确认您的密码：\n");
    scanf("%s",password2);
    while (strcmp(password1,password2)!=0)
    {
        printf("请重新确认密码\n");
        memset(password2,0,sizeof (password2));
        scanf("%s",password2);
    }
    if (strcmp(password1,password2)==0)
    {
        strcpy(p2->num,num);
        strcpy(p2->name,name);
        strcpy(p2->password,password1);
        printf("该会员注册成功！\n");
    }
    print_all();
    printf("请输入想选择的房屋的编号：\n");
    scanf("%s",house);
    struct Node *now=find_id(house);
    if(now==NULL)
        printf("\n没有找到对应的房屋!\n");
    else
    {
        if(now->is_used)
        {
            printf("\n该房屋已经被选了！\n");
        }
        else{
            now->is_used=1;
            printf("\n选择成功！\n");
            }
    }
    strcpy(p2->house,house);

    system("pause");
    Vip_save(p2);
}


void Vip_save(pvip p) //储存到文件
{
    FILE *fp;
    fp=fopen("Vip_list.txt","a+");
    if (fp==NULL)
    {
        printf("不能打开文件！\n");
    }
    else
    {
        fprintf(fp,"%s %s %s %s\n",p->num,p->name,p->password,p->house);
        printf("信息已储存！\n");
    }
    fclose(fp);
}


void Vip_search()
{   system("cls");
    printf("       查询会员\n");
    printf("---------------------\n");
    char num[10];
    pvip p=Vip_readfile();
    printf("请输入想要查询的用户编号：\n");
    scanf("%s",num);
    while(p!=NULL&&strcmp(p->num,num))
    {
        p=p->nextp;
    }
    if (p!=NULL)
    {
        printf("编号：%s\n",p->num);
        printf("会员名：%s\n",p->name);
        printf("房屋信息：%s\n",p->house);
    }
    else
    {
        printf("没有查找到该用户！\n");
    }
    system("pause");
}


void Vip_delet()
{   system("cls");
    printf("       删除会员\n");
    printf("---------------------\n");
    char num[10];
    pvip head=Vip_readfile();
    pvip p1=head;
    pvip p2=p1->nextp;
    printf("请输入想要删除的会员编号：\n");
    scanf("%s",num);
    int found=0;
    while(p2!=NULL)
    {
        if(strcmp(p2->num,num)==0)
        {
            p1->nextp=p2->nextp;
            printf("会员删除成功！\n");
            found=1;
            break;
        }
        p1=p1->nextp;
        p2=p2->nextp;
    }
    if (found!=0)
    {
        p1=head;
        FILE* fp=fopen("Vip_list.txt","w");
        if (fp!=0)
        {
            while (p1!=NULL)
            {
                fprintf(fp,"%s %s %s %s\n",p1->num,p1->name,p1->password,p1->house);
                p1=p1->nextp;
            }
        }
        else
            printf("无法打开文件，存储失败");

        fclose(fp);
    }
    else
    {
        printf("没有找到该会员！");
    }
}


void Vip_modify()
{   system("cls");
    printf("      修改会员\n");
    printf("-----------------------\n");
    pvip head=Vip_readfile();
    pvip p1=head;
    pvip p2=p1->nextp;
    char num[10];
    int c,found=0;
    printf("请输入想要修改的会员编号:");
    scanf("%s",num);
    while (p2!=NULL)
    {
        if(strcmp(p2->num,num)==0)
        {
            printf("请选择想要修改的内容\n");
            printf("1.会员名\n");
            printf("2.密码\n");
            printf("0.退出\n");
            scanf("%d",&c);
            switch(c)
            {
                case 1:
                    printf("请输入修改后名字：\n");
                    char name[10];
                    scanf("%s",name);
                    strcpy(p2->name,name);
                    printf("会员名修改成功！\n");
                    found=1;
                    break;
                case 2:
                    printf("请输入修改后密码：\n");
                    char password[10];
                    scanf("%s",password);
                    strcpy(p2->password,password);
                    printf("密码修改成功！\n");
                    found=1;
                    break;
                case 0:
                    found=2;
                    break;
            }
        }
        p2=p2->nextp;
    }

    if (found==1)
    {
        p1=head;
        FILE* fp=fopen("Vip_list.txt","w");
        if (fp!=NULL)
        {
            while (p1!=NULL)
            {
                fprintf(fp,"%s %s %s %s\n",p1->num,p1->name,p1->password,p1->house);
                p1=p1->nextp;
            }
        }
        else
        {
            printf("无法打开文件，存储失败");
        }
        fclose(fp);
    }
    else if (found==0)
    {
        printf("没有找到该用户");
    }
    system("pause");
}
void worker_manage()
{

    C_W c_w[X];
    int D=RowOfFile("community_worker.txt");        //目前有多少名工作者
    community_worker_Init(D,c_w);
    menu();
    begin(D,c_w);
    return 0;

}
void begin(int D,C_W c_w[])
{
    int choice;

    scanf("%d",&choice);
    printf("\n\n");
    while(choice!=0)
    {
        switch(choice){

        case 1:
            Add(&D,c_w);
            printf("*******successed************\n");
            printf("*****Take the effect after program restart********\n");
            community_worker_Init(D,c_w);
            break;
        case 2:
            Delete(&D,c_w);
            renew(D,c_w);
            break;
        case 3:
            for(int i=0;i<D;i++){
               printf("%d %s %d\n",c_w[i].no,c_w[i].name,c_w[i].work_year);
            }
            break;
        case 4:
            Modify(D,c_w);
            renew(D,c_w);
            break;
        }
        menu();

        scanf("%d",&choice);

    }

}

void community_worker_Init(int D,C_W c_w[])
{
    FILE *fp=fopen("community_worker.txt","r");
    for(int i=0;i<D;i++)
    {
        fscanf(fp,"%d %s %d",&c_w[i].no,c_w[i].name,&c_w[i].work_year);

    }
    fclose(fp);
}
void menu()
{
    printf("\n\n");
        printf("\t\t|----------------工作人员管理系统--------------------|\n");
        printf("\t\t|        0   退出                                             |\n");
        printf("\t\t|        1   录入新员工的信息                                 |\n");
        printf("\t\t|        2   员工辞职，删除信息                               |\n");
        printf("\t\t|        3   展示现有所有员工信息                             |\n");
        printf("\t\t|        4   修改员工信息                                     |\n");
        printf("\t\t|                                                             |\n");
        printf("\t\t|-------------------------------------------------------------|\n");
        printf("\n\t\t请在(0-4)间做出你的选择: ");
}
int RowOfFile(char fname[100])
{
    FILE *file;
    int count=0;
    char out;
    if((file=fopen(fname,"r"))==NULL)
        return 0;
    else{
        while(!feof(file)){
            if((out=fgetc(file))=='\n')
                count++;
        }
    }
    return count;
}

void Add(int *D,C_W c_w[])
{
    FILE *fp=fopen("community_worker.txt","a");
    char mm[20]={"111"};  //姓名
    int yy=0;  //工作年龄
    int i=0;

    if(*D!=0){
        i=c_w[*D-1].no;
    }

    printf("如果你想停止，请输入0，这个工人的编号将是：%d\n请输入此新工作人员的名字：",i+1);
    scanf("%s",mm);
    for(i;mm[0]!='0';i++){
        printf("\n请输入这个工作人员的工作年龄 ：");
        scanf("%d",&yy);
        fprintf(fp,"%d %s %d\n",i+1,mm,yy);
        (*D)++;
        printf("\n如果你想停止，请输入0，这个工人的编号将是：%d \n请输入此新工作人员的名字：",i+2);
        memset(mm,1,20);
        scanf("%s",mm);
    }
    fclose(fp);
}

void renew(int D,C_W c_w[])
{
    FILE *fp=fopen("community_worker.txt","w");
    for(int i=0;i<D;i++){
        fprintf(fp,"%d %s %d\n",c_w[i].no,c_w[i].name,c_w[i].work_year);
    }
}
int search(int D,C_W c_w[]){
    puts("\n你想按照何种方式搜索？\n1.按名字搜索\n2.按工作人员编号搜索");
    int choice=0,number=0;
    char name[20];
    scanf("%d",&choice);
    switch(choice){
        case 1:
            puts("\n请输入名字");
            scanf("%s",name);
            for (int i=0;i<D;i++){
                if(!strcmp(name,c_w[i].name))
                    return i;
            }
            break;
        default:
            puts("\n请输入工作人员编号");
            scanf("%d",&number);
            for (int i=0;i<D;i++){
                if(c_w[i].no==number)
                    return i;
            }
            break;
    }
    return -1;
}
void Modify(int D,C_W c_w[])
{
    int no,i,new_workyear,a;
    for(i=0;i<D;i++){
        printf("%d %s %d\n",c_w[i].no,c_w[i].name,c_w[i].work_year);
    }
    printf("你将选择你要修改的工作人员: ");
    no=search(D,c_w);
    printf("\n这个工作人员的信息是:\n工作编号:%d\n姓名:%s\n工作年龄:%d\n",c_w[no].no,c_w[no].name,c_w[no].work_year);

    printf("请输入新的工作年龄:  ");
    scanf("%d",&new_workyear);
    c_w[no].work_year=new_workyear;
    return 0;
}
void Delete(int *D,C_W c_w[])
{
    int no,i,a;
    for(i=0;i<*D;i++){
               printf("%d %s %d\n",c_w[i].no,c_w[i].name,c_w[i].work_year);
            }
    printf("\n你将会选择你要删除的工作人员 ");
    no=search(*D,c_w);

           printf("\n%d %s %d",c_w[no].no,c_w[no].name,c_w[no].work_year);
           printf("  正在被删除……");
    if(no!=(*D)-1){
     (*D)--;
      for(i=no;i<*D;i++){
        c_w[i]=c_w[i+1];

     }
    }
    else{
        (*D)--;
    }


    return 0;
}

void creat_new(int price,char id[],char type[]){//新建房屋
	Num++;
	char t[50];
	struct Node *temp=(struct Node*)malloc(sizeof(struct Node));//申请内存
	strcpy(temp->id,id);
	strcpy(temp->type,type);
	temp->price=price;
	temp->is_used=0;
	temp->next=NULL;temp->fro=NULL;
	if(head==NULL){
		head=temp;
		tail=temp;
	}
	else{
		temp->fro=tail;
		tail->next=temp;
		tail=temp;
	}

}
void print_all(){//查看全部住房
	struct Node *now=head;
	system("cls");
	printf("目前共有%d套住宅:\n",Num);
	while(now!=NULL){
		printf("  该房的编号是：%s\n",now->id);
		printf("  该房的类型是：%s\n",now->type);
		printf("  价格为：      %d\n",now->price);
		now=now->next;
		printf("\n");

	}
        system("pause");
}
struct Node * find_id(char x[]){//通过编号搜索房屋
	struct Node *now=head;
	while(now!=NULL){
		if(strcmp(now->id,x)==0){
			return now;
		}
		else
			now=now->next;
	}
	return NULL;
}
struct Node * find_price(int x){//通过价格搜索房屋
	struct Node *now=head;
	while(now!=NULL){
		if(now->price==x){
			return now;
		}
		else
			now=now->next;
	}
	return NULL;
}
void change_value(char x[],int val){//修改价格（把编号为x的价格改成val）
	struct Node *now=find_id(x);
	now->price=val;
}
void del(char x[]){
	Num--;
	struct Node *now=find_id(x),*froo,*nextt;
	froo=now->fro;
	nextt=now->next;
	if(head==now){
		if(nextt==NULL)
			head=NULL;
		else
			head=nextt;
	}
	else if(tail==now){
		if(froo==NULL)
			tail=NULL;
		else
			tail=froo;
	}
	if(froo!=NULL)
		froo->next=now->next;
	if(nextt!=NULL)
		nextt->fro=now->fro;
}
void init(){
	FILE *fp=fopen("house data.txt","r");
	char a[50],b[50];
	int x;
	while(fscanf(fp,"%s %s %d",a,b,&x)!=EOF){
		creat_new(x,a,b);
	}
	fclose(fp);
}
void update(){
	FILE *fp=fopen("house data.txt","w");
	struct Node *now=head;
	while(now!=NULL){
		fprintf(fp,"%s %s %d\n",now->id,now->type,now->price);
		now=now->next;
	}
	fclose(fp);
}
void beautiful_house()
{
	printf("欢迎进入房屋管理系统！\n");
	init();
	int opr=0,x;char a[50]="",b[50]="";
	do{system("cls");
    printf("\n\n");
        printf("\t\t|----------------房屋管理系统--------------------|\n");
        printf("\t\t|        0   退出                                |\n");
        printf("\t\t|        1   查看全部房屋                        |\n");
        printf("\t\t|        2   新建住宅                            |\n");
        printf("\t\t|        3   查看/修改房屋信息                   |\n");
        printf("\t\t|        4   搜索房屋                            |\n");
        printf("\t\t|        5   选择房屋                            |\n");
        printf("\t\t|        6   删除房屋信息                        |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t请在(0-6)间做出你的选择: ");
		scanf("%d",&opr);
		switch(opr){
			case 0:{
				return 0;
			}
			case 1:{
				print_all();
				break;
			}
			case 2:{system("cls");
				printf("请输入住宅编号：\n");
				scanf("%s",a);
				printf("请输入住宅类型：\n");
				scanf("%s",b);
				printf("请输入住宅价格：\n");
				scanf("%d",&x);
				creat_new(x,a,b);
				printf("新建成功!\n\n");
				system("pause");
				update();
				break;
			}
			case 3:{system("cls");
				printf("请输入需要查看的房屋编号：\n");
				scanf("%s",a);
				struct Node *now=find_id(a);
				if(now==NULL)
					printf("\n没有找到对应的房屋!\n");
				else{
					printf("\n该房屋的类型是%s,价格为  %d，",now->type,now->price);
					if(now->is_used)
						printf("该房已被选用！\n");
					else
						printf("该房当前空闲\n");
					printf("如果需要修改请输入修改后的价格，若不需要请输入-1：  ");
					scanf("%d",&x);
					if(x!=-1){
						now->price=x;
						printf("修改成功\n\n");
						update();
					}
					else
						printf("\n");
				}
				break;
			}
			case 4:{system("cls");
				printf("请输入房屋的价格：  ");
				scanf("%d",&x);
				struct Node *now=find_price(x);
				if(now==NULL)
					printf("\n没有找到对应的房屋!\n");
				else
					printf("\n该房屋编号为：%s\n",now->id);
				break;
			}
			case 5:{system("cls");
				printf("请输入想选的房屋的编号：\n");
				scanf("%s",a);
				struct Node *now=find_id(a);
				if(now==NULL)
					printf("\n没有找到对应的房屋!\n");
				else{
					if(now->is_used){
						printf("\n该房屋已经被选了！\n");
					}
					else{
						now->is_used=1;
						printf("\n选择成功！\n");
					}
				}
				break;
			}
			case 6:{system("cls");
				printf("请输入想选的房屋的编号：\n");
				scanf("%s",a);
				del(a);
				update();
				printf("删除成功\n\n");
				break;
			}
		}
	}while(1);
	return 0;
}
 struct facilities{

        char name[10];
        char number[10];
        struct facilities*next;
};

    struct facilities *headz;
    typedef struct facilities ft;
    typedef ft* pf;

pf Amuse_readfile() //读取文件并返回表头
{
    FILE *fp;
    pf head=NULL;  //头指针
    pf p1,p2;
    int i=0;  //记录节点数
    fp=fopen("facilities.txt","r");
    if(fp!=NULL)
    {
        while(!feof(fp))
        {

            p2=head;
            i++;
            p1=(pf)malloc(sizeof(ft));
            fscanf(fp,"%s %s\n",p1->name,p1->number);
            if(i==1)
            {

                head=p1;   //头
            }
            else
            {

                while (p2->next!=NULL)
                    p2=p2->next;
                p2->next=p1;
            }
            p1->next=NULL;
        }
    }
    else
    {
        printf("不能打开文件");
    }
    fclose(fp);
    return head;
}
   void print_facilities(){

        pf now = Amuse_readfile();
        system("cls");
        while(now!=NULL){
            printf("  娱乐设施的名称是：%s\n",now->name);
            printf("  娱乐设施参与最多人数是：%s\n",now->number);

            now=now->next;
            printf("\n");
        }

    }
    void save_Amuse(pf p){
        FILE *fp;
        fp=fopen("facilities.txt","a+");
        if (fp==NULL)
        {
            printf("不能打开文件！\n");
        }
        else
        {
            fprintf(fp,"%s %s\n",p->name,p->number);
            printf("信息已储存！\n");
        }
        fclose(fp);
    }
    void newAmuse(){
         pf p1 = Amuse_readfile();
         system("cls");
         pf p2=(pf)malloc(sizeof(ft));
         int mark=2;
         while(p1!=NULL){
            printf("123");
            p1=p1->next;

         }

        printf("请输入新建设施的名称");
        scanf("%s",&p2->name);
        printf("请输入新建设施的使用人数");
        scanf("%s",&p2->number);
        save_Amuse(p2);
        system("cls");
        return 0;

    }

    void delete(){

    system("cls");
    printf("       删除设施\n");
    printf("---------------------\n");
    char num[10];
    pf head=Amuse_readfile();
    pf p1=head;
    pf p2=p1->next;
    printf("请输入想要删除的设施名：\n");
    scanf("%s",num);
    int found=0;
    while(p2!=NULL)
    {
        if(strcmp(p2->name,num)==0)
        {
            p1->next=p2->next;
            printf("设施删除成功！\n");
            found=1;
            break;
        }
        p1=p1->next;
        p2=p2->next;
    }
    if (found!=0)
    {
        p1=head;
        FILE* fp=fopen("facilities.txt","w");
        if (fp!=0)
        {
            while (p1!=NULL)
            {
                fprintf(fp,"%s %s\n",p1->name,p1->number);
                p1=p1->next;
            }
        }
        else
            printf("无法打开文件，存储失败");

        fclose(fp);
    }
    else
    {
        printf("没有找到该设施！");
    }

    }



void amusement(){


    while(1){

    system("cls");

    printf("\n\n");
        printf("\t\t|----------------娱乐设施管理系统----------------|\n");
        printf("\t\t|        0   退出                                |\n");
        printf("\t\t|        1   查看娱乐设施                        |\n");
        printf("\t\t|        2   新建娱乐设施                        |\n");
        printf("\t\t|        3   删除设施信息                        |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t请在(0-3)间做出你的选择: ");



        int choose;
        scanf("%d",&choose);


    switch(choose){


           case 0:{
				return 0;
			}


            case 1:{
				print_facilities();
				system("pause");
				printf("\n");
				break;
			}
			case 2:{system("cls");
			newAmuse();


				break;
			}

			case 3:{

            delete();
            break;
            }



           default:{

                printf("无该功能");
                break;
             }



             system("pause");
             system("cls");
    }
    }}
