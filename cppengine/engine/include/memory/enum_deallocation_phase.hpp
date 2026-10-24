//
// Created by zyiu on 22/10/2026.
//

#ifndef ENUM_DEALLOCATION_PHASE_HPP
#define ENUM_DEALLOCATION_PHASE_HPP

namespace cppengine {
  enum class DeallocationPhase {
    DESTROY,
    RELEASE,
    DISPOSE
  };
}

#endif //ENUM_DEALLOCATION_PHASE_HPP