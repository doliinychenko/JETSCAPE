/*******************************************************************************
 * Copyright (c) The JETSCAPE Collaboration, 2018
 *
 * Modular, task-based framework for simulating all aspects of heavy-ion collisions
 * 
 * For the list of contributors see AUTHORS.
 *
 * Report issues at https://github.com/JETSCAPE/JETSCAPE/issues
 *
 * or via email to bugs.jetscape@gmail.com
 *
 * Distributed under the GNU General Public License 3.0 (GPLv3 or later).
 * See COPYING for details.
 ******************************************************************************/

//  SignalManager instance class (meant as singelton)

#ifndef JETSCAPESIGNALMANAGER_H
#define JETSCAPESIGNALMANAGER_H

#include "InitialState.h"
#include "JetEnergyLoss.h"
#include "JetEnergyLossManager.h"
#include "HadronizationManager.h"
#include "Hadronization.h"
#include "FluidDynamics.h"
#include "HardProcess.h"
#include "JetScapeWriter.h"
#include "PreequilibriumDynamics.h"


#include<iostream>
#include<string>
#include<map>
#include "sigslot.h"

using namespace sigslot;

namespace Jetscape {

class JetScapeSignalManager //: public sigslot::has_slots<sigslot::multi_threaded_local>
{
  
 public:

  static JetScapeSignalManager* Instance();

  void SetInitialStatePointer(shared_ptr<InitialState> m_initial) {initial_state=m_initial;}
  weak_ptr<InitialState> GetInitialStatePointer() {return initial_state;}

  void SetPreEquilibriumPointer(shared_ptr<PreequilibriumDynamics> m_pre_eq) {pre_equilibrium=m_pre_eq;}
  weak_ptr<PreequilibriumDynamics> GetPreEquilibriumPointer() {return pre_equilibrium;}
 
  void SetHydroPointer(shared_ptr<FluidDynamics> m_hydro) {hydro=m_hydro;}
  weak_ptr<FluidDynamics> GetHydroPointer() {return hydro;}
  
  void SetJetEnergyLossManagerPointer(shared_ptr<JetEnergyLossManager> m_jloss) {jloss=m_jloss;}
  weak_ptr<JetEnergyLossManager> GetJetEnergyLossManagerPointer() {return jloss;}
  
  void SetHardProcessPointer(shared_ptr<HardProcess> m_hardp) {hardp=m_hardp;}
  weak_ptr<HardProcess> GetHardProcessPointer() {return hardp;}
  
  void SetWriterPointer(shared_ptr<JetScapeWriter> m_writer) {writer=m_writer;}
  weak_ptr<JetScapeWriter> GetWriterPointer() {return writer;}

  void SetHadronizationManagerPointer(shared_ptr<HadronizationManager> m_hadro) {hadro=m_hadro;}
  weak_ptr<HadronizationManager> GetHadronizationManagerPointer() {return hadro;}

  void SetPartonPrinterPointer(shared_ptr<PartonPrinter> m_pprinter) {pprinter=m_pprinter;}
  weak_ptr<PartonPrinter> GetPartonPrinterPointer() {return pprinter;}
  
  void ConnectJetSignal(shared_ptr<JetEnergyLoss> j);
  void ConnectEdensitySignal(shared_ptr<JetEnergyLoss> j);
  void ConnectAddJetSourceSignal(shared_ptr<JetEnergyLoss> j);
  void ConnectGetTemperatureSignal(shared_ptr<JetEnergyLoss> j);
  void ConnectGetHydroCellSignal(shared_ptr<JetEnergyLoss> j);
  void ConnectGetHardPartonListSignal(shared_ptr<JetEnergyLossManager> jm);
  void ConnectSentInPartonsSignal(shared_ptr<JetEnergyLoss> j,shared_ptr<JetEnergyLoss> j2);
  void ConnectGetOutPartons(shared_ptr<JetEnergyLoss> j,shared_ptr<JetEnergyLoss> j2) {};
  void ConnectGetFinalPartonListSignal(shared_ptr<HadronizationManager> hm);
  void ConnectTransformPartonsSignal(shared_ptr<Hadronization> h,shared_ptr<Hadronization> h2); 
 
  void DisconnectSignal() {}; // to be implememted if needed maybe for Eloss ...!???

  void CleanUp();
  
  int GetNumberOfJetSignals() {return num_jet_signals;}
  int GetNumberOfEdensitySignals() {return num_edensity_signals;}
  int GetNumberOfAddJetSourceSignals() {return num_AddJetSourceSignals;}
  int GetNumberOfGetTemperatureSignals() {return num_GetTemperatureSignals;}
  int GetNumberOfGetHydroCellSignals() {return num_GetHydroCellSignals;}
  
  void PrintJetSignalMap();
  void PrintEdensitySignalMap();
  void PrintAddJetSourceSignalMap() {};
  void PrintGetTemperatureSignalMap() {};
  void PrintGetHydroCellSignalMap();
  void PrintSentInPartonsSignalMap();
  void PrintTransformPartonsSignalMap();
  
 private:

  JetScapeSignalManager() {};
  JetScapeSignalManager(JetScapeSignalManager const&) {};
  static JetScapeSignalManager* m_pInstance;

  weak_ptr<InitialState> initial_state;
  weak_ptr<PreequilibriumDynamics> pre_equilibrium;
  weak_ptr<FluidDynamics> hydro;
  weak_ptr<JetEnergyLossManager> jloss;
  weak_ptr<HardProcess> hardp;
  weak_ptr<JetScapeWriter> writer;
  weak_ptr<HadronizationManager> hadro;
  weak_ptr<PartonPrinter> pprinter;
  
  int num_jet_signals=0;
  int num_edensity_signals=0;
  int num_AddJetSourceSignals=0;
  int num_GetTemperatureSignals=0;
  int num_GetHydroCellSignals=0;
  int num_SentInPartons=0;
  // int num_GetOutPartons=0;
  int num_TransformPartons=0;
  
  map<int,weak_ptr<JetEnergyLoss>> jet_signal_map;
  map<int,weak_ptr<JetEnergyLoss>> edensity_signal_map;
  map<int,weak_ptr<JetEnergyLoss>> AddJetSourceSignal_map;
  map<int,weak_ptr<JetEnergyLoss>> GetTemperatureSignal_map;
  map<int,weak_ptr<JetEnergyLoss>> GetHydroCellSignal_map;

  map<int,weak_ptr<JetEnergyLoss>> SentInPartons_map;
  map<int,weak_ptr<JetEnergyLoss>> GetOutPartons_map;
  map<int,weak_ptr<Hadronization>> TransformPartons_map;
  
};

} // end namespace Jetscape

#endif
