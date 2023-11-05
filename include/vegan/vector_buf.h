#ifndef VEGAN_VECTOR_BUF_H
#define VEGAN_VECTOR_BUF_H

#include <vegan/vector.h>
#include <vegan/utils.h>

namespace vegan {

  template<typename T>
  class vector_buf {
    public:
      vector_buf() {}
      ~vector_buf() { destroy(data()); }

      span<      T> data()       { return first_n(as_span<      T>(b), i); }
      span<const T> data() const { return first_n(as_span<const T>(b), i); }

      //      T *ptr(Long i = 0)       { return as_span<T>(b).ptr(i); }
      //const T *ptr(Long i = 0) const { return as_span<T>(b).ptr(i); }

      Long size() const { return i; }
      Long capacity() const { return as_span<const T>(b).size(); }
      void reserve(Long n);

      void append(span<const T>);
      void append(rv_span<T>);
      void push_back(const T &x) { append(make_span(&x, 1)); }
      void push_back(T &&x) { append(make_rv_span(&x, 1)); }

      void drop_last(Long n = 1) { destroy(last_n(data(), n)); i -= n; }

    private:
      bytes b;
      Long  i = 0;
  };

  template<typename T>
    void vector_buf<T>::reserve(Long n)
    {
      if (n <= capacity()) return;

      bytes nb{n*(Long)sizeof(T)};

      initialize(as_span<T>(b), move(data()));
      destroy(data());
      b = move(nb);
    }

  template<typename T>
    void vector_buf<T>::append(span<const T> x)
    {
      if (capacity() - size() < x.size())
        reserve(max(capacity() == 0 ? 1 : capacity() * 2, size() + x.size()));

      initialize(cut(as_span<T>(b), i), x);
      i += x.size();
    }

  template<typename T>
    void vector_buf<T>::append(rv_span<T> x)
    {
      if (capacity() - size() < x.size())
        reserve(max(capacity() == 0 ? 1 : capacity() * 2, size() + x.size()));

      initialize(cut(as_span<T>(b), i), x);
      i += x.size();
    }

}

#endif
