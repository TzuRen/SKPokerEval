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

#define DECK_SIZE 36

#define NUMBER_OF_SUITS 4
#define NUMBER_OF_FACES 9

#define SPADE 0
#define HEART 1
#define DIAMOND 8
#define CLUB 57

#define INDEX_SPADE 0
#define INDEX_HEART 1
#define INDEX_DIAMOND 2
#define INDEX_CLUB 3
#define NOT_A_SUIT (-1)

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

#define SIX_FIVE 0
#define SEVEN_FIVE 1
#define EIGHT_FIVE 5
#define NINE_FIVE 22
#define TEN_FIVE 94
#define JACK_FIVE 312
#define QUEEN_FIVE 992
#define KING_FIVE 2422
#define ACE_FIVE 5624

#define SIX_FLUSH 1
#define SEVEN_FLUSH SIX_FLUSH << 1
#define EIGHT_FLUSH SEVEN_FLUSH << 1
#define NINE_FLUSH EIGHT_FLUSH << 1
#define TEN_FLUSH NINE_FLUSH << 1
#define JACK_FLUSH TEN_FLUSH << 1
#define QUEEN_FLUSH JACK_FLUSH << 1
#define KING_FLUSH QUEEN_FLUSH << 1
#define ACE_FLUSH KING_FLUSH << 1

// _SEVEN tag suppressed
#define SIX 0
#define SEVEN 1
#define EIGHT 5
#define NINE 22
#define TEN 98
#define JACK 453
#define QUEEN 2031
#define KING 8698
#define ACE 22854
// end of _SEVEN tag suppressed

#define MAX_FIVE_NONFLUSH_KEY_INT ((4 * ACE_FIVE) + KING_FIVE)
#define MAX_FIVE_FLUSH_KEY_INT \
  (ACE_FLUSH | KING_FLUSH | QUEEN_FLUSH | JACK_FLUSH | TEN_FLUSH)
#define MAX_SEVEN_NONFLUSH_KEY_INT ((4 * ACE) + (3 * KING))
#define MAX_SEVEN_FLUSH_KEY_INT                                    \
  (ACE_FLUSH | KING_FLUSH | QUEEN_FLUSH | JACK_FLUSH | TEN_FLUSH | \
   NINE_FLUSH | EIGHT_FLUSH)

#define RANK_OFFSET_SHIFT 9
#define RANK_HASH_MOD ((1 << RANK_OFFSET_SHIFT) - 1)

#define MAX_FLUSH_CHECK_SUM (7 * CLUB)

// Bit masks
#define FLUSH_BIT_SHIFT 23
#define FACE_BIT_MASK ((1 << FLUSH_BIT_SHIFT) - 1)

#endif  // SKPOKEREVAL_CONSTANTS_H_
