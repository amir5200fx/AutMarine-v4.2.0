#pragma once
#ifndef _Merge_Chain3d_Header
#define _Merge_Chain3d_Header

#include <TColEntity_HAry1dOfStaticChain3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Chain3d
		{

		private:

			Global_Handle(Entity_StaticChain3d) theChain_;

			Standard_Real theResolution_;
			Standard_Real theRadius_;

			Standard_Boolean IsDone_;
			Standard_Boolean HandleDegeneray_;

		public:

			Merge_Chain3d(Standard_Real Resolution = 1.0E-3, Standard_Real Radius = 1.0E-6);

			~Merge_Chain3d() { ReleaseMemory(); }

			Global_Handle(Entity_StaticChain3d) Merged() const;

			Standard_Boolean IsDone() const;

			void Import(const TColEntity_HAry1dOfStaticChain3d& Chains);

			void Import(const Entity_StaticChain3d& Chain);

			void SetDegeneracy(const Standard_Boolean HandleDegeneray);

			void Perform();

			void ReleaseMemory();
		};
	}
}

#endif // !_Merge_Chain3d_Header
