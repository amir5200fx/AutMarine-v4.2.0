#pragma once
#ifndef _FvEntity_Face2d_Header
#define _FvEntity_Face2d_Header

#include <Global_Memory.hxx>
#include <Geom_Pnt2d.hxx>
#include <FvBC_Physics.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Node2d;
		class FvEntity_Element2d;

		class FvEntity_Face2d
		{

		private:

			Standard_Integer theIndex_;

			const Global_Handle(FvEntity_Node2d) theNode0_;
			const Global_Handle(FvEntity_Node2d) theNode1_;

			Geom_Pnt2d theCentre_;

			Geom_Pnt2d theN_;
			Geom_Pnt2d theA_;
			Geom_Pnt2d theD_;

			Geom_Pnt2d theRpl_;
			Geom_Pnt2d theRnl_;

			Standard_Real theVolume_;
			Standard_Real thed_;

			FvBC_Physics thePhysics_;

			const Global_Handle(FvEntity_Element2d) theElement_;

			const Global_Handle(FvEntity_Face2d) thePair_;

		public:

			FvEntity_Face2d();

			FvEntity_Face2d(const Standard_Integer theIndex, const Global_Handle(FvEntity_Node2d) theNode0, const Global_Handle(FvEntity_Node2d) theNode1);

			virtual ~FvEntity_Face2d();

			Standard_Integer Index() const;

			const Global_Handle(FvEntity_Node2d) Node(const Standard_Integer theIndex) const;

			const Global_Handle(FvEntity_Element2d) Element() const;

			const Global_Handle(FvEntity_Face2d) Pair() const;

			const Geom_Pnt2d& Centre() const;

			const Geom_Pnt2d& N() const;

			const Geom_Pnt2d& A() const;

			const Geom_Pnt2d& D() const;

			const Geom_Pnt2d& Rpl() const;

			const Geom_Pnt2d& Rnl() const;

			Standard_Real Volume() const;

			Standard_Real d() const;

			FvBC_Physics Physics() const;

			void SetIndex(const Standard_Integer theIndex);

			void SetNode(const Standard_Integer theIndex, const Global_Handle(FvEntity_Node2d) theNode);

			void SetElement(const Global_Handle(FvEntity_Element2d) theElement);

			void SetPair(const Global_Handle(FvEntity_Face2d) thePair);

			void SetCentre(const Geom_Pnt2d& theCoord);

			void SetN(const Geom_Pnt2d& theN);

			void SetA(const Geom_Pnt2d& theA);

			void SetD(const Geom_Pnt2d& theD);

			void SetRpl(const Geom_Pnt2d& theRpl);

			void SetRnl(const Geom_Pnt2d& theRnl);

			void SetVolume(const Standard_Real theVolume);

			void Setd(const Standard_Real thed);

			void SetPhysics(const FvBC_Physics thePhysics);
		};
	}
}

#include <FvEntity_Face2dI.hxx>

#endif // !_FvEntity_Face2d_Header
