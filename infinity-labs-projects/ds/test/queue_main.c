
#include <stdio.h> /* printf */

#include "s_list.h" 
#include "queue.h"


void Red();
void Green();
void ResetColor();

void TestExpected(void *actual, void *expected, const char *func_name);
void TestExpectedINTS(int actual, int expected, const char *func_name);

void TestQueue();
void TestQueueAppend();

int main()
{
	TestQueue();
	TestQueueAppend();
	
	return 0;
}


void TestQueueAppend() 
{
	queue_t *queue1 = QCreate(), *queue2 = QCreate();
	int x1 = 1, x2 = 2, x3 = 3;
	
	printf("\n Append Queues - q1- empty q2- non empty\n");
	QEnqueue(queue2, &x1);
	QEnqueue(queue2, &x2);
	QEnqueue(queue2, &x3);
		
	QAppend(queue1, queue2);
	
	TestExpectedINTS(QGetSize(queue1), 3, "QGetSize- q1");
	TestExpectedINTS(QIsEmpty(queue2), 1, "QIsEmpty - q2");
	
	printf("\n Append Queues - q1- non empty q2- non empty\n");
	QEnqueue(queue2, &x1);  
	QEnqueue(queue2, &x2); 
	QEnqueue(queue2, &x3);
	
	QAppend(queue1, queue2);
	
	TestExpectedINTS(QGetSize(queue1), 6, "QGetSize- q1");
	TestExpectedINTS(QIsEmpty(queue2), 1, "QIsEmpty - q2");
	
	QDequeue(queue1);
	QDequeue(queue1);
	QDequeue(queue1);
	
	TestExpected(QPeek(queue1), &x1, "QEnqueue & QPeek");
	
	QDestroy(queue1);
	QDestroy(queue2);
}

void TestQueue()
{
	queue_t *queue1 = QCreate(), *queue2 = QCreate();
	int x1 = 1, x2 = 2, x3 = 3;
	
	TestExpectedINTS(QIsEmpty(queue1), 1, "QIsEmpty");
	TestExpectedINTS(QGetSize(queue1), 0, "QGetSize");
	
	QEnqueue(queue1, &x1);
	TestExpected(QPeek(queue1), &x1, "QEnqueue & QPeek");
	
	QEnqueue(queue1, &x2);
	TestExpected(QPeek(queue1), &x1, "QEnqueue & QPeek");
	
	QEnqueue(queue1, &x3);
	
	TestExpectedINTS(QIsEmpty(queue1), 0, "QIsEmpty - Not Empty");
	TestExpectedINTS(QGetSize(queue1), 3, "QGetSize");
	
	TestExpected(QDequeue(queue1), &x1, "QDequeue");
	TestExpectedINTS(QGetSize(queue1), 2, "QGetSize & QDequeue");
	
	TestExpected(QDequeue(queue1), &x2, "QDequeue");
	TestExpected(QDequeue(queue1), &x3, "QDequeue");
	TestExpectedINTS(QIsEmpty(queue1), 1, "QIsEmpty & QDequeue");
	
	QDestroy(queue1);

	/* Destroy - On non Empty */
	QEnqueue(queue2, &x1);
	QEnqueue(queue2, &x2);
	
	QDestroy(queue2);
}

void TestExpected(void *actual, void *expected, const char *func_name)
{
	if (actual != expected)
	{
		Red();
	}
	else
	{
		Green();
	}
	
	printf("%s\n", func_name);
	ResetColor();
}

void TestExpectedINTS(int actual, int expected, const char *func_name)
{
	if (actual != expected)
	{
		Red();
	}
	else
	{
		Green();
	}
	
	printf("%s\n", func_name);
	ResetColor();
}

void Red() 
{
	printf("\033[1;31m");
}

void Green() 
{
	printf("\033[0;32m");
}

void ResetColor()
{
	printf("\033[0m");
}

