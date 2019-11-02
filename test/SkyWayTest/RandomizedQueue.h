#pragma once
#include <cassert>
#include <chrono>
#include <memory>
#include <new>
#include <random>
#include <type_traits>

namespace MyContainer {

namespace RandomizedQueueDetals {

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
	explicit Storage(size_t size)
		: m_begin(Alloc<Item>(size))
		, m_end(m_begin)
		, m_capacity(m_begin + size)
	{
	}
	~Storage()
	{
		Free<Item>(m_begin, m_end);
		free(m_begin);
	}
	void swap(Storage& rhs) noexcept
	{
		std::swap(m_begin, rhs.m_begin);
		std::swap(m_end, rhs.m_end);
		std::swap(m_capacity, rhs.m_capacity);
	}
	Item* m_begin;
	Item* m_end;
	Item* m_capacity;
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
	assert(src.m_end - src.m_begin <= dst.m_capacity - dst.m_begin);	// destination must has enough capacity

	CopyImpl(dst, src);

	assert(src.m_end - src.m_begin == dst.m_end - dst.m_begin);			// same size after copy
}

template<typename Item>
typename std::enable_if<std::is_pod<Item>::value, void>::
type Realloc(Storage<Item>& storage)
{
	assert(storage.m_capacity > storage.m_begin);
	const auto size = storage.m_capacity - storage.m_begin;
	const auto newSize = 2 * size;

	auto *data = reinterpret_cast<Item*>(realloc(storage.m_begin, newSize * sizeof(Item)));
	if (!data)
		throw std::bad_alloc();

	storage.m_begin = data;
	storage.m_end = storage.m_begin + size;
	storage.m_capacity = storage.m_begin + newSize;
}

template<typename Item>
typename std::enable_if<!std::is_pod<Item>::value, void>::
type Realloc(Storage<Item>& storage)
{
	assert(storage.m_capacity > storage.m_begin);
	const auto newSize = 2 * (storage.m_capacity - storage.m_begin);

	Storage<Item> newStorage(newSize);
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

} // namespace RandomizedQueueDetals

template<typename Item>
class RandomizedQueue;

template<typename Item>
class RandomizedQueueIterator
{
	friend class RandomizedQueue<Item>;

public:
	using self_type = RandomizedQueueIterator;
	using value_type = Item;
	using reference = Item &;
	using pointer = Item *;
	using difference_type = int;

private:
	RandomizedQueueIterator(pointer srcBegin, pointer& srcEnd, std::default_random_engine& ramdonEngine)
		: m_data(std::make_unique<pointer[]>(srcEnd - srcBegin + 1))
		, m_next(m_data.get())
		, m_end(m_next + (srcEnd - srcBegin))
		, m_srcEnd(srcEnd)
	{
		assert(srcBegin <= srcEnd);
		m_next[srcEnd - srcBegin] = srcEnd;
		for (auto dst = m_next; srcBegin < srcEnd; ++srcBegin, ++dst)
			*dst = srcBegin;

		std::shuffle(m_next, m_end, ramdonEngine);
	}

	explicit RandomizedQueueIterator(pointer& srcEnd)
		: m_data(nullptr)
		, m_next(&srcEnd)
		, m_end(m_next)
		, m_srcEnd(srcEnd)
	{
	}

public:
	RandomizedQueueIterator() = delete;
	RandomizedQueueIterator(const RandomizedQueueIterator& rhs) = default;
	RandomizedQueueIterator(RandomizedQueueIterator&& rhs) = default;
	RandomizedQueueIterator& operator=(const RandomizedQueueIterator& rhs) = default;
	RandomizedQueueIterator& operator=(RandomizedQueueIterator&& rhs) = default;
	~RandomizedQueueIterator() = default;

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
		return *m_next == *rhs.m_next;
	}

	bool operator!=(const self_type& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	reference operator*() noexcept
	{
		assert(m_next < m_end);
		return **m_next;
	}

	pointer operator->() noexcept
	{
		assert(m_next < m_end);
		return *m_next;
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

		value_type item(**m_next++);
		return item;
	}

	// remove next item
	void remove()
	{
		using std::swap;
		if (*m_next + 1 < m_srcEnd)
			swap(**m_next, m_srcEnd[-1]);

		(m_srcEnd-- - 1)->~Item();
		++m_next;
	}

private:
	std::unique_ptr<pointer[]> m_data;
	pointer* m_next;
	pointer* m_end;
	pointer& m_srcEnd;
};


template<typename Item>
class RandomizedQueue {
public:
	RandomizedQueue();									// construct an empty randomized queue
	bool isEmpty() const noexcept;						// is the randomized queue empty?
	int size() const noexcept;							// return the number of items on the randomized queue
	void enqueue(Item item);							// add the item
	Item dequeue();										// remove and return a random item
	Item sample() const;								// return a random item (but do not remove it)
	using iterator =  RandomizedQueueIterator<Item>;	// an independent iterator over items in random order
	iterator begin();									// an iterator front
	iterator end();										// an iterator end

private:
	void CheckAccess() const
	{
		if (isEmpty())
			throw std::range_error("queue is empty");
	}

private:
	RandomizedQueueDetals::Storage<Item> m_storage;
	mutable std::default_random_engine m_ramdonEngine;
};

template<typename Item>
RandomizedQueue<Item>::RandomizedQueue()
	: m_storage(RandomizedQueueDetals::INIT_SIZE)
	, m_ramdonEngine(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()))
{
}

template<typename Item>
bool RandomizedQueue<Item>::isEmpty() const noexcept
{
	return m_storage.m_end == m_storage.m_begin;
}

template<typename Item>
int RandomizedQueue<Item>::size() const noexcept
{
	assert(m_storage.m_end >= m_storage.m_begin);
	return static_cast<int>(m_storage.m_end - m_storage.m_begin);
}

template<typename Item>
void RandomizedQueue<Item>::enqueue(Item item)
{
	RandomizedQueueDetals::CheckArgForNull<Item>(item);
	if (m_storage.m_end == m_storage.m_capacity)
		Realloc(m_storage);

	assert(m_storage.m_end < m_storage.m_capacity);

	new (m_storage.m_end) Item(item);
	++m_storage.m_end;
}

template<typename Item>
Item RandomizedQueue<Item>::dequeue()
{
	using std::swap;
	CheckAccess();

	auto index = m_ramdonEngine() % (m_storage.m_end - m_storage.m_begin);
	if (m_storage.m_begin + index + 1 < m_storage.m_end)
		swap(m_storage.m_begin[index], m_storage.m_end[-1]);

	Item item(m_storage.m_end[-1]);
	(m_storage.m_end-- - 1)->~Item();
	return item;
}

template<typename Item>
Item RandomizedQueue<Item>::sample() const
{
	CheckAccess();
	return Item(*(m_storage.m_begin + m_ramdonEngine() % (m_storage.m_end - m_storage.m_begin)));
}

template<typename Item>
typename RandomizedQueue<Item>::iterator RandomizedQueue<Item>::begin()
{
	return iterator(m_storage.m_begin, m_storage.m_end, m_ramdonEngine);
}

template<typename Item>
typename RandomizedQueue<Item>::iterator RandomizedQueue<Item>::end()
{
	return iterator(m_storage.m_end);
}

} // namespace MyContainer
