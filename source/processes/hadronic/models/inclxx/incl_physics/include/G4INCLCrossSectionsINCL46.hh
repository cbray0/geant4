//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// INCL++ intra-nuclear cascade model
// Alain Boudard, CEA-Saclay, France
// Joseph Cugnon, University of Liege, Belgium
// Jean-Christophe David, CEA-Saclay, France
// Pekka Kaitaniemi, CEA-Saclay, France, and Helsinki Institute of Physics, Finland
// Sylvie Leray, CEA-Saclay, France
// Davide Mancusi, CEA-Saclay, France
//
#define INCLXX_IN_GEANT4_MODE 1

#include "globals.hh"

/** \file G4INCLCrossSectionsINCL46.hh
 * \brief Cross sections used in INCL4.6
 *
 * \date 25nd October 2013
 * \author Davide Mancusi
 */

#ifndef G4INCLCROSSSECTIONSINCL46_HH
#define G4INCLCROSSSECTIONSINCL46_HH

#include "G4INCLICrossSections.hh"

namespace G4INCL {
  /// \brief Cross sections used in INCL4.6

  class CrossSectionsINCL46 : public ICrossSections{
    public:

      /// \brief Elastic particle-particle cross section
      virtual G4double elastic(Particle const * const p1, Particle const * const p2);

      /// \brief Total (elastic+inelastic) particle-particle cross section
      virtual G4double total(Particle const * const p1, Particle const * const p2);

      /// \brief Cross section for NDelta->NN
      virtual G4double NDeltaToNN(Particle const * const p1, Particle const * const p2);

      /// \brief Cross section for NN->NDelta
      virtual G4double NNToNDelta(Particle const * const p1, Particle const * const p2);

      /// \brief Cross section for piN->NDelta
      virtual G4double piNToDelta(Particle const * const p1, Particle const * const p2);

      /// \brief Cross section for X pion production - NN Channel
      virtual G4double NNToxPiNN(const G4int xpi, Particle const * const p1, Particle const * const p2);

      /// \brief Cross section for X pion production - piN Channel
      virtual G4double piNToxPiN(const G4int xpi, Particle const * const p1, Particle const * const p2);

      /** \brief Calculate the slope of the NN DDXS.
       *
       * \param energyCM energy in the CM frame, in MeV
       * \param iso total isospin of the system
       *
       * \return the slope of the angular distribution
       */
      virtual G4double calculateNNAngularSlope(G4double energyCM, G4int iso);

    protected:

      /// \brief Internal implementation of the elastic cross section
      G4double elasticNNLegacy(Particle const * const part1, Particle const * const part2);

      /// \brief Internal function for the delta-production cross section
      G4double deltaProduction(const G4int isospin, const G4double pLab);

      G4double spnPiPlusPHE(const G4double x);
      G4double spnPiMinusPHE(const G4double x);

  };
}

#endif
