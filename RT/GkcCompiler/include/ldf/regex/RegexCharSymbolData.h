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
This file contains component class of regular expression character symbol data.
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __REGEX_CHAR_SYMBOL_DATA_H__
#define __REGEX_CHAR_SYMBOL_DATA_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace GKC {
////////////////////////////////////////////////////////////////////////////////

// RegexCharSymbolData

class RegexCharSymbolData : public _GrammarSymbolDataBase,
							public _I_RegexCharSymbolData_Utility
{
public:
	RegexCharSymbolData() throw()
	{
	}
	~RegexCharSymbolData() throw()
	{
	}

// _I_RegexCharSymbolData_Utility methods
	virtual void GetCharRange(_RegexCharRange& rcr) throw()
	{
		rcr = m_rcr;
	}
	virtual void SetCharRange(const _RegexCharRange& rcr) throw()
	{
		m_rcr = rcr;
	}

private:
	_RegexCharRange m_rcr;

private:
	//noncopyable
	RegexCharSymbolData(const RegexCharSymbolData&) throw();
	RegexCharSymbolData& operator=(const RegexCharSymbolData&) throw();
};

DECLARE_COM_TYPECAST(RegexCharSymbolData)

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
