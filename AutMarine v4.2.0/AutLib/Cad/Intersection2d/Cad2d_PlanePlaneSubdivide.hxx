#pragma once
#ifndef _Cad2d_PlanePlaneSubdivide_Header
#define _Cad2d_PlanePlaneSubdivide_Header

#include <Global_Memory.hxx>
#include <Standard_Stream.hxx>
#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_Plane;

		class Cad2d_PlanePlaneSubdivide
		{

		private:

			const Global_Handle(Cad2d_Plane) thePlane1_;
			const Global_Handle(Cad2d_Plane) thePlane2_;

			Standard_Boolean IsDone_;
			Standard_Boolean AreSubdivided_;

			Global_Handle(Cad2d_Plane) theSubdivided1_;
			Global_Handle(Cad2d_Plane) theSubdivided2_;

		public:

			Cad2d_PlanePlaneSubdivide();

			Cad2d_PlanePlaneSubdivide(const Global_Handle(Cad2d_Plane) thePlane1, const Global_Handle(Cad2d_Plane) thePlane2);

			~Cad2d_PlanePlaneSubdivide();

			void Init(const Global_Handle(Cad2d_Plane) thePlane1, const Global_Handle(Cad2d_Plane) thePlane2);

			void Perform();

			Global_Handle(Cad2d_Plane) SubDivided1() const;

			Global_Handle(Cad2d_Plane) SubDivided2() const;

			Standard_Boolean IsDone() const;

			Standard_Boolean AreSubdivided() const;

			void ExportToPlt(fstream& File) const;

		private:

			void Clear();
		};
	}
}

#include <Cad2d_PlanePlaneSubdivideI.hxx>

#endif // !_Cad2d_PlanePlaneSubdivide_Header
