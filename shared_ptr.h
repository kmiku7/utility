/*
 * Author: kmiku7 <kakoimiku@gmail.com>
 * File: shared_ptr.h
 * Create Date: 2014/05/25 23:59:58
 *
 * Brief:
 *  thread-safe
 *
 **/

#pragma once

#include <cstddef>
#include <iostream>

#ifdef __APPLE__
#include <libkern/OSAtomic.h>
#endif

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

    init(pt);

  }

  shared_ptr(const shared_ptr& rhs): ptr(rhs.ptr), ref_count(rhs.ref_count)
  {
    if( rhs.ptr != NULL)
    {
#ifdef __APPLE__
      OSAtomicIncrement64Barrier(ref_count);
#endif
    }
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

#ifdef __APPLE__
    OSAtomicIncrement64Barrier(ref_count);
#endif
    return *this;
  }

  template<typename U>
  void set(U* pu)
  {
    release();

    if( pu == NULL)
      return;

    init(pu);
  }
    
  
  T*& operator->()
  {
    return ptr;
  }

  int64_t get_rc() const
  {
    return *ref_count;
  }
private:
  T* ptr;
#ifdef __APPLE__
  volatile int64_t* ref_count;
#endif

  void release()
  {
    if( ref_count == NULL)
      return;

#ifdef __APPLE__
    if( OSAtomicDecrement64Barrier(ref_count) == 0)
    {
      delete ptr;
      delete ref_count;
    }
    ptr = NULL;
    ref_count = NULL;
#endif
  }

  void init(T* pt)
  {
#ifdef __APPLE__
    ref_count = new int64_t(1);
#endif
    ptr = pt;
  }

  // forbid
  void* operator new(size_t size) {}
  void operator delete(void* ptr) {}

};

} // end namespace kmtl

/* vim: set ts=2 sw=2 sts=2 tw=80: */

