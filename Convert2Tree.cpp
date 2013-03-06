#include <iostream>
#include <fstream>
#include <vector>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

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
	bool firstEvent = true;

	while(true)
	{
		infile >> pid >> eid >> bx >> by >> charge >> px >> py >> pz >> dedx >> dedx_vtpc1 >> dedx_vtpc2 >> dedx_mtpc >> ndedx >> ndedx_vtpc1 >> ndedx_vtpc2 >> ndedx_mtpc;

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

		particletree.AddParticle(charge, bx, by, px, py, pz, dedx, dedx_vtpc1, dedx_vtpc2, dedx_mtpc, ndedx, ndedx_vtpc1, ndedx_vtpc2, ndedx_mtpc);

		//cout << particletree.Check() << endl;

		//cout << "Event: " << event << " eid:" << eid << " pid: " << pid << " " << charge << " " << px << " " << py << endl;
	}

	particletree.Close();
}
