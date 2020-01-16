////////////////////////////////////////////////////////////////////////
/// \file  EvtTimeShiftI.cxx
/// \brief interface for event time distribution
///
/// \version $Id: EvtTimeShiftI.cxx,v 1.1 2015/06/30 18:01:24 rhatcher Exp $
/// \author  Robert Hatcher <rhatcher \at fnal.gov>
///          Fermi National Accelerator Laboratory
///
/// \update  2015-06-22 initial version
////////////////////////////////////////////////////////////////////////

#include "EvtTimeShiftI.h"
#include "TRandom3.h"

//GENIE includes
#ifdef GENIE_PRE_R3
  #include "GENIE/Utils/StringUtils.h"
#else
  #include "GENIE/Framework/Utils/StringUtils.h"
#endif
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "cetlib_except/exception.h"
#include <iomanip>

namespace evgb {

  EvtTimeShiftI::EvtTimeShiftI(const std::string& config)
    : fRndmGen(new TRandom3), fIsOwned(true), fIsSeeded(false)
  {
    // user should call Config(config) in their constructor
    // but setting the random seed should be common

    // not the most sophisticated of parsing ... but FHICL would be overkill
    std::vector<std::string> strs = GetConfigTokens(config);
    size_t nstrs = strs.size();
    for (size_t i=0; i<nstrs; ++i) {
      if      ( strs[i] == "seed"     ) {
        if ( i+1 >= nstrs ) {
          mf::LogError("EvtTime")
            << "EvtTimeShiftI sorry too few values for '" << strs[i] << "'";
          continue;
        }
        const char* arg = strs[i+1].c_str();
        UInt_t seed = atoi(arg);
        mf::LogInfo("EvtTime")
          << "EvtTimeShiftI set seed to " << seed;
        fRndmGen->SetSeed(seed);
        fIsSeeded = true;
        ++i; // used up an argument
      }
    }

  }

  EvtTimeShiftI::~EvtTimeShiftI()
  {
    if (fIsOwned) delete fRndmGen;
    fRndmGen = 0;
  }
  void EvtTimeShiftI::SetRandomGenerator(TRandom* gen, bool isOwned)
  {
    // deal with what we might already have
    if ( fIsOwned ) { delete fRndmGen; fRndmGen = 0; fIsOwned = false; }

    fRndmGen = gen;
    fIsOwned = isOwned;
  }

  std::vector<std::string> EvtTimeShiftI::GetConfigTokens(const std::string& config)
  {

    std::vector<std::string> strs;
    if ( config == "" ) return strs;

    std::string configLocal = config;

    // blindly reduced UPPER -> lower case above to make this easier
    // convert string to lowercase
    std::transform(configLocal.begin(),configLocal.end(),
                   configLocal.begin(),::tolower);

    // for now make use of GENIE utilities
    strs = genie::utils::str::Split(configLocal,"\t\n ,;=(){}[]");

    // weed out blank ones
    strs.erase(std::remove_if(strs.begin(), strs.end(),
                              [](const std::string& x) {
                                return ( x == "") ; // put your condition here
                              }), strs.end());

    // debugging info
    std::ostringstream msgx;
    msgx << "Config elements:" << std::endl;
    for (size_t j=0; j<strs.size(); ++j) {
      msgx << " [" << std::setw(3) << j << "] -->" << strs[j] << "<--\n";
    }
    // this should end up as LogDebug
    mf::LogDebug("EvtTime") << msgx.str() << std::flush;

    return strs;
  }

} // namespace evgb
