// DeleteDirectory.h: interface for the CDeleteDirectory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELETEDIRECTORY_H__8E7CBA01_530E_4D86_A911_4DAE0BB4AE49__INCLUDED_)
#define AFX_DELETEDIRECTORY_H__8E7CBA01_530E_4D86_A911_4DAE0BB4AE49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Claudio, PoliceMap, 06/03/2004 tutta la classe

class CDeleteDirectory  
{


public:
// CONSTRUCTORS
	CDeleteDirectory();
	virtual ~CDeleteDirectory();

// METHODS
	BOOL		TakeOwnership(LPCTSTR lpszFile);
	BOOL		SetPrivilege(HANDLE hToken,LPCTSTR lpszPrivilege,BOOL bChange);
	BOOL		SetPermission(LPCTSTR lpszFile, LPCTSTR lpszAccess, DWORD dwAccessMask);
	BOOL		DeleteDir(LPCTSTR lpszName);
};

#endif // !defined(AFX_DELETEDIRECTORY_H__8E7CBA01_530E_4D86_A911_4DAE0BB4AE49__INCLUDED_)
