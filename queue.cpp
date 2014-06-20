#include "queue.h"
#include <cstddef>

template <typename T>
class LQueue : public Queue<T> {
private:
	struct elem {
		elem(T const& _inf, elem* _link = NULL) :
			inf(_inf), link(_link) {}
		T inf;
		elem* link;
	};

	elem *front, *back;

	void copyQueue(LQueue const& q) {
		front=back=NULL;
		if (q.empty())
			return;
		push(q.front->inf);
		elem *toCopy = q.front->link;
		while (toCopy != NULL) {
			push(toCopy->inf);
			toCopy = toCopy->link;
		}
	}

	void delQueue() {
		T x;
		while (pop(x));
	}

public:
	LQueue() : front(NULL), back(NULL) {}

	LQueue(LQueue const& q) {
		copyQueue(q);
	}

	LQueue& operator=(LQueue const& q) 
	{
		if (&q != this) 
		{
			delQueue();
			copyQueue(q);
		}
		return *this;
	}

	~LQueue() {
		delQueue();
	}

	// проверка дали опашката е празна
	bool empty() const 
	{
		return front == NULL;
	}

	// добавяне на елемент накрая на опашката
	bool push(T const& x) 
	{
		if (empty()) {
			front = back = new elem(x);
		} else {
			back->link = new elem(x);
			back = back->link;
		}
		return true;
	}

	// изваждане на елемент от началото на опашката
	bool pop(T& x) 
	{
		if (empty())
			return false;
		x = front->inf;
		elem* p = front;
		front = front->link;
		if (front == NULL)
			back = NULL;
		delete p;
		return true;
	}

	// извличане на главата на опашкта
	bool head(T& x) const 
	{
		if (empty())
			return false;
		x = front->inf;
		return true;
	}

};
template<typename T>
int size(LQueue<T> q)
{
	int count=0;
	T x;
	while(q.pop(x))
		count++;
	return count;
}
