#ifndef VEGAN_STACK_H
#define VEGAN_STACK_H

#include <vegan/vector_buf.h>

namespace vegan {

  template<typename T>
    class stack {
      public:
        explicit stack(span<const T> init = span<const T>{})  { b.append(init); }
        explicit stack(rv_span<T> init)  { b.append(init); }
	void push(const T &x) { b.push_back(x); }
	void push(T &&x) { b.push_back(move(x)); }
	T pop() { auto x = move(top()); b.drop_last(); return x; }
	void pop(T &x) { x = move(pop()); }
	T       &top()       { return b.data().back(); }
	const T &top() const { return b.data().back(); }

        Long size() const { return b.size(); }
        bool empty() const { return size() == 0; }
      private:
        vector_buf<T> b;
    };

}

#endif
