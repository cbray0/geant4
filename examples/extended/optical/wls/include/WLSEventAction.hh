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
//
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef WLSEventAction_h
#define WLSEventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"

class WLSRunAction;
class WLSEventActionMessenger;

class WLSEventAction : public G4UserEventAction
{
  public:

    WLSEventAction(WLSRunAction*);
    ~WLSEventAction();

  public:

    void   BeginOfEventAction(const G4Event*);
    void     EndOfEventAction(const G4Event*);

    G4int GetEventNo();
    void SetEventVerbose(G4int);

    void SetDrawFlag(G4String val)  { drawFlag = val; };
    void SetPrintModulo(G4int val)  { printModulo = val; };

    void SetForceDrawPhotons(G4bool b){forcedrawphotons=b;}
    void SetForceDrawNoPhotons(G4bool b){forcenophotons=b;}
 
  private:

    WLSRunAction* runaction;
    WLSEventActionMessenger* eventMessenger;

    G4int verboselevel;
    G4int printModulo;
 
    G4int mppcCollID;
 
    G4String drawFlag;

    G4bool forcedrawphotons;
    G4bool forcenophotons;

};

#endif