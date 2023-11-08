#include<iostream>
using namespace std;

typedef string Key;


class Task {
private:
	Key datetime;
	string desc;
	bool done;
public:
	Task() {}
	Task(Key datetime, string desc): datetime(datetime), desc(desc) { this->done = false; }
	Key getDatetime() { return datetime; };
	string getDesc() { return desc; };
	bool getDone() { return done; };
};

void display_task(Task t) {
	cout << t.getDatetime() << " - " << t.getDesc() << " - ";
	cout << (t.getDone()? "Feito":"Por fazer") << endl;
}

// ----------------------------------------------------------------------------------
template<typename T>
class Node {
public:
	//Task item;
	T item;
	Node *next;
	Node(): next(nullptr) {}
	//Node(Task item): item(item), next(nullptr) {}
	Node(T item): item(item), next(nullptr) {}
};


// SinglyLinkedList
template<typename T>
class List {
private:
	Node<T> *head, *last;
	int length;
	Node<T>* predecessor(Node<T>*);

public:
	List() { 
		initialize(); 
	}

	void initialize();
	void add_item(T);
	void remove_item(Node<T> *p, T &item);
	Node<T>* search(Key);
	const Node<T>* getItems();

};

template<typename T>
void List<T>::initialize() { 
	head = new Node<T>(); 
	head->next = nullptr;
	last = head;
	length = 0;
}

template<typename T>
void List<T>::add_item(T it) {
	last->next = new Node<T>();
	last = last->next;
	last->next = nullptr;
	last->item = it;
	length++;
}

template<typename T>
Node<T>* List<T>::search(Key datetime) {
	Node<T> *p = head->next;
	while (p != nullptr && p->item.getDatetime() != datetime) {
		p = p->next;
	}
	return p;
}

template<typename T>
Node<T>* List<T>::predecessor(Node<T> *r) {
	Node<T> *p = head;
	while (p->next != r) {
		p = p->next;
	}
	return p;
}

template<typename T>
void List<T>::remove_item(Node<T> *r, T &item) {
	if (length == 0 || r == nullptr || r == head) {
		cout << "Impossivel remover o item.\n";
	}
	else{
		item = r->item;
		Node<T>* p = predecessor(r);
		p->next = r->next;
		if (p->next == nullptr) {
			last = p;
		}
		delete r;
	}
}
template<typename T>
const Node<T>* List<T>::getItems() {
	return head;
}

// ------------------------------------------------------------
template<typename T>
void display_list(const Node<T> *head) {
	cout << "Lista:\n";
	Node<T> *p = head->next;
	while (p != nullptr) {
		display_task(p->item);
		p = p->next;
	}
}

int main() {
	List<Task> lista;

	Task t1("8:00", "Dar uma surra no Batman");
	Task t2("8:07", "Ir � academia");
	Task t3("9:00", "Rodizio de Churras");
	Task t4("10:00", "Rol� pela Via L�ctea");

	lista.add_item(t1);
	lista.add_item(t2);
	lista.add_item(t3);
	lista.add_item(t4);
	display_list(lista.getItems());

	cout << endl;
	cout << "Buscando item por chave...\n";
	Key k = "9:00";
	Node<Task>* p = lista.search(k);
	if (p != nullptr)
		display_task(p->item);
	else {
		cout << "Item n�o encontrado\n";
	}

	cout << endl;
	cout << "Removendo item...\n";
	Task it;
	lista.remove_item(p, it);
	if (p != nullptr) {
		display_task(it);
		display_list(lista.getItems());
	} 
	cout << endl;

	return 0;
}

