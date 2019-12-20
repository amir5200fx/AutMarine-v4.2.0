#pragma once
#ifndef _FvEntity_Face2d_Header
#define _FvEntity_Face2d_Header

#include <Global_Memory.hxx>
#include <Geom_Pnt2d.hxx>
#include <FvPrimitives_Label.hxx>
#include <FvPrimitives_Vec2.hxx>
#include <FvBC_Physics.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Node2d;
		class FvEntity_Element2d;
		class FvEntity_Face2d;

		class FvEntity_Face2d
		{

		private:

			Label theIndex_;

			const Global_Handle(FvEntity_Node2d) theNode0_;
			const Global_Handle(FvEntity_Node2d) theNode1_;

			Geom_Pnt2d theCentre_;

			Vec2 theNormal_;
			Vec2 theSf_;
			Vec2 theEf_;
			Vec2 theTf_;
			Vec2 theCF_;

			Scalar theArea_;
			Scalar thegc_;
			Scalar theEfj_;
			Scalar theCFj_;

			FvBC_Physics thePhysics_;

			const Global_Handle(FvEntity_Element2d) theElement_;

			const Global_Handle(FvEntity_Face2d) thePair_;

		public:

			FvEntity_Face2d();

			FvEntity_Face2d(const Label theIndex, const Global_Handle(FvEntity_Node2d) theNode0, const Global_Handle(FvEntity_Node2d) theNode1);

			virtual ~FvEntity_Face2d();

			Label Index() const;

			const Global_Handle(FvEntity_Node2d) Node(const Label theIndex) const;

			const Global_Handle(FvEntity_Element2d) Element() const;

			const Global_Handle(FvEntity_Face2d) Pair() const;

			const Geom_Pnt2d& Centre() const;

			const Vec2& Normal() const;

			const Vec2& Sf() const;

			const Vec2& Ef() const;

			const Vec2& Tf() const;

			const Vec2& CF() const;

			Scalar Area() const;

			Scalar gcCoeff() const;

			Scalar Efj() const;

			Scalar CFj() const;

			FvBC_Physics Physics() const;

			Standard_Boolean IsOnBoundary() const;

			void SetIndex(const Label theIndex);

			void SetNode(const Label theIndex, const Global_Handle(FvEntity_Node2d) theNode);

			void SetElement(const Global_Handle(FvEntity_Element2d) theElement);

			void SetPair(const Global_Handle(FvEntity_Face2d) thePair);

			void SetCentre(const Geom_Pnt2d& theCoord);

			void SetNormal(const Vec2& theVector);

			void SetSf(const Vec2& theVector);

			void SetLength(const Scalar theLength);

			void Setgc(const Scalar thegc);

			void SetPhysics(const FvBC_Physics thePhysics);
		};

	}
}

#include <FvEntity_Face2dI.hxx>

using AutLib::FvLib::FvEntity_Face2d;

#endif // !_FvEntity_Face2d_Header
