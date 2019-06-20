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

#ifndef SKPOKEREVAL_DECKCARDS_H
#define SKPOKEREVAL_DECKCARDS_H

#include <cstdint>
#include "Constants.h"

constexpr uint_fast32_t const card[kDeckSize] = {
    kAce + (kSpade << FLUSH_BIT_SHIFT),
    kAce + (kHeart << FLUSH_BIT_SHIFT),
    kAce + (kDiamond << FLUSH_BIT_SHIFT),
    kAce + (kClub << FLUSH_BIT_SHIFT),

    kKing + (kSpade << FLUSH_BIT_SHIFT),
    kKing + (kHeart << FLUSH_BIT_SHIFT),
    kKing + (kDiamond << FLUSH_BIT_SHIFT),
    kKing + (kClub << FLUSH_BIT_SHIFT),

    kQueen + (kSpade << FLUSH_BIT_SHIFT),
    kQueen + (kHeart << FLUSH_BIT_SHIFT),
    kQueen + (kDiamond << FLUSH_BIT_SHIFT),
    kQueen + (kClub << FLUSH_BIT_SHIFT),

    kJack + (kSpade << FLUSH_BIT_SHIFT),
    kJack + (kHeart << FLUSH_BIT_SHIFT),
    kJack + (kDiamond << FLUSH_BIT_SHIFT),
    kJack + (kClub << FLUSH_BIT_SHIFT),

    kTen + (kSpade << FLUSH_BIT_SHIFT),
    kTen + (kHeart << FLUSH_BIT_SHIFT),
    kTen + (kDiamond << FLUSH_BIT_SHIFT),
    kTen + (kClub << FLUSH_BIT_SHIFT),

    kNine + (kSpade << FLUSH_BIT_SHIFT),
    kNine + (kHeart << FLUSH_BIT_SHIFT),
    kNine + (kDiamond << FLUSH_BIT_SHIFT),
    kNine + (kClub << FLUSH_BIT_SHIFT),

    kEight + (kSpade << FLUSH_BIT_SHIFT),
    kEight + (kHeart << FLUSH_BIT_SHIFT),
    kEight + (kDiamond << FLUSH_BIT_SHIFT),
    kEight + (kClub << FLUSH_BIT_SHIFT),

    kSeven + (kSpade << FLUSH_BIT_SHIFT),
    kSeven + (kHeart << FLUSH_BIT_SHIFT),
    kSeven + (kDiamond << FLUSH_BIT_SHIFT),
    kSeven + (kClub << FLUSH_BIT_SHIFT),

    kSix + (kSpade << FLUSH_BIT_SHIFT),
    kSix + (kHeart << FLUSH_BIT_SHIFT),
    kSix + (kDiamond << FLUSH_BIT_SHIFT),
    kSix + (kClub << FLUSH_BIT_SHIFT)};

constexpr uint_fast8_t const suit[kDeckSize] = {
    kIndexSpade,   kIndexHeart,   kIndexDiamond, kIndexClub,    kIndexSpade,
    kIndexHeart,   kIndexDiamond, kIndexClub,    kIndexSpade,   kIndexHeart,
    kIndexDiamond, kIndexClub,    kIndexSpade,   kIndexHeart,   kIndexDiamond,
    kIndexClub,    kIndexSpade,   kIndexHeart,   kIndexDiamond, kIndexClub,
    kIndexSpade,   kIndexHeart,   kIndexDiamond, kIndexClub,    kIndexSpade,
    kIndexHeart,   kIndexDiamond, kIndexClub,    kIndexSpade,   kIndexHeart,
    kIndexDiamond, kIndexClub,    kIndexSpade,   kIndexHeart,   kIndexDiamond,
    kIndexClub};

constexpr uint_fast16_t const suit_kronecker[kNumberOfSuits][kDeckSize] = {
    {ACE_FLUSH,   0, 0, 0, KING_FLUSH,  0, 0, 0, QUEEN_FLUSH, 0, 0, 0,
     JACK_FLUSH,  0, 0, 0, TEN_FLUSH,   0, 0, 0, NINE_FLUSH,  0, 0, 0,
     EIGHT_FLUSH, 0, 0, 0, SEVEN_FLUSH, 0, 0, 0, SIX_FLUSH,   0, 0, 0},
    {0, ACE_FLUSH,   0, 0, 0, KING_FLUSH,  0, 0, 0, QUEEN_FLUSH, 0, 0,
     0, JACK_FLUSH,  0, 0, 0, TEN_FLUSH,   0, 0, 0, NINE_FLUSH,  0, 0,
     0, EIGHT_FLUSH, 0, 0, 0, SEVEN_FLUSH, 0, 0, 0, SIX_FLUSH,   0, 0},
    {0, 0, ACE_FLUSH,   0, 0, 0, KING_FLUSH,  0, 0, 0, QUEEN_FLUSH, 0,
     0, 0, JACK_FLUSH,  0, 0, 0, TEN_FLUSH,   0, 0, 0, NINE_FLUSH,  0,
     0, 0, EIGHT_FLUSH, 0, 0, 0, SEVEN_FLUSH, 0, 0, 0, SIX_FLUSH,   0},
    {0, 0, 0, ACE_FLUSH,   0, 0, 0, KING_FLUSH,  0, 0, 0, QUEEN_FLUSH,
     0, 0, 0, JACK_FLUSH,  0, 0, 0, TEN_FLUSH,   0, 0, 0, NINE_FLUSH,
     0, 0, 0, EIGHT_FLUSH, 0, 0, 0, SEVEN_FLUSH, 0, 0, 0, SIX_FLUSH}};

#endif
