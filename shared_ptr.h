/*
 * Author: kmiku7 <kakoimiku@gmail.com>
 * File: shared_ptr.h
 * Create Date: 2014/05/25 23:59:58
 *
 * Brief:
 *  single thread version
 *
 **/

#pragma once

#include <cstddef>
#include <iostream>


namespace kmtl
{

template<typename T>
class shared_ptr
{
public:
  explicit shared_ptr(T* pt = NULL): ptr(NULL), ref_count(0)
  {
    if( pt == NULL)
      return;

    ref_count = new size_t;
    ptr = pt;
    *ref_count = 1;
  }

  shared_ptr(const shared_ptr& rhs): ptr(rhs.ptr), ref_count(rhs.ref_count)
  {
    if( rhs.ptr != NULL)
      ++(*ref_count);
  }

  ~shared_ptr()
  {
    release();
  }

  template<typename U>
  shared_ptr& operator=(shared_ptr<U>& rhs)
  {
    release();

    if( rhs.ptr == NULL)
      return *this;

    ptr = rhs.ptr;
    ref_count = rhs.ref_count;

    ++(*ref_count);
    return *this;
  }

  template<typename U>
  void set(U* pu)
  {
    release();

    if( pu == NULL)
      return;

    ref_count = new size_t;
    ptr = pu;
    *ref_count = 1;
  }
    
  
  T*& operator->()
  {
    return ptr;
  }

  size_t get_rc() const
  {
    return *ref_count;
  }
private:
  T* ptr;
  size_t* ref_count;

  void release()
  {
    if( ref_count == NULL)
      return;

    --(*ref_count);
    if( *ref_count == 0)
    {
      delete ptr;
      delete ref_count;
    }
    ptr = NULL;
    ref_count = NULL;
  }

  // forbid
  void* operator new(size_t size) {}
  void operator delete(void* ptr) {}

};

} // end namespace kmtl

/* vim: set ts=2 sw=2 sts=2 tw=80: */

