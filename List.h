#pragma once

#include <string>


struct ListNode{
	ListNode * prev;
	ListNode* next;
	ListNode* rand; // ��������� �� ������������ ������� ������� ������ ���� NULL
	std::string     data;
};

class List
{
public:

	List():
		head(nullptr),
		tail(nullptr),
		count(0)
	{}

	void Serialize(FILE* file);  // ���������� � ���� (���� ������ � ������� fopen(path, "wb"))
	void Deserialize(FILE* file);  // �������� �� ����� (���� ������ � ������� fopen(path, "rb"))

	void pushBack(std::string newData);
	void pushFront(std::string newData);

	void popBack();
	void popFront();

	void randomizePointers();

	void printList();
private:
	ListNode* head;
	ListNode* tail;

	int       count;

	ListNode* getRandomNode(int randInt) const;
};

