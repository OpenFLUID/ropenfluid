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

#include <iostream>

#include <R_ext/Print.h>

#include <QCoreApplication>

#include <openfluid/config.hpp>
#include <openfluid/base/Init.hpp>
#include <openfluid/base/IOListener.hpp>
#include <openfluid/base/RunContextManager.hpp>
#include <openfluid/base/ApplicationException.hpp>
#include <openfluid/machine/Factory.hpp>
#include <openfluid/machine/Engine.hpp>
#include <openfluid/machine/SimulationBlob.hpp>
#include <openfluid/machine/SimulatorPluginsManager.hpp>
#include <openfluid/machine/ModelInstance.hpp>
#include <openfluid/fluidx/FluidXDescriptor.hpp>
#include <openfluid/fluidx/AdvancedMonitoringDescriptor.hpp>
#include <openfluid/fluidx/SimulatorDescriptor.hpp>
#include <openfluid/fluidx/GeneratorDescriptor.hpp>
#include <openfluid/machine/MonitoringInstance.hpp>
#include <openfluid/ware/PluggableWare.hpp>

#include "ROpenFLUID.h"
#include "VerboseMachineListener.hpp"


// =====================================================================
// =====================================================================


static int qapp_argc = 1;
static char qapp_arg0[] = "ROpenFLUID";
static char* qapp_argv[] = { qapp_arg0  , NULL };

struct ROpenFLUID_Blob_t
{
  openfluid::base::IOListener FluidXListener;

  openfluid::fluidx::FluidXDescriptor FluidXDesc;

  bool IsProject;
  bool IsDataset;

  std::string SourcePath;
  std::string OutputDir;

  bool IsSimulationRun;

  ROpenFLUID_Blob_t():
    FluidXDesc(&FluidXListener),
    IsProject(false),IsDataset(false),
    SourcePath(""),OutputDir(""),
    IsSimulationRun(false)
  {

  }

};


static std::string LastErrorMsg = "";


// =====================================================================
// =====================================================================


#define STRING_TO_ALLOCATED_CARRAY(str,carray) \
    char* carray = (char*)malloc((str.length()+1)*sizeof(char)); \
    strcpy(carray,str.c_str());


// =====================================================================
// =====================================================================


void ROpenFLUID_Init()
{
  INIT_OPENFLUID_APPLICATION(qapp_argc,qapp_argv);

  // reset locale for "LC_NUMERIC" To "C"
  // to prevent from Qt changing locale on init
  std::setlocale(LC_NUMERIC,"C");
}


// =====================================================================
// =====================================================================


void ROpenFLUID_DeleteBlob(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Blob(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));
  delete Blob;
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetVersion()
{
  STRING_TO_ALLOCATED_CARRAY(openfluid::config::VERSION_FULL,CStr);
  return CStr;
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetLastError()
{
  return LastErrorMsg.c_str();
}


// =====================================================================
// =====================================================================


void ROpenFLUID_AddExtraSimulatorsPaths(const char* Paths)
{
  // ROpenFLUID_Init();

  openfluid::base::Environment::addExtraSimulatorsDirs(std::string(Paths));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_ResetExtraSimulatorsPaths()
{
  openfluid::base::Environment::resetExtraSimulatorsDirs();
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetSimulatorsPathsCount()
{
  return openfluid::base::Environment::getSimulatorsDirs().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetSimulatorsPaths()
{
  std::vector<std::string> SimsPaths = openfluid::base::Environment::getSimulatorsDirs();

  const unsigned int Count = SimsPaths.size();

  char** Paths = (char**)malloc(Count*sizeof(char*));

  for (unsigned int i=0;i<Count;i++)
  {
    Paths[i] = (char*)malloc(SimsPaths[i].size()+1);
    std::copy(SimsPaths[i].begin(), SimsPaths[i].end(), Paths[i]);
    Paths[i][SimsPaths[i].size()] = '\0';
  }

  return Paths;
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetExtraSimulatorsPathsCount()
{
  return openfluid::base::Environment::getExtraSimulatorsDirs().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetExtraSimulatorsPaths()
{
  std::vector<std::string> ExtraSimsPaths = openfluid::base::Environment::getExtraSimulatorsDirs();

  const unsigned int Count = ExtraSimsPaths.size();

  char** Paths = (char**)malloc(Count*sizeof(char*));

  for (unsigned int i=0;i<Count;i++)
  {
    Paths[i] = (char*)malloc(ExtraSimsPaths[i].size()+1);
    std::copy(ExtraSimsPaths[i].begin(), ExtraSimsPaths[i].end(), Paths[i]);
    Paths[i][ExtraSimsPaths[i].size()] = '\0';
  }

  return Paths;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_AddExtraObserversPaths(const char* Paths)
{
  openfluid::base::Environment::addExtraObserversDirs(std::string(Paths));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_ResetExtraObserversPaths()
{
  openfluid::base::Environment::resetExtraObserversDirs();
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetObserversPathsCount()
{
  return openfluid::base::Environment::getObserversDirs().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetObserversPaths()
{
  std::vector<std::string> ObsPaths = openfluid::base::Environment::getObserversDirs();

  const unsigned int Count = ObsPaths.size();

  char** Paths = (char**)malloc(Count*sizeof(char*));

  for (unsigned int i=0;i<Count;i++)
  {
    Paths[i] = (char*)malloc(ObsPaths[i].size()+1);
    std::copy(ObsPaths[i].begin(), ObsPaths[i].end(), Paths[i]);
    Paths[i][ObsPaths[i].size()] = '\0';
  }

  return Paths;
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetExtraObserversPathsCount()
{
  return openfluid::base::Environment::getExtraObserversDirs().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetExtraObserversPaths()
{
  std::vector<std::string> ExtraObsPaths = openfluid::base::Environment::getExtraObserversDirs();

  const unsigned int Count = ExtraObsPaths.size();

  char** Paths = (char**)malloc(Count*sizeof(char*));

  for (unsigned int i=0;i<Count;i++)
  {
    Paths[i] = (char*)malloc(ExtraObsPaths[i].size()+1);
    std::copy(ExtraObsPaths[i].begin(), ExtraObsPaths[i].end(), Paths[i]);
    Paths[i][ExtraObsPaths[i].size()] = '\0';
  }

  return Paths;
}


// =====================================================================
// =====================================================================


/*
void UpdateOutputsConfig(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t*  Blob(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::vector<openfluid::base::OutputFilesDescriptor>::iterator DescIt;

  for (DescIt = Blob->OutDesc.getFileSets().begin();
       DescIt != Blob->OutDesc.getFileSets().end();
       ++DescIt)
  {
    (*DescIt).setHeaderType(openfluid::base::OutputFilesDescriptor::ColnamesAsData);
    (*DescIt).setDateFormat("%Y%m%d-%H%M%S");
  }

}*/


// =====================================================================
// =====================================================================


ROpenFLUID_ExtBlob_t ROpenFLUID_NewDataBlob()
{
  return (new ROpenFLUID_Blob_t());
}


// =====================================================================
// =====================================================================


ROpenFLUID_ExtBlob_t ROpenFLUID_OpenDataset(const char* Path)
{
  ROpenFLUID_Blob_t* Data = new ROpenFLUID_Blob_t();

  try
  {

    ROpenFLUID_Init();

    openfluid::base::IOListener IOListen;

    openfluid::base::RunContextManager::instance()->setInputDir(std::string(Path));
    Data->FluidXDesc.loadFromDirectory(openfluid::base::RunContextManager::instance()->getInputDir());

    Data->IsSimulationRun = false;

    if (!Data->IsProject)
    {
      Data->IsDataset = true;
      Data->SourcePath = openfluid::base::RunContextManager::instance()->getInputDir();
    }


    return Data;
  }
  catch (openfluid::base::Exception& E)
  {
    LastErrorMsg = "OpenFLUID ERROR: " + std::string(E.what()) +"\n";
  }
  catch (std::bad_alloc& E)
  {
    LastErrorMsg = "MEMORY ALLOCATION ERROR: " + std::string(E.what()) + ". Possibly not enough memory available\n";
  }
  catch (std::exception& E)
  {
    LastErrorMsg = "SYSTEM ERROR: " + std::string(E.what()) +"\n";
  }
  catch (...)
  {
    LastErrorMsg = "UNKNOWN ERROR\n";
  }

  Data->IsProject = false;
  Data->IsDataset = false;
  Data->SourcePath = "";

  return NULL;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetCurrentOutputDir(const char* Path)
{
  openfluid::base::RunContextManager::instance()->setOutputDir(std::string(Path));
}


// =====================================================================
// =====================================================================


ROpenFLUID_ExtBlob_t ROpenFLUID_OpenProject(const char* Path)
{
  try
  {

    ROpenFLUID_Init();

    ROpenFLUID_Blob_t* Data = new ROpenFLUID_Blob_t();

    if (!openfluid::base::RunContextManager::instance()->openProject(std::string(Path)))
      throw openfluid::base::ApplicationException(openfluid::base::ApplicationException::computeContext("ROpenFLUID"),
                                                  std::string(Path) + " is not a correct project path");

    Data->IsProject = true;
    Data->SourcePath = openfluid::base::RunContextManager::instance()->getProjectPath();

    return ROpenFLUID_OpenDataset(openfluid::base::RunContextManager::instance()->getInputDir().c_str());
  }
  catch (openfluid::base::Exception& E)
  {
    LastErrorMsg = "OpenFLUID ERROR: " + std::string(E.what()) +"\n";
  }
  catch (std::bad_alloc& E)
  {
    LastErrorMsg = "MEMORY ALLOCATION ERROR: " + std::string(E.what()) + ". Possibly not enough memory available\n";
  }
  catch (std::exception& E)
  {
    LastErrorMsg = "SYSTEM ERROR: " + std::string(E.what()) +"\n";
  }
  catch (...)
  {
    LastErrorMsg = "UNKNOWN ERROR\n";
  }

  return NULL;
}


// =====================================================================
// =====================================================================


unsigned short int ROpenFLUID_RunSimulation(ROpenFLUID_ExtBlob_t* BlobHandle, int IsVerbose)
{

  try
  {

    // ROpenFLUID_Init();

    openfluid::machine::Engine* Engine;


    //UpdateOutputsConfig(BlobHandle);

    ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

    openfluid::base::IOListener IOListen;
    openfluid::machine::SimulationBlob SimBlob;

    openfluid::machine::SimulatorPluginsManager::instance()->unloadAllWares();


    // ===== spatial domain and run config

    if (IsVerbose)
      Rprintf("%s","Building spatial domain...");

    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(Data->FluidXDesc,SimBlob);

    if (IsVerbose)
      VerboseMachineListener::displayStatus(openfluid::base::Listener::LISTEN_OK);


    // ===== model instance

    if (IsVerbose)
      Rprintf("%s","Building model instance...");

    std::unique_ptr<openfluid::machine::MachineListener> Listener;

    if (IsVerbose)
      Listener.reset(new VerboseMachineListener());
    else
      Listener.reset(new openfluid::machine::MachineListener());


    openfluid::machine::ModelInstance Model(SimBlob,Listener.get());

    openfluid::machine::Factory::buildModelInstanceFromDescriptor(Data->FluidXDesc.modelDescriptor(),Model);

    if (IsVerbose)
      VerboseMachineListener::displayStatus(openfluid::base::Listener::LISTEN_OK);


    // ===== monitoring instance

    if (IsVerbose)
      Rprintf("%s","Building monitoring instance...");

    openfluid::machine::MonitoringInstance Monitoring(SimBlob);

    openfluid::machine::Factory::buildMonitoringInstanceFromDescriptor(Data->FluidXDesc.monitoringDescriptor(),
                                                                       Monitoring);

    if (IsVerbose)
      VerboseMachineListener::displayStatus(openfluid::base::Listener::LISTEN_OK);


    // ===== simulation

    Data->OutputDir = openfluid::base::RunContextManager::instance()->getOutputDir();


    Engine = new openfluid::machine::Engine(SimBlob, Model, Monitoring, Listener.get());

    Engine->initialize();

    Engine->initParams();
    Engine->prepareData();
    Engine->checkConsistency();
    Engine->run();

    Engine->finalize();

    delete Engine;

    Data->IsSimulationRun = true;

    return 1;
  }
  catch (openfluid::base::Exception& E)
  {
    LastErrorMsg = "OpenFLUID ERROR: " + std::string(E.what()) +"\n";
  }
  catch (std::bad_alloc& E)
  {
    LastErrorMsg = "MEMORY ALLOCATION ERROR: " + std::string(E.what()) + ". Possibly not enough memory available\n";
  }
  catch (std::exception& E)
  {
    LastErrorMsg = "SYSTEM ERROR: " + std::string(E.what()) +"\n";
  }
  catch (...)
  {
    LastErrorMsg = "UNKNOWN ERROR\n";
  }

  return 0;
}



// =====================================================================
// =====================================================================


void ROpenFLUID_PrintSimulationInfo(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));


  // Spatial domain

  std::map<openfluid::core::UnitsClass_t,unsigned int> UnitsInfos;

  for (auto& ItUnits : Data->FluidXDesc.spatialDomainDescriptor().spatialUnits())
  {
    openfluid::core::UnitsClass_t ClassName = ItUnits.getUnitsClass();

    if (UnitsInfos.find(ClassName) == UnitsInfos.end())
      UnitsInfos[ClassName] = 0;

    UnitsInfos[ClassName]++;
  }

  Rprintf("Spatial domain is made of %i spatial units\n",
          Data->FluidXDesc.spatialDomainDescriptor().spatialUnits().size());

  for (auto& ItUnitsInfos : UnitsInfos)
    Rprintf(" - %i units of class %s\n",ItUnitsInfos.second,ItUnitsInfos.first.c_str());


  // Model

  Rprintf("Model is made of %i simulation items\n",Data->FluidXDesc.modelDescriptor().items().size());

  for (auto& ItModelInfos : Data->FluidXDesc.modelDescriptor().items())
  {
    Rprintf(" - ");

    if (ItModelInfos->isType(openfluid::ware::WareType::SIMULATOR))
    {
      Rprintf("%s simulator\n",((openfluid::fluidx::SimulatorDescriptor*)(ItModelInfos))->getID().c_str());
    }

    if (ItModelInfos->isType(openfluid::ware::WareType::GENERATOR))
    {
      openfluid::fluidx::GeneratorDescriptor* pGenDesc = ((openfluid::fluidx::GeneratorDescriptor*)ItModelInfos);

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Fixed)
        Rprintf("fixed");

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Random)
        Rprintf("random");

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Interp)
        Rprintf("interp");

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Inject)
        Rprintf("inject");

      Rprintf(" generator for variable %s on units %s\n",pGenDesc->getVariableName().c_str(),pGenDesc->getUnitsClass().c_str());
    }
  }

  // Time period

  Rprintf("Simulation period from %s to %s\n",
          Data->FluidXDesc.runDescriptor().getBeginDate().getAsISOString().c_str(),
          Data->FluidXDesc.runDescriptor().getEndDate().getAsISOString().c_str());

  // Time step

  Rprintf("Simulation time step : %i\n",Data->FluidXDesc.runDescriptor().getDeltaT());

}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetSimulationOutputDir(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string Str = Data->OutputDir;
  STRING_TO_ALLOCATED_CARRAY(Str,CStr);
  return CStr;
}


// =====================================================================
// =====================================================================


int ROpenFLUID_GetDefaultDeltaT(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  return Data->FluidXDesc.runDescriptor().getDeltaT();
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetDefaultDeltaT(ROpenFLUID_ExtBlob_t* BlobHandle, int DeltaT)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  Data->FluidXDesc.runDescriptor().setDeltaT(DeltaT);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetPeriodBeginDate(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string DateStr = Data->FluidXDesc.runDescriptor().getBeginDate().getAsString("%Y-%m-%d %H:%M:%S");

  STRING_TO_ALLOCATED_CARRAY(DateStr,CStr);

  return CStr;
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetPeriodEndDate(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string DateStr = Data->FluidXDesc.runDescriptor().getEndDate().getAsString("%Y-%m-%d %H:%M:%S");

  STRING_TO_ALLOCATED_CARRAY(DateStr,CStr);

  return CStr;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetPeriod(ROpenFLUID_ExtBlob_t* BlobHandle, const char* BeginDate, const char* EndDate)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string StrBeginDate(BeginDate);
  std::string StrEndDate(EndDate);
  openfluid::core::DateTime DateToSet;

  if (!StrBeginDate.empty() && DateToSet.setFromISOString(StrBeginDate))
    Data->FluidXDesc.runDescriptor().setBeginDate(DateToSet);

  if (!StrEndDate.empty() && DateToSet.setFromISOString(StrEndDate))
      Data->FluidXDesc.runDescriptor().setEndDate(DateToSet);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamValStr("");
  std::string SimIDStr(SimID);
  std::string ParamNameStr(ParamName);

  for (auto& ItModelInfos : Data->FluidXDesc.modelDescriptor().items())
  {
    if (ItModelInfos->isType(openfluid::ware::WareType::SIMULATOR) &&
        ((openfluid::fluidx::SimulatorDescriptor*)ItModelInfos)->getID() == SimIDStr)
    {
      openfluid::ware::WareParams_t Params = ItModelInfos->getParameters();
      openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

      if (ItParam != Params.end())
      {
        ParamValStr = (*ItParam).second;
        STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
        return CStr;
      }
    }
  }

  STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
  return CStr;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName, const char* ParamVal)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string SimIDStr(SimID);
  std::string ParamNameStr(ParamName);
  std::string ParamValStr(ParamVal);

  for (auto& ItModelInfos : Data->FluidXDesc.modelDescriptor().items())
  {
    if (ItModelInfos->isType(openfluid::ware::WareType::SIMULATOR) &&
        ((openfluid::fluidx::SimulatorDescriptor*)ItModelInfos)->getID() == SimIDStr)
      ItModelInfos->setParameter(ParamNameStr,ParamValStr);
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string SimIDStr(SimID);
  std::string ParamNameStr(ParamName);

  for (auto& ItModelInfos : Data->FluidXDesc.modelDescriptor().items())
  {
    if (ItModelInfos->isType(openfluid::ware::WareType::SIMULATOR) &&
        ((openfluid::fluidx::SimulatorDescriptor*)ItModelInfos)->getID() == SimIDStr)
      ItModelInfos->eraseParameter(ParamNameStr);
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetGeneratorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, const char* VarName, const char* ParamName, const char* ParamVal)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  std::string VarNameStr(VarName);
  std::string ParamNameStr(ParamName);
  std::string ParamValStr(ParamVal);

  for (auto& ItModelInfos : Data->FluidXDesc.modelDescriptor().items())
  {
    if (ItModelInfos->isType(openfluid::ware::WareType::GENERATOR) &&
        ((openfluid::fluidx::GeneratorDescriptor*)ItModelInfos)->getUnitsClass() == UnitClassStr &&
        ((openfluid::fluidx::GeneratorDescriptor*)ItModelInfos)->getVariableName() == VarNameStr)
    {
      ItModelInfos->setParameter(ParamNameStr,ParamValStr);
    }
  }
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetGeneratorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, const char* VarName, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  std::string VarNameStr(VarName);
  std::string ParamNameStr(ParamName);
  std::string ParamValStr("");

  for (auto& ItModelInfos : Data->FluidXDesc.modelDescriptor().items())
  {
    if (ItModelInfos->isType(openfluid::ware::WareType::GENERATOR) &&
        ((openfluid::fluidx::GeneratorDescriptor*)ItModelInfos)->getUnitsClass() == UnitClassStr &&
        ((openfluid::fluidx::GeneratorDescriptor*)ItModelInfos)->getVariableName() == VarNameStr)
    {
      openfluid::ware::WareParams_t Params = ItModelInfos->getParameters();
      openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

      if (ItParam != Params.end())
      {
        ParamValStr = (*ItParam).second;
        STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
        return CStr;
      }

    }
  }

  STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
  return CStr;

}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName, const char* ParamVal)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamNameStr(ParamName);
  std::string ParamValStr(ParamVal);

  Data->FluidXDesc.modelDescriptor().setGlobalParameter(ParamNameStr,ParamValStr);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamNameStr(ParamName);
  std::string ParamValStr("");

  openfluid::ware::WareParams_t Params = Data->FluidXDesc.modelDescriptor().getGlobalParameters();
  openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

  if (ItParam != Params.end())
  {
    ParamValStr = (*ItParam).second;
    STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
    return CStr;
  }

  STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
  return CStr;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamNameStr(ParamName);

  Data->FluidXDesc.modelDescriptor().eraseGlobalParameter(ParamNameStr);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetObserverParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ObsID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamValStr("");
  std::string ObsIDStr(ObsID);
  std::string ParamNameStr(ParamName);

  for (auto& ItObsInfos : Data->FluidXDesc.monitoringDescriptor().items())
  {
    if (ItObsInfos->isType(openfluid::ware::WareType::OBSERVER) &&
        ((openfluid::fluidx::ObserverDescriptor*)ItObsInfos)->getID() == ObsIDStr)
    {
      openfluid::ware::WareParams_t Params = ItObsInfos->getParameters();
      openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

      if (ItParam != Params.end())
      {
        ParamValStr = (*ItParam).second;
        STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
        return CStr;
      }
    }
  }

  STRING_TO_ALLOCATED_CARRAY(ParamValStr,CStr);
  return CStr;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetObserverParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ObsID, const char* ParamName, const char* ParamVal)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ObsIDStr(ObsID);
  std::string ParamNameStr(ParamName);
  std::string ParamValStr(ParamVal);

  for (auto& ItObsInfos : Data->FluidXDesc.monitoringDescriptor().items())
  {
    if (ItObsInfos->isType(openfluid::ware::WareType::OBSERVER) &&
        ((openfluid::fluidx::ObserverDescriptor*)ItObsInfos)->getID() == ObsIDStr)
      ItObsInfos->setParameter(ParamNameStr,ParamValStr);
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveObserverParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ObsID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ObsIDStr(ObsID);
  std::string ParamNameStr(ParamName);

  for (auto& ItObsInfos : Data->FluidXDesc.monitoringDescriptor().items())
  {
    if (ItObsInfos->isType(openfluid::ware::WareType::OBSERVER) &&
        ((openfluid::fluidx::ObserverDescriptor*)ItObsInfos)->getID() == ObsIDStr)
      ItObsInfos->eraseParameter(ParamNameStr);
  }
}


// =====================================================================
// =====================================================================


std::map<openfluid::core::UnitsClass_t,unsigned int> GetUnitsCountByClasses(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::map<openfluid::core::UnitsClass_t,unsigned int> RetMap;

  for (auto ItUnits : Data->FluidXDesc.spatialDomainDescriptor().spatialUnits())
  {
    if (RetMap.find(ItUnits.getUnitsClass()) == RetMap.end())
      RetMap[ItUnits.getUnitsClass()] = 0;
    RetMap[ItUnits.getUnitsClass()]++;
  }

  return RetMap;
}



// =====================================================================
// =====================================================================


char** ROpenFLUID_GetUnitsClasses(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  std::map<openfluid::core::UnitsClass_t,unsigned int> UnitsCountByClasses;
  UnitsCountByClasses = GetUnitsCountByClasses(BlobHandle);

  std::map<openfluid::core::UnitsClass_t,unsigned int>::iterator ItUCC;
  const unsigned int Count = UnitsCountByClasses.size();

  char** Classes = (char**)malloc(Count*sizeof(char*));

  unsigned int i=0;
  for (auto& ItUCC : UnitsCountByClasses)
  {
    Classes[i] = (char*)malloc(ItUCC.first.size()+1);
    std::copy(ItUCC.first.begin(), ItUCC.first.end(), Classes[i]);
    Classes[i][ItUCC.first.size()] = '\0';
    i++;
  }

  return Classes;

}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetUnitsClassesCount(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  std::map<openfluid::core::UnitsClass_t,unsigned int> UnitsCountByClasses;
  UnitsCountByClasses = GetUnitsCountByClasses(BlobHandle);

  return UnitsCountByClasses.size();
}


// =====================================================================
// =====================================================================


int* ROpenFLUID_GetUnitsIDs(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitsClass)
{
  int Count = ROpenFLUID_GetUnitsIDsCount(BlobHandle,UnitsClass);

  int* IDs = NULL;

  if (Count > 0)
  {
    IDs = (int*)malloc(Count*sizeof(int));

    ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

    unsigned int i=0;
    for (auto& ItUnits : Data->FluidXDesc.spatialDomainDescriptor().spatialUnits())
    {
      if (ItUnits.getUnitsClass() == std::string(UnitsClass))
      {
        IDs[i] = ItUnits.getID();
        i++;
      }
    }
  }

  return IDs;
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetUnitsIDsCount(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitsClass)
{
  std::map<openfluid::core::UnitsClass_t,unsigned int> UnitsCountByClasses;
  UnitsCountByClasses = GetUnitsCountByClasses(BlobHandle);

  unsigned int Count = 0;

  if (UnitsCountByClasses.find(std::string(UnitsClass)) != UnitsCountByClasses.end())
    Count = UnitsCountByClasses[std::string(UnitsClass)];

  return Count;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_CreateAttribute(ROpenFLUID_ExtBlob_t* BlobHandle,
                                const char* UnitsClass, const char* AttrName, const char* AttrValue)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitsClass);
  std::string AttrNameStr(AttrName);
  std::string AttrValStr(AttrValue);


  for (auto& ItAttr : Data->FluidXDesc.spatialDomainDescriptor().attributes())
  {
    if (ItAttr.getUnitsClass() == UnitClassStr)
    {
      for (auto & ItUnitData : ItAttr.attributes())
        ItUnitData.second[AttrNameStr] = AttrValStr;
    }
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetAttribute(ROpenFLUID_ExtBlob_t* BlobHandle,
                             const char* UnitsClass, int UnitID, const char* AttrName, const char* AttrValue)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitsClass);
  std::string AttrNameStr(AttrName);
  std::string AttrValStr(AttrValue);

  for (auto& ItAttr : Data->FluidXDesc.spatialDomainDescriptor().attributes())
  {
    if (ItAttr.getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::AttributesDescriptor::UnitIDAttribute_t::iterator ItUnitData = ItAttr.attributes().find(UnitID);
      if (ItUnitData != ItAttr.attributes().end())
      {
        if ((*ItUnitData).second.find(AttrNameStr) != (*ItUnitData).second.end())
          (*ItUnitData).second[AttrNameStr] = AttrValStr;
      }
    }
  }

}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetAttribute(ROpenFLUID_ExtBlob_t* BlobHandle,
                                    const char* UnitsClass, int UnitID, const char* AttrName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitsClass);
  std::string AttrNameStr(AttrName);
  std::string AttrValStr("");

  for (auto& ItAttr : Data->FluidXDesc.spatialDomainDescriptor().attributes())
  {
    if (ItAttr.getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::AttributesDescriptor::UnitIDAttribute_t::const_iterator ItUnitData = ItAttr.attributes().find(UnitID);
      if (ItUnitData != ItAttr.attributes().end())
      {
        if ((*ItUnitData).second.find(AttrNameStr) != (*ItUnitData).second.end())
        {
          AttrValStr = (*ItUnitData).second.at(AttrNameStr);
          STRING_TO_ALLOCATED_CARRAY(AttrValStr,CStr);
          return CStr;
        }
      }
    }
  }

  STRING_TO_ALLOCATED_CARRAY(AttrValStr,CStr);
  return CStr;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveAttribute(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitsClass, const char* AttrName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitsClass);
  std::string AttrNameStr(AttrName);

  for (auto& ItAttr : Data->FluidXDesc.spatialDomainDescriptor().attributes())
  {
    if (ItAttr.getUnitsClass() == UnitClassStr)
    {
      for (auto& ItUnitData : ItAttr.attributes())
        ItUnitData.second.erase(AttrNameStr);
    }
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_AddVariablesExportAsCSV(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, int UnitID, const char* VarName, int Prec)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  std::string VarNameStr(VarName);
  openfluid::fluidx::AdvancedMonitoringDescriptor AdvMonDesc(Data->FluidXDesc.monitoringDescriptor());

  // 1. add CSV observer if not present

  if (AdvMonDesc.findFirstItem("export.vars.files.csv") < 0)
    AdvMonDesc.appendItem(new openfluid::fluidx::ObserverDescriptor("export.vars.files.csv"));


  openfluid::fluidx::ObserverDescriptor& ObsDesc = AdvMonDesc.itemAt(AdvMonDesc.findFirstItem("export.vars.files.csv"));

  // 2. add ropenfluid format
  ObsDesc.setParameter("format.ropenfluid.header",openfluid::core::StringValue("colnames-as-data"));
  ObsDesc.setParameter("format.ropenfluid.date",openfluid::core::StringValue("%Y%m%d-%H%M%S"));
  ObsDesc.setParameter("format.ropenfluid.colsep",openfluid::core::StringValue(" "));
  if (Prec != -1)
  {
    std::ostringstream ssPrec;
    ssPrec << Prec;
    std::string PrecStr(ssPrec.str());
    ObsDesc.setParameter("format.ropenfluid.precision",openfluid::core::StringValue(PrecStr));
  }

  // 3. add ropenfluidUnitClass output set
  ObsDesc.setParameter("set.ropenfluid"+UnitClassStr+".unitclass",openfluid::core::StringValue(UnitClassStr));
  if (UnitID != -1) {
    std::ostringstream ssUnitID;
    ssUnitID << UnitID;
    std::string UnitIDStr(ssUnitID.str());
    ObsDesc.setParameter("set.ropenfluid"+UnitClassStr+".unitsIDs",openfluid::core::StringValue(UnitIDStr));
  }
  else {
    ObsDesc.setParameter("set.ropenfluid"+UnitClassStr+".unitsIDs",openfluid::core::StringValue("*"));
  }
  if (!VarNameStr.empty()) {
    ObsDesc.setParameter("set.ropenfluid"+UnitClassStr+".vars",openfluid::core::StringValue(VarNameStr));
  }
  else {
    ObsDesc.setParameter("set.ropenfluid"+UnitClassStr+".vars",openfluid::core::StringValue("*"));
  }
  ObsDesc.setParameter("set.ropenfluid"+UnitClassStr+".format",openfluid::core::StringValue("ropenfluid"));
}


