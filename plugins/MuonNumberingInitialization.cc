// -*- C++ -*-
//
// Package:    MuonNumberingInitialization
// Class:      MuonNumberingInitialization
// 
/**\class MuonNumberingInitialization MuonNumberingInitialization.h Geometry/MuonNumberingInitialization/interface/MuonNumberingInitialization.h

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michael Case
//         Created:  Thu Sep 28 16:40:29 PDT 2006
// $Id: MuonNumberingInitialization.cc,v 1.5 2013/01/25 15:20:00 dlange Exp $
//
//


// system include files
#include <memory>
#include <boost/shared_ptr.hpp>

// user include files
#include <FWCore/Framework/interface/ModuleFactory.h>
#include <FWCore/Framework/interface/ESProducer.h>
#include <FWCore/Framework/interface/ESTransientHandle.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h>

#include <DetectorDescription/Core/interface/DDFilter.h>
#include <DetectorDescription/Core/interface/DDFilteredView.h>
#include <DetectorDescription/Core/interface/DDsvalues.h>
#include <Geometry/MuonNumbering/interface/MuonDDDConstants.h>
#include <Geometry/Records/interface/MuonNumberingRecord.h>

using namespace edm;

class MuonNumberingInitialization : public edm::ESProducer {
   public:
      MuonNumberingInitialization(const edm::ParameterSet&);
      ~MuonNumberingInitialization();

      typedef std::auto_ptr<MuonDDDConstants> ReturnType;

      ReturnType produce(const MuonNumberingRecord&);

      void initializeMuonDDDConstants( const IdealGeometryRecord& igr);

   private:
      std::string label_;
      MuonDDDConstants* muonDDDConst_;
};

MuonNumberingInitialization::MuonNumberingInitialization(const edm::ParameterSet& iConfig) : muonDDDConst_(0)
{
  setWhatProduced(this, dependsOn(&MuonNumberingInitialization::initializeMuonDDDConstants));
}


MuonNumberingInitialization::~MuonNumberingInitialization()
{  }


// ------------ method called to produce the data  ------------
MuonNumberingInitialization::ReturnType
MuonNumberingInitialization::produce(const MuonNumberingRecord& iRecord)
{
   LogDebug( "MuonNumbering" ) 
       << "in MuonNumberingInitialization::produce";

   using namespace edm::es;
   if ( muonDDDConst_ == 0 ) {
     LogError( "MuonNumbering" ) << "MuonNumberingInitialization::produceMuonDDDConstants has NOT been initialized!";
     throw;
   }
   return std::auto_ptr<MuonDDDConstants> (muonDDDConst_) ;
}

void MuonNumberingInitialization::initializeMuonDDDConstants( const IdealGeometryRecord& igr ) {

   edm::ESTransientHandle<DDCompactView> pDD;
   igr.get(label_, pDD );

   LogDebug( "MuonNumbering" ) << "in MuonNumberingInitialization::initializeMuonDDDConstants";

   if ( muonDDDConst_ != 0 ) {
     delete muonDDDConst_;
   }

   LogDebug( "MuonNumbering" ) << "about to make my new muonDDDConst_" << std::endl;

   muonDDDConst_ = new MuonDDDConstants( *pDD );
}

//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(MuonNumberingInitialization);
