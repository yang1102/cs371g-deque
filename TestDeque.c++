// --------------------------------
// projects/c++/deque/TestDeque.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// http://www.cplusplus.com/reference/deque/deque/

// --------
// includes
// --------

#include <deque>     // deque
#include <stdexcept> // invalid_argument, out_of_range

#include "gtest/gtest.h"

#include "Deque.h"

// -----
// Using
// -----

using namespace std;

using testing::Test;
using testing::Types;

// -----
// Types
// -----

template <typename T> struct Deque_Fixture : Test {
  using deque_type = T;
  using value_type = typename deque_type::value_type;
};

typedef Types<deque<int>, my_deque<int> > deque_types;

TYPED_TEST_CASE(Deque_Fixture, deque_types);

// -----
// Tests
// -----

TYPED_TEST(Deque_Fixture, test_1) {
  using deque_type = typename TestFixture::deque_type;
  const deque_type x;
  ASSERT_TRUE(x.empty());
}

TYPED_TEST(Deque_Fixture, equal_1) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(10, 4);
  deque_type y(10, 4);
  ASSERT_TRUE(x == y);
}

TYPED_TEST(Deque_Fixture, equal_2) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(10, 4);
  deque_type y(10, 5);
  ASSERT_TRUE(x != y);
}

TYPED_TEST(Deque_Fixture, equal_3) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(11, 4);
  deque_type y(10, 4);
  ASSERT_FALSE(x == y);
}

TYPED_TEST(Deque_Fixture, equal_4) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(10, 4);
  deque_type y(10, 4);
  *(x.end() - 2) = 10;
  ASSERT_FALSE(x == y);
}

TYPED_TEST(Deque_Fixture, less_1) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(4, 'a');
  deque_type y(4, 'b');
  ASSERT_TRUE(x < y);
}

TYPED_TEST(Deque_Fixture, less_2) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(4, 'a');
  deque_type y(5, 'a');
  ASSERT_TRUE(x < y);
}

TYPED_TEST(Deque_Fixture, less_3) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(4, 10);
  deque_type y(4, 40);
  ASSERT_TRUE(x < y);
}

TYPED_TEST(Deque_Fixture, less_4) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(4, 10);
  deque_type y(4, 10);
  *(x.begin()) = 6;
  ASSERT_TRUE(x < y);
}

TYPED_TEST(Deque_Fixture, iterator_equal_1) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin();
  iterator b = x.begin();
  ASSERT_TRUE(a == b);
}

TYPED_TEST(Deque_Fixture, iterator_equal_2) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin();
  iterator b = x.end();
  ASSERT_FALSE(a == b);
}

TYPED_TEST(Deque_Fixture, iterator_equal_3) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin();
  iterator b = x.end();
  ASSERT_TRUE(a != b);
}

TYPED_TEST(Deque_Fixture, iterator_equal_4) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  deque_type y(4, 10);
  iterator a = x.begin();
  iterator b = y.begin();
  ASSERT_TRUE(a != b);
}

TYPED_TEST(Deque_Fixture, iterator_plus_1) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 3);
  iterator a = x.begin() + 2;
  *a = 4;
  ASSERT_TRUE(x[2] == 4);
}

TYPED_TEST(Deque_Fixture, iterator_plus_2) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin() + 3;
  *a = 4;
  ASSERT_TRUE(x[3] == 4);
}

TYPED_TEST(Deque_Fixture, iterator_minus_1) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(10, 4);
  iterator a = x.end() - 2;
  iterator b = x.end() - 3;
  iterator c = x.end() - 5;
  *a = 17;
  *b = 9;
  *c = 2;

  ASSERT_TRUE(x[8] == 17 && x[7] == 9 && x[5] == 2);
}

TYPED_TEST(Deque_Fixture, iterator_constructor_1) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin();
  *(x.begin()) = 5;
  ASSERT_EQ(*a, 5);
}

TYPED_TEST(Deque_Fixture, iterator_constructor_2) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin() + 3;
  ASSERT_EQ(*a, 10);
}

TYPED_TEST(Deque_Fixture, iterator_pre_inc) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin();
  iterator c = ++a;
  iterator b = x.begin() + 1;
  ASSERT_TRUE(b == a && c == b);
}

TYPED_TEST(Deque_Fixture, iterator_post_inc) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.begin();
  iterator c = a++;
  iterator b = x.begin() + 1;
  ASSERT_TRUE(b == a && c == x.begin());
}

TYPED_TEST(Deque_Fixture, iterator_pre_dec) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.end();
  iterator c = --a;
  iterator b = x.end() - 1;
  ASSERT_TRUE(b == a && c == b);
}

TYPED_TEST(Deque_Fixture, iterator_post_dec) {
  using deque_type = typename TestFixture::deque_type;
  using iterator = typename deque_type::iterator;
  deque_type x(4, 10);
  iterator a = x.end();
  iterator c = a--;
  iterator b = x.end() - 1;
  ASSERT_TRUE(b == a && c == x.end());
}

TYPED_TEST(Deque_Fixture, const_iterator_equal_1) {
  using deque_type = typename TestFixture::deque_type;
  using const_iterator = typename deque_type::const_iterator;

  const deque_type x(4, 10);
  const_iterator a = x.begin();
  const_iterator b = x.begin();
  ASSERT_TRUE(a == b);
}

TYPED_TEST(Deque_Fixture, const_iterator_equal_2) {
  using deque_type = typename TestFixture::deque_type;
  using const_iterator = typename deque_type::const_iterator;
  const deque_type x(4, 10);
  const deque_type y(4, 10);
  const_iterator a = x.begin();
  const_iterator b = y.begin();
  ASSERT_TRUE(a != b);
}

TYPED_TEST(Deque_Fixture, inc_const_iterator_1) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(10, 0);

  int count = 0;

  for (typename deque_type::const_iterator i = x.begin(); i != x.end(); ++i) {

    ++count;
  }

  ASSERT_EQ(count, 10);
}

TYPED_TEST(Deque_Fixture, inc_test_const_iterator_2) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(25, 1);

  int count = 0;

  for (typename deque_type::const_iterator i = x.begin(); i != x.end(); ++i) {
    ++count;
  }

  ASSERT_EQ(count, 25);
}

TYPED_TEST(Deque_Fixture, inc_test_const_iterator_3) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(47, 0);

  int count = 0;

  for (typename deque_type::const_iterator i = x.begin(); i != x.end(); ++i) {
    ++count;
  }

  ASSERT_EQ(count, 47);
}

// DEC ITER

TYPED_TEST(Deque_Fixture, dec_test_const_iterator_1) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(10, 0);

  int count = 0;

  for (typename deque_type::const_iterator i = x.end() - 1; i != x.begin();
       --i) {
    ++count;
  }

  ASSERT_EQ(count, 9);
}
TYPED_TEST(Deque_Fixture, dec_test_const_iterator_2) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(10, 0);

  int count = 0;

  for (typename deque_type::const_iterator i = x.end() - 1; i != x.begin();
       --i) {
    ++count;
  }

  ASSERT_EQ(count, 9);
}

// +=

TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_1) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(10, 0);
  typename deque_type::const_iterator i = x.begin();

  ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_2) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(10, 0);
  typename deque_type::const_iterator i = x.begin();

  ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_3) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(45, 0);
  typename deque_type::const_iterator i = x.begin();

  i += 25;

  ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_1) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(10, 0);
  typename deque_type::const_iterator i = x.end() - 1;
  i -= 5;

  ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_2) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(10, 0);
  typename deque_type::const_iterator i = x.end() - 1;

  i -= 5;

  ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_3) {
  typedef typename TestFixture::deque_type deque_type;

  const deque_type x(16, 0);
  typename deque_type::const_iterator i = x.end() - 1;
  i -= 5;

  ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, erase1) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x(16, 1);

  typename deque_type::iterator i = x.begin();

  x.erase(i + 2);

  ASSERT_EQ(x.size(), 15);
}

TYPED_TEST(Deque_Fixture, erase2) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x(16, 1);

  typename deque_type::iterator i = x.begin();

  x.erase(i + 7);

  ASSERT_EQ(x.size(), 15);
}

TYPED_TEST(Deque_Fixture, erase3) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x(16, 1);

  typename deque_type::iterator i = x.begin();

  x.erase(i + 10);
  x.erase(i + 2);

  ASSERT_EQ(x.size(), 14);
}

// INSERT
TYPED_TEST(Deque_Fixture, insert1) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x(16, 1);

  typename deque_type::iterator i = x.begin();

  x.insert(i, 5);

  ASSERT_EQ(x.size(), 17);
  ASSERT_EQ(x[0], 5);
}

TYPED_TEST(Deque_Fixture, insert2) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x(28, 1);

  typename deque_type::iterator i = x.end();

  x.insert(i, 20);

  ASSERT_EQ(x.size(), 29);
  ASSERT_EQ(x[28], 20);
}

// RESIZE

TYPED_TEST(Deque_Fixture, resize1) {

  typedef typename TestFixture::deque_type deque_type;

  deque_type x(5, 0);

  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  x[3] = 3;
  x[4] = 4;

  x.resize(4);

  ASSERT_EQ(x.size(), 4);
  ASSERT_EQ(x.back(), 3);
}

TYPED_TEST(Deque_Fixture, resize2) {

  typedef typename TestFixture::deque_type deque_type;

  deque_type x(25, 0);

  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  x[3] = 3;
  x[4] = 4;

  x.resize(0);

  ASSERT_EQ(x.size(), 0);
}

TYPED_TEST(Deque_Fixture, resize3) {

  typedef typename TestFixture::deque_type deque_type;

  deque_type x(175, 0);

  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  x[3] = 3;
  x[4] = 4;

  x.resize(95);

  ASSERT_EQ(x.size(), 95);
}

TYPED_TEST(Deque_Fixture, resize4) {

  typedef typename TestFixture::deque_type deque_type;

  deque_type x(45, 0);

  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  x[3] = 3;
  x[4] = 4;

  x.resize(59);

  ASSERT_EQ(x.size(), 59);
}

TYPED_TEST(Deque_Fixture, resize5) {

  typedef typename TestFixture::deque_type deque_type;

  deque_type x(45, 0);

  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  x[3] = 3;
  x[4] = 4;

  x.resize(5);

  ASSERT_EQ(x.size(), 5);
}

TYPED_TEST(Deque_Fixture, resize6) {

  typedef typename TestFixture::deque_type deque_type;

  deque_type x(41, 0);

  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  x[3] = 3;
  x[4] = 4;

  x.resize(59);

  ASSERT_EQ(x.size(), 59);
}

TYPED_TEST(Deque_Fixture, resize7) {

  typedef typename TestFixture::deque_type deque_type;

  deque_type x(25, 0);

  x[0] = 0;
  x[1] = 1;
  x[2] = 2;
  x[3] = 3;
  x[4] = 4;

  x.resize(63);

  ASSERT_EQ(x.size(), 63);
}

// TEST REPO SOMEONE ELSES RESIZE TEST
TYPED_TEST(Deque_Fixture, resize_test_1) {
  typedef typename TestFixture::deque_type deque_type;
  deque_type x(3, 1);
  x.resize(3, 2);
  ASSERT_EQ(3, x.size());
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(1, x[i]);
  }
}

TYPED_TEST(Deque_Fixture, resize_test_3) {
  typedef typename TestFixture::deque_type deque_type;
  deque_type x(5);
  for (int i = 0; i < 5; ++i) {
    x[i] = i;
  }
  x.resize(3);
  ASSERT_EQ(3, x.size());
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(i, x[i]);
  }
}

// SWAP
TYPED_TEST(Deque_Fixture, swap1) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x(15, 2);
  deque_type y(10, 3);
  x.swap(y);
  ASSERT_EQ(x.size(), 10);
}

TYPED_TEST(Deque_Fixture, swap2) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x;
  deque_type y(75, 3);
  x.swap(y);
  ASSERT_EQ(x.size(), 75);
}

TYPED_TEST(Deque_Fixture, swap3) {
  typedef typename TestFixture::deque_type deque_type;

  deque_type x(16, 16);
  deque_type y(27, 13);
  x.swap(y);
  ASSERT_EQ(x.size(), 27);
  ASSERT_EQ(*x.begin(), 13);
}

TYPED_TEST(Deque_Fixture, push_back_1) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(7, 1);
  x.push_back(20);
  ASSERT_EQ(x.size(), 8);
  ASSERT_EQ(x.front(), 1);
  ASSERT_EQ(x[7], 20);
}

TYPED_TEST(Deque_Fixture, push_front_1) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(11, 1);
  x.push_front(20);
  ASSERT_EQ(x.size(), 12);
  ASSERT_EQ(x.front(), 20);
  ASSERT_EQ(x[1], 1);
}

TYPED_TEST(Deque_Fixture, push_front_2) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(7, 1);
  x.push_front(4);
  ASSERT_EQ(x.size(), 8);
  ASSERT_EQ(x.front(), 4);
  ASSERT_EQ(x[1], 1);
}

TYPED_TEST(Deque_Fixture, pop_back_1) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(5, 1);
  x[0] = 4;
  ASSERT_EQ(x.front(), 4);
  x.pop_front();
  ASSERT_EQ(x.size(), 4);
  ASSERT_EQ(x.front(), 1);
}

TYPED_TEST(Deque_Fixture, pop_front_1) {
  using deque_type = typename TestFixture::deque_type;
  deque_type x(5, 1);
  x[4] = 4;
  ASSERT_EQ(x.back(), 4);
  x.pop_back();
  ASSERT_EQ(x.size(), 4);
  ASSERT_EQ(x.back(), 1);
}
