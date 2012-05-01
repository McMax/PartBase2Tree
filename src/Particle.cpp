#include "TObject.h"
#include "Particle.h"

Particle::Particle()
{
	fPid = 0;
	fCharge = 0;
	fBx = fBy = fPx = fPy = fPz = 0.;
}

Particle::Particle(UInt_t pid, Short_t charge, 
			Float_t bx, Float_t by,
			Float_t px, Float_t py, Float_t pz)
{
	fPid = pid;
	fCharge = charge;
	fBx = bx;
	fBy = by;
	fPx = px;
	fPy = py;
	fPz = pz;
}

Particle::~Particle()
{

}

ClassImp(Particle);