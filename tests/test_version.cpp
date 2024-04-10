#include <catch2/catch_test_macros.hpp>

extern "C" {
#include <cscene/version.h>
}

TEST_CASE("Major version is same as build")
{
    REQUIRE(cscene_get_build_major() == cscene_get_library_major());
}

TEST_CASE("Minor version is same as build")
{
    REQUIRE(cscene_get_build_minor() == cscene_get_library_minor());
}

TEST_CASE("Revision version is same as build")
{
    REQUIRE(cscene_get_build_revision() == cscene_get_library_revision());
}

TEST_CASE("String version is same as build")
{
    REQUIRE(cscene_get_build_string());
    REQUIRE(cscene_get_library_string());

    REQUIRE(std::string(cscene_get_build_string())
            == std::string(cscene_get_library_string()));
}
