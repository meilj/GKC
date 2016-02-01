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
This file contains GkcSys functions.
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __SA_GKC_SYS_H__
#define __SA_GKC_SYS_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// CRT MemoryManager

SA_FUNCTION GKC::IMemoryManager* _CrtMemoryManager_Get() throw();

//------------------------------------------------------------------------------
// share_ptr_block pool

SA_FUNCTION share_ptr_block* _SpbPool_Allocate() throw();
SA_FUNCTION void _SpbPool_Free(share_ptr_block* p) throw();

//------------------------------------------------------------------------------
// share_array_block pool

SA_FUNCTION share_array_block* _SabPool_Allocate() throw();
SA_FUNCTION void _SabPool_Free(share_array_block* p) throw();

//------------------------------------------------------------------------------
// share_com_block pool

SA_FUNCTION share_com_block* _ScbPool_Allocate() throw();
SA_FUNCTION void _ScbPool_Free(share_com_block* p) throw();

//------------------------------------------------------------------------------
// classes

#pragma pack(push, 1)

// _SObjHelper

class _SObjHelper
{
public:
	static void AddShareRef(share_block_base* p) throw()
	{
		if( p != NULL ) {
			assert( p->GetShareCount() > 0 );  //must have share object
			p->AddRefCopy();
		}
	}
	static void AddWeakRef(share_block_base* p) throw()
	{
		if( p != NULL ) {
			assert( p->GetWeakCount() > 0 );  //must have weak object
			p->WeakAddRef();
		}
	}
	static void MoveDirect(void*& pd, void*& ps) throw()
	{
		pd = ps;
		ps = NULL;
	}
	static void WeakPtrRelease(share_block_base* p) throw()
	{
		assert( p->GetWeakCount() > 0 );  //must have weak object
		if( p->WeakRelease() <= 0 ) {
			//free block
			::_SpbPool_Free(static_cast<share_ptr_block*>(p));
		}
	}
	static void WeakArrayRelease(share_block_base* p) throw()
	{
		assert( p->GetWeakCount() > 0 );  //must have weak object
		if( p->WeakRelease() <= 0 ) {
			//free block
			::_SabPool_Free(static_cast<share_array_block*>(p));
		}
	}
	static void WeakComRelease(share_block_base* p) throw()
	{
		assert( p->GetWeakCount() > 0 );  //must have weak object
		if( p->WeakRelease() <= 0 ) {
			//free block
			::_ScbPool_Free(static_cast<share_com_block*>(p));
		}
	}
	static void SharePtrRelease(share_block_base* p) throw()
	{
		assert( p->GetShareCount() > 0 );  //must have share object
		if( p->Release() <= 0 ) {
			//free object
			(static_cast<share_ptr_block*>(p))->DestroyObject();
			//weak
			WeakPtrRelease(p);
		}
	}
};

// _ShareObjectBase

class _ShareObjectBase
{
protected:
	_ShareObjectBase() throw() : m_pB(NULL)
	{
	}
	_ShareObjectBase(const _ShareObjectBase& src) throw() : m_pB(src.m_pB)
	{
		AddRef();
	}
	_ShareObjectBase(_ShareObjectBase&& src) throw()
	{
		_SObjHelper::MoveDirect(m_pB, src.m_pB);
	}
	~_ShareObjectBase() throw()
	{
	}

protected:
	void AddRef() throw()
	{
		_SObjHelper::AddShareRef(m_pB);
	}

public:
	bool IsBlockNull() const throw()
	{
		return m_pB == NULL;
	}

protected:
	share_block_base* m_pB;
};

// _WeakObjectBase

class _WeakObjectBase
{
protected:
	_WeakObjectBase() throw() : m_pB(NULL)
	{
	}
	_WeakObjectBase(const _WeakObjectBase& src) throw() : m_pB(src.m_pB)
	{
		AddRef();
	}
	_WeakObjectBase(_WeakObjectBase&& src) throw()
	{
		_SObjHelper::MoveDirect(m_pB, src.m_pB);
	}
	~_WeakObjectBase() throw()
	{
	}

protected:
	void AddRef() throw()
	{
		_SObjHelper::AddWeakRef(m_pB);
	}

public:
	bool IsBlockNull() const throw()
	{
		return m_pB == NULL;
	}

protected:
	share_block_base* m_pB;
};

// _SObjT<T, TBase>

template <class T, class TBase>
class _SObjT : public TBase
{
private:
	typedef TBase  baseClass;
	typedef _SObjT<T, TBase>  thisClass;

protected:
	_SObjT() throw()
	{
	}
	_SObjT(const _SObjT& src) throw() : baseClass(static_cast<const baseClass&>(src))
	{
	}
	_SObjT(_SObjT&& src) throw() : baseClass(rv_forward(static_cast<baseClass&>(src)))
	{
	}
	~_SObjT() throw()
	{
	}

	thusClass& operator=(const thisClass& src) throw()
	{
		if( &src != this ) {
			if( src.m_pB != m_pB ) {
				//release
				T* pT = static_cast<T*>(this);
				pT->Release();
				//assign
				m_pB = src.m_pB;
				pT->do_assign(src);
				//add ref
				baseClass::AddRef();
			}
		}
		return *this;
	}
	thisClass& operator=(thisClass&& src) throw()
	{
		if( &src != this ) {
			if( src.m_pB != m_pB ) {
				//release
				T* pT = static_cast<T*>(this);
				pT->Release();
				//move
				_SObjHelper::MoveDirect(m_pB, src.m_pB);
				pT->do_move(src);
			}
		}
		return *this;
	}

private:
	//overrideable
	void Release() throw();
	void do_assign(const thisClass& src) throw();
	void do_move(thisClass&& src) throw();
};

// _SharePtrBase

class _SharePtrBase : public _SObjT<_SharePtrBase, _ShareObjectBase>
{
private:
	typedef _SObjT<_SharePtrBase, _ShareObjectBase>  baseClass;
	typedef _SharePtrBase  thisClass;

protected:
	_SharePtrBase() throw() : m_pT(NULL)
	{
	}
	_SharePtrBase(const _SharePtrBase& src) throw() : baseClass(static_cast<const baseClass&>(src)), m_pT(src.m_pT)
	{
	}
	_SharePtrBase(_SharePtrBase&& src) throw() : baseClass(rv_forward(static_cast<baseClass&>(src)))
	{
		_SObjHelper::MoveDirect(m_pT, src.m_pT);
	}
	~_SharePtrBase() throw()
	{
		Release();
	}

	_SharePtrBase& operator=(const _SharePtrBase& src) throw()
	{
		baseClass::operator=(static_cast<const baseClass&>(src));
		return *this;
	}
	_SharePtrBase& operator=(_SharePtrBase&& src) throw()
	{
		baseClass::operator=(rv_forward(static_cast<baseClass&>(src)));
		return *this;
	}

//overriders

public:
	void Release() throw()
	{
		if( m_pB != NULL ) {
			_SObjHelper::SharePtrRelease(m_pB);
			m_pB = NULL;
			m_pT = NULL;
		}
		else {
			assert( m_pT == NULL );
		} //end if
	}

protected:
	void do_assign(const baseClass& src) throw()
	{
		m_pT = (static_cast<const thisClass&>(src)).m_pT;
	}
	void do_move(baseClass&& src) throw()
	{
		_SObjHelper::MoveDirect(m_pT, (static_cast<thisClass&>(src)).m_pT);
	}

protected:
	void* m_pT;  //A pointer to object

private:
	friend class baseClass;
};

// _WeakPtrBase

class _WeakPtrBase : public _SObjT<_WeakPtrBase, _WeakObjectBase>
{
private:
	typedef _SObjT<_WeakPtrBase, _WeakObjectBase>  baseClass;
	typedef _WeakPtrBase  thisClass;

protected:
	_WeakPtrBase() throw() : m_pT(NULL)
	{
	}
	_WeakPtrBase(const _WeakPtrBase& src) throw() : baseClass(static_cast<const baseClass&>(src)), m_pT(src.m_pT)
	{
	}
	_WeakPtrBase(_WeakPtrBase&& src) throw() : baseClass(rv_forward(static_cast<baseClass&>(src)))
	{
		_SObjHelper::MoveDirect(m_pT, src.m_pT);
	}
	~_WeakPtrBase() throw()
	{
		Release();
	}

	_WeakPtrBase& operator=(const _WeakPtrBase& src) throw()
	{
		baseClass::operator=(static_cast<const baseClass&>(src));
		return *this;
	}
	_WeakPtrBase& operator=(_WeakPtrBase&& src) throw()
	{
		baseClass::operator=(rv_forward(static_cast<baseClass&>(src)));
		return *this;
	}

//overriders

public:
	void Release() throw()
	{
		if( m_pB != NULL ) {
			//weak
			_SObjHelper::WeakPtrRelease(m_pB);
			m_pB = NULL;
			m_pT = NULL;
		}
		else {
			assert( m_pT == NULL );
		} //end if
	}

protected:
	void do_assign(const baseClass& src) throw()
	{
		m_pT = (static_cast<const thisClass&>(src)).m_pT;
	}
	void do_move(baseClass&& src) throw()
	{
		_SObjHelper::MoveDirect(m_pT, (static_cast<thisClass&>(src)).m_pT);
	}

protected:
	void* m_pT;  //A pointer to object

private:
	friend class baseClass;
};

// _SharePtr<T>

template <typename T>
class _SharePtr : public _SharePtrBase
{
private:
	typedef _SharePtrBase  baseClass;
	typedef _SharePtr<T>   thisClass;

public:
	_SharePtr() throw()
	{
	}
	_SharePtr(const _SharePtr& src) throw() : baseClass(static_cast<const baseClass&>(src))
	{
	}
	_SharePtr(_SharePtr&& src) throw() : baseClass(rv_forward(static_cast<baseClass&>(src)))
	{
	}
	~_SharePtr() throw()
	{
	}

	_SharePtr<T>& operator=(const _SharePtr<T>& src) throw()
	{
		baseClass::operator=(static_cast<const baseClass&>(src));
		return *this;
	}
	_SharePtr<T>& operator=(_SharePtr<T>&& src) throw()
	{
		baseClass::operator=(rv_forward(static_cast<baseClass&>(src)));
		return *this;
	}

	bool operator==(const _SharePtr<T>& right) const throw()
	{
		return m_pT == right.m_pT;
	}
	bool operator!=(const _SharePtr<T>& right) const throw()
	{
		return !operator==(right);
	}

	const T& Deref() const throw()
	{
		assert( !IsBlockNull() && m_pT != NULL );
		return *((T*)m_pT);
	}
	T& Deref() throw()
	{
		assert( !IsBlockNull() && m_pT != NULL );
		return *((T*)m_pT);
	}

private:
	friend class _SharePtrHelper;
};

// _WeakPtr<T>

template <typename T>
class _WeakPtr : public _WeakPtrBase
{
private:
	typedef _WeakPtrBase  baseClass;
	typedef _WeakPtr<T>   thisClass;

public:
	_WeakPtr() throw()
	{
	}
	_WeakPtr(const _WeakPtr& src) throw() : baseClass(static_cast<const baseClass&>(src))
	{
	}
	_WeakPtr(_WeakPtr&& src) throw() : baseClass(rv_forward(static_cast<baseClass&>(src)))
	{
	}
	~_WeakPtr() throw()
	{
	}

	_WeakPtr<T>& operator=(const _WeakPtr<T>& src) throw()
	{
		baseClass::operator=(static_cast<const baseClass&>(src));
		return *this;
	}
	_WeakPtr<T>& operator=(_WeakPtr<T>&& src) throw()
	{
		baseClass::operator=(rv_forward(static_cast<baseClass&>(src)));
		return *this;
	}

	bool operator==(const _WeakPtr<T>& right) const throw()
	{
		return m_pT == right.m_pT;
	}
	bool operator!=(const _WeakPtr<T>& right) const throw()
	{
		return !operator==(right);
	}

private:
	friend class _SharePtrHelper;
};

// _SharePtrHelper

class _SharePtrHelper
{
protected:
	BEGIN_NOINLINE
	template <typename T>
	static void object_destruction(void* p) throw()
	END_NOINLINE
	{
		((T*)p)->~T();
	}

public:
	//make share object
	template <typename T, typename... Args>
	static _SharePtr<T> MakeSharePtr(const GKC::RefPtr<GKC::IMemoryManager>& mgr, Args&&... args)
	{
		assert( !mgr.IsNull() );

		//allocate
		share_ptr_block* pB = ::_SpbPool_Allocate();
		if( pB == NULL )
			throw GKC::OutOfMemoryException();

		T* pT = (T*)((const_cast<GKC::RefPtr<GKC::IMemoryManager>&>(mgr)).Deref().Allocate(sizeof(T)));
		if( pT == NULL ) {
			::_SpbPool_Free(pB);
			throw OutOfMemoryException();
		}

		_SharePtr<T> ret;
		//constructor
		try {
			//may throw
			call_constructor(*pT, rv_forward<Args>(args)...);
		}
		catch(...) {
			(const_cast<GKC::RefPtr<GKC::IMemoryManager>&>(mgr)).Deref().Free((uintptr)pT);
			::_SpbPool_Free(pB);
			throw;  //re-throw
		}

		//initialize
		pB->SetMemoryManager(mgr);
		pB->SetAddress(pT);
		pB->SetDestructionFunc(&(object_destruction<T>));

		//return value
		ret.m_pB = static_cast<share_block_base*>(pB);
		ret.m_pT = pT;

		return ret;
	}

	//obtain weak ptr
	template <typename T>
	static _WeakPtr<T> ToWeakPtr(const _SharePtr<T>& sp) throw()
	{
		_WeakPtr<T> ret;
		ret.m_pB = sp.m_pB;
		ret.m_pT = sp.m_pT;
		_SObjHelper::AddWeakRef(ret.m_pB);
		return ret;
	}
	//to share ptr
	template <typename T>
	static _SharePtr<T> ToSharePtr(const _WeakPtr<T>& sp) throw()
	{
		_SharePtr<T> ret;
		ret.m_pB = sp.m_pB;
		ret.m_pT = sp.m_pT;
		if( ret.m_pB != NULL ) {
			if( !((ret.m_pB)->AddRefLock()) ) {
				ret.m_pT = NULL;  //share object freed
				ret.m_pB = NULL;
			}
		}
		return ret;
	}

	//type cast (derived -> base or base -> derived)
	template <class TSrc, class TDest>
	static _SharePtr<TDest> TypeCast(const _SharePtr<TSrc>& sp) throw()
	{
		_SharePtr<TDest> ret;
		ret.m_pB = sp.m_pB;
		ret.m_pT = sp.m_pT;
		if( ret.m_pB != NULL ) {
			assert( ret.m_pT != NULL );  //must have share object
			ret.m_pT = static_cast<TDest*>(ret.m_pT);
			(ret.m_pB)->AddRefCopy();
		}
		return ret;
	}
	template <class TSrc, class TDest>
	static _WeakPtr<TDest> TypeCast(const _WeakPtr<TSrc>& sp) throw()
	{
		_WeakPtr<TDest> ret;
		ret.m_pB = sp.m_pB;
		ret.m_pT = sp.m_pT;
		if( ret.m_pB != NULL ) {
			assert( ret.m_pT != NULL );  //must have weak object
			ret.m_pT = static_cast<TDest*>(ret.m_pT);
			(ret.m_pB)->WeakAddRef();
		}
		return ret;
	}

	//clone
	template <typename T>
	static _SharePtr<T> Clone(const _SharePtr<T>& sp)  //may throw
	{
		return ( !sp.IsBlockNull() )
				? ( assert( m_pT != NULL ), MakeSharePtr((sp.m_pB)->GetMemoryManager(), sp.Deref()) )
				: SharePtr<T>();
	}

	//get internal pointer
	template <typename T>
	static T* GetInternalPointer(const _SharePtr<T>& sp) throw()
	{
		return sp.m_pT;
	}
	template <typename T>
	static T* GetInternalPointer(const _WeakPtr<T>& sp) throw()
	{
		return sp.m_pT;
	}

	//only for test
	template <typename T>
	static int test_get_share_count(const _SharePtr<T>& sp) throw()
	{
		return sp.IsBlockNull() ? 0 : (sp.m_pB)->GetShareCount();
	}
	template <typename T>
	static int test_get_weak_count(const _SharePtr<T>& sp) throw()
	{
		return sp.IsBlockNull() ? 0 : (sp.m_pB)->GetWeakCount();
	}
};

#pragma pack(pop)

//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
#endif //__SA_GKC_SYS_H__
////////////////////////////////////////////////////////////////////////////////
