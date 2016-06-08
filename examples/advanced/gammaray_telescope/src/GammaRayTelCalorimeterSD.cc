//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: GammaRayTelCalorimeterSD.cc,v 1.4 2001/11/29 11:19:18 griccard Exp $
// GEANT4 tag $Name: geant4-05-00 $
// ------------------------------------------------------------
//      GEANT 4 class implementation file
//      CERN Geneva Switzerland
//
//
//      ------------ GammaRayTelCalorimeterSD  ------
//           by  R.Giannitrapani, F.Longo & G.Santin (13 nov 2000)
//
// ************************************************************
#include "G4RunManager.hh"
#include "GammaRayTelCalorimeterSD.hh"
#include "GammaRayTelCalorimeterHit.hh"
#include "GammaRayTelDetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GammaRayTelCalorimeterSD::GammaRayTelCalorimeterSD(G4String name):G4VSensitiveDetector(name)
{
 G4RunManager* runManager = G4RunManager::GetRunManager();
  Detector =
    (GammaRayTelDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
  NbOfCALBars  = Detector->GetNbOfCALBars();
  NbOfCALLayers  = Detector->GetNbOfCALLayers();

  //G4cout <<  NbOfCALBars << " bars " << G4endl;
  //G4cout <<  NbOfCALLayers << " layers " << G4endl;
  
  NbOfCALChannels = NbOfCALBars*NbOfCALLayers;
  
  ChitXID = new G4int[NbOfCALChannels];
  ChitYID = new G4int[NbOfCALChannels];
  collectionName.insert("CalorimeterCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GammaRayTelCalorimeterSD::~GammaRayTelCalorimeterSD()
{
  delete [] ChitXID;
  delete [] ChitYID;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelCalorimeterSD::Initialize(G4HCofThisEvent*HCE)
{
  CalorimeterCollection = new GammaRayTelCalorimeterHitsCollection
    (SensitiveDetectorName,collectionName[0]);
  for (G4int i=0;i<NbOfCALChannels;i++)
      {
	ChitXID[i] = -1;
	ChitYID[i] = -1;
      };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool GammaRayTelCalorimeterSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist)
{ 
  
  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      
  
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* cal_bar = theTouchable->GetVolume();  
  G4VPhysicalVolume* cal_plane = cal_bar->GetMother();

  G4int CALBarNumber=cal_bar->GetCopyNo();
  G4String CALBarName = cal_bar->GetName();
  
  G4int PlaneNumber = 0;
  PlaneNumber=cal_plane->GetCopyNo();
  G4String PlaneName = cal_plane->GetName();


  G4int NChannel = 0;
  
  NChannel = PlaneNumber * NbOfCALBars + CALBarNumber; 
  
  if (PlaneName == "CALLayerX" )
    
    // The hit is on an X CsI plane
    
    {
      // This is a new hit
      if (ChitXID[NChannel]==-1)
	{       
	  GammaRayTelCalorimeterHit* CalorimeterHit = new GammaRayTelCalorimeterHit;
	  CalorimeterHit->SetCALType(1);
	  CalorimeterHit->AddEnergy(edep);
	  CalorimeterHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  CalorimeterHit->SetCALPlaneNumber(PlaneNumber);
	  CalorimeterHit->SetCALBarNumber(CALBarNumber);
	  ChitXID[NChannel] = 
	    CalorimeterCollection->insert(CalorimeterHit) -1;
	}
      else // This is not new
	{
	  (*CalorimeterCollection)
	    [ChitXID[NChannel]]->AddEnergy(edep);
	}
    }
 
  if (PlaneName == "CALLayerY")
    // The hit is on an Y CsI plane    
    {   
      // This is a new hit
      if (ChitYID[NChannel]==-1)
	{       
	  GammaRayTelCalorimeterHit* CalorimeterHit 
	    = new GammaRayTelCalorimeterHit;
	  CalorimeterHit->SetCALType(0);
	  CalorimeterHit->AddEnergy(edep);
	  CalorimeterHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  CalorimeterHit->SetCALPlaneNumber(PlaneNumber);
	  CalorimeterHit->SetCALBarNumber(CALBarNumber);
	  ChitYID[NChannel] = 
	    CalorimeterCollection->insert(CalorimeterHit)-1;
	}
      else // This is not new
	{
	  (*CalorimeterCollection)
	    [ChitYID[NChannel]]->AddEnergy(edep);
	}
    }
  
  return true;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void GammaRayTelCalorimeterSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  static G4int HCID = -1;
  if(HCID<0)
    { 
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
  HCE->AddHitsCollection(HCID,CalorimeterCollection);


  for (G4int i=0;i<NbOfCALChannels;i++) 
    {
      ChitXID[i] = -1;
      ChitYID[i] = -1;
    };
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelCalorimeterSD::clear()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelCalorimeterSD::DrawAll()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelCalorimeterSD::PrintAll()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....













