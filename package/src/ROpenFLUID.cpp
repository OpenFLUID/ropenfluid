/*
  This file is part of OpenFLUID software
  Copyright (c) 2007-2010 INRA-Montpellier SupAgro


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
  along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, INRA gives You the additional right
  to dynamically link the code of OpenFLUID with code not covered
  under the GNU General Public License ("Non-GPL Code") and to distribute
  linked combinations including the two, subject to the limitations in this
  paragraph. Non-GPL Code permitted under this exception must only link to
  the code of OpenFLUID dynamically through the OpenFLUID libraries
  interfaces, and only for building OpenFLUID plugins. The files of
  Non-GPL Code may be link to the OpenFLUID libraries without causing the
  resulting work to be covered by the GNU General Public License. You must
  obey the GNU General Public License in all respects for all of the
  OpenFLUID code and other code used in conjunction with OpenFLUID
  except the Non-GPL Code covered by this exception. If you modify
  this OpenFLUID, you may extend this exception to your version of the file,
  but you are not obligated to do so. If you do not wish to provide this
  exception without modification, you must delete this exception statement
  from your version and license this OpenFLUID solely under the GPL without
  exception.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
*/

#include <iostream>
#include <openfluid/base.hpp>
#include <openfluid/machine.hpp>
#include <openfluid/io.hpp>


#include "ROpenFLUID.h"

/*
struct ROpenFLUID_Blob_t
{
  openfluid::machine::SimulationBlob SBlob;
  openfluid::machine::MachineListener MachineListen;
  openfluid::machine::ModelInstance Model;


  ROpenFLUID_Blob_t()
    : Model(SBlob,&MachineListen)
  {

  }

};
*/


struct ROpenFLUID_Blob_t
{

  openfluid::base::DatastoreDescriptor DataStoreDesc;
  openfluid::base::DomainDescriptor DomainDesc;
  openfluid::base::ModelDescriptor ModelDesc;
  openfluid::base::RunDescriptor RunDesc;
  openfluid::base::OutputDescriptor OutDesc;

  bool IsProject;
  bool IsDataset;

  std::string SourcePath;

  bool IsSimulationRun;

  ROpenFLUID_Blob_t():
    IsProject(false),IsDataset(false),SourcePath(""),
    IsSimulationRun(false)
  {

  }

};


std::string LastErrorMsg = "";


// =====================================================================
// =====================================================================



void ROpenFLUID_Init()
{
  openfluid::base::Init();
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


void ROpenFLUID_AddExtraFunctionsPaths(const char* Paths)
{
  openfluid::base::Init();

  openfluid::base::RuntimeEnvironment::getInstance()->addExtraPluginsPaths(std::string(Paths));
}


// =====================================================================
// =====================================================================


unsigned int ROpenFLUID_GetFunctionsPathsCount()
{
  return openfluid::base::RuntimeEnvironment::getInstance()->getPluginsPaths().size();
}


// =====================================================================
// =====================================================================


char** ROpenFLUID_GetFunctionsPaths()
{
  std::vector<std::string> FuncsPaths = openfluid::base::RuntimeEnvironment::getInstance()->getPluginsPaths();

  const unsigned int Count = FuncsPaths.size();

  char** Paths = (char**)malloc(Count*sizeof(char*));

  for (unsigned int i=0;i<Count;i++)
  {
    Paths[i] = (char*)malloc(FuncsPaths[i].size()+1);
    std::copy(FuncsPaths[i].begin(), FuncsPaths[i].end(), Paths[i]);
    Paths[i][FuncsPaths[i].size()] = '\0';
  }

  return Paths;
}


// =====================================================================
// =====================================================================



void ROpenFLUID_UpdateOutputsConfig(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t*  Blob(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

  // TODO TO BE CONTINUED

}


// =====================================================================
// =====================================================================


ROpenFLUID_ExtBlob_t ROpenFLUID_RunProject(const char* Path)
{

  try
  {
    /*
    openfluid::base::Init();

    openfluid::io::IOListener IOListen;

    if (openfluid::base::ProjectManager::getInstance()->open(std::string(Path)))
    {
      openfluid::base::RuntimeEnvironment::getInstance()->linkToProject();
      openfluid::base::ProjectManager::getInstance()->updateOutputDir();
    }
    else
      throw openfluid::base::OFException("ROpenFLUID",std::string(Path) + " is not a correct project path");

    return ROpenFLUID_RunSimulation(reinterpret_cast<ROpenFLUID_Blob_t*>(ROpenFLUID_OpenDataset(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir().c_str())));
    */
    return NULL;
  }
  catch (openfluid::base::OFException& E)
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

    openfluid::base::Init();


    openfluid::io::IOListener IOListen;
    openfluid::io::FluidXReader FXReader(&IOListen);


    openfluid::base::RuntimeEnvironment::getInstance()->setInputDir(std::string(Path));
    FXReader.loadFromDirectory(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir());

    Data->IsSimulationRun = false;

    Data->DomainDesc = FXReader.getDomainDescriptor();
    Data->ModelDesc = FXReader.getModelDescriptor();
    Data->DataStoreDesc = FXReader.getDatstoreDescriptor();
    Data->OutDesc = FXReader.getOutputDescriptor();
    Data->RunDesc = FXReader.getRunDescriptor();

    if (!Data->IsProject)
    {
      Data->IsDataset = true;
      Data->SourcePath = openfluid::base::RuntimeEnvironment::getInstance()->getInputDir();
    }


    return Data;
  }
  catch (openfluid::base::OFException& E)
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


void ROpenFLUID_SetOutputDir(const char* Path)
{
  openfluid::base::RuntimeEnvironment::getInstance()->setOutputDir(std::string(Path));
}


// =====================================================================
// =====================================================================


ROpenFLUID_ExtBlob_t ROpenFLUID_OpenProject(const char* Path)
{
  try
  {

    openfluid::base::Init();

    ROpenFLUID_Blob_t* Data = new ROpenFLUID_Blob_t();

    openfluid::io::IOListener IOListen;


    if (openfluid::base::ProjectManager::getInstance()->open(std::string(Path)))
    {
      openfluid::base::RuntimeEnvironment::getInstance()->linkToProject();
      openfluid::base::ProjectManager::getInstance()->updateOutputDir();
    }
    else
      throw openfluid::base::OFException("ROpenFLUID",std::string(Path) + " is not a correct project path");

    Data->IsProject = true;
    Data->SourcePath = openfluid::base::ProjectManager::getInstance()->getPath();

    return ROpenFLUID_OpenDataset(openfluid::base::RuntimeEnvironment::getInstance()->getInputDir().c_str());
  }
  catch (openfluid::base::OFException& E)
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


ROpenFLUID_ExtBlob_t ROpenFLUID_RunSimulation(ROpenFLUID_ExtBlob_t* BlobHandle)
{

  try
  {

    openfluid::base::Init();

    openfluid::machine::Engine* Engine;
    ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));

    openfluid::io::IOListener IOListen;
    openfluid::machine::SimulationBlob SimBlob;

    openfluid::machine::PluginManager::getInstance()->unloadAllPlugins();


    openfluid::machine::Factory::buildSimulationBlobFromDescriptors(
        Data->DomainDesc,
        Data->RunDesc,
        Data->OutDesc,
        Data->DataStoreDesc,
        SimBlob);


    openfluid::machine::MachineListener MachineListen;
    openfluid::machine::ModelInstance Model(SimBlob,&MachineListen);

    openfluid::machine::Factory::buildModelInstanceFromDescriptor(Data->ModelDesc,
        Model);


    Engine = new openfluid::machine::Engine(SimBlob, Model, &MachineListen, &IOListen);

    Engine->initialize();

    Engine->initParams();
    Engine->prepareData();
    Engine->checkConsistency();
    Engine->run();
    Engine->saveReports();

    Engine->finalize();

    delete Engine;

    Data->IsSimulationRun = true;

    return Data;
  }
  catch (openfluid::base::OFException& E)
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


void ROpenFLUID_GetSimulationInfo(ROpenFLUID_ExtBlob_t* BlobHandle)
{
  ROpenFLUID_Blob_t* Data(reinterpret_cast<ROpenFLUID_Blob_t*>(BlobHandle));


  // Spatial domain

  std::map<openfluid::core::UnitClass_t,unsigned int> UnitsInfos;

  std::list<openfluid::base::UnitDescriptor>::iterator bItUnits = Data->DomainDesc.getUnits().begin();
  std::list<openfluid::base::UnitDescriptor>::iterator eItUnits = Data->DomainDesc.getUnits().end();

  for (std::list<openfluid::base::UnitDescriptor>::iterator ItUnits = bItUnits;ItUnits != eItUnits;++ItUnits)
  {
    openfluid::core::UnitClass_t ClassName = (*ItUnits).getUnitClass();

    if (UnitsInfos.find(ClassName) == UnitsInfos.end()) UnitsInfos[ClassName] = 0;
    UnitsInfos[ClassName]++;
  }

  std::cout << "Spatial domain is made of " << Data->DomainDesc.getUnits().size() << " spatial units " << std::endl;

  for (std::map<openfluid::core::UnitClass_t,unsigned int>::iterator ItUnitsInfos = UnitsInfos.begin();
       ItUnitsInfos != UnitsInfos.end(); ++ItUnitsInfos)
    std::cout << " - " << (*ItUnitsInfos).second << " units of class " << (*ItUnitsInfos).first << std::endl;


  // Model

  std::cout << "Model is made of " << Data->ModelDesc.getItems().size() << " simulation items " << std::endl;

  for (openfluid::base::ModelDescriptor::ModelDescription_t::iterator ItModelInfos = Data->ModelDesc.getItems().begin();
         ItModelInfos != Data->ModelDesc.getItems().end(); ++ItModelInfos)
  {
    std::cout << " - ";

    if ((*ItModelInfos)->isType(openfluid::base::ModelItemDescriptor::PluggedFunction))
    {
      std::cout << ((openfluid::base::FunctionDescriptor*)(*ItModelInfos))->getFileID() << " simulation function" << std::endl;
    }

    if ((*ItModelInfos)->isType(openfluid::base::ModelItemDescriptor::Generator))
    {
      openfluid::base::GeneratorDescriptor* pGenDesc = ((openfluid::base::GeneratorDescriptor*)(*ItModelInfos));

      if (pGenDesc->getGeneratorMethod() == openfluid::base::GeneratorDescriptor::Fixed)
        std::cout << "fixed";

      if (pGenDesc->getGeneratorMethod() == openfluid::base::GeneratorDescriptor::Random)
        std::cout << "random";

      if (pGenDesc->getGeneratorMethod() == openfluid::base::GeneratorDescriptor::Interp)
        std::cout << "interp";

      if (pGenDesc->getGeneratorMethod() == openfluid::base::GeneratorDescriptor::Inject)
        std::cout << "inject";

      std::cout << " generator for variable " << pGenDesc->getVariableName() << " on units " << pGenDesc->getUnitClass() << std::endl;
    }
  }

  // Time period

  std::cout << "Simulation period from " << Data->RunDesc.getBeginDate().getAsISOString()
            << " to " << Data->RunDesc.getEndDate().getAsISOString() << std::endl;

  // Time step

  std::cout << "Simulation time step : " << Data->RunDesc.getDeltaT() << std::endl;

}
