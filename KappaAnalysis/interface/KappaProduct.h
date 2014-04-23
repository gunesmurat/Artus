
#pragma once

#include "Kappa/DataFormats/interface/Kappa.h"

#include "KappaTools/RootTools/HLTTools.h"

/**
   \brief Container class for everything that can be produced in pipeline.

   Defines any outcome that could be produced by a KappaProducer during a common analysis chain in a 
   given KappaPipeline. Via the PipelineRunner the KappaProduct all extra products in the analysis 
   chain will be passed on to subsequent Producers, Filters and Consumers.
*/

class KappaProduct {
public:
	KappaProduct() {};
	~KappaProduct() {};

	/// added by GenTauDecayProducer
	// can store an arbitrary decay tree
	struct MotherDaughterBundle {
		MotherDaughterBundle( KGenParticle* newnode ) : node( newnode )
		{}

		// must be != null;
		KGenParticle* node;
		// will have 0 entries, if there are no daughters
		std::vector<MotherDaughterBundle> Daughters;
	};

	std::vector<MotherDaughterBundle> m_genBoson;

	/// added by ValidElectronsProducer
	std::vector<KDataElectron*> m_validElectrons;
	std::vector<KDataElectron*> m_invalidElectrons;

	/// added by ValidMuonsProducer
	std::vector<KDataMuon*> m_validMuons;
	std::vector<KDataMuon*> m_invalidMuons;

	/// added by ValidTausProducer
	std::vector<KDataPFTau*> m_validTaus;
	std::vector<KDataPFTau*> m_invalidTaus;

	/// added by ValidJetsProducer
	std::vector<KDataPFJet*> m_validJets;
	std::vector<KDataPFJet*> m_invalidJets;
	
	HLTTools* m_hltInfo = new HLTTools();
	std::string selectedHltName = "";

private:
	
};
