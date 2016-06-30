﻿/*
** Copyright (c) 2016, Xin YUAN, courses of Zhejiang University
** All rights reserved.
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the 2-Clause BSD License.
**
** Author contact information:
**   yxxinyuan@zju.edu.cn
**
*/

/*
This file contains PDA tables for regular expressions.
*/

////////////////////////////////////////////////////////////////////////////////

#include "PreComp.h"

#include "base/Pda.h"
#include "base/PdaTable.h"

#include "ldf/LdfRegexPda.h"

////////////////////////////////////////////////////////////////////////////////
namespace GKC {
////////////////////////////////////////////////////////////////////////////////

// LdfRegexPdaTraits

BEGIN_PDA_TRAIT_CLASS(LdfRegexPdaTraits)
	PDA_BEGIN_STATE_TRANSITION(PDA_STATE_START)
		PDA_STATE_TRANSITION_ENTRY(101, 3)   //regex_exp
		PDA_STATE_TRANSITION_ENTRY(102, 4)   //regex_term
		PDA_STATE_TRANSITION_ENTRY(103, 5)   //regex_factor_1
		PDA_STATE_TRANSITION_ENTRY(27, 6)    //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, 7)    //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(104, 31)  //regex_factor
		PDA_STATE_TRANSITION_ENTRY(105, 30)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(106, 29)  //regex_char_set
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(3)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, PDA_STATE_ACCEPTED)  //$
		PDA_STATE_TRANSITION_ENTRY(26, 12)   //TK_VERT
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(4)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -2)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -2)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(28, -2)   //TK_RPAREN
		PDA_STATE_TRANSITION_ENTRY(103, 8)   //regex_factor_1
		PDA_STATE_TRANSITION_ENTRY(104, 31)  //regex_factor
		PDA_STATE_TRANSITION_ENTRY(27, 6)    //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(105, 30)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(106, 29)  //regex_char_set
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(19, 7)    //TK_LBRACKET
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(5)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -4)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -4)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -4)   //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -4)   //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -4)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(28, -4)   //TK_RPAREN
		PDA_STATE_TRANSITION_ENTRY(25, 9)    //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, 10)   //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, 11)   //TK_QUESTION
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(6)
		PDA_STATE_TRANSITION_ENTRY(102, 4)   //regex_term
		PDA_STATE_TRANSITION_ENTRY(103, 5)   //regex_factor_1
		PDA_STATE_TRANSITION_ENTRY(104, 31)  //regex_factor
		PDA_STATE_TRANSITION_ENTRY(105, 30)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(106, 29)  //regex_char_set
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(101, 17)  //regex_exp
		PDA_STATE_TRANSITION_ENTRY(19, 7)    //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(27, 6)    //TK_LPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(7)
		PDA_STATE_TRANSITION_ENTRY(108, 27)  //regex_char_e
		PDA_STATE_TRANSITION_ENTRY(109, 26)  //regex_char_range
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(105, 14)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(107, 15)  //regex_char_item
		PDA_STATE_TRANSITION_ENTRY(22, 16)   //TK_UPARROW
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(8)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -3)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -3)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -3)   //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -3)   //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -3)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(28, -3)   //TK_RPAREN
		PDA_STATE_TRANSITION_ENTRY(25, 9)    //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, 10)   //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, 11)   //TK_QUESTION
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(9)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -5)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -5)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -5)   //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -5)   //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -5)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -5)   //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -5)   //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -5)   //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -5)   //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(10)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -6)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -6)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -6)   //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -6)   //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -6)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -6)   //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -6)   //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -6)   //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -6)   //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(11)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -7)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -7)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -7)   //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -7)   //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -7)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -7)   //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -7)   //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -7)   //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -7)   //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(12)
		PDA_STATE_TRANSITION_ENTRY(102, 13)  //regex_term
		PDA_STATE_TRANSITION_ENTRY(103, 5)   //regex_factor_1
		PDA_STATE_TRANSITION_ENTRY(27, 6)    //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, 7)    //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(104, 31)  //regex_factor
		PDA_STATE_TRANSITION_ENTRY(105, 30)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(106, 29)  //regex_char_set
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(13)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -1)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -1)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(28, -1)   //TK_RPAREN
		PDA_STATE_TRANSITION_ENTRY(103, 8)   //regex_factor_1
		PDA_STATE_TRANSITION_ENTRY(104, 31)  //regex_factor
		PDA_STATE_TRANSITION_ENTRY(27, 6)    //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(105, 30)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(19, 7)    //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(106, 29)  //regex_char_set
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(14)
		PDA_STATE_TRANSITION_ENTRY(20, -17)  //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -17)  //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(21, 18)   //TK_MINUS
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(15)
		PDA_STATE_TRANSITION_ENTRY(109, 26)  //regex_char_range
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(20, 24)   //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(108, 23)  //regex_char_e
		PDA_STATE_TRANSITION_ENTRY(105, 14)  //regex_char
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(16)
		PDA_STATE_TRANSITION_ENTRY(108, 27)  //regex_char_e
		PDA_STATE_TRANSITION_ENTRY(109, 26)  //regex_char_range
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(107, 19)  //regex_char_item
		PDA_STATE_TRANSITION_ENTRY(105, 14)  //regex_char
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(17)
		PDA_STATE_TRANSITION_ENTRY(26, 12)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(28, 25)   //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(18)
		PDA_STATE_TRANSITION_ENTRY(110, 22)  //regex_char_s
		PDA_STATE_TRANSITION_ENTRY(105, 21)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(19)
		PDA_STATE_TRANSITION_ENTRY(109, 26)  //regex_char_range
		PDA_STATE_TRANSITION_ENTRY(29, 28)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(108, 23)  //regex_char_e
		PDA_STATE_TRANSITION_ENTRY(105, 14)  //regex_char
		PDA_STATE_TRANSITION_ENTRY(20, 20)   //TK_RBRACKET
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(20)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -13)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -13)  //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -13)  //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -13)  //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -13)  //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -13)  //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -13)  //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -13)  //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -13)  //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(21)
		PDA_STATE_TRANSITION_ENTRY(20, -19)  //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -19)  //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(22)
		PDA_STATE_TRANSITION_ENTRY(20, -18)  //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -18)  //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(23)
		PDA_STATE_TRANSITION_ENTRY(20, -14)  //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -14)  //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(24)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -12)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -12)  //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -12)  //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -12)  //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -12)  //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -12)  //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -12)  //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -12)  //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -12)  //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(25)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -9)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -9)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -9)   //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -9)   //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -9)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -9)   //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -9)   //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -9)   //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -9)   //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(26)
		PDA_STATE_TRANSITION_ENTRY(20, -16)  //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -16)  //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(27)
		PDA_STATE_TRANSITION_ENTRY(20, -15)  //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -15)  //TK_CHAR
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(28)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -20)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -20)  //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -20)  //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -20)  //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -20)  //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -20)  //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -20)  //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -20)  //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(20, -20)  //TK_RBRACKET
		PDA_STATE_TRANSITION_ENTRY(21, -20)  //TK_MINUS
		PDA_STATE_TRANSITION_ENTRY(28, -20)  //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(29)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -11)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -11)  //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -11)  //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -11)  //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -11)  //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -11)  //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -11)  //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -11)  //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -11)  //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(30)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -10)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -10)  //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -10)  //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -10)  //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -10)  //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -10)  //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -10)  //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -10)  //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -10)  //TK_RPAREN
	PDA_END_STATE_TRANSITION()
	PDA_BEGIN_STATE_TRANSITION(31)
		PDA_STATE_TRANSITION_ENTRY(PDA_END_OF_EVENT, -8)  //$
		PDA_STATE_TRANSITION_ENTRY(26, -8)   //TK_VERT
		PDA_STATE_TRANSITION_ENTRY(27, -8)   //TK_LPAREN
		PDA_STATE_TRANSITION_ENTRY(19, -8)   //TK_LBRACKET
		PDA_STATE_TRANSITION_ENTRY(29, -8)   //TK_CHAR
		PDA_STATE_TRANSITION_ENTRY(25, -8)   //TK_PLUS
		PDA_STATE_TRANSITION_ENTRY(24, -8)   //TK_STAR
		PDA_STATE_TRANSITION_ENTRY(23, -8)   //TK_QUESTION
		PDA_STATE_TRANSITION_ENTRY(28, -8)   //TK_RPAREN
	PDA_END_STATE_TRANSITION()

	PDA_BEGIN_STATE_SET()
		PDA_STATE_SET_ENTRY(PDA_STATE_START)
		PDA_STATE_SET_ENTRY(3)
		PDA_STATE_SET_ENTRY(4)
		PDA_STATE_SET_ENTRY(5)
		PDA_STATE_SET_ENTRY(6)
		PDA_STATE_SET_ENTRY(7)
		PDA_STATE_SET_ENTRY(8)
		PDA_STATE_SET_ENTRY(9)
		PDA_STATE_SET_ENTRY(10)
		PDA_STATE_SET_ENTRY(11)
		PDA_STATE_SET_ENTRY(12)
		PDA_STATE_SET_ENTRY(13)
		PDA_STATE_SET_ENTRY(14)
		PDA_STATE_SET_ENTRY(15)
		PDA_STATE_SET_ENTRY(16)
		PDA_STATE_SET_ENTRY(17)
		PDA_STATE_SET_ENTRY(18)
		PDA_STATE_SET_ENTRY(19)
		PDA_STATE_SET_ENTRY(20)
		PDA_STATE_SET_ENTRY(21)
		PDA_STATE_SET_ENTRY(22)
		PDA_STATE_SET_ENTRY(23)
		PDA_STATE_SET_ENTRY(24)
		PDA_STATE_SET_ENTRY(25)
		PDA_STATE_SET_ENTRY(26)
		PDA_STATE_SET_ENTRY(27)
		PDA_STATE_SET_ENTRY(28)
		PDA_STATE_SET_ENTRY(29)
		PDA_STATE_SET_ENTRY(30)
		PDA_STATE_SET_ENTRY(31)
	PDA_END_STATE_SET()

	PDA_BEGIN_RULE()
		PDA_RULE_ENTRY(101, 3)    // regex_exp -> regex_exp TK_VERT regex_term
		PDA_RULE_ENTRY(101, 1)    // regex_exp -> regex_term
		PDA_RULE_ENTRY(102, 2)    // regex_term -> regex_term regex_factor_1
		PDA_RULE_ENTRY(102, 1)    // regex_term -> regex_factor_1
		PDA_RULE_ENTRY(103, 2)    // regex_factor_1 -> regex_factor_1 TK_PLUS
		PDA_RULE_ENTRY(103, 2)    // regex_factor_1 -> regex_factor_1 TK_STAR
		PDA_RULE_ENTRY(103, 2)    // regex_factor_1 -> regex_factor_1 TK_QUESTION
		PDA_RULE_ENTRY(103, 1)    // regex_factor_1 -> regex_factor
		PDA_RULE_ENTRY(104, 3)    // regex_factor -> TK_LPAREN regex_exp TK_RPAREN
		PDA_RULE_ENTRY(104, 1)    // regex_factor -> regex_char
		PDA_RULE_ENTRY(104, 1)    // regex_factor -> regex_char_set
		PDA_RULE_ENTRY(106, 3)    // regex_char_set -> TK_LBRACKET regex_char_item TK_RBRACKET
		PDA_RULE_ENTRY(106, 4)    // regex_char_set -> TK_LBRACKET TK_UPARROW regex_char_item TK_RBRACKET
		PDA_RULE_ENTRY(107, 2)    // regex_char_item -> regex_char_item regex_char_e
		PDA_RULE_ENTRY(107, 1)    // regex_char_item -> regex_char_e
		PDA_RULE_ENTRY(108, 1)    // regex_char_e -> regex_char_range
		PDA_RULE_ENTRY(108, 1)    // regex_char_e -> regex_char
		PDA_RULE_ENTRY(109, 3)    // regex_char_range -> regex_char TK_MINUS regex_char_s
		PDA_RULE_ENTRY(110, 1)    // regex_char_s -> regex_char
		PDA_RULE_ENTRY(105, 1)    // regex_char -> TK_CHAR
	PDA_END_RULE()
END_PDA_TRAIT_CLASS(LdfRegexPdaTraits)

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
