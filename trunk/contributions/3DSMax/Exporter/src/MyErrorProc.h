// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __MYERRORPROC__H
#define __MYERRORPROC__H

class MyErrorProc : public IGameErrorCallBack
{
public:
	void ErrorProc( IGameError error)
	{
		TCHAR * buf = GetLastIGameErrorText();
		DebugPrint( "ErrorCode = %d ErrorText = %s\n", error, buf );
	}
};

#endif //__MYERRORPROC__H