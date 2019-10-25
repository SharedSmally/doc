#ifndef CPW_TRAITS_H
#define CPW_TRAITS_H

#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <typeinfo>

/*
Container class templates
Sequence containers:
array	Array class (class template )
vector	Vector (class template )
deque	Double ended queue (class template )
forward_list	Forward list (class template )
list	List (class template )

Container adaptors:
stack	LIFO stack (class template )
queue	FIFO queue (class template )
priority_queue	Priority queue (class template )

Associative containers:
set			Set (class template )
multiset	Multiple-key set (class template )
map			Map (class template )
multimap	Multiple-key map (class template )

Unordered associative containers:
unordered_set		Unordered Set (class template )
unordered_multiset 	Unordered Multiset (class template )
unordered_map 		Unordered Map (class template )
unordered_multimap 	Unordered Multimap (class template )
*/

enum ContainerType {
	VECTOR,     //vector
	DEQUE,      //deque
	LIST,       //list
	STACK,      //stack
	QUEUE,      //queue
	PRIO_QUEUE  //priority_queue
};

template <typename T, ContainerType CTYPE = VECTOR>
struct ContainerTraits {
	typedef T elem_type;
	typedef std::vector<T> type;

	static const char* classname() noexcept { return typeid(type).name(); }

};

template <typename T >
struct ContainerTraits<T, ContainerType::DEQUE> {
	typedef T elem_type;
	typedef std::deque<T> type;
};

template <typename T >
struct ContainerTraits<T, ContainerType::LIST> {
	typedef T elem_type;
	typedef std::list<T> type;
};

template <typename T >
struct ContainerTraits<T, ContainerType::STACK> {
	typedef T elem_type;
	typedef std::stack<T> type;
};

template <typename T >
struct ContainerTraits<T, ContainerType::QUEUE> {
	typedef T elem_type;
	typedef std::queue<T> type;
};

template <typename T >
struct ContainerTraits<T, ContainerType::PRIO_QUEUE> {
	typedef T elem_type;
	typedef std::priority_queue<T> type;
};

// set type traits
template <typename T, bool ordered=true, bool multiple=false>
struct SetTraits {
	typedef T elem_type;
	typedef std::set<T> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};
template <typename T>
struct SetTraits<T, false, false> {
	typedef T elem_type;
	typedef std::unordered_set<T> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};
template <typename T>
struct SetTraits<T, true, true> {
	typedef T elem_type;
	typedef std::multiset<T> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};
template <typename T>
struct SetTraits<T, false, true> {
	typedef T elem_type;
	typedef std::unordered_multiset<T> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};

// map type traits
template <typename KEY, typename VALUE, bool ordered=true, bool multiple=false>
struct MapTraits {
	typedef KEY key_type;
	typedef VALUE value_type;
	typedef std::map<KEY, VALUE> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};
template <typename KEY, typename VALUE>
struct MapTraits<KEY, VALUE, false, false> {
	typedef KEY key_type;
	typedef VALUE value_type;
	typedef std::unordered_map<KEY,VALUE> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};
template <typename KEY, typename VALUE>
struct MapTraits<KEY, VALUE, true, true> {
	typedef KEY key_type;
	typedef VALUE value_type;
	typedef std::multimap<KEY, VALUE> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};
template <typename KEY, typename VALUE>
struct MapTraits<KEY, VALUE, false, true> {
	typedef KEY key_type;
	typedef VALUE value_type;
	typedef std::unordered_multimap<KEY, VALUE> type;
	static const char* classname() noexcept { return typeid(type).name(); }
};

#endif

