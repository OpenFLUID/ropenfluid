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
#include <openfluid/base/Init.hpp>
#include <openfluid/base/IOListener.hpp>
#include <openfluid/base/ProjectManager.hpp>
#include <openfluid/base/ApplicationException.hpp>
#include <openfluid/machine.hpp>
#include <openfluid/fluidx/FluidXDescriptor.hpp>
#include <openfluid/fluidx/AdvancedMonitoringDescriptor.hpp>
#include <openfluid/fluidx/SimulatorDescriptor.hpp>
#include <openfluid/fluidx/GeneratorDescriptor.hpp>
#include <openfluid/machine/MonitoringInstance.hpp>
#include <openfluid/ware/PluggableWare.hpp>

#include "ROpenFLUID.h"

#include <QCoreApplication>


static int qapp_argc = 1;
static char *qapp_argv[] = { "ROpenFLUID" };

struct ROpenFLUID_Blob_t
{

  openfluid::fluidx::FluidXDescriptor FluidXDesc;

  bool IsProject;
  bool IsDataset;

  std::string SourcePath;
  std::string OutputDir;

  bool IsSimulationRun;

  ROpenFLUID_Blob_t():
    IsProject(false),IsDataset(false),
    SourcePath(""),OutputDir(""),
    IsSimulationRun(false), FluidXDesc(NULL)
  {

  }

};


std::string LastErrorMsg = "";


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
  return openfluid::config::FULL_VERSION.c_str();
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

  openfluid::base::RuntimeEnvironment::getInstance()->addExtraSimulatorsPluginsPaths(std::string(Paths));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_ResetExtraSimulatorsPaths()
{
  openfluid::base::RuntimeEnvironment::getInstance()->resetExtraSimulatorsPluginsPaths();
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetSimulatorsPathsCount()
{
  return openfluid::base::RuntimeEnvironment::getInstance()->getSimulatorsPluginsPaths().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetSimulatorsPaths()
{
  std::vector<std::string> SimsPaths = openfluid::base::RuntimeEnvironment::getInstance()->getSimulatorsPluginsPaths();

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
  return openfluid::base::RuntimeEnvironment::getInstance()->getExtraSimulatorsPluginsPaths().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetExtraSimulatorsPaths()
{
  std::vector<std::string> ExtraSimsPaths = openfluid::base::RuntimeEnvironment::getInstance()->getExtraSimulatorsPluginsPaths();

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
  openfluid::base::RuntimeEnvironment::getInstance()->addExtraObserversPluginsPaths(std::string(Paths));
}


// =====================================================================
// =====================================================================


void ROpenFLUID_ResetExtraObserversPaths()
{
  openfluid::base::RuntimeEnvironment::getInstance()->resetExtraObserversPluginsPaths();
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetObserversPathsCount()
{
  return openfluid::base::RuntimeEnvironment::getInstance()->getObserversPluginsPaths().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetObserversPaths()
{
  std::vector<std::string> ObsPaths = openfluid::base::RuntimeEnvironment::getInstance()->getObserversPluginsPaths();

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
  return openfluid::base::RuntimeEnvironment::getInstance()->getExtraObserversPluginsPaths().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetExtraObserversPaths()
{
  std::vector<std::string> ExtraObsPaths = openfluid::base::RuntimeEnvironment::getInstance()->getExtraObserversPluginsPaths();

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

    openfluid::base::RuntimeEnvironment::getInstance()->setInputDir(std::string(Path));
    Data->FluidXDesc.loadFromDirectory(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir());

    Data->IsSimulationRun = false;

    if (!Data->IsProject)
    {
      Data->IsDataset = true;
      Data->SourcePath = openfluid::base::RuntimeEnvironment::getInstance()->getInputDir();
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
  openfluid::base::RuntimeEnvironment::getInstance()->setOutputDir(std::string(Path));
}


// =====================================================================
// =====================================================================


ROpenFLUID_ExtBlob_t ROpenFLUID_OpenProject(const char* Path)
{
  try
  {

    ROpenFLUID_Init();

    ROpenFLUID_Blob_t* Data = new ROpenFLUID_Blob_t();

    if (openfluid::base::ProjectManager::getInstance()->open(std::string(Path)))
    {
      openfluid::base::RuntimeEnvironment::getInstance()->linkToProject();
      openfluid::base::ProjectManager::getInstance()->updateOutputDir();
    }
    else
      throw openfluid::base::ApplicationException("ROpenFLUID",std::string(Path) + " is not a correct project path");

    Data->IsProject = true;
    Data->SourcePath = openfluid::base::ProjectManager::getInstance()->getPath();

    return ROpenFLUID_OpenDataset(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir().c_str());
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


unsigned short int ROpenFLUID_RunSimulation(ROpenFLUID_ExtBlob_t* BlobHandle)
{

  try
  {

    // ROpenFLUID_Init();

    openfluid::machine::Engine* Engine;


    //UpdateOutputsConfig(BlobHandle);

    ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

    openfluid::base::IOListener IOListen;
    openfluid::machine::SimulationBlob SimBlob;

    openfluid::machine::SimulatorPluginsManager::getInstance()->unloadAllWares();

    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(
        Data->FluidXDesc,
        SimBlob);


    openfluid::machine::MachineListener MachineListen;    
    openfluid::machine::ModelInstance Model(SimBlob,&MachineListen);

    openfluid::machine::Factory::buildModelInstanceFromDescriptor(Data->FluidXDesc.getModelDescriptor(),
        Model);

    openfluid::machine::MonitoringInstance Monitoring(SimBlob);

    openfluid::machine::Factory::buildMonitoringInstanceFromDescriptor(Data->FluidXDesc.getMonitoringDescriptor(),
                                                                       Monitoring);


    Data->OutputDir = openfluid::base::RuntimeEnvironment::getInstance()->getOutputDir();

    Engine = new openfluid::machine::Engine(SimBlob, Model, Monitoring, &MachineListen);

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

  std::map<openfluid::core::UnitClass_t,unsigned int> UnitsInfos;

  std::list<openfluid::fluidx::UnitDescriptor>::iterator bItUnits = Data->FluidXDesc.getDomainDescriptor().getUnits().begin();
  std::list<openfluid::fluidx::UnitDescriptor>::iterator eItUnits = Data->FluidXDesc.getDomainDescriptor().getUnits().end();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator ItUnits = bItUnits;ItUnits != eItUnits;++ItUnits)
  {
    openfluid::core::UnitClass_t ClassName = (*ItUnits).getUnitClass();

    if (UnitsInfos.find(ClassName) == UnitsInfos.end()) UnitsInfos[ClassName] = 0;
    UnitsInfos[ClassName]++;
  }

  Rprintf("Spatial domain is made of %i spatial units\n",Data->FluidXDesc.getDomainDescriptor().getUnits().size());

  for (std::map<openfluid::core::UnitClass_t,unsigned int>::iterator ItUnitsInfos = UnitsInfos.begin();
       ItUnitsInfos != UnitsInfos.end(); ++ItUnitsInfos)
    Rprintf(" - %i units of class %s\n",(*ItUnitsInfos).second,(*ItUnitsInfos).first.c_str());


  // Model

  Rprintf("Model is made of %i simulation items\n",Data->FluidXDesc.getModelDescriptor().getItems().size());

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getModelDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getModelDescriptor().getItems().end(); ++ItModelInfos)
  {
    Rprintf(" - ");

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedSimulator))
    {
      Rprintf("%s simulator\n",((openfluid::fluidx::SimulatorDescriptor*)(*ItModelInfos))->getFileID().c_str());
    }

    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator))
    {
      openfluid::fluidx::GeneratorDescriptor* pGenDesc = ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos));

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Fixed)
        Rprintf("fixed");

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Random)
        Rprintf("random");

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Interp)
        Rprintf("interp");

      if (pGenDesc->getGeneratorMethod() == openfluid::fluidx::GeneratorDescriptor::Inject)
        Rprintf("inject");

      Rprintf(" generator for variable %s on units %s\n",pGenDesc->getVariableName().c_str(),pGenDesc->getUnitClass().c_str());
    }
  }

  // Time period

  Rprintf("Simulation period from %s to %s\n",Data->FluidXDesc.getRunDescriptor().getBeginDate().getAsISOString().c_str(),Data->FluidXDesc.getRunDescriptor().getEndDate().getAsISOString().c_str());

  // Time step

  Rprintf("Simulation time step : %i\n",Data->FluidXDesc.getRunDescriptor().getDeltaT());

}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetSimulationOutputDir(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  return Data->OutputDir.c_str();
}


// =====================================================================
// =====================================================================


int ROpenFLUID_GetDefaultDeltaT(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  return Data->FluidXDesc.getRunDescriptor().getDeltaT();
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetDefaultDeltaT(ROpenFLUID_ExtBlob_t* BlobHandle, int DeltaT)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  Data->FluidXDesc.getRunDescriptor().setDeltaT(DeltaT);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetPeriodBeginDate(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  return Data->FluidXDesc.getRunDescriptor().getBeginDate().getAsString("%Y-%m-%d %H:%M:%S").c_str();
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetPeriodEndDate(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  return Data->FluidXDesc.getRunDescriptor().getEndDate().getAsString("%Y-%m-%d %H:%M:%S").c_str();
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
    Data->FluidXDesc.getRunDescriptor().setBeginDate(DateToSet);

  if (!StrEndDate.empty() && DateToSet.setFromISOString(StrEndDate))
      Data->FluidXDesc.getRunDescriptor().setEndDate(DateToSet);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamValStr("");
  std::string SimIDStr(SimID);
  std::string ParamNameStr(ParamName);

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getModelDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getModelDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedSimulator) &&
        ((openfluid::fluidx::SimulatorDescriptor*)(*ItModelInfos))->getFileID() == SimIDStr)
    {
      openfluid::ware::WareParams_t Params = (*ItModelInfos)->getParameters();
      openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

      if (ItParam != Params.end())
      {
        ParamValStr = (*ItParam).second;
        return ParamValStr.c_str();
      }
    }
  }

  return ParamValStr.c_str();
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName, const char* ParamVal)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string SimIDStr(SimID);
  std::string ParamNameStr(ParamName);
  std::string ParamValStr(ParamVal);

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getModelDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getModelDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedSimulator) &&
        ((openfluid::fluidx::SimulatorDescriptor*)(*ItModelInfos))->getFileID() == SimIDStr)
      (*ItModelInfos)->setParameter(ParamNameStr,ParamValStr);
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveSimulatorParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* SimID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string SimIDStr(SimID);
  std::string ParamNameStr(ParamName);

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getModelDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getModelDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedSimulator) &&
        ((openfluid::fluidx::SimulatorDescriptor*)(*ItModelInfos))->getFileID() == SimIDStr)
      (*ItModelInfos)->eraseParameter(ParamNameStr);
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

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getModelDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getModelDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator) &&
        ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos))->getUnitClass() == UnitClassStr &&
        ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos))->getVariableName() == VarNameStr)
    {
      (*ItModelInfos)->setParameter(ParamNameStr,ParamValStr);
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

  for (openfluid::fluidx::CoupledModelDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getModelDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getModelDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::Generator) &&
        ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos))->getUnitClass() == UnitClassStr &&
        ((openfluid::fluidx::GeneratorDescriptor*)(*ItModelInfos))->getVariableName() == VarNameStr)
    {
      openfluid::ware::WareParams_t Params = (*ItModelInfos)->getParameters();
      openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

      if (ItParam != Params.end())
      {
        ParamValStr = (*ItParam).second;
        return ParamValStr.c_str();
      }

    }
  }
  return ParamValStr.c_str();
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName, const char* ParamVal)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamNameStr(ParamName);
  std::string ParamValStr(ParamVal);

  Data->FluidXDesc.getModelDescriptor().setGlobalParameter(ParamNameStr,ParamValStr);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamNameStr(ParamName);
  std::string ParamValStr("");

  openfluid::ware::WareParams_t Params = Data->FluidXDesc.getModelDescriptor().getGlobalParameters();
  openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

  if (ItParam != Params.end())
  {
    ParamValStr = (*ItParam).second;
    return ParamValStr.c_str();
  }

  return ParamValStr.c_str();
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveModelGlobalParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamNameStr(ParamName);

  Data->FluidXDesc.getModelDescriptor().eraseGlobalParameter(ParamNameStr);
}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetObserverParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ObsID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ParamValStr("");
  std::string ObsIDStr(ObsID);
  std::string ParamNameStr(ParamName);

  for (openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getMonitoringDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getMonitoringDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedObserver) &&
        ((openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos))->getID() == ObsIDStr)
    {
      openfluid::ware::WareParams_t Params = (*ItModelInfos)->getParameters();
      openfluid::ware::WareParams_t::iterator ItParam = Params.find(ParamNameStr);

      if (ItParam != Params.end())
      {
        ParamValStr = (*ItParam).second;
        return ParamValStr.c_str();
      }
    }
  }

  return ParamValStr.c_str();
}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetObserverParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ObsID, const char* ParamName, const char* ParamVal)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ObsIDStr(ObsID);
  std::string ParamNameStr(ParamName);
  std::string ParamValStr(ParamVal);

  for (openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getMonitoringDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getMonitoringDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedObserver) &&
        ((openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos))->getID() == ObsIDStr)
      (*ItModelInfos)->setParameter(ParamNameStr,ParamValStr);
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveObserverParam(ROpenFLUID_ExtBlob_t* BlobHandle, const char* ObsID, const char* ParamName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string ObsIDStr(ObsID);
  std::string ParamNameStr(ParamName);

  for (openfluid::fluidx::MonitoringDescriptor::SetDescription_t::iterator ItModelInfos = Data->FluidXDesc.getMonitoringDescriptor().getItems().begin();
         ItModelInfos != Data->FluidXDesc.getMonitoringDescriptor().getItems().end(); ++ItModelInfos)
  {
    if ((*ItModelInfos)->isType(openfluid::fluidx::ModelItemDescriptor::PluggedObserver) &&
        ((openfluid::fluidx::ObserverDescriptor*)(*ItModelInfos))->getID() == ObsIDStr)
      (*ItModelInfos)->eraseParameter(ParamNameStr);
  }
}


// =====================================================================
// =====================================================================


std::map<openfluid::core::UnitClass_t,unsigned int> GetUnitsCountByClasses(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::map<openfluid::core::UnitClass_t,unsigned int> RetMap;

  std::list<openfluid::fluidx::UnitDescriptor>& Units = Data->FluidXDesc.getDomainDescriptor().getUnits();

  for (std::list<openfluid::fluidx::UnitDescriptor>::iterator ItUnits = Units.begin();ItUnits != Units.end();++ItUnits)
  {
    if (RetMap.find((*ItUnits).getUnitClass()) == RetMap.end()) RetMap[(*ItUnits).getUnitClass()] = 0;
    RetMap[(*ItUnits).getUnitClass()]++;
  }

  return RetMap;
}



// =====================================================================
// =====================================================================


char** ROpenFLUID_GetUnitsClasses(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  std::map<openfluid::core::UnitClass_t,unsigned int> UnitsCountByClasses;
  UnitsCountByClasses = GetUnitsCountByClasses(BlobHandle);

  std::map<openfluid::core::UnitClass_t,unsigned int>::iterator ItUCC;
  const unsigned int Count = UnitsCountByClasses.size();

  char** Classes = (char**)malloc(Count*sizeof(char*));

  unsigned int i=0;
  for (ItUCC=UnitsCountByClasses.begin();ItUCC!=UnitsCountByClasses.end();++ItUCC)
  {
    Classes[i] = (char*)malloc((*ItUCC).first.size()+1);
    std::copy((*ItUCC).first.begin(), (*ItUCC).first.end(), Classes[i]);
    Classes[i][(*ItUCC).first.size()] = '\0';
    i++;
  }

  return Classes;

}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetUnitsClassesCount(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  std::map<openfluid::core::UnitClass_t,unsigned int> UnitsCountByClasses;
  UnitsCountByClasses = GetUnitsCountByClasses(BlobHandle);

  return UnitsCountByClasses.size();
}


// =====================================================================
// =====================================================================


int* ROpenFLUID_GetUnitsIDs(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass)
{
  int Count = ROpenFLUID_GetUnitsIDsCount(BlobHandle,UnitClass);

  int* IDs = NULL;

  if (Count > 0)
  {
    IDs = (int*)malloc(Count*sizeof(int));

    ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

    std::list<openfluid::fluidx::UnitDescriptor>& Units = Data->FluidXDesc.getDomainDescriptor().getUnits();

    unsigned int i=0;
    for (std::list<openfluid::fluidx::UnitDescriptor>::iterator ItUnits = Units.begin();ItUnits != Units.end();++ItUnits)
    {
      if ((*ItUnits).getUnitClass() == std::string(UnitClass))
      {
        IDs[i] = (*ItUnits).getUnitID();
        i++;
      }
    }
  }

  return IDs;
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetUnitsIDsCount(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass)
{
  std::map<openfluid::core::UnitClass_t,unsigned int> UnitsCountByClasses;
  UnitsCountByClasses = GetUnitsCountByClasses(BlobHandle);

  unsigned int Count = 0;

  if (UnitsCountByClasses.find(std::string(UnitClass)) != UnitsCountByClasses.end())
    Count = UnitsCountByClasses[std::string(UnitClass)];

  return Count;
}


// =====================================================================
// =====================================================================


void ROpenFLUID_CreateAttribute(ROpenFLUID_ExtBlob_t* BlobHandle,const char* UnitClass, const char* AttrName, const char* AttrValue)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  std::string AttrNameStr(AttrName);
  std::string AttrValStr(AttrValue);

  std::list<openfluid::fluidx::AttributesDescriptor>& Attrs = Data->FluidXDesc.getDomainDescriptor().getAttributes();

  for (std::list<openfluid::fluidx::AttributesDescriptor>::iterator ItAttr = Attrs.begin();ItAttr != Attrs.end();++ItAttr)
  {
    if ((*ItAttr).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::AttributesDescriptor::UnitIDAttribute_t::iterator ItUnitData = (*ItAttr).getAttributes().begin();

      for (ItUnitData;ItUnitData!=(*ItAttr).getAttributes().end();++ItUnitData)
        (*ItUnitData).second[AttrNameStr] = AttrValStr;
    }
  }

}


// =====================================================================
// =====================================================================


void ROpenFLUID_SetAttribute(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, int UnitID, const char* AttrName, const char* AttrValue)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  std::string AttrNameStr(AttrName);
  std::string AttrValStr(AttrValue);

  std::list<openfluid::fluidx::AttributesDescriptor>& Attrs = Data->FluidXDesc.getDomainDescriptor().getAttributes();

  for (std::list<openfluid::fluidx::AttributesDescriptor>::iterator ItAttr = Attrs.begin();ItAttr != Attrs.end();++ItAttr)
  {
    if ((*ItAttr).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::AttributesDescriptor::UnitIDAttribute_t::iterator ItUnitData = (*ItAttr).getAttributes().find(UnitID);
      if (ItUnitData != (*ItAttr).getAttributes().end())
      {
        if ((*ItUnitData).second.find(AttrNameStr) != (*ItUnitData).second.end())
          (*ItUnitData).second[AttrNameStr] = AttrValStr;
      }
    }
  }

}


// =====================================================================
// =====================================================================


const char* ROpenFLUID_GetAttribute(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, int UnitID, const char* AttrName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  std::string AttrNameStr(AttrName);
  std::string AttrValStr("");

  std::list<openfluid::fluidx::AttributesDescriptor>& Attrs = Data->FluidXDesc.getDomainDescriptor().getAttributes();

  for (std::list<openfluid::fluidx::AttributesDescriptor>::iterator ItAttr = Attrs.begin();ItAttr != Attrs.end();++ItAttr)
  {
    if ((*ItAttr).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::AttributesDescriptor::UnitIDAttribute_t::const_iterator ItUnitData = (*ItAttr).getAttributes().find(UnitID);
      if (ItUnitData != (*ItAttr).getAttributes().end())
      {
        if ((*ItUnitData).second.find(AttrNameStr) != (*ItUnitData).second.end())
          return ((*ItUnitData).second.at(AttrNameStr).c_str());
      }
    }
  }

  return "";
}


// =====================================================================
// =====================================================================


void ROpenFLUID_RemoveAttribute(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass, const char* AttrName)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  std::string AttrNameStr(AttrName);

  std::list<openfluid::fluidx::AttributesDescriptor>& Attrs = Data->FluidXDesc.getDomainDescriptor().getAttributes();

  for (std::list<openfluid::fluidx::AttributesDescriptor>::iterator ItAttr = Attrs.begin();ItAttr != Attrs.end();++ItAttr)
  {
    if ((*ItAttr).getUnitsClass() == UnitClassStr)
    {
      openfluid::fluidx::AttributesDescriptor::UnitIDAttribute_t::iterator ItUnitData = (*ItAttr).getAttributes().begin();

      for (ItUnitData;ItUnitData!=(*ItAttr).getAttributes().end();++ItUnitData)
        (*ItUnitData).second.erase(AttrNameStr);
    }
  }
}


// =====================================================================
// =====================================================================


void ROpenFLUID_AddVariablesExportAsCSV(ROpenFLUID_ExtBlob_t* BlobHandle, const char* UnitClass)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  std::string UnitClassStr(UnitClass);
  openfluid::fluidx::AdvancedMonitoringDescriptor AdvMonDesc(Data->FluidXDesc.getMonitoringDescriptor());

  // 1. add CSV observer if not present

  try
  {
    AdvMonDesc.getDescriptor("export.vars.files.csv");
  }
  catch (openfluid::base::Exception& E)
  {
    AdvMonDesc.addToObserverList("export.vars.files.csv");
  }

  // 2. add ropenfluid format
  AdvMonDesc.getDescriptor("export.vars.files.csv").setParameter("format.ropenfluid.header",openfluid::core::StringValue("colnames-as-data"));
  AdvMonDesc.getDescriptor("export.vars.files.csv").setParameter("format.ropenfluid.date",openfluid::core::StringValue("%Y%m%d-%H%M%S"));
  AdvMonDesc.getDescriptor("export.vars.files.csv").setParameter("format.ropenfluid.colsep",openfluid::core::StringValue(" "));

  // 3. add ropenfluidUnitClass output set
  AdvMonDesc.getDescriptor("export.vars.files.csv").setParameter("set.ropenfluid"+UnitClassStr+".unitclass",openfluid::core::StringValue(UnitClassStr));
  AdvMonDesc.getDescriptor("export.vars.files.csv").setParameter("set.ropenfluid"+UnitClassStr+".unitsIDs",openfluid::core::StringValue("*"));
  AdvMonDesc.getDescriptor("export.vars.files.csv").setParameter("set.ropenfluid"+UnitClassStr+".vars",openfluid::core::StringValue("*"));
  AdvMonDesc.getDescriptor("export.vars.files.csv").setParameter("set.ropenfluid"+UnitClassStr+".format",openfluid::core::StringValue("ropenfluid"));
}
