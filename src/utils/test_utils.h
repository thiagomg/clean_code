#pragma once

#define ENSURE_EQUAL(left, right) { \
    if(left == right) { \
        std::cout << "PASSED - line=" << __LINE__ << ": " \
        << (#left) << " == " << (#right) << std::endl; \
    } \
    else { \
        std::cout << "FAILED - line=" << __LINE__ << ": " \
        << (#left) << " != " << (#right) \
        << std::endl; \
    }\
}
