#include "fl/web/HttpQuery.hpp"
using namespace Forward::Web;

#include <gtest/gtest.h>

TEST(URICoding, Encode) 
{
    EXPECT_TRUE(Coding::UrlEncodeUtf8("Hello World") == "Hello+World");
    EXPECT_TRUE(Coding::UrlEncodeUtf8("abc123!@#$%^&*()+-=") == "abc123%21%40%23%24%25%5E%26%2A%28%29%2B-%3D");
    EXPECT_TRUE(Coding::UrlEncodeUtf8("äöü") == "%C3%A4%C3%B6%C3%BC");
    EXPECT_TRUE(Coding::UrlEncodeUtf8("你好") == "%E4%BD%A0%E5%A5%BD");
}
TEST(URICoding, Decode) 
{
    EXPECT_TRUE("Hello World" == Coding::UrlDecodeUtf8("Hello+World"));
    EXPECT_TRUE("abc123!@#$%^&*()+-=" == Coding::UrlDecodeUtf8("abc123%21%40%23%24%25%5E%26%2A%28%29%2B-%3D"));
    EXPECT_TRUE("äöü" == Coding::UrlDecodeUtf8("%C3%A4%C3%B6%C3%BC"));
    EXPECT_TRUE("你好" == Coding::UrlDecodeUtf8("%E4%BD%A0%E5%A5%BD"));
}

TEST(HttpQueryTest, ValidQuery) 
{
    std::string queryStr = "p=value1";
    HttpQuery query(queryStr);

    EXPECT_TRUE(query.IsValid());
    EXPECT_TRUE(query.HasKey("p"));

    EXPECT_TRUE(query.Value("p") == "value1");

    EXPECT_TRUE(query.Arg("p").GetName() == "p");
    EXPECT_TRUE(query.Arg("p").GetData() == "value1");
}

TEST(HttpQueryTest, MultipleQuery) 
{
    HttpQuery query("param1=value1&p=v");

    EXPECT_TRUE(query.IsValid());

    EXPECT_TRUE(query.HasKey("param1"));
    EXPECT_TRUE(query.HasKey("p"));

    EXPECT_TRUE(query.Value("param1") == "value1");
    EXPECT_TRUE(query.Value("p") == "v");

    EXPECT_TRUE(query.Arg("param1").GetData() == "value1");
    EXPECT_TRUE(query.Arg("p").GetData() == "v");
}