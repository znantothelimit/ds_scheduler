#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcpy()함수 사용위해 string.h 헤더파일 추가

typedef char Element; // 형변환을 용이하게 하기 위해 Element 정의
typedef struct LinkedNode { // 노드 구조체 
	Element schedule[256]; // 최대 256자의 문자열을 저장할 수 있음
	struct LinkedNode* link; // 노드의 link로서 다른 노드들과 연결됨
} Node;

Node* top = NULL; // stack의 top(맨 위 헤드포인터) 선언 및 NULL값 초기화
Node* front = NULL; // queue의 front(전단) 선언 및 NULL값으로 초기화
Node* rear = NULL; // queue의 rear(후단)선언 및 NULL값으로 초기화

void error(char* str) // 에러 메시지 출력 함수
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};

/*스택 연산 함수*/
// 스택 공백 검사 함수 
int is_empty() { return top == NULL; } // 스택 맨 위가 NULL값이면 공백상태 -> 1 반환 

// 스택 초기화 함수
void init_stack() { top = NULL; } 

// 스택 크기 반환 함수
int size()
{
	Node* p;
	int count = 0;
	for (p = top; p != NULL; p = p->link)
		count++; // top에서부터 시작한 node가 link를 따라 갈 때마다 count
	return count; 
}

// 스택에 요소를 넣는 함수
void push(Element* e)
{
	Node* p = (Node*)malloc(sizeof(Node)); 
	strcpy(p->schedule, e); // strcpy()함수 사용하여 함수의 인수로 받은 문자열을 p 데이터 필드에 복사
	p->link = top; // push된 노드가 스택의 top이 되므로 link값에 top값 대입
	top = p; // top에 push된 요소인 p 대입
}

// 스택 요소를 삭제하고 그 값을 반환하는 함수(문자열 반환)
Element* pop()
{
	Node* p; 
	Element* e = "\0"; // 삭제하고 반환해줄 현재 top값을 저장시켜 줄 문자열 포인터 e 선언 후 초기화
	if (is_empty()) // 공백상태인지 검사
		error("스택 공백 에러\n");
	p = top; // p애 top 대입
	top = p->link; // top이 요소 삭제 후 새롭게 top이 될 요소를 가리키도록 함
	strcpy(e, p->schedule); // 삭제될 노드의 데이터 필드값(문자열)을 e로 복사 
	free(p); 
	return e; // 복사된 문자열 반환
}

// 스택 요소 삭제 없이 top의 데이터를 반환하는 함수(문자열 반환)
Element* peek()
{
	if (is_empty()) // 공백상태인지 검사
		error("스택 공백 에러\n");
	return top->schedule; // top값의 데이터필드(문자열) 반환
}

// 스택 없애는 함수
void destroy_stack()
{
	while (is_empty() == 0)
		pop(); // 공백상태가 될 때까지 pop();
}

// 스택 안의 데이터 요소 출력하는 함수
void print_stack()
{
	Node* p;
	for (p = top; p != NULL; p = p->link)
		printf("%s\n", p->schedule); // p가 top에서부터 링크를 따라가 끝까지 각 노드의 데이터값(문자열)을 출력
}

/*큐 연산 함수*/
// 큐 공백 검사 함수
int is_queue_empty() { return front == NULL; } // 큐의 전단이 NULL값일 경우 공백상태

// 큐 초기화 함수
void init_queue() { front = rear = NULL; } 

// 큐 크기 반환 함수
int queue_size()
{
	Node* p;
	int count = 0;
	for (p = front; p != NULL; p = p->link)
		count++; // front에서부터 시작한 node가 link를 따라 갈 때마다 count
	return count;
}

// 큐에 요소를 넣는 함수
void enqueue(Element* e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	strcpy(p->schedule, e); // 함수의 인수로 받은 문자열을 p 노드의 데이터 필드에 복사
	p->link = NULL; 

	if (is_queue_empty()) front = rear = p; // 만약 공백상태라면 전단=후단=p가 됨(원형 큐에 노드가 한 개이므로)
	else { // 공백상태가 아니라면
		rear->link = p; // 후단과 p를 링크
		rear = p; // p가 후단이 됨
	}
}

// 큐 요소를 삭제하고 그 값을 반환하는 함수(문자열 반환)
Element* dequeue()
{
	Node* p;
	Element* e = "\0"; // 삭제하고 반환해줄 현재 rear값을 저장시켜 줄 문자열 포인터 e 선언 후 초기화
	if (is_queue_empty()) // 공백상태인지 검사
		error("큐 공백 에러\n");
	p = front; // p에 전단 대입
	front = front->link; // 전단의 링크 수정
	if (front == NULL) rear = NULL; // 만약 수정된 전단이 null값이라면 후단도 NULL값인 공백상태가 됨
	strcpy(e, p->schedule); // 삭제될 노드의 데이터 필드값(문자열)을 e로 복사 
	free(p);
	return e; // 복사된 문자열 반환
}

// 큐 요소 삭제 없이 front의 데이터를 반환하는 함수(문자열 반환)
Element* queue_peek()
{
	if (is_queue_empty()) // 공백상태인지 검사
		error("큐 공백 에러\n");
	return front->schedule; // front값의 데이터필드(문자열) 반환
}

// 큐 없애는 함수
void destroy_queue()
{
	while (is_queue_empty() == 0)
		dequeue(); // 공백상태가 될 때까지 dequeue();
}

// 큐 안의 데이터 요소 출력하는 함수
void print_queue()
{
	Node* p;
	for (p = front; p != NULL; p = p->link)
		printf("%s\n", p->schedule); // p가 front에서부터 링크를 따라가 끝까지 각 노드의 데이터값(문자열)을 출력
}


int main(int argc, char* argv[])
{
	char command; 
	Node Schedule;
	int sorq; // stack을 사용할 것인지, queue를 사용할 것인지 저장할 변수 선언

	printf("\n");

	if ((argc != 2)) // 메인함수에 전달할 정보가 2개가 아니라면(실행파일명, 체크값)
	{
		printf("invalid input(please input like this -> exefilename modenumber)\n");
		exit(1);
	}

	sorq = atoi(argv[1]); // 스택을 사용할지(0) 큐를 사용할지(1) 메인함수의 argument로 입력받아 int형으로 대입

	if (sorq == 0) // 0을 argument로 입력받을 시 스택으로 스케줄러 구현(입력의 역순으로 출력됨)
	{
		init_stack(); // 스택 초기화
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
				printf("스케줄러를 종료합니다.\n");
				break;
			}
			else {
				printf("잘못 입력하였습니다.\n");
				printf("\n");
			}
		} while (command != 'q'); // do while문을 사용하여 command 값에 따라 스케줄러가 계속 구현되도록 함
		destroy_stack(); // 스택 파괴
	}

	else if(sorq == 1) // 0을 argument로 입력받을 시 큐로 스케줄러 구현(입력한 순서대로 출력됨)
	{
		init_queue(); // 큐 초기화
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
				printf("스케줄러를 종료합니다.\n");
				break;
			}
			else {
				printf("잘못 입력하였습니다.\n");
				printf("\n");
			}
		} while (command != 'q'); // do while문을 사용하여 command 값에 따라 스케줄러가 계속 구현되도록 함
		destroy_queue(); // 큐 파괴
	}

	return 0;
}

