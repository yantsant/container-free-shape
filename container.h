#pragma once
#include <array>
#include <random>
#include <iostream>
#include <cassert>

template<typename container_type>
class container {
	std::vector<size_t> DIMS;
	std::vector<container<container_type>>* _SubContainer = nullptr;
	std::vector<container_type>*             _Elem = nullptr;
	void _reset_elems();
	void _alloc_elems(size_t DIM);
	void _alloc(const std::vector<size_t>& DIMENSIONS);
	void _reset();
	void _copy(const container& rhs);
	void _move(container&& rhs);
protected:

public:
	explicit container() {};
	~container() { _reset(); };

	container(const container& rhs) {
		_copy(rhs);
	};

	container(container&& rhs) noexcept {
		_move((container&&)rhs);
	};

	container& operator = (const container& rhs) {
		_copy(rhs);
		return *this;
	};

	container& operator = (container&& rhs) noexcept {
		_move((container&&)rhs);
		return *this;
	};

	container(const std::vector<size_t>& DIMENSIONS) {
		_alloc(DIMENSIONS);
	};
};

template<typename container_type>
void container<container_type>::_reset_elems() {
	_Elem->clear();
	delete _Elem;
};

template<typename container_type>
void container<container_type>::_alloc_elems(size_t DIM) {
	_Elem = new std::vector<container_type>;
	_Elem->resize(DIM);
};

template<typename container_type>
void container<container_type>::_alloc(const std::vector<size_t>& DIMENSIONS) {
	DIMS = DIMENSIONS;
	size_t DIM = DIMS.front();
	if (DIMS.size() > 1) {
		std::vector<size_t> NASTED_DIM = DIMENSIONS;
		NASTED_DIM.erase(NASTED_DIM.begin());
		_SubContainer = new std::vector<container<container_type>>;
		_SubContainer->resize(DIM);
		for (size_t i = 0; i < DIM; i++)
			(*_SubContainer)[i] = container<container_type>(NASTED_DIM);
	}
	else {
		_alloc_elems(DIM);
		return;
	}
};

template<typename container_type>
void container<container_type>::_reset() {
	if (_SubContainer != nullptr) {
		_SubContainer->clear();
		delete _SubContainer;
	}
	if (_Elem != nullptr) _reset_elems();
};

template<typename container_type>
void container<container_type>::_copy(const container<container_type>& rhs) {
	if (_SubContainer == nullptr && _Elem == nullptr) {
		_alloc(rhs.DIMS);
		*_SubContainer = *rhs._SubContainer;
	}
	else {
		assert(DIMS == rhs.DIMS && " different shapes of containers");
		if (_Elem == nullptr && rhs._Elem != nullptr) {
			_alloc_elems(rhs.DIMS[0]);
			*_Elem = *rhs._Elem;
		}
	}

	DIMS = rhs.DIMS;
};

template<typename container_type>
void container<container_type>::_move(container&& rhs) {
	std::swap(_SubContainer, rhs._SubContainer);
	std::swap(_Elem, rhs._Elem);

	DIMS = std::move(rhs.DIMS);
	rhs._SubContainer = nullptr;
	rhs._Elem = nullptr;
};