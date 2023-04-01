#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcpy()�Լ� ������� string.h ������� �߰�

typedef char Element; // ����ȯ�� �����ϰ� �ϱ� ���� Element ����
typedef struct LinkedNode { // ��� ����ü 
	Element schedule[256]; // �ִ� 256���� ���ڿ��� ������ �� ����
	struct LinkedNode* link; // ����� link�μ� �ٸ� ����� �����
} Node;

Node* top = NULL; // stack�� top(�� �� ���������) ���� �� NULL�� �ʱ�ȭ
Node* front = NULL; // queue�� front(����) ���� �� NULL������ �ʱ�ȭ
Node* rear = NULL; // queue�� rear(�Ĵ�)���� �� NULL������ �ʱ�ȭ

void error(char* str) // ���� �޽��� ��� �Լ�
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};

/*���� ���� �Լ�*/
// ���� ���� �˻� �Լ� 
int is_empty() { return top == NULL; } // ���� �� ���� NULL���̸� ������� -> 1 ��ȯ 

// ���� �ʱ�ȭ �Լ�
void init_stack() { top = NULL; } 

// ���� ũ�� ��ȯ �Լ�
int size()
{
	Node* p;
	int count = 0;
	for (p = top; p != NULL; p = p->link)
		count++; // top�������� ������ node�� link�� ���� �� ������ count
	return count; 
}

// ���ÿ� ��Ҹ� �ִ� �Լ�
void push(Element* e)
{
	Node* p = (Node*)malloc(sizeof(Node)); 
	strcpy(p->schedule, e); // strcpy()�Լ� ����Ͽ� �Լ��� �μ��� ���� ���ڿ��� p ������ �ʵ忡 ����
	p->link = top; // push�� ��尡 ������ top�� �ǹǷ� link���� top�� ����
	top = p; // top�� push�� ����� p ����
}

// ���� ��Ҹ� �����ϰ� �� ���� ��ȯ�ϴ� �Լ�(���ڿ� ��ȯ)
Element* pop()
{
	Node* p; 
	Element* e = "\0"; // �����ϰ� ��ȯ���� ���� top���� ������� �� ���ڿ� ������ e ���� �� �ʱ�ȭ
	if (is_empty()) // ����������� �˻�
		error("���� ���� ����\n");
	p = top; // p�� top ����
	top = p->link; // top�� ��� ���� �� ���Ӱ� top�� �� ��Ҹ� ����Ű���� ��
	strcpy(e, p->schedule); // ������ ����� ������ �ʵ尪(���ڿ�)�� e�� ���� 
	free(p); 
	return e; // ����� ���ڿ� ��ȯ
}

// ���� ��� ���� ���� top�� �����͸� ��ȯ�ϴ� �Լ�(���ڿ� ��ȯ)
Element* peek()
{
	if (is_empty()) // ����������� �˻�
		error("���� ���� ����\n");
	return top->schedule; // top���� �������ʵ�(���ڿ�) ��ȯ
}

// ���� ���ִ� �Լ�
void destroy_stack()
{
	while (is_empty() == 0)
		pop(); // ������°� �� ������ pop();
}

// ���� ���� ������ ��� ����ϴ� �Լ�
void print_stack()
{
	Node* p;
	for (p = top; p != NULL; p = p->link)
		printf("%s\n", p->schedule); // p�� top�������� ��ũ�� ���� ������ �� ����� �����Ͱ�(���ڿ�)�� ���
}

/*ť ���� �Լ�*/
// ť ���� �˻� �Լ�
int is_queue_empty() { return front == NULL; } // ť�� ������ NULL���� ��� �������

// ť �ʱ�ȭ �Լ�
void init_queue() { front = rear = NULL; } 

// ť ũ�� ��ȯ �Լ�
int queue_size()
{
	Node* p;
	int count = 0;
	for (p = front; p != NULL; p = p->link)
		count++; // front�������� ������ node�� link�� ���� �� ������ count
	return count;
}

// ť�� ��Ҹ� �ִ� �Լ�
void enqueue(Element* e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	strcpy(p->schedule, e); // �Լ��� �μ��� ���� ���ڿ��� p ����� ������ �ʵ忡 ����
	p->link = NULL; 

	if (is_queue_empty()) front = rear = p; // ���� ������¶�� ����=�Ĵ�=p�� ��(���� ť�� ��尡 �� ���̹Ƿ�)
	else { // ������°� �ƴ϶��
		rear->link = p; // �Ĵܰ� p�� ��ũ
		rear = p; // p�� �Ĵ��� ��
	}
}

// ť ��Ҹ� �����ϰ� �� ���� ��ȯ�ϴ� �Լ�(���ڿ� ��ȯ)
Element* dequeue()
{
	Node* p;
	Element* e = "\0"; // �����ϰ� ��ȯ���� ���� rear���� ������� �� ���ڿ� ������ e ���� �� �ʱ�ȭ
	if (is_queue_empty()) // ����������� �˻�
		error("ť ���� ����\n");
	p = front; // p�� ���� ����
	front = front->link; // ������ ��ũ ����
	if (front == NULL) rear = NULL; // ���� ������ ������ null���̶�� �Ĵܵ� NULL���� ������°� ��
	strcpy(e, p->schedule); // ������ ����� ������ �ʵ尪(���ڿ�)�� e�� ���� 
	free(p);
	return e; // ����� ���ڿ� ��ȯ
}

// ť ��� ���� ���� front�� �����͸� ��ȯ�ϴ� �Լ�(���ڿ� ��ȯ)
Element* queue_peek()
{
	if (is_queue_empty()) // ����������� �˻�
		error("ť ���� ����\n");
	return front->schedule; // front���� �������ʵ�(���ڿ�) ��ȯ
}

// ť ���ִ� �Լ�
void destroy_queue()
{
	while (is_queue_empty() == 0)
		dequeue(); // ������°� �� ������ dequeue();
}

// ť ���� ������ ��� ����ϴ� �Լ�
void print_queue()
{
	Node* p;
	for (p = front; p != NULL; p = p->link)
		printf("%s\n", p->schedule); // p�� front�������� ��ũ�� ���� ������ �� ����� �����Ͱ�(���ڿ�)�� ���
}


int main(int argc, char* argv[])
{
	char command; 
	Node Schedule;
	int sorq; // stack�� ����� ������, queue�� ����� ������ ������ ���� ����

	printf("\n");

	if ((argc != 2)) // �����Լ��� ������ ������ 2���� �ƴ϶��(�������ϸ�, üũ��)
	{
		printf("invalid input(please input like this -> exefilename modenumber)\n");
		exit(1);
	}

	sorq = atoi(argv[1]); // ������ �������(0) ť�� �������(1) �����Լ��� argument�� �Է¹޾� int������ ����

	if (sorq == 0) // 0�� argument�� �Է¹��� �� �������� �����ٷ� ����(�Է��� �������� ��µ�)
	{
		init_stack(); // ���� �ʱ�ȭ
		do {
			printf(" i:(input the schedule) s:(Show me the schedule) q:(quit the program) : ");
			scanf("%c", &command);
			rewind(stdin);
			printf("\n");

			if (command == 'i') {
				printf("  input your schedule : ");
				fgets(Schedule.schedule, 256, stdin);
				push(Schedule.schedule);
				printf("\n");
			}
			else if (command == 's') {
				print_stack();
			}
			else if (command == 'q') {
				printf("�����ٷ��� �����մϴ�.\n");
				break;
			}
			else {
				printf("�߸� �Է��Ͽ����ϴ�.\n");
				printf("\n");
			}
		} while (command != 'q'); // do while���� ����Ͽ� command ���� ���� �����ٷ��� ��� �����ǵ��� ��
		destroy_stack(); // ���� �ı�
	}

	else if(sorq == 1) // 0�� argument�� �Է¹��� �� ť�� �����ٷ� ����(�Է��� ������� ��µ�)
	{
		init_queue(); // ť �ʱ�ȭ
		do {
			printf(" i:(input the schedule) s:(Show me the schedule) q:(quit the program) : ");
			scanf("%c", &command);
			rewind(stdin);
			printf("\n");

			if (command == 'i') {
				printf("  input your schedule : ");
				fgets(Schedule.schedule, 256, stdin);
				enqueue(Schedule.schedule);
				printf("\n");
			}
			else if (command == 's') {
				print_queue();
			}
			else if (command == 'q') {
				printf("�����ٷ��� �����մϴ�.\n");
				break;
			}
			else {
				printf("�߸� �Է��Ͽ����ϴ�.\n");
				printf("\n");
			}
		} while (command != 'q'); // do while���� ����Ͽ� command ���� ���� �����ٷ��� ��� �����ǵ��� ��
		destroy_queue(); // ť �ı�
	}

	return 0;
}

