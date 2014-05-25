/*
 * Author: kmiku7 <kakoimiku@gmail.com>
 * File: test_shared_ptr.cpp
 * Create Date: 2014/05/26 00:20:04
 *
 * Brief:
 *
 *
 **/

#include "shared_ptr.h"
#include <iostream>

class foo
{
public:
  foo(int _tag): tag(_tag)
  {
    std::cout << "foo cons tag: " << tag << std::endl;
  }

  virtual ~foo()
  {
    std::cout << "foo des tag: " << tag << std::endl;
  }

  virtual void print_tag()
  {
    std::cout << "foo print_tag: " << tag << std::endl;
  }

protected:
  int tag;
};

class bar: public foo
{
public:
  bar(int _tag): foo(_tag)
  {
    std::cout << "bar cons tag: " << tag << std::endl;
  }

  ~bar()
  {
    std::cout << "bar des tag: " << tag << std::endl;
  }

  void print_tag()
  {
    std::cout << "bar print_tag: " << tag << std::endl;
  }
};

int main(int argc, char** argv)
{
  using kmtl::shared_ptr;

  shared_ptr<foo> s1;
  //shared_ptr<foo>* ps = new shared_ptr<foo>;

  foo* f = new foo(1);

  s1.set(f);
  std::cout << "rc " << s1.get_rc() << std::endl;

  {
    std::cout << "step in inner" << std::endl;
    shared_ptr<foo> s2 = s1;
    std::cout << "step out inner" << std::endl;
    std::cout << "rc " << s1.get_rc() << std::endl;
    std::cout << "rc " << s2.get_rc() << std::endl;
  }
  std::cout << "split --- " << std::endl;
  std::cout << "rc " << s1.get_rc() << std::endl;
  
  shared_ptr<foo> s3(new foo(2));
  std::cout << "rc " << s3.get_rc() << std::endl;

  s1 = s3;
  std::cout << "end" << std::endl;
  return 0;
}


/* vim: set ts=2 sw=2 sts=2 tw=80: */

