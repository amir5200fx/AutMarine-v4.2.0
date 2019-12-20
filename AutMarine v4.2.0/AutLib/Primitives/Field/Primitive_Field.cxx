#include <Primitive_Field.hxx>

AutLib::Primitive_Field::Primitive_Field()
{
}

AutLib::Primitive_Field::Primitive_Field
(
	const Standard_Integer NbVariables, 
	const Standard_Integer NbPoints
)
	: theNbVariables_(NbVariables)
	, theNbPoints_(NbPoints)
{
	theField_.Resize(theNbPoints_);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(theField_)
	)
	{
		theField_[Index].Resize(theNbVariables_);
	}
}

AutLib::Primitive_Field::Primitive_Field(const TColStd_Ary1dOfAry1dOfReal & Field)
	: theNbPoints_(Field.Size())
{
	if (NOT theNbPoints_)
	{
		theNbVariables_ = 0;
	}
	else
	{
		theNbVariables_ = Field[0].Size();

		theField_ = Field;
	}
}