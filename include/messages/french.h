///
/// @file message.h
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
///
///
#ifndef MESSAGES_FRENCH_H
#define MESSAGES_FRENCH_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "messages.h"

namespace stocos {

class French : public Messages {
  public:
	French() {
		this->operator[]("MPI") = "MPI_fr";
	}
};

} // namespace stocos

#endif