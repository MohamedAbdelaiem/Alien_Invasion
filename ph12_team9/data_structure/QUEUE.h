#pragma once
#include"LinkedQueue.h"
template<class T>
class QUEUE : public LinkedQueue<T> 
{
	bool add_first_or_last_flag;
	bool delete_first_or_last_flag;
public:
	QUEUE(): add_first_or_last_flag(true), delete_first_or_last_flag(true)
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
		if (add_first_or_last_flag)
		{
			enqueue_first(entry);
			add_first_or_last_flag =false;
		}
		else
		{
			this->enqueue(entry);
			add_first_or_last_flag = true;
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
	bool delete_first_or_last(T& element1)
	{
		if (this->delete_first_or_last_flag)
		{
			if (this->dequeue(element1))
			{
				delete_first_or_last_flag = false;
				return true;
			}
				return false;
		}
		else
		{
			if (this->dequeue_last(element1))
			{
				delete_first_or_last_flag = true;
				return true;
			}
				return false;
		}
	}
	void set_starting_dequeue_first() //--> to start dequeue from first
	{
		delete_first_or_last_flag = true;
	}

	
};

