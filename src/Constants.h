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

#ifndef SKPOKEREVAL_CONSTANTS_H_
#define SKPOKEREVAL_CONSTANTS_H_

#include <stdint.h>

constexpr int kNumberOfSuits = 4;
constexpr int kNumberOfFaces = 9;

constexpr int kDeckSize = kNumberOfSuits * kNumberOfFaces;

constexpr int kSpade = 0;
constexpr int kHeart = 1;
constexpr int kDiamond = 8;
constexpr int kClub = 57;

constexpr int kIndexSpade = 0;
constexpr int kIndexHeart = 1;
constexpr int kIndexDiamond = 2;
constexpr int kIndexClub = 3;
constexpr int kNotASuit = -1;

// Cards
constexpr uint8_t kAs = 0;
constexpr uint8_t kAh = 1;
constexpr uint8_t kAd = 2;
constexpr uint8_t kAc = 3;
constexpr uint8_t kKs = 4;
constexpr uint8_t kKh = 5;
constexpr uint8_t kKd = 6;
constexpr uint8_t kKc = 7;
constexpr uint8_t kQs = 8;
constexpr uint8_t kQh = 9;
constexpr uint8_t kQd = 10;
constexpr uint8_t kQc = 11;
constexpr uint8_t kJs = 12;
constexpr uint8_t kJh = 13;
constexpr uint8_t kJd = 14;
constexpr uint8_t kJc = 15;
constexpr uint8_t kTs = 16;
constexpr uint8_t kTh = 17;
constexpr uint8_t kTd = 18;
constexpr uint8_t kTc = 19;
constexpr uint8_t k9s = 20;
constexpr uint8_t k9h = 21;
constexpr uint8_t k9d = 22;
constexpr uint8_t k9c = 23;
constexpr uint8_t k8s = 24;
constexpr uint8_t k8h = 25;
constexpr uint8_t k8d = 26;
constexpr uint8_t k8c = 27;
constexpr uint8_t k7s = 28;
constexpr uint8_t k7h = 29;
constexpr uint8_t k7d = 30;
constexpr uint8_t k7c = 31;
constexpr uint8_t k6s = 32;
constexpr uint8_t k6h = 33;
constexpr uint8_t k6d = 34;
constexpr uint8_t k6c = 35;

constexpr int kSixFive = 0;
constexpr int kSevenFive = 1;
constexpr int kEightFive = 5;
constexpr int kNineFive = 22;
constexpr int kTenFive = 94;
constexpr int kJackFive = 312;
constexpr int kQueenFive = 992;
constexpr int kKingFive = 2422;
constexpr int kAceFive = 5624;

constexpr int SIX_FLUSH = 1;
constexpr int SEVEN_FLUSH = SIX_FLUSH << 1;
constexpr int EIGHT_FLUSH = SEVEN_FLUSH << 1;
constexpr int NINE_FLUSH = EIGHT_FLUSH << 1;
constexpr int TEN_FLUSH = NINE_FLUSH << 1;
constexpr int JACK_FLUSH = TEN_FLUSH << 1;
constexpr int QUEEN_FLUSH = JACK_FLUSH << 1;
constexpr int KING_FLUSH = QUEEN_FLUSH << 1;
constexpr int ACE_FLUSH = KING_FLUSH << 1;

// _SEVEN tag suppressed
constexpr int kSix = 0;
constexpr int kSeven = 1;
constexpr int kEight = 5;
constexpr int kNine = 22;
constexpr int kTen = 98;
constexpr int kJack = 453;
constexpr int kQueen = 2031;
constexpr int kKing = 8698;
constexpr int kAce = 22854;
// end of _SEVEN tag suppressed

constexpr int MAX_FIVE_NONFLUSH_KEY_INT = 4 * kAceFive + kKingFive;
constexpr int MAX_FIVE_FLUSH_KEY_INT =
    ACE_FLUSH | KING_FLUSH | QUEEN_FLUSH | JACK_FLUSH | TEN_FLUSH;
constexpr int MAX_SEVEN_NONFLUSH_KEY_INT = 4 * kAce + 3 * kKing;
constexpr int MAX_SEVEN_FLUSH_KEY_INT = ACE_FLUSH | KING_FLUSH | QUEEN_FLUSH |
                                        JACK_FLUSH | TEN_FLUSH | NINE_FLUSH |
                                        EIGHT_FLUSH;

constexpr int RANK_OFFSET_SHIFT = 9;
constexpr int RANK_HASH_MOD = (1 << RANK_OFFSET_SHIFT) - 1;

constexpr int MAX_FLUSH_CHECK_SUM = 7 * kClub;

// Bit masks
constexpr int FLUSH_BIT_SHIFT = 23;
constexpr int FACE_BIT_MASK = (1 << FLUSH_BIT_SHIFT) - 1;

#endif  // SKPOKEREVAL_CONSTANTS_H_
