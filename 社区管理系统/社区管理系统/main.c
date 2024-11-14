#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define X 100      //���������ߵ�����
#define A 20    //������ʩ��Ŀ

typedef struct community_worker{
    int no;
    char name[20];
    int work_year;
}C_W;


struct Node{
	int price;//סլ�۸�
	char id[50];//סլ���
	char type[50];//��������
	int is_used;
	struct Node *next,*fro;
};
struct Node *head=NULL,*tail=NULL;//����ͷ,β
int Num=0;//�ܹ����ٸ�����
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

void Vip_select(); //����ѡ��
pvip Vip_readfile(); //��ȡ�ļ���Ϣ
void Vip_creat(); //�½���Ա
void Vip_save(); //����Ա��Ϣ���浽�ļ�
void Vip_search(); //��ѯ��Ա
void Vip_modify(); //�޸Ļ�Ա
void Vip_delet(); //ɾ����Ա

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

void administrate() //����Ա��¼
{
    int n=1;

    do
    {  int password;
        printf("\n\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|             ��ӭ����С������ϵͳ               |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("���������룺");
        scanf("%d",&password);
        if(password==Pass)
        {
            printf("����������ȷ!\n");
            system("pause");
            n=0;
        }
        if(password!=Pass)
        {
            printf("��������������������룡\n");
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
           default:printf("�������������֣�\n");
           system("pause\n");
           break;

        }

    }

}

void menu1()
{   system("cls");
    printf("\n\n");
        printf("\t\t|----------------С������ϵͳ--------------------|\n");
        printf("\t\t|        0   �˳�                                |\n");
        printf("\t\t|        1   ���ݹ���                            |\n");
        printf("\t\t|        2   ��Ա����                            |\n");
        printf("\t\t|        3   ������ʩ����                        |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t����(0-3)���������ѡ��: ");

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
           default:printf("�������������֣�\n");
           system("pause\n");
           break;
        }

    system("cls");
}

void menu2()
{   system("cls");
    printf("\n\n");
        printf("\t\t|----------------��Ա����ϵͳ--------------------|\n");
        printf("\t\t|        0   �˳�                                |\n");
        printf("\t\t|        1   ס������                            |\n");
        printf("\t\t|        2   ����������Ա����                    |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t����(0-2)���������ѡ��: ");

}


void Vip_select() //����ѡ��
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
           default:printf("�������������֣�\n");
           system("pause\n");
           break;
        }
    }
    system("cls");
}


void Vip_menu() //���ܲ˵�
{   system("cls");
    printf("\n\n");
        printf("\t\t|----------------ס������ϵͳ--------------------|\n");
        printf("\t\t|        0   �˳�                                |\n");
        printf("\t\t|        1   �½���Ա                            |\n");
        printf("\t\t|        2   ��ѯ��Ա                            |\n");
        printf("\t\t|        3   ɾ����Ա                            |\n");
        printf("\t\t|        4   �޸Ļ�Ա                            |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t����(0-4)���������ѡ��: ");


}


pvip Vip_readfile() //��ȡ�ļ������ر�ͷ
{
    FILE *fp;
    pvip head=NULL;  //ͷָ��
    pvip p1,p2;
    int i=0;  //��¼�ڵ���
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
                head=p1;   //ͷ
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
        printf("���ܴ��ļ�");
    }
    fclose(fp);
    return head;
}

void Vip_creat() //�½���Ա
{
    pvip p1=Vip_readfile();
    pvip p2=(pvip)malloc(sizeof(vip));  //����ռ�
    char num[10],name[10],password1[10],password2[10],house[10];
    system("cls");
    printf("       ע���Ա\n");
    printf("-----------------------\n");
    printf("���������Ļ�Ա��ţ�\n");
    scanf("%s",num);
    while(p1!=NULL)
    {
        if(strcmp(num,p1->num)!=0) //��ֹ�����ͬ
        {
            p1=p1->nextp;
        }
        else
        {
            printf("�ñ���ѱ�ռ�ã����������룡\n");
            memset(num,0,sizeof (num)); //��mun�����ʼ��0
            scanf("%s",num);
        }
    }
    printf("���������Ļ�Ա����\n");
    scanf("%s",name);
    printf("�������������룺\n");
    scanf("%s",password1);
    printf("��ȷ���������룺\n");
    scanf("%s",password2);
    while (strcmp(password1,password2)!=0)
    {
        printf("������ȷ������\n");
        memset(password2,0,sizeof (password2));
        scanf("%s",password2);
    }
    if (strcmp(password1,password2)==0)
    {
        strcpy(p2->num,num);
        strcpy(p2->name,name);
        strcpy(p2->password,password1);
        printf("�û�Աע��ɹ���\n");
    }
    print_all();
    printf("��������ѡ��ķ��ݵı�ţ�\n");
    scanf("%s",house);
    struct Node *now=find_id(house);
    if(now==NULL)
        printf("\nû���ҵ���Ӧ�ķ���!\n");
    else
    {
        if(now->is_used)
        {
            printf("\n�÷����Ѿ���ѡ�ˣ�\n");
        }
        else{
            now->is_used=1;
            printf("\nѡ��ɹ���\n");
            }
    }
    strcpy(p2->house,house);

    system("pause");
    Vip_save(p2);
}


void Vip_save(pvip p) //���浽�ļ�
{
    FILE *fp;
    fp=fopen("Vip_list.txt","a+");
    if (fp==NULL)
    {
        printf("���ܴ��ļ���\n");
    }
    else
    {
        fprintf(fp,"%s %s %s %s\n",p->num,p->name,p->password,p->house);
        printf("��Ϣ�Ѵ��棡\n");
    }
    fclose(fp);
}


void Vip_search()
{   system("cls");
    printf("       ��ѯ��Ա\n");
    printf("---------------------\n");
    char num[10];
    pvip p=Vip_readfile();
    printf("��������Ҫ��ѯ���û���ţ�\n");
    scanf("%s",num);
    while(p!=NULL&&strcmp(p->num,num))
    {
        p=p->nextp;
    }
    if (p!=NULL)
    {
        printf("��ţ�%s\n",p->num);
        printf("��Ա����%s\n",p->name);
        printf("������Ϣ��%s\n",p->house);
    }
    else
    {
        printf("û�в��ҵ����û���\n");
    }
    system("pause");
}


void Vip_delet()
{   system("cls");
    printf("       ɾ����Ա\n");
    printf("---------------------\n");
    char num[10];
    pvip head=Vip_readfile();
    pvip p1=head;
    pvip p2=p1->nextp;
    printf("��������Ҫɾ���Ļ�Ա��ţ�\n");
    scanf("%s",num);
    int found=0;
    while(p2!=NULL)
    {
        if(strcmp(p2->num,num)==0)
        {
            p1->nextp=p2->nextp;
            printf("��Աɾ���ɹ���\n");
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
            printf("�޷����ļ����洢ʧ��");

        fclose(fp);
    }
    else
    {
        printf("û���ҵ��û�Ա��");
    }
}


void Vip_modify()
{   system("cls");
    printf("      �޸Ļ�Ա\n");
    printf("-----------------------\n");
    pvip head=Vip_readfile();
    pvip p1=head;
    pvip p2=p1->nextp;
    char num[10];
    int c,found=0;
    printf("��������Ҫ�޸ĵĻ�Ա���:");
    scanf("%s",num);
    while (p2!=NULL)
    {
        if(strcmp(p2->num,num)==0)
        {
            printf("��ѡ����Ҫ�޸ĵ�����\n");
            printf("1.��Ա��\n");
            printf("2.����\n");
            printf("0.�˳�\n");
            scanf("%d",&c);
            switch(c)
            {
                case 1:
                    printf("�������޸ĺ����֣�\n");
                    char name[10];
                    scanf("%s",name);
                    strcpy(p2->name,name);
                    printf("��Ա���޸ĳɹ���\n");
                    found=1;
                    break;
                case 2:
                    printf("�������޸ĺ����룺\n");
                    char password[10];
                    scanf("%s",password);
                    strcpy(p2->password,password);
                    printf("�����޸ĳɹ���\n");
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
            printf("�޷����ļ����洢ʧ��");
        }
        fclose(fp);
    }
    else if (found==0)
    {
        printf("û���ҵ����û�");
    }
    system("pause");
}
void worker_manage()
{

    C_W c_w[X];
    int D=RowOfFile("community_worker.txt");        //Ŀǰ�ж�����������
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
        printf("\t\t|----------------������Ա����ϵͳ--------------------|\n");
        printf("\t\t|        0   �˳�                                             |\n");
        printf("\t\t|        1   ¼����Ա������Ϣ                                 |\n");
        printf("\t\t|        2   Ա����ְ��ɾ����Ϣ                               |\n");
        printf("\t\t|        3   չʾ��������Ա����Ϣ                             |\n");
        printf("\t\t|        4   �޸�Ա����Ϣ                                     |\n");
        printf("\t\t|                                                             |\n");
        printf("\t\t|-------------------------------------------------------------|\n");
        printf("\n\t\t����(0-4)���������ѡ��: ");
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
    char mm[20]={"111"};  //����
    int yy=0;  //��������
    int i=0;

    if(*D!=0){
        i=c_w[*D-1].no;
    }

    printf("�������ֹͣ��������0��������˵ı�Ž��ǣ�%d\n��������¹�����Ա�����֣�",i+1);
    scanf("%s",mm);
    for(i;mm[0]!='0';i++){
        printf("\n���������������Ա�Ĺ������� ��");
        scanf("%d",&yy);
        fprintf(fp,"%d %s %d\n",i+1,mm,yy);
        (*D)++;
        printf("\n�������ֹͣ��������0��������˵ı�Ž��ǣ�%d \n��������¹�����Ա�����֣�",i+2);
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
    puts("\n���밴�պ��ַ�ʽ������\n1.����������\n2.��������Ա�������");
    int choice=0,number=0;
    char name[20];
    scanf("%d",&choice);
    switch(choice){
        case 1:
            puts("\n����������");
            scanf("%s",name);
            for (int i=0;i<D;i++){
                if(!strcmp(name,c_w[i].name))
                    return i;
            }
            break;
        default:
            puts("\n�����빤����Ա���");
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
    printf("�㽫ѡ����Ҫ�޸ĵĹ�����Ա: ");
    no=search(D,c_w);
    printf("\n���������Ա����Ϣ��:\n�������:%d\n����:%s\n��������:%d\n",c_w[no].no,c_w[no].name,c_w[no].work_year);

    printf("�������µĹ�������:  ");
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
    printf("\n�㽫��ѡ����Ҫɾ���Ĺ�����Ա ");
    no=search(*D,c_w);

           printf("\n%d %s %d",c_w[no].no,c_w[no].name,c_w[no].work_year);
           printf("  ���ڱ�ɾ������");
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

void creat_new(int price,char id[],char type[]){//�½�����
	Num++;
	char t[50];
	struct Node *temp=(struct Node*)malloc(sizeof(struct Node));//�����ڴ�
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
void print_all(){//�鿴ȫ��ס��
	struct Node *now=head;
	system("cls");
	printf("Ŀǰ����%d��סլ:\n",Num);
	while(now!=NULL){
		printf("  �÷��ı���ǣ�%s\n",now->id);
		printf("  �÷��������ǣ�%s\n",now->type);
		printf("  �۸�Ϊ��      %d\n",now->price);
		now=now->next;
		printf("\n");

	}
        system("pause");
}
struct Node * find_id(char x[]){//ͨ�������������
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
struct Node * find_price(int x){//ͨ���۸���������
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
void change_value(char x[],int val){//�޸ļ۸񣨰ѱ��Ϊx�ļ۸�ĳ�val��
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
	printf("��ӭ���뷿�ݹ���ϵͳ��\n");
	init();
	int opr=0,x;char a[50]="",b[50]="";
	do{system("cls");
    printf("\n\n");
        printf("\t\t|----------------���ݹ���ϵͳ--------------------|\n");
        printf("\t\t|        0   �˳�                                |\n");
        printf("\t\t|        1   �鿴ȫ������                        |\n");
        printf("\t\t|        2   �½�סլ                            |\n");
        printf("\t\t|        3   �鿴/�޸ķ�����Ϣ                   |\n");
        printf("\t\t|        4   ��������                            |\n");
        printf("\t\t|        5   ѡ����                            |\n");
        printf("\t\t|        6   ɾ��������Ϣ                        |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t����(0-6)���������ѡ��: ");
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
				printf("������סլ��ţ�\n");
				scanf("%s",a);
				printf("������סլ���ͣ�\n");
				scanf("%s",b);
				printf("������סլ�۸�\n");
				scanf("%d",&x);
				creat_new(x,a,b);
				printf("�½��ɹ�!\n\n");
				system("pause");
				update();
				break;
			}
			case 3:{system("cls");
				printf("��������Ҫ�鿴�ķ��ݱ�ţ�\n");
				scanf("%s",a);
				struct Node *now=find_id(a);
				if(now==NULL)
					printf("\nû���ҵ���Ӧ�ķ���!\n");
				else{
					printf("\n�÷��ݵ�������%s,�۸�Ϊ  %d��",now->type,now->price);
					if(now->is_used)
						printf("�÷��ѱ�ѡ�ã�\n");
					else
						printf("�÷���ǰ����\n");
					printf("�����Ҫ�޸��������޸ĺ�ļ۸�������Ҫ������-1��  ");
					scanf("%d",&x);
					if(x!=-1){
						now->price=x;
						printf("�޸ĳɹ�\n\n");
						update();
					}
					else
						printf("\n");
				}
				break;
			}
			case 4:{system("cls");
				printf("�����뷿�ݵļ۸�  ");
				scanf("%d",&x);
				struct Node *now=find_price(x);
				if(now==NULL)
					printf("\nû���ҵ���Ӧ�ķ���!\n");
				else
					printf("\n�÷��ݱ��Ϊ��%s\n",now->id);
				break;
			}
			case 5:{system("cls");
				printf("��������ѡ�ķ��ݵı�ţ�\n");
				scanf("%s",a);
				struct Node *now=find_id(a);
				if(now==NULL)
					printf("\nû���ҵ���Ӧ�ķ���!\n");
				else{
					if(now->is_used){
						printf("\n�÷����Ѿ���ѡ�ˣ�\n");
					}
					else{
						now->is_used=1;
						printf("\nѡ��ɹ���\n");
					}
				}
				break;
			}
			case 6:{system("cls");
				printf("��������ѡ�ķ��ݵı�ţ�\n");
				scanf("%s",a);
				del(a);
				update();
				printf("ɾ���ɹ�\n\n");
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

pf Amuse_readfile() //��ȡ�ļ������ر�ͷ
{
    FILE *fp;
    pf head=NULL;  //ͷָ��
    pf p1,p2;
    int i=0;  //��¼�ڵ���
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

                head=p1;   //ͷ
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
        printf("���ܴ��ļ�");
    }
    fclose(fp);
    return head;
}
   void print_facilities(){

        pf now = Amuse_readfile();
        system("cls");
        while(now!=NULL){
            printf("  ������ʩ�������ǣ�%s\n",now->name);
            printf("  ������ʩ������������ǣ�%s\n",now->number);

            now=now->next;
            printf("\n");
        }

    }
    void save_Amuse(pf p){
        FILE *fp;
        fp=fopen("facilities.txt","a+");
        if (fp==NULL)
        {
            printf("���ܴ��ļ���\n");
        }
        else
        {
            fprintf(fp,"%s %s\n",p->name,p->number);
            printf("��Ϣ�Ѵ��棡\n");
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

        printf("�������½���ʩ������");
        scanf("%s",&p2->name);
        printf("�������½���ʩ��ʹ������");
        scanf("%s",&p2->number);
        save_Amuse(p2);
        system("cls");
        return 0;

    }

    void delete(){

    system("cls");
    printf("       ɾ����ʩ\n");
    printf("---------------------\n");
    char num[10];
    pf head=Amuse_readfile();
    pf p1=head;
    pf p2=p1->next;
    printf("��������Ҫɾ������ʩ����\n");
    scanf("%s",num);
    int found=0;
    while(p2!=NULL)
    {
        if(strcmp(p2->name,num)==0)
        {
            p1->next=p2->next;
            printf("��ʩɾ���ɹ���\n");
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
            printf("�޷����ļ����洢ʧ��");

        fclose(fp);
    }
    else
    {
        printf("û���ҵ�����ʩ��");
    }

    }



void amusement(){


    while(1){

    system("cls");

    printf("\n\n");
        printf("\t\t|----------------������ʩ����ϵͳ----------------|\n");
        printf("\t\t|        0   �˳�                                |\n");
        printf("\t\t|        1   �鿴������ʩ                        |\n");
        printf("\t\t|        2   �½�������ʩ                        |\n");
        printf("\t\t|        3   ɾ����ʩ��Ϣ                        |\n");
        printf("\t\t|                                                |\n");
        printf("\t\t|------------------------------------------------|\n");
        printf("\n\t\t����(0-3)���������ѡ��: ");



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

                printf("�޸ù���");
                break;
             }



             system("pause");
             system("cls");
    }
    }}
