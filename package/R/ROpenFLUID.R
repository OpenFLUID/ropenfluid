##
#  This file is part of OpenFLUID software
#  Copyright (c) 2007-2010 INRA-Montpellier SupAgro
#
#
# == GNU General Public License Usage ==
#
#  OpenFLUID is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  OpenFLUID is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.
#
#  In addition, as a special exception, INRA gives You the additional right
#  to dynamically link the code of OpenFLUID with code not covered
#  under the GNU General Public License ("Non-GPL Code") and to distribute
#  linked combinations including the two, subject to the limitations in this
#  paragraph. Non-GPL Code permitted under this exception must only link to
#  the code of OpenFLUID dynamically through the OpenFLUID libraries
#  interfaces, and only for building OpenFLUID plugins. The files of
#  Non-GPL Code may be link to the OpenFLUID libraries without causing the
#  resulting work to be covered by the GNU General Public License. You must
#  obey the GNU General Public License in all respects for all of the
#  OpenFLUID code and other code used in conjunction with OpenFLUID
#  except the Non-GPL Code covered by this exception. If you modify
#  this OpenFLUID, you may extend this exception to your version of the file,
#  but you are not obligated to do so. If you do not wish to provide this
#  exception without modification, you must delete this exception statement
#  from your version and license this OpenFLUID solely under the GPL without
#  exception.
#
#
# == Other Usage ==
#
#  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
#  license, and requires a written agreement between You and INRA.
#  Licensees for Other Usage of OpenFLUID may use this file in accordance
#  with the terms contained in the written agreement between You and INRA.
##



.First.lib <- function(lib, pkg)
{
  library.dynam("ROpenFLUID", pkg, lib)
}


# =====================================================================
# =====================================================================


OpenFLUID.dummy <- function(msg)
{
  stopifnot(is.character(msg))
  
  .Call("Dummy", msg, PACKAGE="ROpenFLUID")
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


OpenFLUID.getVersion <- function()
{  
  .Call("GetVersion",PACKAGE="ROpenFLUID")  
}


# =====================================================================
# =====================================================================

OpenFLUID.getSimulationInfo <- function(ofblob)
{
  stopifnot(!is.null(ofblob))
  
  .Call("GetSimulationInfo", ofblob, PACKAGE="ROpenFLUID")
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


OpenFLUID.addExtraFunctionsPaths <- function(paths)
{
  stopifnot(is.character(paths))
  
  .Call("AddExtraFunctionsPaths", paths, PACKAGE="ROpenFLUID")  

  return(invisible(NULL))
}
  

# =====================================================================
# =====================================================================


OpenFLUID.getExtraFunctionsPaths <- function()
{
  .Call("GetFunctionsPaths",PACKAGE="ROpenFLUID")  
}


# =====================================================================
# =====================================================================


OpenFLUID.runProject <- function(path)
{
  stopifnot(is.character(path))
  
  ret <- .Call("RunProject", path, PACKAGE="ROpenFLUID")
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.newProject <- function()
{ 
  ret <- .Call("NewProject", PACKAGE="ROpenFLUID")
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.openProject <- function(path)
{
  stopifnot(is.character(path))
  
  ret <- .Call("OpenProject", path, PACKAGE="ROpenFLUID")
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.openDataset <- function(path)
{
  stopifnot(is.character(path))
  
  ret <- .Call("OpenDataset", path, PACKAGE="ROpenFLUID")
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.setOutputDir <- function(path)
{
  stopifnot(is.character(path))
  
  .Call("SetOutputDir", path, PACKAGE="ROpenFLUID")  

  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


OpenFLUID.saveProject <- function(ofblob)
{
  stopifnot(!is.null(ofblob))  
  
  stop("under construction")
}


# =====================================================================
# =====================================================================


OpenFLUID.saveProjectAs <- function(ofblob,path)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(path))
  
  stop("under construction")
}


# =====================================================================
# =====================================================================


OpenFLUID.runSimulation <- function(ofblob)
{
  stopifnot(!is.null(ofblob))
  
  ret <- .Call("RunSimulation", ofblob, PACKAGE="ROpenFLUID")
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.setFunctionParam <- function(ofblob,funcid,paramname,paramval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(funcid))
  stopifnot(is.character(paramname))
  stopifnot(is.character(paramval))
  
  .Call("SetFunctionParam", ofblob, funcid, paramname, paramval, PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


OpenFLUID.getFunctionParam <- function(ofblob,funcid,paramname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(funcid))
  stopifnot(is.character(paramname))
  
  ret <- .Call("GetFunctionParam", ofblob, funcid, paramname, PACKAGE="ROpenFLUID")  
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.setGeneratorParam <- function(ofblob,unitclass,varname,paramname,paramval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.character(varname))
  stopifnot(is.character(paramname))
  stopifnot(is.character(paramval))
  
  .Call("SetGeneratorParam", ofblob, unitclass, varname, paramname, paramval, PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


OpenFLUID.getGeneratorParam <- function(ofblob,unitclass,varname,paramname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.character(varname))
  stopifnot(is.character(paramname))
  
  ret <- .Call("GetGeneratorParam", ofblob, unitclass, varname, paramname, PACKAGE="ROpenFLUID")  
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.setInputData <- function(ofblob,unitclass,unitid,idataname,idataval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.integer(unitid))
  stopifnot(is.character(idataname))
  stopifnot(is.character(idataval))  
  
  .Call("SetInputData", ofblob, unitclass, unitid, idataname, idataval, PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


OpenFLUID.getInputData <- function(ofblob,unitclass,unitid,idataname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.integer(unitid))
  stopifnot(is.character(idataname))
  
  ret <- .Call("GetInputData", ofblob, unitclass, unitid, idataname, PACKAGE="ROpenFLUID")  
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.createInputData <- function(ofblob,unitclass,idataname,idataval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.character(idataname))
  stopifnot(is.character(idataval))  
  
  .Call("CreateInputData", ofblob, unitclass, idataname, idataval, PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}

# =====================================================================
# =====================================================================


OpenFLUID.setDeltaT <- function(ofblob,deltat)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.integer(deltat))  
  stopifnot(deltat > 0)
  
  .Call("SetDeltaT", ofblob, deltat, PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


OpenFLUID.getDeltaT <- function(ofblob)
{
  stopifnot(!is.null(ofblob))  
  
  ret <- .Call("GetDeltaT", ofblob, PACKAGE="ROpenFLUID")  
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


OpenFLUID.loadResult <- function(ofblob,unitclass,unitid,suffix)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.integer(unitid))
  stopifnot(is.character(suffix))
  
	stop("under construction")
}
