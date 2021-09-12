#include<exception>

template<class T>
class MyListClass;

template<class T>
class ListNode {
public:
	using value_type = T;
private:
	value_type _value;
	ListNode<value_type>* _prev = nullptr;
	ListNode<value_type>* _next = nullptr;
	friend class MyListClass<T>;
public:
	ListNode(value_type value) {
		this->_value = value;
	}
	value_type get() const{
		return this->_value;
	}
	ListNode<value_type>* next() const{
		return this->_next;
	}
	ListNode<value_type>* prev() const{
		return this->_prev;
	}
	void set(value_type v) {
		this->_value = v;
	}
	bool has_next() {
		return _next != nullptr;
	}
};

template<class T>
class MyListClass {
public:
	using value_type = T;
private:
	ListNode<value_type>* _start = nullptr;
	ListNode<value_type>* _end = nullptr;
	size_t _size = 0;
	void check_index(size_t index) {
		if (index < 0 || index >= _size) {
			throw std::exception("Bad index");
		}
	}
public:
	~MyListClass() {
		ListNode<value_type>* current = this->_start;
		while (current != nullptr) {
			ListNode<value_type>* tmp = current;
			current = current->_next;
			delete tmp;
		}
	}
	ListNode<value_type>* begin() const{
		return _start;
	}
	ListNode<value_type>* end() const{
		return _end;
	}
	ListNode<value_type>* get(size_t index) {
		int current = 0;
		ListNode<value_type>* ptr_current = begin();
		check_index(index);
		while (current < index) {
			ptr_current = ptr_current->_next;
			++current;
		}
		return ptr_current;
	}
	size_t size() const{
		return this->_size;
	}
	void insert(value_type value) {
		if (_start == nullptr) {
			this->_end = this->_start = new ListNode<value_type>(value);
		}
		else {
			ListNode<value_type>* temp = _start;
			this->_start = new ListNode<value_type>(value);
			this->_start->_next = temp;
			temp->_prev = _start;
		}
		++_size;
	}
	void insert_back(value_type value) {
		if (_start == nullptr) {
			insert(value);
		}
		else {
			ListNode<value_type>* temp = new ListNode<value_type>(value);
			ListNode<value_type>* prev_end = this->_end;
			this->_end->_next = temp;
			temp->_prev = this->_end;
			this->_end = temp;
			++_size;
		}
	}
	void insert(size_t index, value_type value) {
		check_index(index);
		if (index == 0) {
			insert(value);
		}
		else if (index + 1 == _size) {
			insert_back(value);
		}
		else {
			ListNode<value_type>* current = get(index); // [prev] <-> [current] ===> [prev] <-> [new] <-> [current]
			ListNode<value_type>* prev = current->_prev;
			ListNode<value_type>* newv = new ListNode<value_type>(value);
			prev->_next = newv;
			newv->_next = current;
			current->_prev = newv;
			newv->_prev = prev;
			++_size;
		}
	}
};
