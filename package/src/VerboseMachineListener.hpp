/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
  
*/



#ifndef __VERBOSEMACHINELISTENER_HPP__
#define __VERBOSEMACHINELISTENER_HPP__


#include <R_ext/Print.h>

#include <openfluid/machine/MachineListener.hpp>


class VerboseMachineListener : public openfluid::machine::MachineListener
{
  private:

    static void displayStatusWithLeftMargin(const openfluid::base::Listener::Status& Status)
    {
      switch (Status)
      {
        case openfluid::base::Listener::LISTEN_ERROR :
          Rprintf("%14s\n","[Error]");
          break;
        case openfluid::base::Listener::LISTEN_OK :
          Rprintf("%14s\n","[OK]");
          break;
        case openfluid::base::Listener::LISTEN_WARNING :
          Rprintf("%14s\n","[Warning]");
          break;
      }
    };

  public:

    VerboseMachineListener()
    { };

    ~VerboseMachineListener()
    { };


    static void displayStatus(const openfluid::base::Listener::Status& Status)
    {
      switch (Status)
      {
        case openfluid::base::Listener::LISTEN_ERROR :
          Rprintf(" [Error]\n");
          break;
        case openfluid::base::Listener::LISTEN_OK :
          Rprintf(" [OK]\n");
          break;
        case openfluid::base::Listener::LISTEN_WARNING :
          Rprintf(" [Warning]\n");
          break;
      }
    };


    void onInitParams()
    {
      Rprintf("%s","Initializing parameters...");
    };

    void onInitParamsDone(const openfluid::base::Listener::Status& Status)
    {
      displayStatus(Status);
    };


    void onPrepareData()
    {
      Rprintf("%s","Preparing data...");
    };

    void onPrepareDataDone(const openfluid::base::Listener::Status& Status)
    {
      displayStatus(Status);
    };


    void onCheckConsistency()
    {
      Rprintf("%s","Checking consistency...");
    };

    void onCheckConsistencyDone(const openfluid::base::Listener::Status& Status)
    {
      displayStatus(Status);
    };


    void onInitializeRun()
    {
      Rprintf("%s","\nInitializing simulation...");
    };

    void onInitializeRunDone(const openfluid::base::Listener::Status& Status)
    {
      displayStatus(Status);
    };


    void onBeforeRunSteps()
    {

      Rprintf("   Progress            Real time              Status\n");
      Rprintf("   --------            ---------              ------\n");
    };

    void onRunStep(const openfluid::base::SimulationStatus* SimStatus)
    {
      double Percent = (double(SimStatus->getCurrentTimeIndex())/double(SimStatus->getSimulationDuration()))*100;
      Rprintf("  %7.2f%%%27s",Percent,SimStatus->getCurrentDate().getAsISOString().c_str());
    };

    void onRunStepDone(const openfluid::base::Listener::Status& Status)
    {
      displayStatusWithLeftMargin(Status);
    };


    void onAfterRunSteps()
    { };

    void onFinalizeRun()
    {
      Rprintf("%s","Finalizing simulation...");
    };

    void onFinalizeRunDone(const openfluid::base::Listener::Status& Status)
    {
      displayStatus(Status);
    };


};


#endif /* __VERBOSEMACHINELISTENER_HPP__ */
