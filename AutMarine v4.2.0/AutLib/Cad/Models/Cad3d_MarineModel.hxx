#pragma once
#ifndef _Cad3d_MarineModel_Header
#define _Cad3d_MarineModel_Header

#include <gp_Ax2.hxx>
#include <gp_Trsf.hxx>
#include <Standard_String.hxx>
#include <Standard_Stream.hxx>
#include <Global_Memory.hxx>
#include <Entity_Box3d.hxx>
#include <TopoDS_Shape.hxx>

//#include <TColCad3d_HBasicQueueOfDatum.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_Solid;

		class Cad3d_MarineModel
		{

		protected:

			gp_Ax2 theSystem_;

			TopoDS_Shape myModel_;

			Standard_String theName_;
			Standard_String theIgesFileName_;

			Standard_Boolean toDiscrete_;
			Standard_Boolean toSolid_;
			Standard_Boolean IsDone_;

			M_GEO Entity_Box3d theBox_;

			//TColCad3d_HBasicQueueOfDatum theDatum_;

		public:

			virtual ~Cad3d_MarineModel();

			//! This a virtual method and not supposed to be called!
			virtual void Make();

			Standard_Boolean IsDone() const;

			Standard_Real CalcVolume() const;

			//! Warning: This object is not removed automatically!
			Global_Handle(Cad3d_Solid) GetSolid(const Standard_Real Deflection = 0.05, const Standard_Real Angle = 0.1) const;

			const M_GEO Entity_Box3d& BoundingBox() const;

			const gp_Ax2& CoordinateSystem() const;

			const TopoDS_Shape& Shape() const;

			const Standard_String& Name() const;

			const Standard_String& IGESFileName()const;

			void SetName(const Standard_String theName);

			void SetIGESFileName(const Standard_String theName);

			void SetToDiscreteMyModel();

			void SetToMakeAsSolid();

			void DiscreteMyModel(const Standard_Real Deflection = 0.05, const Standard_Real Angle = 0.1);

			void TransformTo(const gp_Ax2& theSystem);

			void Scale(const Standard_Real theValue);

			void ExportToIGES() const;

			void ExportMyModelToPlt(fstream& File) const;

			void ExportCurvesOfMyModelToPlt(fstream& File) const;

		protected:

			Cad3d_MarineModel();

			void CalcBoundingBox();

			void FixNullCurves();

		};
	}
}

#include <Cad3d_MarineModelI.hxx>

#endif // !_Cad3d_MarineModel_Header
