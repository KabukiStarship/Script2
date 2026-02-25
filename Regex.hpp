// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_OP_HPP
#define CRABS_OP_HPP 1
#include "String.hpp"
#if SEAM >= CRABS_OPERATION
namespace _ {

const {
  RegexPatternLengthMax = 256,  //< The maximum length of a regex pattern.
}

struct Regex {
  CHA pattern[RegexPatternLengthMax]; //< The regex pattern.
  DTB options;                        //< The regex options.
};

}  //< namespace _
#endif
#endif
