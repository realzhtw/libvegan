#include <vegan/vector.h>
#include <vegan/string.h>
#include <vegan/string_utils.h>
#include <vegan/stdio.h>
#include <vegan/fs.h>

using namespace vegan;

int main()
{
   auto l = fs::ls(".");

   for (const auto &s : l)
     println(s);
  
}
