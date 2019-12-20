#include <Tetrahedra_QualityMeasureParameters.hxx>

AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::Tetrahedra_QualityMeasureParameters()
{
}

AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::Tetrahedra_QualityMeasureParameters
(
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1,
	const Geom_Pnt3d & theP2,
	const Geom_Pnt3d & theP3
)
{
	Perform(theP0, theP1, theP2, theP3);
}

void AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::Init
(
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1,
	const Geom_Pnt3d & theP2,
	const Geom_Pnt3d & theP3
)
{
	Perform(theP0, theP1, theP2, theP3);
}

void AutLib::GeoLib::Tetrahedra_QualityMeasureParameters::Perform
(
	const Geom_Pnt3d& a, 
	const Geom_Pnt3d& b,
	const Geom_Pnt3d& c,
	const Geom_Pnt3d& d
)
{
	t_ = a - d;
	u_ = b - d;
	v_ = c - d;

	lad_ = t_.TwoNormSQ();
	lbd_ = u_.TwoNormSQ();
	lcd_ = v_.TwoNormSQ();

	lab_ = (a - b).TwoNormSQ();
	lbc_ = (b - c).TwoNormSQ();
	lac_ = (c - a).TwoNormSQ();

	//lrms_ = sqrt((lad_*lad_ + lbd_*lbd_ + lcd_*lcd_ + lab_*lab_ + lbc_*lbc_ + lac_*lac_) / 6.0);

	Na_ = CrossProduct(u_, v_);
	Nb_ = CrossProduct(v_, t_);
	Nc_ = CrossProduct(t_, u_);
	Nd_ = CrossProduct(u_ - v_, t_ - v_);

	Aa_ = Na_.TwoNormSQ();
	Ab_ = Nb_.TwoNormSQ();
	Ac_ = Nc_.TwoNormSQ();
	Ad_ = Nd_.TwoNormSQ();

	V_ = DotProduct(t_, CrossProduct(u_, v_));

	//Z_ = ABS((t_.TwoNormSQ()*CrossProduct(u_, v_) + u_.TwoNormSQ()*CrossProduct(v_, t_) + v_.TwoNormSQ()*CrossProduct(t_, u_)).TwoNorm());
}