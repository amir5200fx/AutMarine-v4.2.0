#pragma once
#ifndef _TColStd_Ary1dOfNumAvlTreeOfInteger_Header
#define _TColStd_Ary1dOfNumAvlTreeOfInteger_Header

#include <ADT_Ary1d.hxx>
#include <ADT_NumbAvlTree.hxx>

namespace AutLib
{
	typedef ADT_Ary1d<ADT_NumbAvlTree<Standard_Integer>> TColStd_Ary1dOfNumAvlTreeOfInteger;
}

#endif // !_TColStd_Ary1dOfNumAvlTreeOfInteger_Header
