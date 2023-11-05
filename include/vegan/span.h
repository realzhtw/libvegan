#ifndef VEGAN_SPAN_H
#define VEGAN_SPAN_H

#include <vegan/types.h>
#include <vegan/utils.h>

namespace vegan {

  template<typename T> class vector;

  class bytes;

  template<typename T> class span {
    public:
      span() {}
      span(T *p, Long n): impl{p, p + n} {}
      //explicit span(T *p, T *q): impl{p, q} {}
      template<Long N> span(T (&x)[N]): span{x, N} {}
      span(bytes &);
      span(const bytes &);
      span(vector<T> &x);
      span(span<remove_const_t<T>> x): span{x.ptr(), x.size()} {}
      span(rv_span<remove_const_t<T>> x): span{x.ptr(), x.size()} {}
      template<typename U> span(span<U> x): span{x.ptr(), x.size()} {}

      T *ptr(Long i = 0) const { return impl.begin + i; }
      Long size() const { return impl.end - impl.begin; }

      T &operator[](Long i) const { return *ptr(i); }

      T &front() const { return *ptr(0); }
      T &back() const { return *ptr(size() - 1); }

      T *begin() const { return impl.begin; }
      T *end() const { return impl.end; }

      void drop_first(Long n = 1) { impl.begin += min(n, size()); }
      void drop_last(Long n = 1) { impl.end -= min(n, size()); }

    private:
      struct Impl {
        T *begin = nullptr;
        T *end = nullptr;
      } impl;
  };

  template<typename T> class rv_span {
    public:
      explicit rv_span(T *p, Long n): impl{p, p + n} {}

      T *ptr(Long i = 0) const { return impl.begin + i; }
      Long size() const { return impl.end - impl.begin; }

      auto operator[](Long i) const { return move(*ptr(i)); }

      operator span<const T>() const { return make_span(ptr(), size()); }

    private:
      struct Impl {
        T *begin = nullptr;
	T *end = nullptr;
      } impl;
  };

  template<typename T> span<T> make_span(T *p, Long n) { return {p, n}; }
  template<typename T> span<T> make_span(T &x) { return make_span(&x, 1); }
  template<typename T> rv_span<T> make_rv_span(T *p, Long n) { return rv_span<T>{p, n}; }

  template<> span<      byte>::span(      bytes &b);
  template<> span<const byte>::span(const bytes &b);

  template<typename T, typename U> span<T> as_span(span<U> s);

  template<typename T>  span<      T> as_span(span<      byte> s) { return span<      T>{reinterpret_cast<      T *>(s.ptr()), s.size()}; }
  template<typename T>  span<const T> as_span(span<const byte> s) { return span<const T>{reinterpret_cast<const T *>(s.ptr()), s.size()}; }

  template<typename T, Long N> span<T> as_span(T (&x)[N]) { return make_span(x, N); }

  template<typename T> span<      T> as_span(      vector<T> &x) { return make_span(x.ptr(), x.size()); }
  template<typename T> span<const T> as_span(const vector<T> &x) { return make_span(x.ptr(), x.size()); }


  template<typename T> span<T> drop_first(span<T> s, Long n = 1) { s.drop_first(n); return s; }
  template<typename T> span<T> drop_last(span<T> s, Long n = 1) { s.drop_last(n); return s; }
  template<typename T> span<T> first_n(span<T> s, Long n) { s.drop_last(max(s.size() - n, 0)); return s; }
  template<typename T> span<T> last_n(span<T> s, Long n) { s.drop_first(max(s.size() - n, 0)); return s; }
  template<typename T> span<T> cut(span<T> s, Long i) { return drop_first(s, i); }
  template<typename T> span<T> cut(span<T> s, Long i, Long n) { return first_n(drop_first(s, i), n); }

  template<typename T>
    bool sorted(span<const T> x)
    {
      for (Long i = 0; i < x.size() - 1; ++i)
        if (!(x[i] <= x[i+1]))
          return false;
      return true;
    }

  template<typename T> bool sorted(const T &x) { return sorted(as_span(x)); }

}

#endif
