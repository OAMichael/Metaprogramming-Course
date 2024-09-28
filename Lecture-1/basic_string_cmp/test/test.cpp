#include <gtest/gtest.h>

#include <compare.h>

// Check operator== for std::basic_string and std::basic_string
TEST(basic_string_compare, basic_string_basic_string_eq) {
    std::string str1 = "str1";
    std::string str2 = "str1";

    EXPECT_TRUE(MyCompare::operator==(str1, str2));
}

TEST(basic_string_compare, basic_string_basic_string_noteq) {
    std::string str1 = "str1";
    std::string str2 = "str2";

    EXPECT_FALSE(MyCompare::operator==(str1, str2));
}


// Check operator== for std::basic_string and null-terminated array of CharT
TEST(basic_string_compare, basic_string_char_arr_eq) {
    std::string str1 = "str1";
    const char* str2 = "str1";

    EXPECT_TRUE(MyCompare::operator==(str1, str2));
}

TEST(basic_string_compare, basic_string_char_arr_noteq) {
    std::string str1 = "str1";
    const char* str2 = "str2";

    EXPECT_FALSE(MyCompare::operator==(str1, str2));
}


// Check operator== for null-terminated array of CharT and std::basic_string
TEST(basic_string_compare, char_arr_basic_string_eq) {
    const char* str1 = "str1";
    std::string str2 = "str1";

    EXPECT_TRUE(MyCompare::operator==(str1, str2));
}

TEST(basic_string_compare, char_arr_basic_string_noteq) {
    const char* str1 = "str1";
    std::string str2 = "str2";

    EXPECT_FALSE(MyCompare::operator==(str1, str2));
}



int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
