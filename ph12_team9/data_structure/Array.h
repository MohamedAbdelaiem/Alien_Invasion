#pragma once
#include<iostream>
using namespace std;
template <class T>
class Array
{
	enum Max_size{max=1000};
	T* arr[max];
	int count;
public:

	//default constructor
	Array() :count(0)     
	{
		for (int i = 0; i < max; i++) arr[i] = nullptr;
	}

	//check if the array is empty or not
	bool isEmpty()       
	{
		return (!count);
	}

	//insert element to the array
	bool insert(T item)     
	{
		if (count == max - 1) return false;  
		T* ptr = new T;
		*ptr = item;
		arr[count++] = ptr;
		return true;
	}

	//remove the element which has the given index
	bool remove(int index, T& item)   
	{
		if (index >= count||index<0) return false;  //check if the array is empty or the given index is not has an item or the index <0
		item = *arr[index];
		delete arr[index];
		arr[index] = arr[count-1];
		arr[count - 1] = nullptr;
		count--;
		return true;
	}
	//print the content of the array
	void display() 
	{
		cout << "[ ";
		for (int i = 0; i < count; i++)
		{
			cout << *arr[i]<<" ";
		}
		cout << "]";
		cout << endl;
	}
	int get_count()
	{
		return count;
	}
	//peek an item of an index 
	bool peek(T& item,int index)
	{
		if (isEmpty()) return false;
		item = *arr[index];
		return true;
	}
	~Array()
	{
		for (int i = 0; i < max; i++)
		{
			if (arr[i] != nullptr)
			{
				delete arr[i];
				arr[i] = nullptr;
			}
		}
	}
};