#include "List.h"
#include <iostream>
#include <map>
#include <vector>
#include <random>

void List::Serialize(FILE* file)
{
	ListNode* currentNode = head;

	while (currentNode != nullptr)
	{
		fprintf(file, "%u %u\n%s\n",
			reinterpret_cast<std::uintptr_t>(currentNode),
			reinterpret_cast<std::uintptr_t>(currentNode->rand),
			currentNode->data.c_str());

		currentNode = currentNode->next;
	}
}

void List::Deserialize(FILE* file)
{
	std::map<std::uintptr_t, ListNode*> nodes;

	nodes[reinterpret_cast<std::uintptr_t>(nullptr)] = nullptr;

	std::uintptr_t nodeKey;
	std::uintptr_t randKey;

	std::vector<std::uintptr_t> randKeys;

	while (fscanf_s(file, "%u %u\n", &nodeKey, &randKey) != EOF)
	{
		char charBuf;
		char buffer[256];
		size_t lineIndex = 0;

		while ((charBuf = fgetc(file)) != '\n')
		{
			buffer[lineIndex] = charBuf;
			lineIndex++;
		}

		buffer[lineIndex] = '\0';

		pushBack(buffer);

		nodes[nodeKey] = tail;

		randKeys.push_back(randKey);
	}

	ListNode* currentNode = head;
	size_t keyIndex = 0;

	while (currentNode != nullptr)
	{
		currentNode->rand = nodes[randKeys[keyIndex]];
		currentNode = currentNode->next;
		keyIndex++;
	}
}

void List::pushBack(std::string newData)
{
	ListNode* newNode = new ListNode{ nullptr,nullptr,nullptr, newData };
	ListNode* curNode = tail;

	if (tail != nullptr)
	{
		tail->next = newNode;
		newNode->prev = tail;
	}

	tail = newNode;
	count++;

	if (curNode == nullptr)
	{
		head = tail;
	}
}

void List::pushFront(std::string newData)
{
	ListNode* newNode = new ListNode{ nullptr,nullptr,nullptr, newData };
	ListNode* curNode = head;

	if (head != nullptr)
	{
		head->prev = newNode;
		newNode->next = head;
	}

	head = newNode;
	count++;

	if (curNode == nullptr)
	{
		tail = head;
	}
}

void List::popBack()
{
	if (tail != nullptr)
	{
		if (tail != head)
		{
			tail->prev->next = tail->next;
			ListNode* curTail = tail;
			tail = tail->prev;
			delete curTail;
		}
		else
		{
			delete tail;
			tail = nullptr;
			head = nullptr;
		}

		count--;
	}
}

void List::popFront()
{
	if (head != nullptr)
	{
		if (head != tail)
		{
			head->next->prev = head->prev;
			ListNode* curHead = head;
			head = head->next;
			delete curHead;
		}
		else
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}

		count--;
	}
}

void List::randomizePointers()
{
	ListNode* currentPtr = head;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, count);
	

	while (currentPtr != nullptr)
	{
		int randInt = uni(rng);

		currentPtr->rand = getRandomNode(randInt);
		currentPtr = currentPtr->next;
	}
}

void List::printList()
{
	
	ListNode* curNode = head;

	while (curNode != nullptr)
	{
		std::cout << "Data: " << curNode->data << " || " <<
			" Current Ptr: " << curNode << " || " <<
			" Next Ptr: " << curNode->next << " || " <<
			" Prev Ptr: " << curNode->prev << " || " <<
			" Rand Ptr: " << curNode->rand << std::endl;
		curNode = curNode->next;
	}

}

ListNode* List::getRandomNode(int randInt) const
{
	if ((count <= 0) || (randInt == count)) return nullptr;

	int index = 0;

	ListNode* randNode = head;

	while (index < randInt)
	{
		randNode = randNode->next;
		index++;
	}

	return randNode;
}
