#ifndef QUEUE_H_
#define QUEUE_H_

template <typename T>
class Queue 
{
public:
	// проверка дали опашката е празна
	virtual bool empty() const = 0;
	// добавяне на елемент накрая на опашката
	virtual bool push(T const&) = 0;
	// изваждане на елемент от началото на опашката
	virtual bool pop(T&) = 0;
	// извличане на главата на опашкта
	virtual bool head(T&) const = 0;
};


#endif /* QUEUE_H_ */
