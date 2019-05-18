typedef int SDataType;
typedef struct Stack
{
	SDataType* _array;
	int _top;
	int _capacity;
}Stack;
void StackInit(Stack* ps) {
	assert(ps);
	ps->_array = (SDataType*)malloc(sizeof(SDataType) * 3);
	if (ps->_array == NULL) {
		assert(0);
		return;
	}
	ps->_capacity = 3;
	ps->_top = 0;
}

void StackDestory(Stack* ps) {
	assert(ps);
	if (ps->_array) {
		free(ps->_array);
		ps->_capacity = 0;
		ps->_top = 0;
	}
}

void CheckCapacity(Stack* ps) {
	assert(ps);
	if (ps->_capacity == ps->_top) {
		int newCapacity = ps->_capacity * 2;
		SDataType* pTemp = (SDataType*)malloc(sizeof(SDataType)*newCapacity);
		if (pTemp == NULL) {
			assert(0);
			return;
		}
		for (int i = 0; i < ps->_top; ++i) {
			pTemp[i] = ps->_array[i];
		}
		free(ps->_array);
		ps->_array = pTemp;
		ps->_capacity = newCapacity;
	}
}

void StackPush(Stack* ps, SDataType data) {
	CheckCapacity(ps);
	ps->_array[ps->_top++] = data;
}
void StackPop(Stack* ps) {
	assert(ps);
	if (StackEmpty(ps))
		return;
	ps->_top--;
}
SDataType StackTop(Stack* ps) {
	assert(ps);
	return ps->_array[ps->_top - 1];
}
int StackEmpty(Stack* ps) {
	assert(ps);
	return ps->_top == 0;
}
int StackSize(Stack* ps) {
	assert(ps);
	return ps->_top;
}

typedef struct {
	Stack _s1;//模拟入队列操作
	Stack _s2;//模拟出队列操作
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue* pmq = (MyQueue*)malloc(sizeof(MyQueue));
	if (pmq == NULL) {
		assert(0);
		return NULL;
	}
	StackInit(&pmq->_s1);
	StackInit(&pmq->_s2);
	return pmq;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	assert(obj);
	StackPush(&obj->_s1,x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	assert(obj);
	if (StackEmpty(&obj->_s2)) {
		while (!StackEmpty(&obj->_s1)) {
			StackPush(&obj->_s2, StackTop(&obj->_s1));
			StackPop(&obj->_s1);
		}
	}
		int ret = StackTop(&obj->_s2);
		StackPop(&obj->_s2);
		return ret;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	assert(obj);
	if (StackEmpty(&obj->_s2)) {
		while (!StackEmpty(&obj->_s1)) {
			StackPush(&obj->_s2, StackTop(&obj->_s1));
			StackPop(&obj->_s1);
		}
	}
	return StackTop(&obj->_s2);
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	assert(obj);
	if (StackEmpty(&obj->_s1) && StackEmpty(&obj->_s2))
		return true;
	return false;
}

void myQueueFree(MyQueue* obj) {
	StackDestory(&obj->_s1);
	StackDestory(&obj->_s2);
	free(obj);
}
