#include "fl/net/http/HttpUrl.hpp"
using namespace fl;

#include <gtest/gtest.h>

TEST(HttpUrlTest, ValidHttpUrl) {
    std::string urlStr = "http://www.example.com/path/to/resource?p=value1#fragment";
    HttpUrl url(urlStr);

    EXPECT_EQ(url.Protocol(), "http");
    EXPECT_EQ(url.Domain(), "www.example.com");
    EXPECT_EQ(url.Target(), "/path/to/resource");
    EXPECT_EQ(url.Query().ToString(), "p=value1");
    EXPECT_EQ(url.Section(), "fragment");
}

TEST(HttpUrlTest, HttpUrlWithoutQueryAndFragment) {
    std::string urlStr = "http://www.example.com/path/to/resource";
    HttpUrl url(urlStr);

    EXPECT_EQ(url.Protocol(), "http");
    EXPECT_EQ(url.Domain(), "www.example.com");
    EXPECT_EQ(url.Target(), "/path/to/resource");
    EXPECT_EQ(url.Query().ToString(), "");
    EXPECT_EQ(url.Section(), "");
}

TEST(HttpUrlTest, HttpUrlWithoutDomain) {
    std::string urlStr = "http://localhost/path/to/resource?param1=value1&p=v#fragment";
    HttpUrl url(urlStr);

    EXPECT_EQ(url.Protocol(), "http");
    EXPECT_EQ(url.Domain(), "localhost");
    EXPECT_EQ(url.Target(), "/path/to/resource");
    EXPECT_EQ(url.Query().ToString(), "param1=value1&p=v");
    EXPECT_EQ(url.Section(), "fragment");
}