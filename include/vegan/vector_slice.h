#ifndef VEGAN_VECTOR_SLICE_H
#define VEGAN_VECTOR_SLICE_H

#include <vegan/types.h>

namespace vegan {

  template<typename T> class vector;
  template<typename T> class vector_ref;
  template<typename T> class const_vector_ref;

  template<typename T>
    class vector_slice {
      public:
        vector_slice() {}
        explicit vector_slice(T *p, Long s, Long n): p{p}, s{s}, n{n} {}
        vector_slice(vector<T> &);
        vector_slice(vector_ref<T>);

        T *ptr(Long i = 0) const { return p+i*s; }

        Long size() const { return n; }
        bool empty() const { return size() == 0; }
        T &operator[](Long i) const { return *ptr(i); }

      private:
       T    *p = nullptr;
       Long  s = 0;
       Long  n = 0;
    };

  template<typename T>
    class const_vector_slice {
      public:
        const_vector_slice() {}
        explicit const_vector_slice(const T *p, Long s, Long n): p{p}, s{s}, n{n} {}
        const_vector_slice(const vector<T> &);
        const_vector_slice(const_vector_ref<T>);

        const T *ptr(Long i = 0) const { return p+i*s; }

        Long size() const { return n; }
        bool empty() const { return size() == 0; }
        const T &operator[](Long i) const { return *ptr(i); }

      private:
       const T *p = nullptr;
       Long     s = 0;
       Long     n = 0;
    };

}

#endif
