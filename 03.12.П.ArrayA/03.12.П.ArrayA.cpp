//03.12.П.1
//ассоциативный массив на АВЛ-дереве.
//прошу прощения, что чуть позже отправил, были неполадки
#include <iostream>

int max(int a, int b) {
	return (a > b) ? a : b;
}

struct Node {
	int key;
	int value;
	Node* left;
	Node* right;
	Node() :key(NULL), value(NULL), left(NULL), right(NULL) {}
	Node(int _key, int _value) : key(_key), value(_value), left(NULL), right(NULL) {}
};
struct Array {
	Node* root;
	Array() : root(nullptr) {}
	//вставка элемента
	void insert(int _key, int _value) {
		insert(root, _key, _value);
		return;
	}
	Node* insert(Node*& _node, int _key, int _value) {
		if (_node == NULL) {
			_node = new Node(_key, _value);
			return _node;
		}
		else if (_key < _node->key) {
			_node->left = insert(_node->left, _key, _value);
			_node = balance(_node);
		}
		else if (_key >= _node->key) {
			_node->right = insert(_node->right, _key, _value);
			_node = balance(_node);
		}
		return _node;
	}
	//возврат значения по ключу
	int value(int _key) {
		return search(_key)->value;
	}
	//поиск элемента
	Node* search(int _key) {
		return search(_key, root);
	}
	Node* search(int _key, Node* _node) {
		if (_node != NULL) {
			if (_key == _node->key) {
				return _node;
			}
			if (_key < _node->key) {
				return search(_key, _node->left);
			}
			else {
				return search(_key, _node->right);
			}
		}
		else {
			return NULL;
		}
	}
	//количество элементов
	int size() {
		return size(root);
	}
	int size(Node* _node) {
		int n = 0;
		if (_node != NULL) {
			n = 1;
			n += size(_node->left);
			n += size(_node->right);
		}
		return n;
	}
	//вывод дерева в графическом виде
	void print() {
		print(root, 0);
	}
	void print(Node* _node, int space)
	{
		while (_node != NULL) {
			print(_node->right, space + 5);

			for (int i = 0; i <= space; ++i) {
				std::cout << " ";
			}
			std::cout << "(" << _node->key << "," << _node->value << ")" << std::endl;

			_node = _node->left;
			space += 5;
		}
	}
	//центрированный обход дерева
	void inOrderPrint() {
		inOrderPrint(root);
		std::cout << std::endl;
	}
	void inOrderPrint(Node* _node) {
		if (_node != NULL) {
			inOrderPrint(_node->left);
			std::cout << _node->key << " ";
			inOrderPrint(_node->right);
		}
	}
	//обратный обход дерева
	void postOrderPrint() {
		postOrderPrint(root);
		std::cout << std::endl;
	}
	void postOrderPrint(Node* _node) {
		if (_node != NULL) {
			inOrderPrint(_node->left);
			inOrderPrint(_node->right);
			std::cout << _node->key << " ";
		}
	}
	//прямой обход дерева
	void preOrderPrint() {
		preOrderPrint(root);
		std::cout << std::endl;
	}
	void preOrderPrint(Node* _node) {
		if (_node != NULL) {
			std::cout << _node->key << " ";
			inOrderPrint(_node->left);
			inOrderPrint(_node->right);
		}
	}
	//рекурсивное удаление дерева
	void deleteArray() {
		if (root != NULL) {
			deleteArray(root);
		}
		std::cout << "Array removed";
	}
	void deleteArray(Node* _node) {
		if (_node != NULL) {
			deleteArray(_node->left);
			deleteArray(_node->right);
			delete _node;
		}
	}
	//функция нахождения высоты вершины
	int height(Node* _node) {
		int _height = 0;
		if (_node != NULL) {
			int a = height(_node->left);
			int b = height(_node->right);
			_height = max(a, b) + 1;
		}
		return _height;
	}
	//разница высот вершин
	int difference(Node* _node) {
		int left_height = height(_node->left);
		int right_height = height(_node->right);
		return left_height - right_height;
	}
	//балансировка дерева
	Node* balance(Node* _node) {
		int _balance = difference(_node);
		if (_balance > 1)
		{
			if (difference(_node->left) > 0)
				_node = ll_rotation(_node);
			else
				_node = lr_rotation(_node);
		}
		else if (_balance < -1)
		{
			if (difference(_node->right) > 0)
				_node = rl_rotation(_node);
			else
				_node = rr_rotation(_node);
		}
		return _node;
	}
	//удаление по значению
	void remove(int _key) {
		remove(root, _key);
	}
	Node* remove(Node* _node, int _key) {
		Node* tmp;
		//Элемент не был найден
		if (_node == NULL) {
			std::cout << "Element not found" << std::endl;
			return NULL;
		}
		else if (_key < _node->key) {
			_node->left = remove(_node->left, _key);
		}
		else if (_key > _node->key) {
			_node->right = remove(_node->right, _key);
		}
		//Элемент найден
		//У него 2 потомка
		else if (_node->left && _node->right) {
			tmp = minNode(_node->right);
			_node->key = tmp->key;
			_node->right = remove(_node->right, _node->key);
		}
		//у него отсутствуют потомки или только один
		else {
			tmp = _node;
			if (_node->left == NULL) _node = _node->right;
			else if (_node->right == NULL) _node = _node->left;
			delete tmp;
		}
		if (_node == NULL) return _node;
		_node = balance(_node);
	}
	//минимальный потомок
	Node* minNode(Node* _node) {
		if (_node == NULL) {
			return NULL;
		}
		else if (_node->left == NULL) {
			return _node;
		}
		else {
			return minNode(_node->left);
		}
	}

	//все вращения
	//правое->правое вращение
	Node* rr_rotation(Node* parent) {
		Node* _node = parent->right;
		parent->right = _node->left;
		_node->left = parent;
		return _node;
	}
	//правое->правое вращение
	Node* rl_rotation(Node* parent)
	{
		Node* _node = parent->right;
		parent->right = ll_rotation(_node);
		return rr_rotation(parent);
	}
	//левое->левое вращение
	Node* ll_rotation(Node* parent) {
		Node* _node = parent->left;
		parent->left = _node->right;
		_node->right = parent;
		return _node;
	}
	//левое->правое вращение
	Node* lr_rotation(Node* parent) {
		Node* _node = parent->left;
		parent->left = rr_rotation(_node);
		return ll_rotation(parent);
	}
};

int main() {
	Array new_array;

	new_array.insert(1, 2);
	new_array.insert(2, 3);
	new_array.insert(3, 4);
	new_array.insert(4, 5);
	new_array.insert(5, 6);
	new_array.insert(6, 7);
	new_array.insert(7, 8);
	new_array.insert(8, 9);
	new_array.insert(9, 10);
	new_array.insert(10, 11);
	new_array.insert(11, 12);
	new_array.insert(12, 1);
	/*
	new_array.inOrderPrint();
	new_array.preOrderPrint();
	new_array.postOrderPrint();
	*/
	int k;
	std::cout << "Enter the key for which output the value: ";
	std::cin >> k;
	std::cout << "Value is: " << new_array.value(k) << std::endl;
	std::cout << std::endl;
	std::cout << "Size is: " << new_array.size() << std::endl;
	std::cout << std::endl;
	new_array.print();
	std::cout << std::endl;

	new_array.remove(8);
	std::cout << "Size is: " << new_array.size() << std::endl;
	new_array.print();

	new_array.remove(10);
	std::cout << "Size is: " << new_array.size() << std::endl;
	new_array.print();

	new_array.deleteArray();
	return 0;
}