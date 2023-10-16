#ifndef VEGAN_UNIQUE_PTR_H
#define VEGAN_UNIQUE_PTR_H

#include <vegan/types.h>

namespace vegan {

  template<typename T>
    class unique_ptr {
      public:
        unique_ptr() {}
        explicit unique_ptr(T *p): p{p} {}
	unique_ptr(const unique_ptr<T> &) = delete;
	unique_ptr(unique_ptr<T> &&np): p{np.get()} { np.release(); }
	~unique_ptr() { reset(); }

	unique_ptr<T> &operator=(const unique_ptr<T> &) = delete;
	unique_ptr<T> &operator=(unique_ptr<T> &&np) { if (&np != this) reset(np.release()); return *this; }

	void reset(T *np = nullptr) { if (p != nullptr) delete p; p = np; }
	T *release() { auto t = p; p = nullptr; return t; }

	T *get() const { return p; }
	T *operator->() const { return p; }
        T &operator*() const { return *p; }
      private:
	T *p = nullptr;
    };

  template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) { return unique_ptr<T>{new T(forward<Args>(args)...)}; }

}

#endif
