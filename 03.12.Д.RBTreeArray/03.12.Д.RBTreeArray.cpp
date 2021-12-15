//03.12.П.1
//ассоциативный массив на RB-дереве.
#include <iostream>

int max(int a, int b) {
	return (a > b) ? a : b;
}
int* operator_value;
struct Node {
	int key;
	int value;
	bool color;//0 - чёрный, 1 - красный
	Node* left;
	Node* right;


	Node() :key(NULL), value(NULL), color(0), left(NULL), right(NULL) {}
	Node(int _key) : key(_key), value(NULL), color(0), left(NULL), right(NULL) {}
	Node(int _key, int _value) : key(_key), value(_value), color(0), left(NULL), right(NULL) {}
};
struct Array {
	//Нулевая вершина
	Node* NULL_NODE = new Node();
	Node* root = NULL_NODE;
	
	Array() {}

	//оператор [_key]
	int& operator [](int _key) {
		insert(_key, NULL);
		return *operator_value;
	}
	//вставка элемента
	void insert(int _key, int _value) {
		//если дерево пусто
		if (root == NULL_NODE) {
			root = new Node(_key, _value);
			root->color = 0; //корень всегда чёрный
			root->left = NULL_NODE;
			root->right = NULL_NODE;
			operator_value = &root->value;
			return;
		}
		insert(root, _key, _value);
	}
	Node* insert(Node*& _node, int _key, int _value) {
		if (_node == NULL_NODE) {
			_node = new Node(_key, _value);
			_node->color = 1; //вставляем всегда красную вершину
			_node->left = NULL_NODE;
			_node->right = NULL_NODE;
			operator_value = &_node->value;
			return _node;
		}
		else if (_key < _node->key) {
			_node->left = insert(_node->left, _key, _value);
			_node = balance2(_node);
		}
		else if (_key > _node->key) {
			_node->right = insert(_node->right, _key, _value);
			_node = balance2(_node);
		}
		//случай совпадения ключей
		else {
			if (_value != NULL) {
				_node->value = _value;
			}
			operator_value = &_node->value;
		}
		return _node;
	}
	//функция балансировки при вставке
	Node* balance2(Node* _node) {
		//случай I - дядя красный
		if ((_node->right->color == 1) && (_node->left->color == 1) && ((_node->left->left->color == 1)||(_node->left->right->color == 1)||(_node->right->left->color == 1)||(_node->right->right->color == 1))){
			if (_node != root) {
				_node->color = 1;
			}
			_node->left->color = 0;
			_node->right->color = 0;
		}
		//случай II - дядя чёрный
		else if (_node->right->color == 0 && _node->left->color == 1 && _node->left->left->color == 1) {
			_node = right_rotation(_node);
			_node->color = 0;
			_node->right->color = 1;
		} 
		else if (_node->left->color == 0 && _node->right->color == 1 && _node->right->right->color == 1) {
			_node = left_rotation(_node);
			_node->color = 0;
			_node->left->color = 1;
		}
		//случай III - другая картинка
		else if (_node->right->color == 0 && _node->left->color == 1 && _node->left->right->color == 1) {
			_node->left = left_rotation(_node->left);
			_node = right_rotation(_node);
			_node->color = 0;
			_node->right->color = 1;
		}
		else if (_node->left->color == 0 && _node->right->color == 1 && _node->right->left->color == 1) {
			_node->right = right_rotation(_node->right);
			_node = left_rotation(_node);
			_node->color = 0;
			_node->left->color = 1;
		}
		return _node;
	}
	//левый поворот
	Node* right_rotation(Node* parent) {
		Node* _tmp = parent->left;
		parent->left = _tmp->right;
		_tmp->right = parent;
		return _tmp;
	}
	//правый поворот
	Node* left_rotation(Node* parent) {
		Node* _tmp = parent->right;
		parent->right = _tmp->left;
		_tmp->left = parent;
		return _tmp;
	}
	//возврат значения по ключу
	int value(int _key) {
		Node* _search = search(_key);
		if (_search == NULL) {
			std::cout << "No such key" << std::endl;
			return 0;
		}
		else {
			return search(_key)->value;
		}
	}
	//поиск элемента
	Node* search(int _key) {
		return search(_key, root);
	}
	Node* search(int _key, Node* _node) {
		if (_node != NULL_NODE) {
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
		if (_node != NULL_NODE) {
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
		while (_node != NULL_NODE) {
			print(_node->right, space + 5);

			for (int i = 0; i <= space; ++i) {
				std::cout << " ";
			}
			std::cout << "(" << _node->key << "," << _node->value << ")" << std::endl;
			_node = _node->left;
			space += 5;
		}
	}
	//вывод дерева с NULL
	void print2() {
		print2(root, 0);
	}
	void print2(Node* _node, int space)
	{
		while (_node != NULL) {
			if (_node == NULL_NODE) {
				for (int i = 0; i <= space; ++i) {
					std::cout << " ";
				}
				std::cout << "NULL" << std::endl;
				return;
			}
			
				print2(_node->right, space + 5);
				for (int i = 0; i <= space; ++i) {
					std::cout << " ";
				}

				if (_node->color) {
					std::cout << "(" << _node->key << "," << "r" << ")" << std::endl;
				}
				else {
					std::cout << "(" << _node->key << "," << "b" << ")" << std::endl;
				}
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
		if (_node != NULL_NODE) {
			inOrderPrint(_node->left);
			std::cout << "[" << _node->key << ", " << _node->value << "] ";
			inOrderPrint(_node->right);
		}
	}
	//обратный обход дерева
	void postOrderPrint() {
		postOrderPrint(root);
		std::cout << std::endl;
	}
	void postOrderPrint(Node* _node) {
		if (_node != NULL_NODE) {
			inOrderPrint(_node->left);
			inOrderPrint(_node->right);
			std::cout << "[" << _node->key << ", " << _node->value << "] ";
		}
	}
	//прямой обход дерева
	void preOrderPrint() {
		preOrderPrint(root);
		std::cout << std::endl;
	}
	void preOrderPrint(Node* _node) {
		if (_node != NULL_NODE) {
			std::cout << "[" << _node->key << ", " << _node->value << "] ";
			inOrderPrint(_node->left);
			inOrderPrint(_node->right);
		}
	}
	//рекурсивное удаление дерева
	void deleteArray() {
		if (root != NULL_NODE) {
			deleteArray(root);
		}
		std::cout << "Array removed";
	}
	void deleteArray(Node* _node) {
		if (_node != NULL_NODE) {
			deleteArray(_node->left);
			deleteArray(_node->right);
			delete _node;
		}
	}
	//функция нахождения чёрной высоты вершины
	int height(Node* _node) {
		int _height = 1;
		if (_node != NULL_NODE) {
			int a = height(_node->left);
			int b = height(_node->right);
			if (_node->color == 0) {
				_height = max(a, b) + 1;
			}
			else {
				_height = max(a, b);
			}
		}
		return _height;
	}
	//разница чёрных высот вершин
	int difference(Node* _node) {
		int left_height = height(_node->left);
		int right_height = height(_node->right);
		return left_height - right_height;
	}
	//удаление по значению
	void remove(int _key) {
		remove(root, _key);
	}
	Node* remove(Node* _node, int _key) {
		Node* tmp;
		//Элемент не был найден
		if (_node == NULL_NODE) {
			std::cout << "Element not found" << std::endl;
			return NULL_NODE;
		}
		else if (_key < _node->key) {
			_node->left = remove(_node->left, _key);
		}
		else if (_key > _node->key) {
			_node->right = remove(_node->right, _key);
		}
		//Элемент найден
		//У него обе ссылки на NULL_NODE (нет действительных потомков) или же всего один потомок
		else if (_node->left == NULL_NODE || _node->right == NULL_NODE) {
			tmp = _node;
			//оба NULL_NODE
			if (_node->left == NULL_NODE && _node->right == NULL_NODE) {
				_node = NULL_NODE;
			}
			//левый NULL_NODE
			else if (_node->left == NULL_NODE) {
				_node = _node->right;
				_node->color = 0;
			}
			//правый NULL_NODE
			else {
				_node = _node->left;
				_node->color = 0;
			}
			delete tmp;
		}
		//Если у него два потомка
		else {
			tmp = minNode(_node->right);
			_node->key = tmp->key;
			_node->value = tmp->value;
			_node->right = remove(_node->right, _node->key);
		}

		//return _node;

		//если NULL_NODE, то идём дальше, иначе баланс
		if (_node == NULL_NODE || (difference(_node) == 0)) {
			return _node;
		} 
		_node = balance(_node);
	}
	//баланс при удалении (рассматриваются случии, в которых при удалении следует восстанавливать баланс)
	Node* balance(Node* _node) {
		//только если X - чёрный
		if ((_node->left->color == 1) && (_node->right->color == 1)) {
			return _node;
		}
		//случай I - брат красный
		if (_node->left->color == 0 && _node->right->color == 1) {
			_node = left_rotation(_node);
			_node->left = balance(_node->left);
		}//зеркальный случай
		else if (_node->left->color == 1 && _node->right->color == 0) {
			_node = right_rotation(_node);
			_node->right = balance(_node->right);
		}
		//случай II A - брат чёрный (оба племянника чёрные)
		else if (_node->right != NULL_NODE && _node->right->left->color == 0 && _node->right->right->color == 0) {
			_node->color = 0;
			_node->left->color = 1;
		}//зеркальный случай
		else if (_node->left != NULL_NODE &&_node->left->left->color == 0 && _node->left->right->color == 0) {
			_node->color = 0;
			_node->left->color = 1;
		}
		//случай II B - брат чёрный (левый племянник красный)
		else if (_node->right != NULL_NODE &&_node->right->left->color == 1 && _node->right->right->color == 0) {
			_node->right = right_rotation(_node->right);
			_node->right->color = 0;
			_node->right->right->color = 1;
		}//зеркальная ситуация
		else if (_node->left != NULL_NODE && _node->left->right->color == 1 && _node->left->left->color == 0) {
			_node->left = left_rotation(_node->left);
			_node->left->color = 0;
			_node->left->left->color = 1;
		}
		//случай II С - брат чёрный (правый племянник красный)
		else if (_node->right != NULL_NODE &&_node->right->right->color == 1) {
			_node = left_rotation(_node);
			//b становится цвета a
			_node->color = _node->left->color;
			_node->left->color = 0;
			_node->right->color = 0;
		}//зеркальный случай
		else if (_node->left != NULL_NODE && _node->left->left->color == 1) {
			_node = right_rotation(_node);
			//b становится цвета a
			_node->color = _node->right->color;
			_node->left->color = 0;
			_node->right->color = 0;
		}
		return _node;
	}
	//минимальный потомок (для remove)
	Node* minNode(Node* _node) {
		if (_node->left == NULL_NODE) {
			return _node;
		}
		else {
			return minNode(_node->left);
		}
	}
	//проверка на выполнения условия красный пораждает чёрного
	bool red_after_red(Node* _node) {
		if (_node->left == NULL_NODE || _node->right == NULL_NODE) {
			return false;
		}
		else if ((_node->color == 1) && ((_node->left->color == 1) || (_node->right->color == 1))) {
			return true;
		}
		return max(red_after_red(_node->left), red_after_red(_node->right));
	}
	//проверка на выполнение свойств
	void rb_check() {

		std::cout << "It is RB-Tree: " << std::boolalpha << ((difference(root) == 0) && (!red_after_red(root))) << std::endl; 
		return;
	}
};

int main() {
	Array new_array;
	
	/*
	//заполнение с клавиатуры
	int number;
	std::cout << "Input nuber of elements: " << std::endl;
	std::cin >> number;
	for (int i = 0; i < number; ++i){
		int key;
		int value;
		std::cout << "Input key: " << std::endl;
		std::cin >> key;
		std::cout << "Input value: " << std::endl;
		std::cin >> value;
		new_array.insert(key, value);

	}
	*/
	
	//можно заполнять как через оператор []
	new_array[10] = 1; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[85] = 2; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[15] = 3; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[70] = 4; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[20] = 5; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[60] = 6; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[30] = 7; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[50] = 8; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[65] = 9; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[80] = 10; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[90] = 11; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[40] = 12; new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array[5] = 13; new_array.print(); new_array.rb_check(); std::cout << "====================" << std::endl;
	//так и через функцию 
	new_array.insert(55, 14); new_array.print2(); new_array.rb_check(); std::cout << "====================" << std::endl;
	new_array.inOrderPrint();
	new_array.deleteArray();
	return 0;
}