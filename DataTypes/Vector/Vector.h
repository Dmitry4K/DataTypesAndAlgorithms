#include<iostream>

namespace d4k {
	template<class T> class vector {
	private:
		T* storage_;
		size_t size_;
		size_t capacity_;
	public:
		vector() : storage_(nullptr), size_(0), capacity_(0) {};
		vector(size_t size, const T default_value = T()) {
			storage_ = new T[size];
			size_ = size;
			capacity_ = size;
			for (int i = 0; i < (int)size; i++)
				storage_[i] = default_value;
		}
		~vector() {
			delete[] storage_;
			storage_ = nullptr;
			size_ = 0;
			capacity_ = 0;
		}
		T* begin() const {
			return storage_;
		}
		T* end() const {
			return storage_ ? storage_ + size_ : nullptr;
		}
		size_t size() const {
			return size_;
		}
		bool empty() const {
			return size() == 0;
		}
		size_t capacity() const {
			return capacity_;
		}

		T& at(int index) const {
			if (index < 0 || index >= (int)size_)
				throw std::out_of_range("Out of range!");
			return storage_[index];
		}
		T& operator[](int index) const
		{
			return at(index);
		}
		void push_back(const T& value) {
			if (size_ == capacity_) {
				T* temp_storage_ = storage_;
				size_ == 0 ? capacity_ = 1 : capacity_ *= 2;
				storage_ = new T[capacity_];
				for (size_t i = 0; i < size_; i++)
					storage_[i] = temp_storage_[i];
				delete[] temp_storage_;
			}
			storage_[size_++] = value;
			return;
		}
		vector<T>& operator= (const vector<T>& other) {
			delete [] storage_;
			storage_ = new T[other.capacity_];
			capacity_ = other.capacity_;
			size_ = other.size_;
			for (int i = 0; i < (int)size_; i++)
				storage_[i] = other.storage_[i];
			return *this;
		}
	};
}
