#ifndef VEGAN_HOLDER_PTR_H
#define VEGAN_HOLDER_PTR_H

#include <vegan/types.h>
#include <vegan/memory.h>

namespace vegan {

  template<typename T> class unique_ptr;

  template<typename T>
    class holder_ptr {
      public:
        holder_ptr() {}
	explicit holder_ptr(T *p, bool own = false): rep{reinterpret_cast<uintptr_t>(p)} { if (own) rep |= owner_mask; }
	holder_ptr(const holder_ptr<T> &) = delete;
	holder_ptr(unique_ptr<T> &&p): holder_ptr(p.release(), true) {}
	~holder_ptr() { reset(); }

	holder_ptr<T> &operator=(const holder_ptr<T> &) = delete;

	bool owns() const { return rep & owner_mask; }
	//void release() { rep = rep & ~owner_mask; }
	void reset() { if (owns()) del(); rep = 0; }

	T *get() const { return reinterpret_cast<T *>(rep & ~owner_mask); }

	T *operator->() const { return get(); }
        T &operator*() const { return *get(); }

      private:
        void del() { T *p = get(); destroy(p); free(p); }

      private:
	static constexpr uintptr_t owner_mask = 1;
	uintptr_t rep = 0;
    };

  template<typename T> bool operator==(const holder_ptr<T> &p, const holder_ptr<T> &q) { return p.get() == q.get(); }
  template<typename T> bool operator!=(const holder_ptr<T> &p, const holder_ptr<T> &q) { return !(p == q); }

}

#endif
