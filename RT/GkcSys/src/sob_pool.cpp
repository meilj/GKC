﻿/*
** Copyright (c) 2013, Xin YUAN, courses of Zhejiang University
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
This file contains shared-object-header-block pool functions.
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "_GkcSys.h"

#include "globals.h"

////////////////////////////////////////////////////////////////////////////////

//internal

template <class TElement>
inline TElement* t_pool_allocate(fixed_size_memory_pool<sizeof(TElement)>& pool) throw()
{
	TElement* p = NULL;
	try {
		GKC::SyncLock<GKC::Mutex> lock(GET_SA_GLOBAL_VARIABLE(g_mutex));
		p = (TElement*)pool.Allocate();
	}
	catch(...) {
		p = NULL;
	}
	//constructor
	if( p != NULL )
		call_constructor(*p);  //no throw
	return p;
}
template <class TElement>
inline void t_pool_free(fixed_size_memory_pool<sizeof(TElement)>& pool, TElement* p) throw()
{
	if( p == NULL )
		return ;
	//destructor
	p->~TElement();
	try {
		GKC::SyncLock<GKC::Mutex> lock(GET_SA_GLOBAL_VARIABLE(g_mutex));
		pool.Free(p);
	}
	catch(...) {
	}
}

//functions

//SPB

share_ptr_block* _SpbPool_Allocate() throw()
{
	return t_pool_allocate<share_ptr_block>(GET_SA_GLOBAL_VARIABLE(spb_pool));
}
void _SpbPool_Free(share_ptr_block* p) throw()
{
	t_pool_free<share_ptr_block>(GET_SA_GLOBAL_VARIABLE(spb_pool), p);
}

//SAB

share_array_block* _SabPool_Allocate() throw()
{
	return t_pool_allocate<share_array_block>(GET_SA_GLOBAL_VARIABLE(sab_pool));
}
void _SabPool_Free(share_array_block* p) throw()
{
	t_pool_free<share_array_block>(GET_SA_GLOBAL_VARIABLE(sab_pool), p);
}

//SCB

share_com_block* _ScbPool_Allocate() throw()
{
	return t_pool_allocate<share_com_block>(GET_SA_GLOBAL_VARIABLE(scb_pool));
}
void _ScbPool_Free(share_com_block* p) throw()
{
	t_pool_free<share_com_block>(GET_SA_GLOBAL_VARIABLE(scb_pool), p);
}

////////////////////////////////////////////////////////////////////////////////
