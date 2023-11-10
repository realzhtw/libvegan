#include <vegan/xml.h>
#include <vegan/string_io.h>
#include <gtest/gtest.h>

#include <vegan/stdio.h>
#include <vegan/utf8.h>

namespace {

  using namespace vegan;

  TEST(xml, character_types)
  {
    string_ref s = u8":AZazÀÖØöø˿ͰͽͿ";
    rune r;
    while (parse_rune(s, r)) {
      EXPECT_TRUE(xml::is_name_start_char(r));
      EXPECT_TRUE(xml::is_name_char(r));
    }
    EXPECT_TRUE(xml::is_name_start_char(rune{0x37f}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x1fff}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x200c}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x200d}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x2070}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x218f}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x2c00}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x2fef}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x3001}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0xd7ff}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0xf900}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0xfdcf}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0xfdff}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0xfffd}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0x10000}));
    EXPECT_TRUE(xml::is_name_start_char(rune{0xeffff}));
    s = "-.0123456789·‿⁀";
    while (parse_rune(s, r)) {
      EXPECT_FALSE(xml::is_name_start_char(r));
      EXPECT_TRUE(xml::is_name_char(r));
    }
    EXPECT_FALSE(xml::is_name_start_char(rune{0x300}));
    EXPECT_FALSE(xml::is_name_start_char(rune{0x36f}));
    EXPECT_TRUE(xml::is_name_char(rune{0x300}));
    EXPECT_TRUE(xml::is_name_char(rune{0x36f}));
  }

}
