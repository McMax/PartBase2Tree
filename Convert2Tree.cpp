#include <iostream>
#include <fstream>
#include <vector>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "Particle.h"
#include "ParticleTree.h"

using namespace std;

#define NEVENTS 100000000

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		cout << "USAGE: converter <inputfile> <outputfile>" << endl;
		return 0;
 	}

	ifstream infile(argv[1]);

	ParticleTree particletree(argv[2]);
	
	cout << "Converting" << endl;

	int event = 0;
	unsigned pid, eid = 0, old_eid = 0;
	short charge;
	float bx, by, px, py, pz, dedx, dedx_vtpc1, dedx_vtpc2, dedx_mtpc;
	int ndedx, ndedx_vtpc1, ndedx_vtpc2, ndedx_mtpc;
	float vtpc1sx, vtpc1sy, vtpc1ex, vtpc1ey, vtpc2sx, vtpc2sy, vtpc2ex, vtpc2ey, mtpcsx, mtpcsy, mtpcex, mtpcey;
	bool firstEvent = true;

	Particle particle;

	while(true)
	{
		particle.Clear();

		infile >> pid >> eid >> 
			bx >> by >> charge >> 
			px >> py >> pz >> 
			dedx >> dedx_vtpc1 >> dedx_vtpc2 >> dedx_mtpc >> 
			ndedx >> ndedx_vtpc1 >> ndedx_vtpc2 >> ndedx_mtpc >>
			vtpc1sx >> vtpc1sy >> vtpc1ex >> vtpc1ey >> 
			vtpc2sx >> vtpc2sy >> vtpc2ex >> vtpc2ey >> 
			mtpcsx >> mtpcsy >> mtpcex >> mtpcey;

		if(firstEvent)
		{
			particletree.BeginEvent();
			old_eid = eid;
			++event;
			firstEvent = false;
		}

		if(infile.eof())
		{
			particletree.EndEvent();
			break;
		}
		if(old_eid != eid)
		{
			particletree.EndEvent();
			//cout << "New event: " << eid << endl;

			if(++event >= NEVENTS)
				break;
			else if(!(event%500))
				cout << "Event " << event << endl;

			particletree.BeginEvent();
			old_eid = eid;
		}

		particle.SetPid(pid);
		particle.SetCharge(charge);
		particle.SetBpar(bx, by);
		particle.SetP(px, py, pz);
		particle.Setdedx(dedx, dedx_vtpc1, dedx_vtpc2, dedx_mtpc);
		particle.SetNdedx(ndedx, ndedx_vtpc1, ndedx_vtpc2, ndedx_mtpc);
		particle.SetVTPC1points(vtpc1sx, vtpc1sy, vtpc1ex, vtpc1ey);
		particle.SetVTPC2points(vtpc2sx, vtpc2sy, vtpc2ex, vtpc2ey);
		particle.SetMTPCpoints(mtpcsx, mtpcsy, mtpcex, mtpcey);

		particletree.AddParticle(particle);
		
		//cout << particletree.Check() << endl;

		//cout << "Event: " << event << " eid:" << eid << " pid: " << pid << " " << charge << " " << px << " " << py << endl;
	}

	particletree.Close();
}
