#pragma once
#ifndef _FvVariables_Header
#define _FvVariables_Header

#include <Global_Macros.hxx>
#include <Standard_TypeDef.hxx>
#include <FvVariables_Faces2d.hxx>
#include <FvVariables_Elements2d.hxx>
#include <FvVariables_ContinuityMatrix.hxx>
#include <FvVariables_MomentumMatrix.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVariables2d
		{

		private:

			mutable FvVariables_Faces2d theUf_;

			mutable FvVariables_Faces2d theXuf_;
			mutable FvVariables_Faces2d theXvf_;
			mutable FvVariables_Faces2d theXpf_;

			mutable FvVariables_Elements2d theXu0_;
			mutable FvVariables_Elements2d theXv0_;
			mutable FvVariables_Elements2d theXp0_;
			mutable FvVariables_Elements2d theXu_;
			mutable FvVariables_Elements2d theXv_;
			mutable FvVariables_Elements2d theXp_;
			mutable FvVariables_Elements2d theXpp_;

			mutable FvVariables_Elements2d theAp_;

			mutable FvVariables_Elements2d theBu_;
			mutable FvVariables_Elements2d theBv_;
			mutable FvVariables_Elements2d theBp_;

			mutable FvVariables_Elements2d theHu_;
			mutable FvVariables_Elements2d theHv_;

			mutable TColGeom_Ary1dOfPnt2d theGradXu_;
			mutable TColGeom_Ary1dOfPnt2d theGradXv_;

			mutable FvVariables_ContinuityMatrix theAc_;
			mutable FvVariables_MomentumMatrix theAm_;

		public:

			FvVariables2d();

			const FvVariables_Faces2d& Uf() const;

			const FvVariables_Faces2d& Xuf() const;

			const FvVariables_Faces2d& Xvf() const;

			const FvVariables_Faces2d& Xpf() const;

			const FvVariables_Elements2d& Xu0() const;

			const FvVariables_Elements2d& Xv0() const;

			const FvVariables_Elements2d& Xp0() const;

			const FvVariables_Elements2d& Xu() const;

			const FvVariables_Elements2d& Xv() const;

			const FvVariables_Elements2d& Xp() const;

			const FvVariables_Elements2d& Ap() const;

			const FvVariables_Elements2d& Xpp() const;

			const FvVariables_Elements2d& Bu() const;

			const FvVariables_Elements2d& Bv() const;

			const FvVariables_Elements2d& Bp() const;

			const FvVariables_Elements2d& Hu() const;

			const FvVariables_Elements2d& Hv() const;

			const TColGeom_Ary1dOfPnt2d& GradXu() const;

			const TColGeom_Ary1dOfPnt2d& GradXv() const;

			Standard_Real Uf(const Standard_Integer theIndex) const;

			Standard_Real Xuf(const Standard_Integer theIndex) const;

			Standard_Real Xvf(const Standard_Integer theIndex) const;

			Standard_Real Xpf(const Standard_Integer theIndex) const;

			Standard_Real Xu0(const Standard_Integer theIndex) const;

			Standard_Real Xv0(const Standard_Integer theIndex) const;

			Standard_Real Xp0(const Standard_Integer theIndex) const;

			Standard_Real Xu(const Standard_Integer theIndex) const;

			Standard_Real Xv(const Standard_Integer theIndex) const;

			Standard_Real Xp(const Standard_Integer theIndex) const;

			Standard_Real Ap(const Standard_Integer theIndex) const;

			Standard_Real Xpp(const Standard_Integer theIndex) const;

			Standard_Real Bu(const Standard_Integer theIndex) const;

			Standard_Real Bv(const Standard_Integer theIndex) const;

			Standard_Real Bp(const Standard_Integer theIndex) const;

			Standard_Real Hu(const Standard_Integer theIndex) const;

			Standard_Real Hv(const Standard_Integer theIndex) const;

			const Geom_Pnt2d& GradXu(const Standard_Integer theIndex) const;

			const Geom_Pnt2d& GradXv(const Standard_Integer theIndex) const;

			void SetUf(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXuf(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXvf(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXpf(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXu0(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXv0(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXp0(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXu(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXv(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXp(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetAp(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetXpp(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetBu(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetBv(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetBp(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetHu(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetHv(const Standard_Integer theIndex, const Standard_Real theValue) const;

			void SetGradXu(const Standard_Integer theIndex, const Geom_Pnt2d& theValue) const;

			void SetGradXv(const Standard_Integer theIndex, const Geom_Pnt2d& theValue) const;

			void SetAmLength(const Standard_Integer theIndex0, const Standard_Integer theLength) const;

			void SetAm(const Standard_Integer theIndex0, const Standard_Integer theIndex1, const Standard_Integer theNb, const Standard_Real theValue) const;

			void AllocateMemory(const Standard_Integer theNbElements, const Standard_Integer theNbFaces);
		};
	}
}

#include <FvVariables2dI.hxx>

#endif // !_FvVariables_Header
