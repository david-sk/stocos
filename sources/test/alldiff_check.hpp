///
/// @file criteria.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef ALLDIFF_CHECK_H
#define ALLDIFF_CHECK_H

namespace stocos {

template<typename SOL, typename TYPE_FITNESS> class Alldiff_check {
  public:
	Alldiff_check() {}

	virtual ~Alldiff_check() {}

	bool operator()(const SOL& s) {}
};

} // namespace stocos

#endif