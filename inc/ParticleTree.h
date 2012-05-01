#ifndef PARTICLETREE_H
#define PARTICLETREE_H

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"

#include "Particle.h"
#include "Event.h"

class ParticleTree
{
	TFile *file;
	TTree *tree;
	Particle *particle;
	Event *event;
	UInt_t part_id;
	UInt_t ev_id;

public:
	ParticleTree(TString filename);
	void BeginEvent();
	void EndEvent();
	UInt_t Check();
	void AddParticle(Short_t, Float_t, Float_t, Float_t, Float_t, Float_t);
	void Close();
	virtual ~ParticleTree();
};

#endif