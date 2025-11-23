#include <iostream>
#include <fstream>

struct IntArray 
{
  int * a;
  size_t size;

  IntArray(int i) : 
  a(new int[1]), 
  size(1) 
  {
    * a = i;
  }

  IntArray(size_t k, int i = 0) : 
  a(new int[k]), 
  size(k) 
  {
    for (size_t j = 0; j < k; ++j)
    {
      a[j] = i;
    }
  }

  IntArray (const IntArray & rhs) :
  a(new int [rhs.getSize()]),
  size(rhs.getSize())
  {
    for (size_t i = 0; i < getSize(); ++i)
    {
      a[i] = rhs.get(i);
    }
  }

  ~IntArray() 
  {
    delete[] a;
  }

  IntArray & operator=(const IntArray & rhs)
  {
    if (this != &rhs) 
    {
      int * tmp = new int [rhs.getSize()];
      for (size_t i = 0; i < rhs.getSize(); ++i)
      {
        tmp[i] = rhs.get(i);
      }
      delete[] a;
      a = tmp;
      size = rhs.getSize();
    }
    return * this;
  }
  
  IntArray (IntArray && rhs):
  a(rhs.a),
  size(rhs.getSize())
  {
    rhs.a = nullptr;
  }

  IntArray & operator=(IntArray && rhs)
  {
    delete[] a;
    a = rhs.a;
    size = rhs.size;
    rhs.a = nullptr;
    return * this;
  }

  int get(size_t id) const noexcept
  {
    return a[id];
  }

  void set(size_t id, int v) 
  {
    a[id] = v;
  }

  size_t getSize() const noexcept 
  {
    return size;
  }

  int last() const noexcept
  {
    return get(getSize() - 1);
  }

  void add(int v)
  {
    int * tmp = new int[getSize() + 1];
    for (size_t i = 0; i < getSize(); ++i)
    {
      tmp[i] = get(i);
    }
    tmp[getSize()] = v;
    delete[] a;
    a = tmp;
    ++size;
  }
};

struct IntMatrix 
{
  IntArray data;
  size_t rows;
  size_t cols;

  IntMatrix(size_t r = 0, size_t c = 0) : 
  data(r * c), 
  rows(r), 
  cols(c) 
  {
  }

  bool inputMatrix (const char * file) 
  {
    std::ifstream input(file);
    if (!input)
    {
      return false;
    }
    size_t r, c;
    input >> r >> c;
    rows = r;
    cols = c;
    data = IntArray(r * c, 0);
    for (size_t i = 0; i < r; ++i) 
    {
      for (size_t j = 0; j < c; ++j) 
      {
        int v;
        input >> v;
        set(i, j, v);
      }
    }
    return true;
  }

  size_t getRows() const 
  { 
    return rows; 
  }

  size_t getCols() const 
  { 
    return cols; 
  }

  int get(size_t i, size_t j) const 
  {
    return data.get(i * cols + j);
  }

  void set(size_t i, size_t j, int v) 
  {
    data.set(i * cols + j, v);
  }

  void print() const 
  {
    for (size_t i = 0; i < rows; ++i) 
    {
      for (size_t j = 0; j < cols; ++j) 
      {
        std::cout << get(i, j) << " ";
      }
      std::cout << "\n";
    }
  }

  bool addColumn(size_t after, int v)
  {
  }

  bool addRowAndColumn(size_t afterRow, size_t afterCol)
  {
  }
};
