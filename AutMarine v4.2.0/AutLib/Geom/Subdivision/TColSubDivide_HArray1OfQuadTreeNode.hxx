#pragma once
#ifndef _TColSubDivide_HArray1OfQuadTreeNode_Header
#define _TColSubDivide_HArray1OfQuadTreeNode_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>
#include <SubDivide_QuadTreeNode.hxx>

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO SubDivide_QuadTreeNode)> TColSubDivide_HArray1OfQuadTreeNode;
}

#endif // !_TColSubDivide_HArray1OfQuadTreeNode_Header
