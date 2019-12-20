#pragma once
#ifndef _Mesh_SurfaceSizeValues_Header
#define _Mesh_SurfaceSizeValues_Header

#include <Standard_TypeDef.hxx>
#include <Mesh_SizeMethodInfo.hxx>
#include <Mesh_RelativeAbsoluteInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh_SurfaceSizeValues
		{

		private:

			Mesh_SizeMethodInfo theSizeMethod_;

			Mesh_RelativeAbsoluteInfo theRelativeAbsolute_;

			Standard_Real theMinSize_;
			Standard_Real theTargetSize_;

		public:

			Mesh_SurfaceSizeValues();

			Mesh_SizeMethodInfo& SizeMethod();

			Mesh_RelativeAbsoluteInfo& RelativeAbsolute();

			Mesh_SizeMethodInfo SizeMethod() const;

			Mesh_RelativeAbsoluteInfo RelativeAbsolute() const;

			Standard_Real MinSize() const;

			Standard_Real TargetSize() const;

			void SetMinSize(const Standard_Real Value);

			void SetTargetSize(const Standard_Real Value);

			void SetSizeMethod(Mesh_SizeMethodInfo SizeMethod);

			void SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo RelativeAbsolute);
		};
	}
}

#include <Mesh_SurfaceSizeValuesI.hxx>

#endif // !_Mesh_SurfaceSizeValues_Header
