#pragma once
#ifndef _Merge_Chain2d_Header
#define _Merge_Chain2d_Header

#include <TColEntity_HAry1dOfStaticChain2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Chain2d
		{

		private:

			Global_Handle(Entity_StaticChain2d) theChain_;

			Standard_Real theResolution_;
			Standard_Real theRadius_;

			Standard_Boolean IsDone_;
			Standard_Boolean HandleDegeneray_;

		public:

			Merge_Chain2d(Standard_Real Resolution = 1.0E-3, Standard_Real Radius = 1.0E-6);

			~Merge_Chain2d() { ReleaseMemory(); }

			Global_Handle(Entity_StaticChain2d) Merged() const;

			Standard_Boolean IsDone() const;

			void SetDegeneracy(const Standard_Boolean Degeneracy);

			void Import(const TColEntity_HAry1dOfStaticChain2d& Chains);

			void Import(const Entity_StaticChain2d& Chain);

			void Perform();

			void ReleaseMemory();
		};
	}
}

#endif // !_Merge_Chain2d_Header
