#pragma once

#include <cassert>
#include <new>
#include <type_traits>

namespace MyContainer {

namespace DequeDetails {

constexpr size_t INIT_SIZE = 16;

template<typename Item>
Item* Alloc(size_t size)
{
	auto* data = reinterpret_cast<Item*>(malloc(size * sizeof(Item)));
	if (!data)
		throw std::bad_alloc();

	return data;
}

template<typename Item>
void Free(Item* begin, Item* end)
{
	assert(begin <= end);
	while (begin < end)
		begin++->~Item();
}

template<typename Item>
struct Storage
{
	Storage(size_t size, size_t beginIndex)
		: m_capacityBegin(Alloc<Item>(size))
		, m_begin(m_capacityBegin + beginIndex)
		, m_end(m_begin)
		, m_capacityEnd(m_capacityBegin + size)
	{
	}
	~Storage()
	{
		Free<Item>(m_begin, m_end);
		free(m_capacityBegin);
	}
	void swap(Storage& rhs) noexcept
	{
		std::swap(m_capacityBegin, rhs.m_capacityBegin);
		std::swap(m_capacityEnd, rhs.m_capacityEnd);
		std::swap(m_begin, rhs.m_begin);
		std::swap(m_end, rhs.m_end);
	}
	Item* m_capacityBegin;
	Item* m_begin;
	Item* m_end;
	Item* m_capacityEnd;
};

template<typename Item>
typename std::enable_if<std::is_pod<Item>::value, void>::
type CopyImpl(Storage<Item>& dst, const Storage<Item>& src)
{
	const auto size = src.m_end - src.m_begin;
	memcpy(dst.m_begin, src.m_begin, size * sizeof(Item));
	dst.m_end = dst.m_begin + size;
}

template<typename Item>
typename std::enable_if<!std::is_pod<Item>::value, void>::
type CopyImpl(Storage<Item>& dst, const Storage<Item>& src)
{
	for (auto* pSrc = src.m_begin; pSrc < src.m_end; ++pSrc, ++dst.m_end)
		new (dst.m_end) Item(*pSrc);
}

template<typename Item>
void Copy(Storage<Item>& dst, const Storage<Item>& src)
{
	assert(dst.m_end == dst.m_begin);									// destination must be empty
	assert(src.m_end - src.m_begin <= dst.m_capacityEnd - dst.m_begin);	// destination must has enough capacity

	CopyImpl(dst, src);

	assert(src.m_end - src.m_begin == dst.m_end - dst.m_begin);			// same size after copy
}

template<typename Item>
void Realloc(Storage<Item>& storage)
{
	assert(storage.m_capacityEnd > storage.m_capacityBegin);
	const auto newSize = 2 * (storage.m_capacityEnd - storage.m_capacityBegin);
	Storage<Item> newStorage(newSize, (newSize - (storage.m_capacityEnd - storage.m_capacityBegin)) / 2);
	Copy<Item>(newStorage, storage);
	newStorage.swap(storage);
}

template<typename Item>
typename std::enable_if<!(false
	|| std::is_integral	<Item>::value
	|| std::is_pointer	<Item>::value
), void>::
type CheckArgForNull(const Item& item)
{
	// no null argument possible
}

template<typename Item>
typename std::enable_if<std::is_integral<Item>::value, void>::
type CheckArgForNull(Item item)
{
	if (item == static_cast<Item>(0))
		throw std::invalid_argument("null argument");
}

template<typename Item>
typename std::enable_if<std::is_pointer<Item>::value, void>::
type CheckArgForNull(Item item)
{
	if (item == nullptr)
		throw std::invalid_argument("null argument");
}

} // namespace DequeDetails


template<typename Item>
class Deque;


template<typename Item>
class DequeIterator
{
	friend class Deque<Item>;

public:
	using self_type = DequeIterator;
	using value_type = Item;
	using reference = Item&;
	using pointer = Item*;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = int;

private:
	DequeIterator(pointer next, const pointer end) noexcept
		: m_next(next)
		, m_end(end)
	{
	}

public:
	DequeIterator() = delete;
	DequeIterator(const DequeIterator& rhs) = default;
	DequeIterator(DequeIterator&& rhs) = default;
	DequeIterator& operator=(const DequeIterator& rhs) = default;
	DequeIterator& operator=(DequeIterator&& rhs) = default;
	~DequeIterator() = default;

public:
	self_type& operator++() noexcept
	{
		++m_next;
		assert(m_next <= m_end);
		return *this;
	}

	self_type operator++(int) noexcept
	{
		self_type copy(*this);
		++(*this);
		return copy;
	}

	bool operator==(const self_type& rhs) const noexcept
	{
		return m_next == rhs.m_next;
	}

	bool operator!=(const self_type& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	reference operator*() noexcept
	{
		assert(m_next < m_end);
		return *m_next;
	}

	pointer operator->() noexcept
	{
		assert(m_next < m_end);
		return m_next;
	}

	self_type operator+(difference_type n) noexcept
	{
		self_type result(*this);
		result.m_next += n;
		return result;
	}

	self_type& operator+=(difference_type n) noexcept
	{
		*this = *this + n;
		return*this;
	}

public:
	// check if next item exists
	bool hasNext() const noexcept
	{
		return m_next < m_end;
	}

	// return the next item
	value_type next()
	{
		if (!hasNext())
			throw std::range_error("end reached");

		value_type item(*m_next++);
		return item;
	}

	// remove next item
	void remove()
	{
		throw std::domain_error("remove not allowed");
	}

private:
	pointer m_next;
	const pointer m_end;
};


template<typename Item>
class Deque {
public:
	Deque();										// construct an empty deque
	bool isEmpty() const noexcept;					// is the deque empty?
	int size() const noexcept;						// return the number of items on the deque
	void addFirst(Item item);						// add the item to the front
	void addLast(Item item);						// add the item to the end
	Item removeFirst();								// remove and return the item from the front
	Item removeLast();								// remove and return the item from the end
	using iterator =  DequeIterator<Item>;			// an iterator over items in order from front to end
	iterator begin();								// an iterator front
	iterator end();									// an iterator end

private:
	void CheckRemove() const;

private:
	DequeDetails::Storage<Item> m_storage;
};

template<typename Item>
Deque<Item>::Deque()
	: m_storage(DequeDetails::INIT_SIZE, DequeDetails::INIT_SIZE / 2)
{
}

template<typename Item>
bool Deque<Item>::isEmpty() const noexcept
{
	return m_storage.m_end == m_storage.m_begin;
}

template<typename Item>
int Deque<Item>::size() const noexcept
{
	assert(m_storage.m_end >= m_storage.m_begin);
	return static_cast<int>(m_storage.m_end - m_storage.m_begin);
}

template<typename Item>
void Deque<Item>::addFirst(Item item)
{
	DequeDetails::CheckArgForNull<Item>(item);
	if (m_storage.m_begin == m_storage.m_capacityBegin)
		Realloc(m_storage);

	assert(m_storage.m_begin > m_storage.m_capacityBegin);

	new (m_storage.m_begin - 1) Item(item);
	--m_storage.m_begin;
}

template<typename Item>
void Deque<Item>::addLast(Item item)
{
	DequeDetails::CheckArgForNull<Item>(item);
	if (m_storage.m_end == m_storage.m_capacityEnd)
		Realloc(m_storage);

	assert(m_storage.m_end < m_storage.m_capacityEnd);

	new (m_storage.m_end) Item(item);
	++m_storage.m_end;
}

template<typename Item>
Item Deque<Item>::removeFirst()
{
	CheckRemove();

	Item item(*m_storage.m_begin);
	m_storage.m_begin++->~Item();
	return item;
}

template<typename Item>
Item Deque<Item>::removeLast()
{
	CheckRemove();

	Item item(m_storage.m_end[-1]);
	(m_storage.m_end-- - 1)->~Item();
	return item;
}

template<typename Item>
typename Deque<Item>::iterator Deque<Item>::begin()
{
	return iterator(m_storage.m_begin, m_storage.m_end);
}

template<typename Item>
typename Deque<Item>::iterator Deque<Item>::end()
{
	return iterator(m_storage.m_end, m_storage.m_end);
}

template<typename Item>
void Deque<Item>::CheckRemove() const
{
	if (isEmpty())
		throw std::range_error("deque is empty");
}

} // namespace MyContainer
