#pragma once
#include"LinkedQueue.h"
template<class T>
class QUEUE : public LinkedQueue<T> 
{
	bool flag;
public:
	QUEUE(): flag(true)
	{
	}
	bool enqueue_first(const T &entry)
	{
		if (this->isEmpty())
		{
			this->enqueue(entry);
		}
		else
		{
			NODE_2<T>* temp= new NODE_2<T> (entry);
			temp->set_next(this->frontPtr);
			this->frontPtr->set_prev(temp);
			this->frontPtr = temp;
			this->count++;
		}
		return true;
	}
	bool enqueue_first_last(const T& entry)
	{
		if (flag)
		{
			enqueue_first(entry);
			flag=false;
		}
		else
		{
			this->enqueue(entry);
			flag = true;
		}
		return true;
	}
	//dequeue from the first and the end of the queue
	bool dequeue_last_first(T& front_entry,T& last_entry)
	{
		if (this->isEmpty()||this->frontPtr==this->backPtr)
		{
			return false;
		}
		else
		{
			this->dequeue(front_entry);
			dequeue_last(last_entry);
			return true;
		}
	}
	//dequeue from the end of the modified queue
	bool dequeue_last(T& element)
	{	
		if (this->frontPtr == this->backPtr)
		{
			return this->dequeue(element);			
		}
		else
		{
			NODE_2<T>* update = this->backPtr->get_prev();
			update->set_next(nullptr);
			element = this->backPtr->get_item();
			delete this->backPtr;
			this->backPtr = update;
			this->count--;
			return true;
		}
	}
	//peek from first and last of the modified queue
	bool peek_last_first(T& element1, T& element2)
	{
		if (this->frontPtr == this->backPtr)
		{
			return false;
		}
		else
		{
			element1 =this->frontPtr->get_item();
			element2 = this->backPtr->get_item();
			return true;
		}
	}

	
};

