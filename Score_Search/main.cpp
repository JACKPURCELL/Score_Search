#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#pragma warning(disable : 6031)

#define MAX_SNO 12
#define MAX_CNO 12
#define MAX_SNAME 10
#define MAX_CNAME 10
#define MAX_SEX 4
#define MAX_MAJOR 20
#define MAX_SIZE 30

int Stu_Count=0, Cou_Count=0, CG_Count=0, SG_Count=0;


typedef struct Student
{
	char sno[12];
	char sname[50];
	char sex[10];
	char major[50];
} student;

typedef struct Studentlist
{
	student data;
	struct Studentlist* next;
}studentlist;


typedef struct Course
{
	char cno[12];
	char cname[50];
	int classhours;
} course;

typedef struct Courselist
{
	course data;
	struct Courselist* next;
}courselist;

typedef struct CourseGrade
{
	char sno[12];
	char cno[12];
	int score;
} courseGrade;

typedef struct CourseGradelist
{
	courseGrade data;
	struct CourseGradelist* next;
}courseGradelist;

typedef struct StudentGrade
{
	char sno[12];
	char cno[12];
	char major[50];
	char sname[50];
	char cname[50];
	int score;
} studentGrade;

typedef struct StudentGradelist
{
	studentGrade data;
	struct StudentGradelist* next;
}studentGradelist;

typedef struct Qhead
{
	studentGrade data[30];
	int  front;
	int rear;
}qhead;

//--------------------------------------------------------------------
//�����Ʒ�ļ��Ƿ���ڻ����Ƿ�Ϊ��
//--------------------------------------------------------------------
bool check_nullfile(void)
{

	FILE *fp = fopen("student.dat", "r");
	if (!fp) {
		printf("��Ʒ��Ϣ��ʼ���ļ������ڣ�����Ϊ���½�һ��.\n");
		FILE *fp = fopen("student.dat", "w");
		fclose(fp);
		return false;
	}
	else {
		int temp;
		int res = fscanf(fp, "%d", &temp);
		fclose(fp);
		if (res <= 0)
			return false;
		else
			return true;
	}
}

//--------------------------------------------------------------------
//���ж�ȡ�������Ϣ
//--------------------------------------------------------------------
int read_line(char str[], int n)
{
	int ch, i = 0;

	while (isspace(ch = getchar()))
		;
	while (ch != '\n' && ch != EOF) {
		if (i < n)
			str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}

//--------------------------------------------------------------------
//����Ļ�����ѧ����Ϣ
//--------------------------------------------------------------------
void OutputS(studentlist* S) {
	if (Stu_Count == 0) {
		printf("��ѧ����Ϣ���Զ��˳�!");
		return;
	}
	studentlist* cur;
	cur = S->next;
	for (; cur != NULL; cur = cur->next) {//���������ݽ��ж�ȡ
		printf("%s\t%s\t%s\t%s\n", cur->data.sno, cur->data.sname, cur->data.sex,cur->data.major);
	}
}


//--------------------------------------------------------------------
//ð������ʵ�ֶ�ѧ������ڵ������
//--------------------------------------------------------------------
void bubble_sort_S(studentlist** S) {
	if (Stu_Count == 0) {
		printf("��ѧ����Ϣ���Զ��˳�!");
		return;
	}
	int N = 0;
	studentlist* p, * prev, * cur, * t;

	p = (*S)->next;
	prev = (*S);
	cur = (*S)->next;
	while (p)
	{
		p = p->next;
		N++;
	}
	for (int j = 0; j < N - 1; j++)
	{
		prev = (*S);
		cur = (*S)->next;
		for (int k = 0; k < N - j - 1; k++) {

			if (strcmp(cur->data.sno , cur->next->data.sno)>0) {
				t = cur;
				cur = cur->next;
				t->next = cur->next;
				prev->next = cur;
				cur->next = t;
			}
			if (cur->next->next != NULL) {
				prev = cur;
				cur = cur->next;
			}
			else {
				break;
			}
		}
	}
}


//--------------------------------------------------------------------
//ð������ʵ�ֶԳɼ�����ڵ�ĳɼ�����
//--------------------------------------------------------------------
void bubble_sort_SCORE(studentGradelist** SG) {
	if (SG_Count == 0) {
		printf("�޳ɼ���Ϣ���Զ��˳�!");
		return;
	}
	int N = 0;
	studentGradelist* p, * prev, * cur, * t;

	p = (*SG)->next;
	prev = (*SG);
	cur = (*SG)->next;
	while (p)
	{
		p = p->next;
		N++;
	}
	for (int j = 0; j < N - 1; j++)
	{
		prev = (*SG);
		cur = (*SG)->next;
		for (int k = 0; k < N - j - 1; k++) {

			if (cur->data.score< cur->next->data.score) {
				t = cur;
				cur = cur->next;
				t->next = cur->next;
				prev->next = cur;
				cur->next = t;
			}
			if (cur->next->next != NULL) {
				prev = cur;
				cur = cur->next;
			}
			else {
				break;
			}
		}
	}
}

//--------------------------------------------------------------------
//ð������ʵ�ֶԿγ�����ڵ������
//--------------------------------------------------------------------
void bubble_sort_C(courselist** C) {
	if (Cou_Count == 0) {
		printf("�޿γ���Ϣ���Զ��˳�!");
		return;
	}
	int N = 0;
	courselist* p, * prev, * cur, * t;

	p = (*C)->next;
	prev = (*C);
	cur = (*C)->next;
	while (p)
	{
		p = p->next;
		N++;
	}
	for (int j = 0; j < N - 1; j++)
	{
		prev = (*C);
		cur = (*C)->next;
		for (int k = 0; k < N - j - 1; k++) {

			if (strcmp(cur->data.cno ,cur->next->data.cno)>0) {
				t = cur;
				cur = cur->next;
				t->next = cur->next;
				prev->next = cur;
				cur->next = t;
			}
			if (cur->next->next != NULL) {
				prev = cur;
				cur = cur->next;
			}
			else {
				break;
			}
		}
	}
}

//--------------------------------------------------------------------
//��ȡѧ����Ϣ�ļ�student.dat������,����������S
//--------------------------------------------------------------------
void info_stu_init(studentlist **S) {
	FILE *fp = fopen("student.dat", "r");

	studentlist *new_node, *cur;
	cur = (*S);
	while (check_nullfile() && !feof(fp)) {		
		new_node = (studentlist*)malloc(sizeof(studentlist));
		new_node->next = NULL;
		fscanf(fp, "%s", &new_node->data.sno);
		fscanf(fp, "\t%s", &new_node->data.sname);
		fscanf(fp, "\t%s", &new_node->data.sex);
		fscanf(fp, "\t%s\n", &new_node->data.major);

		cur->next = new_node;
		if ((*S)->next == NULL) {
			(*S)->next = cur->next;
		}
		cur = cur->next;
		Stu_Count++;
	}
	if (Stu_Count != 0) {
		fclose(fp);
	}
	bubble_sort_S(S);
	printf("\nѧ����Ϣ�����ļ��ѽ�������%d��ѧ����Ϣ\n", Stu_Count);
	OutputS(*S);
}
//--------------------------------------------------------------------
//���һ��ѧ����Ϣ
//--------------------------------------------------------------------
void info_stu_insert(studentlist **S) {

	studentlist *new_node, *cur;

	new_node = (studentlist*)malloc(sizeof(studentlist));
	if (new_node == NULL) {
		printf("Database is full; can't add more parts.\n");
		return;
	}

	printf("����ѧ����Ϣ:  \n");
	printf("ѧ��: ");
	read_line(new_node->data.sno, MAX_SNO);
	printf("����: ");
	read_line(new_node->data.sname, MAX_SNAME);
	printf("�Ա�: ");
	read_line(new_node->data.sex, MAX_SEX);
	printf("רҵ: ");
	read_line(new_node->data.major, MAX_MAJOR);
	
	cur = (*S)->next;

	if (cur == NULL) {
		(*S)->next = new_node;
		new_node->next = NULL;
	}
	else {
		while (NULL != cur->next) {
			cur = cur->next;
		}
		cur->next = new_node;
		new_node->next = NULL;
	}
	Stu_Count++;
	printf("����ɹ���\n");
}

//--------------------------------------------------------------------
//ѧ����Ϣ�����ļ�student.dat�����̺���������S
//--------------------------------------------------------------------
void info_stu_flush(studentlist **S) {
	if (Stu_Count == 0) {
		printf("��ѧ����Ϣ���Զ��˳�!");
		exit(0);
	}
	FILE *fp;
	fp = fopen("student.dat", "w");
	studentlist *new_node = (*S)->next;
	while (new_node != NULL) {//����������д�뵽student.dat
		fprintf(fp, "%s\t", new_node->data.sno);
		fprintf(fp, "%s\t", new_node->data.sname);
		fprintf(fp, "%s\t", new_node->data.sex);
		fprintf(fp, "%s\n", new_node->data.major);
		new_node = new_node->next;
	}
	if (Stu_Count != 0) {
		printf("%d����Ʒ��Ϣ����student.dat�ļ�\n", Stu_Count);
	}
	else {
		printf("δд���κ���Ʒ��Ϣ��student.dat�ļ�\n");
	}
	Stu_Count = 0;
	fclose(fp);
}

//--------------------------------------------------------------------
//����Ļ������γ���Ϣ
//--------------------------------------------------------------------
void OutputC(courselist* C) {
	if (Cou_Count == 0) {
		printf("��ѧ����Ϣ���Զ��˳�!");
		return;
	}
	courselist* cur;
	cur = C->next;
	for (; cur != NULL; cur = cur->next) {//���������ݽ��ж�ȡ
		printf("%s\t%s\t%d\n", cur->data.cno, cur->data.cname, cur->data.classhours);
	}
}

//--------------------------------------------------------------------
//��ȡ�γ���Ϣ�ļ�course.dat������,����������C
//--------------------------------------------------------------------
void info_cou_init(courselist **C) {
	int i = 0, j = 0;
	FILE *fp = fopen("course.dat", "r");

	courselist *new_node, *cur;
	cur = (*C);
	while (check_nullfile() && !feof(fp)) {		
		new_node = (courselist*)malloc(sizeof(courselist));
		new_node->next = NULL;
		fscanf(fp, "%s", &new_node->data.cno);
		fscanf(fp, "\t%s", &new_node->data.cname);
		fscanf(fp, "\t%d\n", &new_node->data.classhours);

		cur->next = new_node;
		if ((*C)->next == NULL) {
			(*C)->next = cur->next;
		}
		cur = cur->next;
		Cou_Count++;
	}
	if (Cou_Count != 0) {
		fclose(fp);
	}
	bubble_sort_C(C);
	printf("\n�γ���Ϣ�����ļ��ѽ�������%d���γ���Ϣ\n", Cou_Count);
	OutputC(*C);
}

//--------------------------------------------------------------------
//���γ���Ϣ�ļ�course.dat�����̺���������C
//--------------------------------------------------------------------
void info_cou_flush(courselist** C) {
	if (Cou_Count == 0) {
		printf("�޿γ���Ϣ���Զ��˳�!");
		exit(0);
	}
	FILE* fp;
	fp = fopen("course.dat", "w");
	courselist* new_node = (*C)->next;
	while (new_node != NULL) {//����������д�뵽course.dat
		fprintf(fp, "%s\t", new_node->data.cno);
		fprintf(fp, "%s\t", new_node->data.cname);
		fprintf(fp, "%d\n", new_node->data.classhours);
		new_node = new_node->next;
	}
	if (Cou_Count != 0) {
		printf("%d���γ���Ϣ����course.dat�ļ�\n", Cou_Count);
	}
	else {
		printf("δд���κ���Ʒ��Ϣ��course.dat�ļ�\n");
	}
	Cou_Count = 0;
	fclose(fp);
}

//--------------------------------------------------------------------
//��ӿγ���Ϣ
//--------------------------------------------------------------------
void info_cou_insert(courselist**C) {

	courselist *new_node, *cur;

	new_node = (courselist*)malloc(sizeof(courselist));
	if (new_node == NULL) {
		printf("Database is full; can't add more parts.\n");
		return;
	}

	printf("����γ���Ϣ:  \n");
	printf("�γ̺�: ");
	read_line(new_node->data.cno, MAX_CNO);
	printf("�γ�����: ");
	read_line(new_node->data.cname, MAX_CNAME);
	printf("��ʱ��: ");
	scanf("%d", &new_node->data.classhours);

	cur = (*C)->next;

	if (cur == NULL) {
		(*C)->next = new_node;
		new_node->next = NULL;
	}
	else {
		while (NULL != cur->next) {
			cur = cur->next;
		}
		cur->next = new_node;
		new_node->next = NULL;
	}
	Cou_Count++;
	printf("����ɹ���\n");

}



//--------------------------------------------------------------------
//����Ļ������γ̳ɼ���Ϣ
//--------------------------------------------------------------------
void OutputCG(courseGradelist* CG) {
	if (CG_Count == 0) {
		printf("�޳ɼ���Ϣ���Զ��˳�!");
		return;
	}
	courseGradelist* cur;
	cur = CG->next;
	for (; cur != NULL; cur = cur->next) {//���������ݽ��ж�ȡ
		printf("%s\t%s\t%d\n", cur->data.sno, cur->data.cno, cur->data.score);
	}
}

//--------------------------------------------------------------------
//����ʵ�ֶԳɼ�����ڵ������
//--------------------------------------------------------------------
void bubble_sort_CG(courseGradelist** CG) {
	if (CG_Count == 0) {
		printf("����Ʒ��Ϣ���Զ��˳�!");
		return;
	}
	int N = 0;
	courseGradelist* p, * prev, * cur, * t;

	p = (*CG)->next;
	prev = (*CG);
	cur = (*CG)->next;
	while (p)
	{
		p = p->next;
		N++;
	}
	for (int j = 0; j < N - 1; j++)
	{
		prev = (*CG);
		cur = (*CG)->next;
		for (int k = 0; k < N - j - 1; k++) {

			if (strcmp(cur->data.cno, cur->next->data.cno) > 0) {
				t = cur;
				cur = cur->next;
				t->next = cur->next;
				prev->next = cur;
				cur->next = t;
			}
			if (cur->next->next != NULL) {
				prev = cur;
				cur = cur->next;
			}
			else {
				break;
			}

		}
	}

	for (int j = 0; j < N - 1; j++)
	{
		prev = (*CG);
		cur = (*CG)->next;
		for (int k = 0; k < N - j - 1; k++) {

			if (strcmp(cur->data.sno, cur->next->data.sno) > 0 && strcmp(cur->data.cno, cur->next->data.cno) == 0) {
				t = cur;
				cur = cur->next;
				t->next = cur->next;
				prev->next = cur;
				cur->next = t;
			}
			if (cur->next->next != NULL) {
				prev = cur;
				cur = cur->next;
			}
			else {
				break;
			}

		}
	}

	OutputCG(*CG);
}

//--------------------------------------------------------------------
//��ȡ�γ���Ϣ�ļ�courseGrade.dat������,����������CG
//--------------------------------------------------------------------
void info_CG_init(courseGradelist **CG) {
	int i = 0, j = 0;
	FILE *fp = fopen("courseGrade.dat", "r");

	courseGradelist *new_node, *cur;
	cur = (*CG);
	while (check_nullfile() && !feof(fp)) {
		new_node = (courseGradelist*)malloc(sizeof(courseGradelist));
		new_node->next = NULL;
		fscanf(fp, "%s", &new_node->data.sno);
		fscanf(fp, "\t%s", &new_node->data.cno);
		fscanf(fp, "\t%d\n", &new_node->data. score);

		cur->next = new_node;
		if ((*CG)->next == NULL) {
			(*CG)->next = cur->next;
		}
		cur = cur->next;
		CG_Count++;
	}
	if (CG_Count != 0) {
		fclose(fp);
	}	
	printf("\n�γ���Ϣ�����ļ��ѽ�������%d���γ̳ɼ���Ϣ\n", CG_Count);
	bubble_sort_CG(*&CG);

}

//--------------------------------------------------------------------
//���һ���ɼ���Ϣ
//--------------------------------------------------------------------
void info_CG_insert(courseGradelist **CG) {

	courseGradelist *new_node, *cur;

	new_node = (courseGradelist*)malloc(sizeof(courseGradelist));
	if (new_node == NULL) {
		printf("Database is full; can't add more parts.\n");
		return;
	}

	printf("����ѧ����Ϣ:  \n");
	printf("ѧ��: ");
	read_line(new_node->data.sno, MAX_SNO);
	printf("�γ̱��: ");
	read_line(new_node->data.cno, MAX_CNO);
	printf("�ɼ�: ");
	scanf("%d", &new_node->data.score);

	cur = (*CG)->next;

	if (cur == NULL) {
		(*CG)->next = new_node;
		new_node->next = NULL;
	}
	else {
		while (NULL != cur->next) {
			cur = cur->next;
		}
		cur->next = new_node;
		new_node->next = NULL;
	}
	CG_Count++;
	printf("����ɹ���\n");
}

//--------------------------------------------------------------------
//���ɼ������ļ�courseGrade.dat�����̺���������CG
//--------------------------------------------------------------------
void info_CG_flush(courseGradelist **CG) {
	if (CG_Count == 0) {
		printf("��ѧ����Ϣ���Զ��˳�!");
		exit(0);
	}
	FILE* fp;
	fp = fopen("courseGrade.dat", "w");
	courseGradelist* new_node = (*CG)->next;
	while (new_node != NULL) {//����������д�뵽student.dat
		fprintf(fp, "%s\t", new_node->data.sno);
		fprintf(fp, "%s\t", new_node->data.cno);
		fprintf(fp, "%d\n", new_node->data.score);
		new_node = new_node->next;
	}
	if (CG_Count != 0) {
		printf("%d���ɼ���Ϣ����courseGrade.dat�ļ�\n", CG_Count);
	}
	else {
		printf("δд���κ���Ʒ��Ϣ��courseGrade.dat�ļ�\n");
	}
	CG_Count = 0;
	fclose(fp);
}

//--------------------------------------------------------------------
//����Ļ�����ѧ���ɼ���Ϣ
//--------------------------------------------------------------------
void OutputSG(studentGradelist* SG) {
	if (SG_Count == 0) {
		printf("�޳ɼ���Ϣ���Զ��˳�!\n");
		return;
	}
	studentGradelist* cur;
	cur = SG->next;
	for (; cur != NULL; cur = cur->next) {//���������ݽ��ж�ȡ
		printf("%s\t%s\t%s\t%s\t%s\t%d\n", cur->data.sno, cur->data.sname, cur->data.major,cur->data.cno, cur->data.cname, cur->data.score);
	}
}

//--------------------------------------------------------------------
//����ʵ�ֶ�ѧ���ɼ�����ڵ������
//--------------------------------------------------------------------
void bubble_sort_SG(studentGradelist** SG) {
	if (CG_Count == 0) {
		printf("�޳ɼ���Ϣ���Զ��˳�!");
		return;
	}
	int N = 0;
	studentGradelist* p, * prev, * cur, * t;

	p = (*SG)->next;
	prev = (*SG);
	cur = (*SG)->next;
	while (p)
	{
		p = p->next;
		N++;
	}
	for (int j = 0; j < N - 1; j++)
	{
		prev = (*SG);
		cur = (*SG)->next;
		for (int k = 0; k < N - j - 1; k++) {

			if (strcmp(cur->data.sno, cur->next->data.sno) > 0) {
				t = cur;
				cur = cur->next;
				t->next = cur->next;
				prev->next = cur;
				cur->next = t;
			}
			if (cur->next->next != NULL) {
				prev = cur;
				cur = cur->next;
			}
			else {
				break;
			}

		}
	}

	for (int j = 0; j < N - 1; j++)
	{
		prev = (*SG);
		cur = (*SG)->next;
		for (int k = 0; k < N - j - 1; k++) {

			if (cur->data.score< cur->next->data.score && strcmp(cur->data.sno, cur->next->data.sno) == 0) {
				t = cur;
				cur = cur->next;
				t->next = cur->next;
				prev->next = cur;
				cur->next = t;
			}
			if (cur->next->next != NULL) {
				prev = cur;
				cur = cur->next;
			}
			else {
				break;
			}

		}
	}

	printf("��ǰ��%d���ɼ���Ϣ:", N);
}

//--------------------------------------------------------------------
//�����γ̳ɼ�
//--------------------------------------------------------------------
void SG_create(studentGradelist** SG, courselist** C, courseGradelist** CG, studentlist** S) {
	int i = 0, j = 0;
	
	studentGradelist* new_node, * cur;
	courselist* cur_C;
	courseGradelist* cur_CG;
	studentlist* cur_S;
	cur = (*SG), cur_C = (*C)->next; cur_CG = (*CG)->next, cur_S = (*S)->next;

	for (i = 0; i < CG_Count; i++) {
		new_node = (studentGradelist*)malloc(sizeof(studentGradelist));
		new_node->next = NULL;

		strcpy(new_node->data.sno, cur_CG->data.sno);
		strcpy(new_node->data.cno, cur_CG->data.cno);
		new_node->data.score=cur_CG->data.score;

		for (cur_S = (*S); cur_S != NULL;) {
			if (strcmp(new_node->data.sno, cur_S->data.sno) == 0) {
				strcpy(new_node->data.sname, cur_S->data.sname);
				strcpy(new_node->data.major, cur_S->data.major);
				break;
			}
			cur_S = cur_S->next;
		}

		for(cur_C=(*C); cur_C != NULL;) {
			if (strcmp(new_node->data.cno, cur_C->data.cno) == 0) {
				strcpy(new_node->data.cname, cur_C->data.cname);
				break;
		}
			cur_C = cur_C->next; 
		}
		cur->next = new_node;
		if ((*SG)->next == NULL) {
			(*SG)->next = cur->next;
		}
		cur = cur->next;
		cur_CG = cur_CG->next;
		SG_Count++;
	}
		
	
	bubble_sort_SG(SG);

	FILE* fp;
	fp = fopen("studentGrade.dat", "w");
	new_node = *SG;
	while (new_node != NULL) {
		fprintf(fp, "%s\t", new_node->data.sno);
		fprintf(fp, "%s\t", new_node->data.sname);
		fprintf(fp, "%s\t", new_node->data.major);
		fprintf(fp, "%s\t", new_node->data.cno);
		fprintf(fp, "%s\t", new_node->data.cname);
		fprintf(fp, "%d\n", new_node->data.score);
		new_node = new_node->next;
	}
	if (SG_Count != 0) {
		printf("%d����Ʒ��Ϣ����studentGrade.dat�ļ�\n", SG_Count);
	}
	else {
		printf("δд���κ���Ʒ��Ϣ��studentGrade.dat�ļ�\n");
	}
	fclose(fp);
	OutputSG(*SG);
}


//--------------------------------------------------------------------
//����һ���ɼ���Ϣ
//--------------------------------------------------------------------
void search_score(studentGradelist** SG) {
	if(SG_Count == 0) {
		printf("�޳ɼ���Ϣ���Զ��˳�!");
		return;
	}
	char cno[MAX_CNO];
	bubble_sort_SG(SG);
	studentGradelist* prev, * cur;
	printf("������Ҫ���ҵĿγ̺�(-1�˳�����): ");
	scanf("%s", &cno);
	if (!strcmp(cno, "-1\0")) {
		printf("���˳�!");
		return;
	}
	for (cur = (*SG)->next;cur!=NULL; cur = cur->next) {
		if (!strcmp(cno, cur->data.cno)) break;
		else if (strcmp(cno, cur->data.cno) && cur->next == NULL) {
			printf("�γ̺Ų����ڣ�");
			return;
		}
	}	
	bubble_sort_SCORE(SG);
	for (cur = (*SG)->next; cur != NULL; cur = cur->next) {
		if (!strcmp(cno, cur->data.cno)) {
			printf("%s\t%s\t%s\t%s\t%s\t%d\n", cur->data.sno, cur->data.sname, cur->data.major, cur->data.cno, cur->data.cname, cur->data.score);
		}
	}


}

//--------------------------------------------------------------------
//����<60�ɼ���Ϣ
//--------------------------------------------------------------------
void search_60score(studentGradelist** SG) {
	if (SG_Count == 0) {
		printf("�޳ɼ���Ϣ���Զ��˳�!");
		return;
	}
	char cno[MAX_CNO];
	bubble_sort_SG(SG);
	studentGradelist* prev, * cur;
	printf("������Ҫ���ҵĿγ̺�(-1�˳�����): ");
	scanf("%s", &cno);
	if (!strcmp(cno, "-1\0")) {
		printf("���˳�!");
		return;
	}

	for (cur = (*SG)->next; cur != NULL; cur = cur->next) {
		if (!strcmp(cno, cur->data.cno)) break;
		else if (strcmp(cno, cur->data.cno) && cur->next == NULL) {
			printf("�γ̺Ų����ڣ�\n");
			return;
		}
	}	

	bubble_sort_SCORE(SG);
	int count=0;
	for (cur = (*SG)->next; cur != NULL; cur = cur->next) {
		if (!strcmp(cno, cur->data.cno) && cur->data.score < 60) {
			count++;
		}
	}
	if(count==0){
		printf("��<60�ĳɼ���Ϣ! \n");
		return;
	}
	for (cur = (*SG)->next; cur != NULL; cur = cur->next) {
		if (!strcmp(cno, cur->data.cno) && cur->data.score < 60) {
			printf("%s\t%s\t%s\t%s\t%s\t%d\n", cur->data.sno, cur->data.sname, cur->data.major, cur->data.cno, cur->data.cname, cur->data.score);
		}
	}
}

//--------------------------------------------------------------------
//ѧ����Ϣ���������µ�����
//--------------------------------------------------------------------
void reverse(studentlist** S)
{
	studentlist rever[20];
	int top = -1;
	studentlist* new_node, * cur;
	new_node=(studentlist*)malloc(sizeof(studentlist));
	cur = (*S)->next;

	while (cur != NULL) {
		rever[++top] =*cur;
		cur = cur->next;
	}
	while (top != -1) {
		printf("%s\t%s\t%s\t%s\n", (&rever[top])->data.sno, (&rever[top])->data.sname, (&rever[top])->data.sex, (&rever[top])->data.major);
		top--;
	}
}


//--------------------------------------------------------------------
//��ʽ��������
//--------------------------------------------------------------------
void bubble_sort_Q(qhead* Q) {
	if (Q->rear == 0) {
		printf("�޳ɼ���Ϣ���Զ��˳�!");
		return;
	}
	int N = Q->rear , cur = 0;
	StudentGrade* t;
	t = (studentGrade*)malloc(sizeof(studentGrade));

	for (int j = 0; j < N - 1; j++)
	{
		cur = 0;
		for (int k = 0; k < N - j - 1; k++) {

			if (strcmp(Q->data[cur].sno, Q->data[cur + 1].sno) > 0) {
				*t = Q->data[cur];
				Q->data[cur] = Q->data[cur+1];
				Q->data[cur + 1] = *t;
			}
			if (cur != Q->rear - 2) {
				cur++;
			}
			else {
				break;
			}
		}
	}

	for (int j = 0; j < N - 1; j++)
	{
		cur = 0;
		for (int k = 0; k < N - j - 1; k++) {

			if (Q->data[cur].score < Q->data[cur + 1].score && strcmp(Q->data[cur].sno, Q->data[cur + 1].sno) == 0) {
				*t = Q->data[cur];
				Q->data[cur] = Q->data[cur+1];
				Q->data[cur + 1] = *t;
			}
			if (cur != Q->rear - 2) {
				cur++;
			}
			else {
				break;
			}
		}
	}

}

//--------------------------------------------------------------------
//��ʽ����
//--------------------------------------------------------------------
void listqueue(courselist** C, courseGradelist** CG, studentlist** S,qhead *Q) {
	int num, i, j;
	Q->front = 0;
	Q->rear = 0;

	studentGrade* new_node;
	new_node = (studentGrade*)malloc(sizeof(studentGrade));
	courselist* cur_C;
	courseGradelist* cur_CG;
	studentlist* cur_S;
	cur_C = (*C)->next; cur_CG = (*CG)->next, cur_S = (*S)->next;

	for (i = 0; i < CG_Count; i++) {

		strcpy(new_node->sno, cur_CG->data.sno);
		strcpy(new_node->cno, cur_CG->data.cno);
		new_node->score = cur_CG->data.score;

		for (cur_S = (*S); cur_S != NULL;) {
			if (strcmp(new_node->sno, cur_S->data.sno) == 0) {
				strcpy(new_node->sname, cur_S->data.sname);
				strcpy(new_node->major, cur_S->data.major);
				break;
			}
			cur_S = cur_S->next;
		}

		for (cur_C = (*C); cur_C != NULL;) {
			if (strcmp(new_node->cno, cur_C->data.cno) == 0) {
				strcpy(new_node->cname, cur_C->data.cname);
				break;
			}
			cur_C = cur_C->next;
		}

		Q->data[Q->rear]=*new_node;
		if (Q->rear <MAX_SIZE) {
			Q->rear = (Q->rear + 1) ;
		}
		else {
			return;
		}
		cur_CG = cur_CG->next;
	}



	bubble_sort_Q(Q);


	FILE* fp;
	fp = fopen("studentGrade.dat", "w");
	int new_int = 0;

	while (new_int != Q->rear) {
		fprintf(fp, "%s\t", Q->data[new_int].sno);
		fprintf(fp, "%s\t", Q->data[new_int].sname);
		fprintf(fp, "%s\t", Q->data[new_int].major);
		fprintf(fp, "%s\t", Q->data[new_int].cno);
		fprintf(fp, "%s\t", Q->data[new_int].cname);
		fprintf(fp, "%d\n", Q->data[new_int]. score);
		new_int++;
	}
	if (new_int != 0) {
		printf("%d���ɼ���Ϣ����studentGrade.dat�ļ�\n", new_int);
	}
	else {
		printf("δд���κγɼ���Ϣ��studentGrade.dat�ļ�\n");
	}
	SG_Count = 0;
	fclose(fp);

	for (int i = 0; i < Q->rear ; i++) {
		printf("%s\t%s\t%s\t%s\t%s\t%d\n", Q->data[i].sno, Q->data[i].sname, Q->data[i].major, Q->data[i].cno, Q->data[i].cname, Q->data[i].score);
	}
}


int main(void) {

	//char code;
	studentlist *S;
	S = (studentlist*)malloc(sizeof(studentlist));
	S->next = NULL;

	courselist *C;
	C = (courselist*)malloc(sizeof(courselist));
	C->next = NULL;

	courseGradelist *CG;
	CG = (courseGradelist*)malloc(sizeof(courseGradelist));
	CG->next = NULL;

	StudentGradelist* SG;
	SG = (StudentGradelist*)malloc(sizeof(StudentGradelist));
	SG->next = NULL;

	qhead* Q;
	Q = (qhead*)malloc(sizeof(qhead));

	char code;
	for (;;) {

		printf("\n+++++++++++++++https://github.com/JACKPURCELL+++++++++++++++\n"
			"(1) ����10��ѧ����¼���������ļ�student.dat�У�\n"
			"(2) ����3�ſγ���Ϣ��¼���������ļ�course.dat�У�\n"
			"(3) ��������10λͬѧ�Ŀ��Գɼ����ļ�courseGrade.dat�У�\n"
			"(4) ���ļ���ȡѧ����Ϣ���γ���Ϣ���ɼ���Ϣ��\n"
			"(5) ��ѯ����ѧ�����пγ̵Ŀ��Գɼ���\n"
			"(6) ��ѯָ���γ̺ŵ�����ѧ���Ŀ��Գɼ���\n"
			"(7) ��ѯָ���γ̺ŵĿ��Գɼ�С��60�ֵ�ѧ���ɼ���Ϣ��\n"
			"(8) ʹ��ջʵ��ѧ����Ϣ���������µ�����\n"
			"(9) ʹ����ʽ����)��ѯ����ѧ�����пγ̵Ŀ��Գɼ���\n"
			"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		scanf(" %c", &code);
		while (getchar() != '\n')
			;
		switch (code) {
		case '1':
			for (int i = 0; i < 10; i++) {//����ʮ��ѧ����Ϣ
				info_stu_insert(&S);
			}			
			info_stu_flush(&S); 
			break;
		case '2':
			for (int i = 0; i < 3; i++) {//�������ſγ���Ϣ
				info_cou_insert(&C);
			}
			info_cou_flush(&C); 
			break;
		case '3':
			for (int i = 0; i < MAX_SIZE; i++) {//����ɼ���Ϣ
				info_CG_insert(&CG);
			}
			info_CG_flush(&CG);
			break;
		case '4':
			info_stu_init(&S);
			info_cou_init(&C);
			info_CG_init(&CG);
			break;
		case '5':
			SG_create(&SG, &C, &CG, &S);
			break;
		case '6':
			search_score(&SG);
			break;
		case '7':
			search_60score(&SG);
			break;
		case '8':
			reverse(&S);
			break;
		case '9':
			listqueue(&C, &CG, &S, Q);
			break;
		}
	}
	return 0;
}
