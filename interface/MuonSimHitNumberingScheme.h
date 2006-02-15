#ifndef MuonNumbering_MuonSimHitNumberingScheme_h
#define MuonNumbering_MuonSimHitNumberingScheme_h

/** \class MuonSimHitNumberingScheme
 *
 * wrapper class to handle numbering schemes for the different
 * MuonSubDetector's
 *  
 *  $Date: 2005/10/18 16:54:41 $
 *  $Revision: 1.1 $
 * \author Arno Straessner, CERN <arno.straessner@cern.ch>
 *
 */

#include "Geometry/MuonNumbering/interface/MuonNumberingScheme.h"

class MuonBaseNumber;
class MuonSubDetector;

class MuonSimHitNumberingScheme : public MuonNumberingScheme {

 public:

  MuonSimHitNumberingScheme(MuonSubDetector*);
  ~MuonSimHitNumberingScheme();
  
  virtual int baseNumberToUnitNumber(const MuonBaseNumber);
  
 private:

  MuonSubDetector* theDetector;
  MuonNumberingScheme* theNumbering;
};

#endif
