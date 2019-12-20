#pragma once
#ifndef _Mesh_LaplacianSmoothingInfo_Header
#define _Mesh_LaplacianSmoothingInfo_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh_LaplacianSmoothingInfo
		{

		private:

			Standard_Integer theMaxLevels_;

			Standard_Real theUnderRelaxation_;

			Standard_Boolean BeApply_;

		public:

			Mesh_LaplacianSmoothingInfo();

			Standard_Integer MaxLevels() const;

			Standard_Real UnderRelaxation() const;

			Standard_Boolean beApply() const;

			void SetMaxLevels(const Standard_Integer MaxLevels);

			void SetUnderRelaxation(const Standard_Real UnderRelaxation);

			void SetApply(const Standard_Boolean Apply);

		};
	}
}

#endif // !_Mesh_LaplacianSmoothingInfo_Header
