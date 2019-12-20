#pragma once
#ifndef _Prop_PropView_Header
#define _Prop_PropView_Header

#include <Prop_BladeFaces.hxx>
#include <TColProp_HAry1dOfExpandedView.hxx>
#include <TColProp_HAry1dOfWrappedSection.hxx>
#include <TColProp_HAry1dOfUnWrappedSection.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_PropView
		{

		private:

			TColProp_HAry1dOfExpandedView theExpanded_;

			TColProp_HAry1dOfWrappedSection theWrapped_;

			TColProp_HAry1dOfUnWrappedSection theUnWrapped_;

			Prop_BladeFaces theSurfaces_;

		public:

			Prop_PropView();

			const TColProp_HAry1dOfExpandedView& ExpandedView() const;

			const TColProp_HAry1dOfWrappedSection& WrappedView() const;

			const TColProp_HAry1dOfUnWrappedSection& UnWrappedView() const;

			const Prop_BladeFaces& Surfaces() const;

			const Global_Handle(Prop_ExpandedView) ExpandedView(const Standard_Integer theIndex) const;

			const Global_Handle(Prop_WrappedSection) WrappedSection(const Standard_Integer theIndex) const;

			const Global_Handle(Prop_UnWrappedSection) UnWrappedSection(const Standard_Integer theIndex) const;

			Prop_BladeFaces& Surfaces();

			void SetExpandedView(const Standard_Integer theIndex, const Global_Handle(Prop_ExpandedView) theExpandedView);

			void SetWrappedSection(const Standard_Integer theIndex, const Global_Handle(Prop_WrappedSection) theWrappedSection);

			void SetUnWrappedSection(const Standard_Integer theIndex, const Global_Handle(Prop_UnWrappedSection) theUnWrappedSection);

			void AllocateMemory(const Standard_Integer theNbSections);
		};
	}
}

#include <Prop_PropViewI.hxx>

#endif // !_Prop_PropView_Header
