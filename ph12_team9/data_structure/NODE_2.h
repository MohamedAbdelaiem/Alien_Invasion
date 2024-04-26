#pragma once
template<class T>
class NODE_2 
{
private:
	NODE_2<T>* prev;//pointer to the previous node
	NODE_2<T>* next;//pointer to the next node
	T item;
public:
	//default constructor
	NODE_2()
	{
		next = prev = nullptr;
	}
	//non default constructors
	NODE_2(const T& r_Item)
	{
		next = nullptr;
		prev = nullptr;
		item = r_Item;
	}
	NODE_2(const T& r_Item, NODE_2<T>* previous, NODE_2<T>* Next)
	{
		item = r_Item;
		next = Next;
		prev = previous;
	}
	//set the previous pointer
	void set_prev(NODE_2<T>* prevptr)
	{
		prev = prevptr;
	}
	//get the previous pointer
	NODE_2<T>* get_prev() const
	{
		return prev;
	}
	//set the next pointer
	void set_next(NODE_2<T>* NEXT)
	{
		next = NEXT;
	}
	//get the next pointer
	NODE_2<T>* getNext() const
	{
		return next;
	}
	//set the data
	void set_item(T enter_item)
	{
		item = enter_item;
	}
	//get the data
	T get_item()
	{
		return item;
	}
};

