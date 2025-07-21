#pragma once
#define pub
#define priv

// Emitted by yappc
// Emitting 4 declarations

#include <iostream>
;

namespace stream {
    using reader = std::istream;
;

    using writer = std::ostream;
;

    using stream = std::iostream;
;

}
#undef pub
#undef priv
