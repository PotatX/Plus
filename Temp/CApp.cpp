#include <iostream>
using namespace std;

struct User {
	string name;
	string surname;
	int age;
};

struct Node {
	User* user;
	Node* next;
	Node* prev;
};

struct List {
	Node* head;
	Node* tail;
	int size = 0;
};

Node* createNode(string name, string surname, int age) {
	User* user = new User;
	user->age = age;
	user->surname = surname;
	user->name = name;

	Node* node = new Node;

	node->user = user;
	node->next = nullptr;
	node->prev = nullptr;

	return node;
}

List* addToOrdered(List* list, string name, string surname, int age) {
	Node* newNode = createNode(name, surname, age);
	Node* head = list->head;
	Node* tail = list->tail;

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else if (age < head->user->age) {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	else {
		Node* tmp = head;

		while (tmp->next != nullptr && age > tmp->next->user->age) {
			tmp = tmp->next;
		}

		if (tmp->next == nullptr) {
			tmp->next = newNode;
			newNode->prev = tmp;
			tail = newNode;
		}
		else {
			tmp->next->prev = newNode;
			newNode->next = tmp->next;
			tmp->next = newNode;
			newNode->prev = tmp;
		}
	}

	list->head = head;
	list->tail = tail;
	list->size = ++list->size;

	return list;
}


void printList(List* list) {
	Node* head = list->head;
	Node* tail = list->tail;

	cout << list->size << endl;

	while (head->next != nullptr) {
		cout << head->user->name << " " << head->user->surname << " " << head->user->age << "; ";
		head = head->next;
	}

	cout << tail->user->name << " " << tail->user->surname << " " << tail->user->age << "; ";

	cout << endl;
}

int main() {
	List* list = new List;
	list->head = nullptr;
	list->tail = nullptr;

	addToOrdered(list, "Danya", "Kamyshov", 14);
	addToOrdered(list, "Danya", "Kamyshov", 11);
	addToOrdered(list, "Danya", "Kamyshov", 17);
	addToOrdered(list, "Danya", "Kamyshov", 19);
	addToOrdered(list, "Danya", "Kamyshov", 20);
	addToOrdered(list, "Danya", "Kamyshov", 11);

	printList(list);
}