#include <gtest/gtest.h>

typedef const int* (*BinarySearchFunction)(const int *, const int*, int);

class BinarySearchTest : public ::testing::TestWithParam<BinarySearchFunction> {
public:
  static const int data[];
  const int *first;
  const int *last;
  const int *expected;
  int x;
  BinarySearchFunction bs;

  BinarySearchTest() {
    bs = GetParam();
  }

};
const int BinarySearchTest::data[] =  {-1, 2, 2, 7};

TEST_P(BinarySearchTest, NormalCases) {

  first = &data[0];
  last = &data[4];
  x = 2;
  expected = &data[1];
  EXPECT_EQ(expected, bs(first, last, x));

  last = &data[1];
  x = -1;
  expected = &data[0];
  EXPECT_EQ(expected, bs(first, last, x));
}

TEST_P(BinarySearchTest, AbnormalCases) {
  expected = NULL;

  first = NULL;
  last = &data[1];
  x = -1;
  EXPECT_EQ(expected, bs(first, last, x));

  first = &data[0];
  last = NULL;
  EXPECT_EQ(expected, bs(first, last, x));

  last = &data[4];
  x = -2;
  EXPECT_EQ(expected, bs(first, last, x));

  x = 3;
  EXPECT_EQ(expected, bs(first, last, x));

  x = 10;
  EXPECT_EQ(expected, bs(first, last, x));

  last = &data[0];
  x = -1;
  EXPECT_EQ(expected, bs(first, last, x));

  first = &data[1];
  EXPECT_EQ(expected, bs(first, last, x));
}



const int* binarySearch(const int *first, const int *last, int x) {
  if (first == NULL || last == NULL || last < first) return NULL;
  const int *low = first;
  const int *high = last;
  while (low < high) {
    const int * mid = low + (high - low) / 2;
    if (*mid >= x) {
      high = mid;
    }else {
      low = mid+1;
    }
  }
  return (high != last && x == *high) ? high : NULL;
}

INSTANTIATE_TEST_CASE_P(instance,
                        BinarySearchTest,
                        ::testing::Values(binarySearch));
