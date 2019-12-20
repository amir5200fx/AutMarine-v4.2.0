#pragma once
#ifndef _FvGeom_StaticMesh2d_Header
#define _FvGeom_StaticMesh2d_Header

#include <FvPrimitives_Label.hxx>
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

			TColFvGeom_Ary1dOfFace2d theFaces_;

			TColFvGeom_Ary1dOfElement2d theElements_;

		public:

			FvGeom_StaticMesh2d();

			Label NbNodes() const;

			Label NbElements() const;

			Label NbFaces() const;

			const FvGeom_Node2d& Node(const Label theIndex) const;

			const FvGeom_Element2d& Element(const Label theIndex) const;

			const FvGeom_Face2d& Face(const Label theIndex) const;

			void Import(fstream& File);
		};
	}
}

#include <FvGeom_StaticMesh2dI.hxx>

#endif // !_FvGom_StaticMesh2d_Header
