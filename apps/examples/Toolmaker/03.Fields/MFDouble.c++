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

/*--------------------------------------------------------------
 *  This is an example from the Inventor Toolmaker,
 *  chapter 3, example 4.
 *
 *  Source file for "MFDouble" field.
 *------------------------------------------------------------*/

#include "MFDouble.h"

// Defines all required member variables and functions for a
// multiple-value field. We use the version that allocates field
// value storage with malloc(), since there is no constructor to
// call for our values.
SO_MFIELD_SOURCE_MALLOC(MFDouble, double, double);

//
// Initializes the class, setting up runtime type info.
//

void
MFDouble::initClass()
{
   // This macro takes the name of the class and the name of the
   // parent class
   SO_MFIELD_INIT_CLASS(MFDouble, SoMField);
}

//
// This reads one value of the double-precision field from a
// file. It is passed the index of the value to read; we can
// assume that the field already contains enough room to hold
// this value. It returns FALSE if the value could not be read
// successfully.
//

SbBool
MFDouble::read1Value(SoInput *in, int index)
{
   // Read a double from the input
   return in->read(values[index]);
}

//
// This writes one value of a double-precision field to a
// file.
//

void
MFDouble::write1Value(SoOutput *out, int index) const
{
   // Write a double
   out->write(values[index]);
}

//
// Returns number of ASCII values to write out per line.
//

int
MFDouble::getNumValuesPerLine() const
{
   // We can probably fit 4 doubles per line pretty easily.
   return 4;
}
