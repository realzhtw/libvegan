#include <vegan/string_output_port.h>
#include <vegan/stdio.h>
#include <vegan/string.h>
#include <gtest/gtest.h>

namespace {

  using namespace vegan;

  TEST(string_output_port, simple)
  {
    string_output_port p;
    EXPECT_EQ(p.data(), "");
    string_ref quote = "For a sensation to be felt as pain is for it to be pain.";
    fprintln(p, quote);
    EXPECT_EQ(p.data(), quote + "\n");
    string_ref author = "Saul Kripke";
    fprintln(p, author);
    EXPECT_EQ(p.data(), quote + "\n" + author + "\n");
  }

  TEST(string_output_port, with_output_to_string)
  {
    string_ref quote = "Emacs is written in Lisp";
    auto s = with_output_to_string([&] { println(quote); });
    EXPECT_EQ(s, quote + "\n");
  }

}
