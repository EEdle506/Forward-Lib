#include "fl/core/Flags.hpp"
using namespace Forward;

#include <gtest/gtest.h>

enum class MyEnum
{
    None = 0,
    First = 1 << 0,
    Second = 1 << 1,
    Third = 1 << 2,
};
ENUM_FLAGS(MyEnum, MyEnumFlags);
DECLARE_ENUM_OPERATORS(MyEnum);

TEST(Flags, Equal) 
{
    MyEnumFlags flags = MyEnum::First | MyEnum::Third;

    EXPECT_TRUE(flags.Test(MyEnum::First));
    EXPECT_TRUE(flags.Test(MyEnum::Third));
    EXPECT_TRUE(flags.Test(MyEnum::Third | MyEnum::First));

    auto test1 = flags.Test(MyEnum::Second);
    EXPECT_FALSE(test1);

    auto test2 = flags.Test(MyEnum::None);
    EXPECT_FALSE(test2);
}