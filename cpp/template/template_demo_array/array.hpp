#pragma once
template <class T>
class Array
{
public:
	Array(int capacity) {
		capacity_ = capacity;
		paddress_ = new T[capacity_];
		size_ = 0;
	}

	Array(const Array& arr) {
		capacity_ = arr.capacity_;
		size_ = arr.size_;
		paddress_ = new T[capacity_];
		for (int i = 0; i < size_; i++) {
			paddress_[i] = arr.paddress_[i];
		}
	}

	// ����[]
	T& operator[] (int index) {
		return paddress_[index];
	}
	
	// β��
	void push_back(const T& val) {
		if (capacity_ == size_) {
			return;
		}
		paddress_[size_++] = val;
	}

	// βɾ
	void pop_back() {
		if (size_ == 0) {
			return;
		}
		size_--;
	}

	int get_size() {
		return size_;
	}

	~Array() {
		if (paddress_ != nullptr) {
			std::cout << "~Array..." << std::endl;
			delete[] paddress_;
			paddress_ = nullptr;
			size_ = 0;
			capacity_ = 0;
		}
	}
private:
	T* paddress_;	// ָ��ѿռ䣬�洢����
	int capacity_;	// ����
	int size_;		// ��ǰԪ�ظ���
};