#pragma once
#include "stdafx.h"

template<typename type>
class DList
{
private:
	struct node
	{
		type data;
		node* next, *prev;

		node( type _data, node* _prev, node* _next ) : data( _data ), prev( _prev ), next( _next )
		{
		}
	};

	node* first, *last;
	int size;

public:
	DList()
	{
		first = last = nullptr;
		size = 0;
	}

	DList( const DList& _other );

	int getSize() const
	{
		return size;
	}

	~DList();

	void clear( void );
	void push_back( type _data );
	void push_front( type _data );
	void erase( int _index );
	type& operator[]( int _index );
	const type& operator[]( int _index ) const;
	DList<type>& operator=( const DList<type>& _other );
};

template<typename type>
void DList<type>::erase( int _index )
{
	if ( _index < 0 || size <= _index )
		throw std::out_of_range( "DList_erase_IndexOutOfRange" );
	else
	{
		if ( first == last )
		{
			delete first;
			first = last = nullptr;
			size = 0;
			return;
		}

		node* t = first;

		for ( int i = 0; i < _index; ++i )
			t = t->next;

		if ( t == last )
		{
			t->prev->next = nullptr;
			last = last->prev;
		}
		else if ( t == first )
		{
			t->next->prev = nullptr;
			first = first->next;
		}
		else
		{
			t->next->prev = t->prev;
			t->prev->next = t->next;
		}

		delete t;
		--size;
	}
}

template<typename type>
void DList<type>::clear( void )
{
	for ( node* t = first; first; t = first )
	{
		first = first->next;
		delete t;
	}
	size = 0;
	first = last = nullptr;
}

template<typename type>
void DList<type>::push_back( type _data )
{
	node* n = new node( _data, last, nullptr );

	if ( last )
		last->next = n;
	else
		first = n;

	last = n;

	++size;
}

template<typename type>
void DList<type>::push_front( type _data )
{
	node* n = new node( _data, nullptr, first );

	if ( first )
		first->prev = n;
	else
		last = n;

	first = n;

	++size;
}

template<typename type>
type& DList<type>::operator[]( int _index )
{
	if ( _index < 0 || size <= _index )
		throw std::out_of_range( "DList_operator[]_IndexOutOfRange" );
	else
	{
		node* t = first;

		int i = 0;
		for ( ; i < _index; ++i )
			t = t->next;

		return t->data;
	}
}

template<typename type>
const type& DList<type>::operator[]( int _index ) const
{
	if ( _index < 0 || _index >= size )
		throw std::out_of_range( "DList_operator[]_const_IndexOutOfRange" );
	else
	{
		node* t = first;

		int i = 0;
		for ( ; i < _index; ++i )
			t = t->next;

		return t->data;
	}
}

template<typename type>
DList<type>::DList( const DList<type> & _other )
{
	first = last = nullptr;
	size = 0;
	for ( node* temp = _other.first; temp; temp = temp->next ) push_back( temp->data );
}

template<typename type>
DList<type>::~DList()
{
	for ( node* t = first; first; t = first )
	{
		first = first->next;
		delete t;
	}
}

template<typename type>
DList<type>& DList<type>::operator=( const DList<type>& _other )
{
	if ( this != &_other )
	{
		clear();
		node* t = _other.first;
		while ( t )
		{
			push_back( t->data );
			t = t->next;
		}
	}

	return *this;
}

// ☻☺ トニー ☺☻ -- Y:2015年 //