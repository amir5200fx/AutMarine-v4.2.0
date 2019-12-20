#pragma once
#ifndef _Primitive_Field_Header
#define _Primitive_Field_Header

#include <TColStd_Ary1dOfAry1dOfReal.hxx>
#include <Standard_String.hxx>

namespace AutLib
{

	class Primitive_Field
	{

	private:

		Standard_Integer theNbVariables_;
		Standard_Integer theNbPoints_;

		Standard_String theVariablesName_;

		TColStd_Ary1dOfAry1dOfReal theField_;

	public:

		Primitive_Field();

		Primitive_Field(const Standard_Integer NbVariables, const Standard_Integer NbPoints);

		Primitive_Field(const TColStd_Ary1dOfAry1dOfReal& Field);

		Standard_Integer NbPoints() const;

		Standard_Integer NbVariables() const;

		const Standard_String& VariablesName() const;

		const TColStd_Ary1dOfReal& Variables(const Standard_Integer Point) const;

		const TColStd_Ary1dOfAry1dOfReal& Field() const;

		void SetValue(const Standard_Integer Point, const Standard_Integer Variable, const Standard_Real value);

		void SetVariablesName(const Standard_String& Name);
	};
}

#include <Primitive_FieldI.hxx>

#endif // !_Primitive_Field_Header
