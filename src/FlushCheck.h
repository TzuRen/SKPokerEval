// SKPokerEval
//
// Copyright 2010 Kenneth J. Shackleton
//
// This program gives you software freedom; you can copy, convey, propagate,
// redistribute and/or modify this program under the terms of the GNU General
// Public License (GPL) as published by the Free Software Foundation (FSF),
// either version 3 of the License, or (at your option) any later version of
// the GPL published by the FSF.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program in a file in the top-level directory called "GPLv3". If
// not, see http://www.gnu.org/licenses/.

#ifndef SKPOKEREVAL_FLUSHCHECK_H
#define SKPOKEREVAL_FLUSHCHECK_H

#include <array>
#include <cstdint>

#include "Constants.h"

using FlushCheckArray = std::array<int_fast8_t, 7 * kClub + 1>;

FlushCheckArray flush_check = [] {
  FlushCheckArray array = {};
  for (auto& c : array)
    c = kNotASuit;

  int suits[] = {kSpade, kHeart, kDiamond, kClub};
  for (int i = 0; i < 4; ++i)
    for (auto c : suits)
      for (auto d : suits)
        array[5 * suits[i] + c + d] = i;

  return array;
}();

#endif  // SKPOKEREVAL_FLUSHCHECK_H
