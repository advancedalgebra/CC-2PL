#pragma once
#include "thread_safe_list.h"
#include "global.h"
#include<queue>
#include<string>
#include<unordered_map>
#include<mutex>
#include<vector>
using namespace std;

/**/
struct LockEntry {
	lock_t type;
	std::thread::id tid;
};

struct Data {
	time_t timestamp;
	int value; // �������ֵ
	LockEntry owner; // ��ǰ�������ϵ�������˭
    thread_safe::list<LockEntry*> waitlist; // �̰߳�ȫ���б���¼Ŀǰ���������ϵĵȴ��б�
	bool deleted;
	std::mutex latch; // �������������̶߳����������

	Data() {
		value = -1;
		owner.type = LOCK_NONE;
		deleted = false;
	}
	
	void set(Data* data1, Data* data2) {
		data1->deleted = data2->deleted;
		data1->owner = data2->owner;
		data1->timestamp = data2->timestamp;
		data1->value = data2->value;
		data1->waitlist = data2->waitlist;
		data1->waitlist = data2->waitlist;
	}

	Data& operator=(const Data& d) {
		set(this, (Data*)&d);
		return *this;
	}

	Data(const Data& d) {
		*this = d;
	}
};

class Engine {
public:
	Engine() {
		cc = CC_LOCK;
	}
	Engine(cc_type type) {
		cc = type;
	}
	RC find();
	RC update();
	RC delete_();

	std::unordered_map<std::string, Data> data_map;  //hash map���洢���ݵĽṹ
private:
	cc_type cc;
};