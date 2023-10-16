#include <vegan/vector_buf.h>

namespace vegan {

  template<typename T>
    class stack {
      public:
        stack(const_vector_ref<T> init = vector_ref<T>{})  { b.append(init); }
	void push(const T &x) { b.append(x); }
	void pop() { b.drop_last(); }
	T       &top()       { return b.data()[b.size() - 1]; }
	const T &top() const { return b.data()[b.size() - 1]; }
      private:
        vector_buf<T> b;
    };

}
