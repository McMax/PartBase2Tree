#include <iostream>
#include <fstream>
#include <vector>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "ParticleTree.h"

using namespace std;

#define NEVENTS 100000000

int main()
{
	ifstream infile("ParticlesBase.txt");

	ParticleTree particletree("ParticleTree_40MC.root");
	
	cout << "Converting" << endl;

	int event = 0;
	unsigned pid, eid = 0, old_eid = 0;
	short charge;
	float bx, by, px, py, pz;
	bool firstEvent = true;

	while(true)
	{
		infile >> pid >> eid >> bx >> by >> charge >> px >> py >> pz;

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
			else if(!(event%10000))
				cout << "Event " << event << endl;

			particletree.BeginEvent();
			old_eid = eid;
		}

		particletree.AddParticle(charge, bx, by, px, py, pz);

		//cout << particletree.Check() << endl;

		//cout << "Event: " << event << " eid:" << eid << " pid: " << pid << " " << charge << " " << px << " " << py << endl;
	}

	particletree.Close();
}
