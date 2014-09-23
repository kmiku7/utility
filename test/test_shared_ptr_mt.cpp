/*
 * Author: kmiku7 <kakoimiku@gmail.com>
 * File: test_shared_ptr_mt.cpp
 * Create Date: 2014/05/26 12:36:13
 *
 * Brief:
 *
 *
 **/

#include "shared_ptr.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cassert>
#include <cstdio>

using namespace std;

class foo
{
public:
  foo()
  {
    cout << pthread_self() << "\tcons" << endl;
  }

  ~foo()
  {
    cout << pthread_self() << "\tdes" << endl;
  }

  void print_tag()
  {
    //cout << pthread_self() << "\t TAG:" << this << endl;
    printf("pid:%p, %p\n", pthread_self(), this);
  }

};

class thread_frame
{
public:
  kmtl::shared_ptr<foo> ptr;
  size_t idx;
};

void* process(void* frm)
{
  thread_frame* frame = static_cast<thread_frame*>(frm);
  assert(frame!=NULL);

  for( int i = 0; i < 20; ++i)
  {
    int sleep_time = arc4random_uniform(100);
    usleep(sleep_time);
    kmtl::shared_ptr<foo> ptr = frame->ptr;
    ptr->print_tag();
  }

  return NULL;
}

int main(int argc, char** argv)
{
  const int thread_num = 100;
  pthread_t pid[thread_num] = {0};

  thread_frame frame;
  thread_frame* thd_frm[thread_num] = {0};

  foo* f = new foo;
  frame.ptr.set(f);

  for( int i = 0; i < thread_num; ++i)
  {
    thd_frm[i] = new thread_frame(frame);
    pthread_create( pid+i, NULL, process, static_cast<void*>(thd_frm[i]));
  }

  for( int i = 0; i < thread_num; ++i)
  {
    pthread_join(pid[i], NULL);
  }

  for( int i = 0; i < thread_num; ++i)
  {
    delete thd_frm[i];
    thd_frm[i] = NULL;
  }

  return 0;
}


/* vim: set ts=2 sw=2 sts=2 tw=80: */

