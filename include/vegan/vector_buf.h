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

            vector_ref<T> data()       { return first_n(b.as_vector<T>(), i); }
      const_vector_ref<T> data() const { return first_n(b.as_vector<T>(), i); }

            T *ptr(Long i = 0)       { return b.as_vector<T>().ptr(i); }
      const T *ptr(Long i = 0) const { return b.as_vector<T>().ptr(i); }

      Long size() const { return i; }
      Long capacity() const { return b.as_vector<T>().size(); }
      void reserve(Long n);

      void append(const_vector_ref<T>);
      void append(vector_rv_ref<T>);
      void append(const T &x) { append(const_vector_ref<T>{&x, 1}); }
      void append(T &&x) { append(vector_rv_ref<T>{&x, 1}); }

    private:
      bytes b;
      Long  i = 0;
  };

  template<typename T>
    void vector_buf<T>::reserve(Long n)
    {
      if (n <= capacity()) return;

      bytes nb{n*(Long)sizeof(T)};

      initialize(nb.as_vector<T>().ptr(), move(data()));
      destroy(data());
      b = move(nb);
    }

  template<typename T>
    void vector_buf<T>::append(const_vector_ref<T> x)
    {
      if (capacity() - size() < x.size())
        reserve(max(capacity() == 0 ? 1 : capacity() * 2, size() + x.size()));

      initialize(ptr(i), x);
      i += x.size();
    }

  template<typename T>
    void vector_buf<T>::append(vector_rv_ref<T> x)
    {
      if (capacity() - size() < x.size())
        reserve(max(capacity() == 0 ? 1 : capacity() * 2, size() + x.size()));

      initialize(ptr(i), x);
      i += x.size();
    }

}

#endif
