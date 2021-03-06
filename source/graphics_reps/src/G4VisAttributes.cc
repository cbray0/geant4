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
// $Id: G4VisAttributes.cc 102310 2017-01-20 15:27:13Z gcosmo $
//
// 
// John Allison  23rd October 1996

#include "G4VisAttributes.hh"

#include "G4AttValue.hh"
#include "G4AttDef.hh"

G4VisAttributes::G4VisAttributes (const G4VisAttributes& va):
fVisible             (va.fVisible),
fDaughtersInvisible  (va.fDaughtersInvisible),
fColour              (va.fColour),
fLineStyle           (va.fLineStyle),
fLineWidth           (va.fLineWidth),
fForceDrawingStyle   (va.fForceDrawingStyle),
fForcedStyle         (va.fForcedStyle),
fForceAuxEdgeVisible (va.fForceAuxEdgeVisible),
fForcedLineSegmentsPerCircle (va.fForcedLineSegmentsPerCircle),
fStartTime           (va.fStartTime),
fEndTime             (va.fEndTime),
// AttValues are created afresh for each object (using the
// CreateAttValues message), but deletion is the responsibility of
// the creator.  So just copy pointer.
fAttValues           (va.fAttValues),
// AttDefs, if any, belong to the object from which they were obtained
// (with a GetAttDefs message), so just copy pointer.
fAttDefs             (va.fAttDefs)
{}

G4VisAttributes::G4VisAttributes ():
fVisible             (true),
fDaughtersInvisible  (false),
fColour              (G4Colour ()),
fLineStyle           (unbroken),
fLineWidth           (1.),
fForceDrawingStyle   (false),
fForcedStyle         (wireframe),
fForceAuxEdgeVisible (false),
fForcedLineSegmentsPerCircle (0),  // <=0 means not forced.
fStartTime           (-DBL_MAX),
fEndTime             (DBL_MAX),
fAttValues           (0),
fAttDefs             (0)
{}

G4VisAttributes::G4VisAttributes (G4bool visibility):
fVisible             (visibility),
fDaughtersInvisible  (false),
fColour              (G4Colour ()),
fLineStyle           (unbroken),
fLineWidth           (1.),
fForceDrawingStyle   (false),
fForcedStyle         (wireframe),
fForceAuxEdgeVisible (false),
fForcedLineSegmentsPerCircle (0),  // <=0 means not forced.
fStartTime           (-DBL_MAX),
fEndTime             (DBL_MAX),
fAttValues           (0),
fAttDefs             (0)
{}

G4VisAttributes::G4VisAttributes (const G4Colour& colour):
fVisible             (true),
fDaughtersInvisible  (false),
fColour              (colour),
fLineStyle           (unbroken),
fLineWidth           (1.),
fForceDrawingStyle   (false),
fForcedStyle         (wireframe),
fForceAuxEdgeVisible (false),
fForcedLineSegmentsPerCircle (0),  // <=0 means not forced.
fStartTime           (-DBL_MAX),
fEndTime             (DBL_MAX),
fAttValues           (0),
fAttDefs             (0)
{}

G4VisAttributes::G4VisAttributes (G4bool visibility,
                                  const G4Colour& colour):
fVisible             (visibility),
fDaughtersInvisible  (false),
fColour              (colour),
fLineStyle           (unbroken),
fLineWidth           (1.),
fForceDrawingStyle   (false),
fForcedStyle         (wireframe),
fForceAuxEdgeVisible (false),
fForcedLineSegmentsPerCircle (0),  // <=0 means not forced.
fStartTime           (-DBL_MAX),
fEndTime             (DBL_MAX),
fAttValues           (0),
fAttDefs             (0)
{}

G4VisAttributes::~G4VisAttributes()
{
}

G4VisAttributes& G4VisAttributes::operator= (const G4VisAttributes& rhs)
{
  if (&rhs == this) return *this;
  fVisible             = rhs.fVisible;
  fDaughtersInvisible  = rhs.fDaughtersInvisible;
  fColour              = rhs.fColour;
  fLineStyle           = rhs.fLineStyle;
  fLineWidth           = rhs.fLineWidth;
  fForceDrawingStyle   = rhs.fForceDrawingStyle;
  fForcedStyle         = rhs.fForcedStyle;
  fForceAuxEdgeVisible = rhs.fForceAuxEdgeVisible;
  fForcedLineSegmentsPerCircle = rhs.fForcedLineSegmentsPerCircle;
  fStartTime           = rhs.fStartTime;
  fEndTime             = rhs.fEndTime;
  // AttValues are created afresh for each object (using the
  // CreateAttValues message), but deletion is the responsibility of
  // the creator.  So just copy pointer.
  fAttValues           = rhs.fAttValues;
  // AttDefs, if any, belong to the object from which they were obtained
  // (with a GetAttDefs message), so just copy pointer.
  fAttDefs             = rhs.fAttDefs;
  return *this;
}

// Deprecated 14 July 2016  JA
const G4VisAttributes  G4VisAttributes::Invisible = G4VisAttributes (false);

const G4VisAttributes& G4VisAttributes::GetInvisible() {
  static const G4VisAttributes invisible = G4VisAttributes(false);
  return invisible;
}

const std::vector<G4AttValue>* G4VisAttributes::CreateAttValues () const {
  // Create an expendable copy on the heap...
  return new std::vector<G4AttValue>(*fAttValues);
}

void G4VisAttributes::SetForceLineSegmentsPerCircle (G4int nSegments) {
  const G4int nSegmentsMin = fMinLineSegmentsPerCircle;
  if (nSegments > 0 && nSegments < nSegmentsMin) {
    nSegments = nSegmentsMin;
    G4cout <<
      "G4VisAttributes::SetForcedLineSegmentsPerCircle: attempt to set the"
      "\nnumber of line segements per circle < " << nSegmentsMin
         << "; forced to " << nSegments << G4endl;
  }
  fForcedLineSegmentsPerCircle = nSegments;
}

std::ostream& operator << (std::ostream& os, const G4VisAttributes& a)
{
  os << "G4VisAttributes: ";
  if (!a.fVisible) os << "in";
  os << "visible, daughters ";
  if (a.fDaughtersInvisible) os << "in";
  os << "visible, colour: " << a.fColour;
  os << "\n  linestyle: ";
  switch (a.fLineStyle) {
    case G4VisAttributes::unbroken:
      os << "solid"; break;
    case G4VisAttributes::dashed:
      os << "dashed"; break;
    case G4VisAttributes::dotted: os << "dotted"; break;
    default: os << "unrecognised"; break;
  }
  os << ", line width: " << a.fLineWidth;
  os << ", min line segments per circle: " << a.GetMinLineSegmentsPerCircle();
  os << "\n  drawing style: ";
  if (a.fForceDrawingStyle) {
    os << "forced to: ";
    switch (a.fForcedStyle) {
      case G4VisAttributes::wireframe:
        os << "wireframe"; break;
      case G4VisAttributes::solid:
        os << "solid"; break;
      default: os << "unrecognised"; break;
    }
  }
  else {
    os << "not forced";
  }
  os << ", auxiliary edge visibility: ";
  if (!a.fForceAuxEdgeVisible) {
    os << "not ";
  }
  os << "forced";
  os << "\n  line segments per circle: ";
  if (a.fForcedLineSegmentsPerCircle > 0) {
    os << "forced to " << a.fForcedLineSegmentsPerCircle;
  } else {
    os << "not forced.";
  }
  os << "\n  time range: (" << a.fStartTime << ',' << a.fEndTime << ')';
  os << "\n  G4AttValue pointer is ";
  if (a.fAttValues) {
    os << "non-";
  }
  os << "zero";
  os << ", G4AttDef pointer is ";
  if (a.fAttDefs) {
    os << "non-";
  }
  os << "zero";
  return os;
}

G4bool G4VisAttributes::operator != (const G4VisAttributes& a) const {

  if (
      (fVisible            != a.fVisible)            ||
      (fDaughtersInvisible != a.fDaughtersInvisible) ||
      (fColour             != a.fColour)             ||
      (fLineStyle          != a.fLineStyle)          ||
      (fLineWidth          != a.fLineWidth)          ||
      (fForceDrawingStyle  != a.fForceDrawingStyle)  ||
      (fForceAuxEdgeVisible!= a.fForceAuxEdgeVisible)||
      (fForcedLineSegmentsPerCircle != a.fForcedLineSegmentsPerCircle) ||
      (fStartTime          != a.fStartTime)          ||
      (fEndTime            != a.fEndTime)            ||
      (fAttValues          != a.fAttValues)          ||
      (fAttDefs            != a.fAttDefs)
      )
    return true;

  if (fForceDrawingStyle) {
    if (fForcedStyle != a.fForcedStyle) return true;
  }

  return false;
}

G4bool G4VisAttributes::operator == (const G4VisAttributes& a) const {
  return !(G4VisAttributes::operator != (a));
}
