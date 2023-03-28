#include <vegan/vector.h>
#include <vegan/string.h>
#include <vegan/string_utils.h>
#include <vegan/stdio.h>
#include <vegan/fs.h>
#include <vegan/sort.h>

using namespace vegan;

int main()
{
   auto files = fs::ls(".");

   sort(files);

   for (const auto &f : files)
     if (!has_prefix(f, "."))
       println(f);
}
