#pragma once

#include "interaction_type.hpp"
#include "object_kind.hpp"
#include <map>

typedef std::pair<ObjectKind *, ObjectKind *> PairOfKinds;
typedef std::pair<PairOfKinds, INTERACTION_TYPE> Interaction;
typedef std::map<PairOfKinds, INTERACTION_TYPE> Interactions;
