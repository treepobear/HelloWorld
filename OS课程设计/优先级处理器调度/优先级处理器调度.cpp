#include"pch.h"
#include <iostream>
#include<string>
using namespace std;

struct PCB
{
	string name;
	int priority;
	int time;
	//char state = 'R';    // 我觉得不需要这个 直接拿time是否等于零判断进程状态
	PCB *next;
};

PCB* CreatePCB(string n) {
	PCB* p = new PCB;
	p->name = n;
	cout << "输入" << p->name << "的优先级：";
	cin >> p->priority;
	cout << "输入预计运行时间：";
	cin >> p->time;
	return p;
}

//需要传入首结点和要插入的结点，插入的时候按优先级排好
void AddToQueue(PCB* L, PCB* p) {
	//如果只有首结点，直接放在首结点后面
	if (L->next == NULL) {
		L->next = p;
		p->next = NULL;
		return;
	}
	else {
		PCB* r = L; //工作结点r
		//扫描整条链
		while (r->next != NULL) {
			//如果工作结点r优先级小于要插入的结点p 就把p插入在r前面
			if (r->next->priority < p->priority) {
				p->next = r->next;
				r->next = p;
				return;
			}
			else {
				r = r->next;
			}
		}
		//到链尾还比p大，p插在最后
		r->next = p;
		p->next = NULL;
		return;
	}
}

void PrintPCB(PCB* L) {
	cout << "当前队列中的进程：" << endl;
	PCB* w = L->next;
	if (w != NULL) {
		cout << "进程名   优先级   预计运行时间" << endl;
		while (w != NULL) {
			cout << w->name << "\t   " << w->priority << "\t   " << w->time << endl;
			w = w->next;
		}
	}
	else {
		cout << "队列空！" << endl;
	}
}

void Run(PCB* L) {
	PCB* r = L->next;
	while (r != NULL) {
		cout << "------进程" << r->name << "运行一次------" << endl;
		r->priority--;
		r->time--;
		//时间为0了退出队列不重新加入队列
		if (r->time == 0) {
			//L->next->state = 'E';
			L->next = r->next;
		}
		//时间不为0先退出队列再重新加入队列
		else {
			L->next = r->next;
			r->next = NULL;
			AddToQueue(L, r);
		}
		PrintPCB(L);
		r = L->next;
	}
	cout << "-----系统运行结束-----" << endl;
}

int main() {
	PCB *L;
	L = new PCB;//初始化头结点
	L->next = NULL;
	AddToQueue(L, CreatePCB("p1"));
	AddToQueue(L, CreatePCB("p2"));
	AddToQueue(L, CreatePCB("p3"));
	AddToQueue(L, CreatePCB("p4"));
	AddToQueue(L, CreatePCB("p5"));
	Run(L);
}
