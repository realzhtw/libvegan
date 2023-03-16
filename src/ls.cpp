#include <vegan/vector.h>
#include <vegan/string.h>
#include <vegan/string_utils.h>
#include <vegan/stdio.h>

using namespace vegan;

int main()
{
   vector<string> list{10};

   for (Long i = 0; i != list.size(); ++i)
     list[i] = "aoeu";
   
   for (const auto &s : list)
     println(s);
  
}
