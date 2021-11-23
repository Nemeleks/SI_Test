#pragma warning(disable:4996)

#include <iostream>
#include <string.h>
#include "List.h"
#include "removeDups.h"

int main()
{
	char pSTR[] = "AAA BBB AAA";

	std::cout << "String before remove dups: " << std::endl;
	std::cout << pSTR << std::endl;

	removeDups(pSTR);
	std::cout << "String after remove dups: " << std::endl;
	std::cout << pSTR << std::endl;
	std::cout << std::endl;


	List* list = new List();

	list->pushFront("Head");
	list->pushFront("New Head");
	list->pushBack("Tail");
	list->pushBack("NewTail");

	list->randomizePointers();

	std::cout << "List before serialization:" << std::endl;
	list->printList();
	std::cout << std::endl;

	FILE* file = fopen("serializedData.bin", "wb");
	if (file != nullptr)
	{
		list->Serialize(file);
		fclose(file);
	}
	delete list;

	file = fopen("serializedData.bin", "rb");
	if (file != nullptr)
	{
		List* newList = new List();

		newList->Deserialize(file);
		fclose(file);

		std::cout << "List after deserialization:" << std::endl;
		newList->printList();

		delete newList;
	}

	return 0;
}


