/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

//  -*- C++ -*-

/*
 * Copyright (C) 1991   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |	Callback list - a list of callback functions and associated data,
 |   with member functions to add, remove, and invoke callbacks.
 |	
 |   Classes:	MyFloatCallbackList
 |
 |   Author(s):	David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FLOAT_CALLBACK_LIST_
#define  _SO_FLOAT_CALLBACK_LIST_

#include <Inventor/SbPList.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: MyFloatCallbackList
//
//////////////////////////////////////////////////////////////////////////////

// Callback functions that are registered with this class should
// be cast to this type.
typedef void MyFloatCallbackListCB(void *userData, float callbackData);

// C-api: prefix=SoFCBList
class MyFloatCallbackList {
    
  public:

    MyFloatCallbackList();
    ~MyFloatCallbackList();
    
    //
    // Managing callback functions
    // At callback time, f will be called with userData as the first
    // parameter, and callback specific data as the second parameter.
    // e.g. (*f)(userData, callbackData);

    // C-api: name=addCB
    void    addCallback(MyFloatCallbackListCB *f, void *userData = NULL);
    // C-api: name=removeCB
    void    removeCallback(MyFloatCallbackListCB *f, void *userData = NULL);
    
    // C-api: name=clearCB
    void    clearCallbacks()			    { list.truncate(0); }
    // C-api: name=getNumCB
    int	    getNumCallbacks() const		    { return list.getLength(); }

    // C-api: name=invokeCB
    void    invokeCallbacks(float callbackData);

  private:
  
    // callbackList holds a list of functions and user data
    SbPList 	list;
};

#endif  /* _SO_FLOAT_CALLBACK_LIST_ */
