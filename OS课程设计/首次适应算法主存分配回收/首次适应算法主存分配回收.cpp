#include "pch.h"
#include<iostream>
#include<string>
using namespace std;

int num = 3;//标记内存中载入了几个进程
//随便设内存大小为128好了
int Memory[128] = {
	0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,2,2,2,2,
	2,2,2,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,3,3,
	3,3,3,3,3,3,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

//空闲分区结点FreeBlock
struct FB {
	int FBid = 0;
	int startAddr = 0;
	int len = 0;
	FB* next = NULL;
	FB* before = NULL;
};

FB* Init() {
	FB* w = new FB;
	FB* h = new FB;

	int now = 0;
	int i = 0;

	while (now < 128) {
		for (now; now < 128; now++) {
			if (Memory[now] == 0) {
				w->startAddr = now;
				break;
			}
		}

		for (now; now < 128; now++) {
			if (Memory[now] != 0 || now == 127) {
				w->len = now - (w->startAddr);
				w->FBid = i++;
				break;
			}
		}
		if (i == 1) {
			h = w;
		}
		FB* m = new FB;
		m->before = w;
		w->next = m;
		w = m;
		now++;
	}

	return h;
}

void PrintMemory() {
	cout << "\n当前内存状态：" << endl;
	cout << "----------------------------------" << endl;
	cout << "StartAddr      Length      Status" << endl;
	cout << "----------------------------------" << endl;

	int now = 0;
	int end = 0;
	int sAddr;
	int status;

	while (now < 128) {
		if (Memory[now] == 0) {
			status = 0;
		}
		else {
			status = Memory[now];
		}
		now++;
		sAddr = now - 1;
		for (now; now < 128; now++) {
			if (Memory[now] != status) {
				end++;
				break;
			}
			end++;
		}
		string s;
		if (status == 0) {
			s = "Free";
		}
		else {
			s = "Allocated";
		}
		cout << sAddr << "\t\t" << end - sAddr << "\t   " << s << endl;
	}

}

void PrintFreeBlocks(FB* h) {
	cout << "\n空闲的内存块：" << endl;
	FB* w = h;
	cout << "----------------------------------" << endl;
	cout << "StartAddr       Length       FreeBlockID" << endl;
	cout << "----------------------------------" << endl;
	while (w->next != NULL) {
		cout << w->startAddr << "\t\t" << w->len << "\t\t" << w->FBid << endl;
		w = w->next;
	}
}

FB* Load(int len, FB* h) {
	FB* w = h;//工作结点,从链首开始
	num++;
	while (w->next != NULL) {
		if (len < w->len) {
			for (int i = w->startAddr; i < w->startAddr + len; i++) {
				Memory[i] = num;
			}
			w->startAddr = w->startAddr + len;
			w->len = w->len - len;
			return h;
		}
		if (len == w->len) {
			for (int i = w->startAddr; i < w->startAddr + len; i++) {
				Memory[i] = num;
			}
			w->next->before = w->before;//删去该空闲块
			w = w->next;
			h = w;
			while (w->next != NULL) {
				w->FBid--;
				w = w->next;
			}
			return h;
		}
		w = w->next;
	}

	return h;
}

FB* Release(int start, FB* h) {
	FB* w = h;
	int i = start;
	num--;
	int PCBnum = Memory[start];
	while (Memory[i] == PCBnum) {
		Memory[i] = 0;
		i++;//最后i会指向释放完以后的下一个地址
	}

	//如果释放的内存块前面是空的
	if (Memory[start - 1] == 0 && Memory[i] != 0) {
		//定位到前面的FB
		while (w->next != NULL) {
			if ((w->startAddr + w->len) == start) {
				w->len = i - w->startAddr;
				return h;
			}
			w = w->next;
		}
	}
	//如果释放的内存块后面是空的
	if (Memory[i] == 0 && Memory[start - 1] != 0) {
		while (w->next != NULL) {
			if (w->startAddr == i) {
				w->startAddr = start;
				w->len = w->len + i - start;
				return h;
			}
			w = w->next;
		}
	}
	//前后都是空的
	if (Memory[start - 1] == 0 && Memory[i] == 0) {
		while (w->next != NULL) {
			if ((w->startAddr + w->len) == start) {
				w->len = w->next->len + w->next->startAddr - w->startAddr;
				w->next = w->next->next;//删除释放的内存块后面的那个空闲块
				w->next->before = w;
				w = w->next;
				//更新之后的空闲块ID
				while (w->next != NULL) {
					w->FBid++;
					w = w->next;
				}
				return h;
			}
			w = w->next;
		}
	}
	//前后都不是空的
	if (Memory[start - 1] != 0 && Memory[i] != 0) {
		FB* nfb = new FB;
		nfb->startAddr = start;
		nfb->len = i - start;
		int temp = start - 1;
		while (Memory[temp] != 0 && temp != 0) {
			temp--;
		}
		if (temp != 0) {
			while (w->next != NULL) {
				if ((w->startAddr + w->len) == temp + 1) {
					nfb->next = w->next;
					w->next->before = nfb;
					nfb->before = w;
					w->next = nfb;
					w = nfb;
					//更新FBid
					while (w->next != NULL) {
						w->FBid = w->before->FBid + 1;
						w = w->next;
					}
					return h;
				}
				w = w->next;
			}
		}
		//要改首结点了呢
		else {
			nfb->FBid = 0;
			nfb->next = h;
			h->before = nfb;
			h = nfb;
			while (w->next != NULL) {
				w->FBid++;
				w = w->next;
			}
			return h;
		}

	}
	return h;
}

int main() {
	FB* h = Init();
	int c;
	while (true) {
		PrintMemory();
		PrintFreeBlocks(h);
		cout << "\n\n分配(1) or 释放(0) or 退出(3)？" << endl;
		cin >> c;
		if (c == 1) {
			cout << "大小？" << endl;
			int s;
			cin >> s;
			h = Load(s, h);
		}
		else if (c == 0) {
			cout << "释放内存块的首地址？" << endl;
			int s;
			cin >> s;
			h = Release(s, h);
		}
		else if (c == 3) {
			break;
		}
	}
}
