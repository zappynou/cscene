#include <cscene/config.h>
#include <cscene/version.h>

uint32_t cscene_get_library_major(void)
{
    return PACKAGE_VERSION_MAJOR;
}

uint16_t cscene_get_library_minor(void)
{
    return PACKAGE_VERSION_MINOR;
}

uint16_t cscene_get_library_revision(void)
{
    return PACKAGE_VERSION_REVISION;
}

const char *cscene_get_library_string(void)
{
    return PACKAGE_VERSION_STRING;
}
