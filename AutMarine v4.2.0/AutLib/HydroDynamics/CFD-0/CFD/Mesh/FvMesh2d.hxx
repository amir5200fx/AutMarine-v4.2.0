#pragma once
#ifndef _FvMesh2d_Header
#define _FvMesh2d_Header

//#include <FvGeom_Node2d.hxx>
//#include <FvGeom_Face2d.hxx>
//#include <FvGeom_Element2d.hxx>
#include <TColFvEntity_HAry1dOfNode2d.hxx>
#include <TColFvEntity_HAry1dOfFace2d.hxx>
#include <TColFvEntity_HAry1dOfElement2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_StaticMesh2d;

		class FvMesh2d
		{

		private:

			TColFvEntity_HAry1dOfNode2d theNodes_;

			TColFvEntity_HAry1dOfElement2d theElements_;

			TColFvEntity_HAry1dOfFace2d theFaces_;
			TColFvEntity_HAry1dOfFace2d theBoundaries_;

		public:

			FvMesh2d();

			Standard_Integer NbNodes() const;

			Standard_Integer NbFaces() const;

			Standard_Integer NbElements() const;

			const Global_Handle(FvEntity_Node2d) Node(const Standard_Integer theIndex) const;

			const Global_Handle(FvEntity_Face2d) Face(const Standard_Integer theIndex) const;

			const Global_Handle(FvEntity_Element2d) Element(const Standard_Integer theIndex) const;

			void ImportFrom(const FvGeom_StaticMesh2d& theStatic);
		};
	}
}

#include <FvMesh2dI.hxx>

#endif // !_FvMesh2d_Header
