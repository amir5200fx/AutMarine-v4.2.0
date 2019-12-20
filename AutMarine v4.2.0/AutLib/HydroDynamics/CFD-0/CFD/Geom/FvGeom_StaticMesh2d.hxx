#pragma once
#ifndef _FvGeom_StaticMesh2d_Header
#define _FvGeom_StaticMesh2d_Header

#include <Standard_Stream.hxx>
#include <TColFvGeom_Ary1dOfNode2d.hxx>
#include <TColFvGeom_Ary1dOfFace2d.hxx>
#include <TColFvGeom_Ary1dOfElement2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_StaticMesh2d
		{

		private:

			TColFvGeom_Ary1dOfNode2d theNodes_;

			TColFvGeom_Ary1dOfElement2d theElements_;

			TColFvGeom_Ary1dOfFace2d theFaces_;

		public:

			FvGeom_StaticMesh2d();

			void Import(fstream& File);

			Standard_Integer NbNodes() const;

			Standard_Integer NbElements() const;

			Standard_Integer NbFaces() const;

			const FvGeom_Node2d& Node(const Standard_Integer theIndex) const;

			const FvGeom_Element2d& Element(const Standard_Integer theIndex) const;

			const FvGeom_Face2d& Face(const Standard_Integer theIndex) const;
		};
	}
}

#include <FvGeom_StaticMesh2dI.hxx>

#endif // !_FvGeom_StaticMesh2d_Header
