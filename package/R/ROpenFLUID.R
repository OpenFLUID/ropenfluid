##
#
#  This file is part of OpenFLUID software
#  Copyright(c) 2007, INRA - Montpellier SupAgro
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
#  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.
#
#
# == Other Usage ==

#  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
#  license, and requires a written agreement between You and INRA.
#  Licensees for Other Usage of OpenFLUID may use this file in accordance
#  with the terms contained in the written agreement between You and INRA.
#  
##





.First.lib <- function(lib, pkg)
{  
  library.dynam("ROpenFLUID", pkg, lib)
}


# =====================================================================
# =====================================================================

#' Adds paths to search for simulators
#' 
#' @param paths the semicolon separated paths to add
#' 
#' @examples \dontrun{
#' OpenFLUID.addExtraSimulatorsPaths("/first/path/to/add")
#' OpenFLUID.addExtraSimulatorsPaths("/second/path/to/add:/third/path/to/add")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getExtraSimulatorsPaths}}
OpenFLUID.addExtraSimulatorsPaths <- function(paths)
{
  stopifnot(is.character(paths))
  
  .Call("AddExtraSimulatorsPaths", paths, PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================

#' Adds export of simulation variables as CSV files for a given units class
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the units class to add for simulation variables export
#' 
#' @examples \dontrun{
#' OpenFLUID.addVariablesExportAsCSV("TU")
#' OpenFLUID.addVariablesExportAsCSV("RS")
#' }
#'
#' @seealso \code{\link{OpenFLUID.loadResult}}
OpenFLUID.addVariablesExportAsCSV <- function(ofblob,unitclass)
{
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitclass))
  
  .Call("AddVariablesExportAsCSV", ofblob, unitclass, PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Creates an attribute for all spatial units of a class, initialized with a default value
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the unit class
#' @param attrname the attribute name
#' @param attrval the default attribute value for alla units
#' 
#' @examples \dontrun{
#' OpenFLUID.createAttribute(ofsim,"SU","area",1.0)
#' OpenFLUID.createAttribute(ofsim,"SU","code","NONE")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getAttribute}}
#' @seealso \code{\link{OpenFLUID.setAttribute}}
OpenFLUID.createAttribute <- function(ofblob,unitclass,attrname,attrval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.character(attrname))  
  
  .Call("CreateAttribute", ofblob, unitclass, attrname, as.character(attrval), PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Returns the simulation time step
#' 
#' @param ofblob the simulation definition blob
#' @return the time step value in seconds
#' 
#' @examples \dontrun{
#' deltat = OpenFLUID.getDeltaT(ofsim)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.setDeltaT}}
OpenFLUID.getDeltaT <- function(ofblob)
{
  stopifnot(!is.null(ofblob))  
  
  ret <- .Call("GetDeltaT", ofblob, PACKAGE="ROpenFLUID")  
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


#' Returns the added paths to search for simulators
#' 
#' @return a vector of paths
#' 
#' @examples \dontrun{
#' paths = OpenFLUID.getExtraSimulatorsPaths()
#' }
#' 
#' @seealso \code{\link{OpenFLUID.addExtraSimulatorsPaths}}
OpenFLUID.getExtraSimulatorsPaths <- function()
{
  .Call("GetSimulatorsPaths",PACKAGE="ROpenFLUID")  
}


# =====================================================================
# =====================================================================


#' Returns a simulator parameter value
#' 
#' @param ofblob the simulation definition blob
#' @param simid the simulator ID
#' @param paramname the name of the parameter
#' @return the parameter value
#' 
#' @examples \dontrun{
#' val = OpenFLUID.getSimulatorParam(ofsim,"my.simulator","coeff")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.setSimulatorParam}}
OpenFLUID.getSimulatorParam <- function(ofblob,simid,paramname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(simid))
  stopifnot(is.character(paramname))
  
  .Call("GetSimulatorParam", ofblob, simid, paramname, PACKAGE="ROpenFLUID")  
}


# =====================================================================
# =====================================================================


#' Returns a generator parameter value
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the unit class to which the generator is applied
#' @param varname the variable name to which the generator is applied
#' @param paramname the name of the parameter
#' @return the parameter value
#' 
#' @examples \dontrun{
#' val = OpenFLUID.getGeneratorParam(ofsim,"SU","var.flux","fixedvalue")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.setGeneratorParam}}
OpenFLUID.getGeneratorParam <- function(ofblob,unitclass,varname,paramname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.character(varname))
  stopifnot(is.character(paramname))
  
  .Call("GetGeneratorParam", ofblob, unitclass, varname, paramname, PACKAGE="ROpenFLUID")    
}


# =====================================================================
# =====================================================================


#' Returns an attribute value for a given spatial unit
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the unit class
#' @param unitid the unit ID
#' @param attrname the name of the attribute
#' @return the attribute value
#' 
#' @examples \dontrun{
#' val = OpenFLUID.getAttribute(ofsim,"SU",18,"length")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.createAttribute}}
#' @seealso \code{\link{OpenFLUID.setAttribute}}
OpenFLUID.getAttribute <- function(ofblob,unitclass,unitid,attrname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.numeric(unitid))
  stopifnot(is.character(attrname))
  
  ret <- .Call("GetAttribute", ofblob, unitclass, as.integer(unitid), attrname, PACKAGE="ROpenFLUID")  
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


#' Returns a model global parameter value
#' 
#' @param ofblob the simulation definition blob
#' @param paramname the name of the parameter
#' @return the parameter value
#' 
#' @examples \dontrun{
#' val = OpenFLUID.getModelGlobalParam(ofsim,"gvalue")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.setModelGlobalParam}}
OpenFLUID.getModelGlobalParam <- function(ofblob,paramname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(paramname))
  
  .Call("GetModelGlobalParam", ofblob, paramname, PACKAGE="ROpenFLUID")    
}


# =====================================================================
# =====================================================================


#' Returns the simulation period begin date
#' 
#' @param ofblob the simulation definition blob
#' @return the begin date as an ISO datetime string (\%Y-\%m-\%d \%H:\%M:\%S)
#' 
#' @examples \dontrun{
#' bdate = OpenFLUID.getPeriodBeginDate(ofsim)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.setPeriodBeginDate}}
#' @seealso \code{\link{OpenFLUID.getPeriodEndDate}}
#' @seealso \code{\link{OpenFLUID.setPeriodEndDate}}
OpenFLUID.getPeriodBeginDate <- function(ofblob)
{
  stopifnot(!is.null(ofblob))  
  
  .Call("GetPeriodBeginDate", ofblob, PACKAGE="ROpenFLUID")
}


# =====================================================================
# =====================================================================


#' Returns the existing units classes
#' 
#' @param ofblob the simulation definition blob
#' @return a vector of units classes
#' 
#' @examples \dontrun{
#' cls = OpenFLUID.getUnitsClasses(ofsim)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getUnitsIDs}}
OpenFLUID.getUnitsClasses <- function(ofblob)
{
  stopifnot(!is.null(ofblob))  
  
  .Call("GetUnitsClasses", ofblob, PACKAGE="ROpenFLUID")
}


# =====================================================================
# =====================================================================


#' Returns the existing units IDs for a given units class
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the units class
#' @return a vector of units IDs
#' 
#' @examples \dontrun{
#' ids = OpenFLUID.getUnitsIDs(ofsim,"SU")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getUnitsClasses}}
OpenFLUID.getUnitsIDs <- function(ofblob,unitclass)
{
  stopifnot(!is.null(ofblob))  
  
  .Call("GetUnitsIDs", ofblob, unitclass, PACKAGE="ROpenFLUID")
}


# =====================================================================
# =====================================================================


#' Returns the simulation period end date
#' 
#' @param ofblob the simulation definition blob
#' @return the end date as an ISO datetime string (\%Y-\%m-\%d \%H:\%M:\%S)
#' 
#' @examples \dontrun{
#' edate = OpenFLUID.getPeriodEndDate(ofsim)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.setPeriodEndDate}}
#' @seealso \code{\link{OpenFLUID.getPeriodBeginDate}}
#' @seealso \code{\link{OpenFLUID.setPeriodBeginDate}}
OpenFLUID.getPeriodEndDate <- function(ofblob)
{
  stopifnot(!is.null(ofblob))  
  
  .Call("GetPeriodEndDate", ofblob, PACKAGE="ROpenFLUID")
}


# =====================================================================
# =====================================================================


#' Returns the OpenFLUID version
#' 
#' @return the OpenFLUID version number
#' 
#' @examples \dontrun{
#' v = OpenFLUID.getVersion()
#' }
OpenFLUID.getVersion <- function()
{  
  .Call("GetVersion",PACKAGE="ROpenFLUID")  
}


# =====================================================================
# =====================================================================


#' Loads results as a dataframe, giving dataset informations
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the unit class
#' @param unitid the unit ID
#' @param varname the variable name
#' @return a dataframe containing the simulation results
#' 
#' @examples \dontrun{
#' resSU18 = OpenFLUID.loadResult(ofsim,"SU",18,"runoff")
#' resRS1 = OpenFLUID.loadResult(ofsim,"RS",1,"waterlevel")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.loadResultFile}}
OpenFLUID.loadResult <- function(ofblob,unitclass,unitid,varname)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.numeric(unitid))
  stopifnot(is.character(varname))
  
  filename = .Call("GetSimulationOutputDir", ofblob, PACKAGE="ROpenFLUID")
  
  filename = paste(filename,"ropenfluid",sep="/")
  filename = paste(filename,unitclass,sep="")
  filename = paste(filename,unitclass,sep="_")
  filename = paste(filename,as.integer(unitid),sep="")
  filename = paste(filename,varname,sep="_")
  filename = paste(filename,".csv",sep="")
  
  return(OpenFLUID.loadResultFile(filename))
}


# =====================================================================
# =====================================================================


#' Loads results as a dataframe, giving output file name
#' 
#' @param filepath the full path of file to load
#' @return a dataframe containing the simulation results
#' 
#' @examples \dontrun{
#' resSU18 = OpenFLUID.loadResultFile("/path/to/output/SU18_full.out")
#' resRS1 = OpenFLUID.loadResultFile("/path/to/output/RS1_waterlevel.out")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.loadResult}}
OpenFLUID.loadResultFile <- function(filepath)
{
  stopifnot(is.character(filepath))
  
  data = read.csv(file=filepath,head=TRUE,sep=" ",stringsAsFactors=F)
  data$datetime = as.POSIXct(data$datetime,format="%Y%m%d-%H%M%S",tz="UTC")
  
  return(data)
}



# =====================================================================
# =====================================================================


#OpenFLUID.newProject <- function()
#{ 
#  ret <- .Call("NewProject", PACKAGE="ROpenFLUID")
#  
#  stopifnot(!is.null(ret))
#  
#  return(ret)
#}


# =====================================================================
# =====================================================================


#' Opens a dataset and returns a simulation definition blob
#' 
#' @param path the full path of the dataset to open
#' @return a simulation definition blob
#' 
#' @examples \dontrun{
#' ofsim = OpenFLUID.openDataset("/path/to/dataset")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.openProject}}
#' @seealso \code{\link{OpenFLUID.runSimulation}}
OpenFLUID.openDataset <- function(path)
{
  stopifnot(is.character(path))
  
  ret <- .Call("OpenDataset", path, PACKAGE="ROpenFLUID")
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================


#' Opens a project and returns a simulation definition blob
#' 
#' @param path the full project to open
#' @return a simulation definition blob
#' 
#' @examples \dontrun{
#' ofsim = OpenFLUID.openProject("/path/to/project")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.openDataset}}
#' @seealso \code{\link{OpenFLUID.runProject}}
OpenFLUID.openProject <- function(path)
{
  stopifnot(is.character(path))
  
  ret <- .Call("OpenProject", path, PACKAGE="ROpenFLUID")
  
  stopifnot(!is.null(ret))
  
  return(ret)
}


# =====================================================================
# =====================================================================

#' Prints informations to screen about simulation definition blob
#' 
#' @param ofblob the simulation definition blob
#' 
#' @examples \dontrun{
#' OpenFLUID.printSimulationInfo(ofsim)
#' }
OpenFLUID.printSimulationInfo <- function(ofblob)
{
  stopifnot(!is.null(ofblob))
  
  .Call("PrintSimulationInfo", ofblob, PACKAGE="ROpenFLUID")
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Runs a project and returns a simulation definition blob
#' 
#' @param path the full path of the dataset to open
#' @return a simulation definition blob
#' 
#' @examples \dontrun{
#' ofsim = OpenFLUID.runProject("/path/to/dataset")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.runSimulation}}
#' @seealso \code{\link{OpenFLUID.openProject}}
OpenFLUID.runProject <- function(path)
{
  stopifnot(is.character(path))
  
  ofdata = OpenFLUID.openProject(path)
  
  OpenFLUID.runSimulation(ofdata)  
  
  return(ofdata)
}


# =====================================================================
# =====================================================================


#' Runs a simulation from a simulation definition blob
#' 
#' @param ofblob the simulation definition blob
#' 
#' @examples \dontrun{
#' OpenFLUID.runSimulation(ofsim)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.runProject}}
#' @seealso \code{\link{OpenFLUID.openProject}}
#' @seealso \code{\link{OpenFLUID.openDataset}}
OpenFLUID.runSimulation <- function(ofblob)
{
  stopifnot(!is.null(ofblob))
  
  .Call("RunSimulation", ofblob, PACKAGE="ROpenFLUID")
  
  return(invisible(NULL))  
}


# =====================================================================
# =====================================================================


#' Sets the current output directory for simulations
#' 
#' @param path the output directory path
#' 
#' @examples \dontrun{
#' OpenFLUID.setCurrentOutputDir("/path/to/output")
#' }
OpenFLUID.setCurrentOutputDir <- function(path)
{
  stopifnot(is.character(path))
  
  .Call("SetCurrentOutputDir", path, PACKAGE="ROpenFLUID")  

  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Sets the simulation time step
#' 
#' @param ofblob the simulation definition blob
#' @param deltat the time step value in seconds
#' 
#' @examples \dontrun{
#' OpenFLUID.setDeltaT(60)
#' OpenFLUID.setDeltaT(86400) 
#' }
#'
#' @seealso \code{\link{OpenFLUID.getDeltaT}}
OpenFLUID.setDeltaT <- function(ofblob,deltat)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.numeric(deltat))  
  stopifnot(deltat > 0)
  
  .Call("SetDeltaT", ofblob, as.integer(deltat), PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Sets a simulator parameter value
#' 
#' @param ofblob the simulation definition blob
#' @param simid the simulation simulator id
#' @param paramname the name of the parameter
#' @param paramval the parameter value
#' 
#' @examples \dontrun{
#' OpenFLUID.setSimulatorParam(ofsim,"my.simulator","coeff",3)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getSimulatorParam}}
OpenFLUID.setSimulatorParam <- function(ofblob,simid,paramname,paramval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(simid))
  stopifnot(is.character(paramname))
  
  
  .Call("SetSimulatorParam", ofblob, simid, paramname, as.character(paramval), PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Sets a generator parameter value
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the unit class to which the generator is applied
#' @param varname the variable name to which the generator is applied
#' @param paramname the name of the parameter
#' @param paramval the value of the parameter
#' 
#' @examples \dontrun{
#' OpenFLUID.setGeneratorParam(ofsim,"SU","var.flux","fixedvalue",12.3)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getGeneratorParam}}
OpenFLUID.setGeneratorParam <- function(ofblob,unitclass,varname,paramname,paramval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.character(varname))
  stopifnot(is.character(paramname))

  .Call("SetGeneratorParam", ofblob, unitclass, varname, paramname, as.character(paramval), PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Sets an attribute value for a given spatial unit
#' 
#' @param ofblob the simulation definition blob
#' @param unitclass the unit class
#' @param unitid the unit ID
#' @param attrname the name of the attribute
#' @param attrval the value of the attribute
#' 
#' @examples \dontrun{
#' OpenFLUID.setAttribute(ofsim,"SU",18,"length",12.3)
#' OpenFLUID.setAttribute(ofsim,"SU",18,"CODE","ABC")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.createAttribute}}
#' @seealso \code{\link{OpenFLUID.getAttribute}}
OpenFLUID.setAttribute <- function(ofblob,unitclass,unitid,attrname,attrval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(unitclass))
  stopifnot(is.numeric(unitid))
  stopifnot(is.character(attrname))    
  
  .Call("SetAttribute", ofblob, unitclass, as.integer(unitid), attrname, as.character(attrval), PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Sets a model global parameter value
#' 
#' @param ofblob the simulation definition blob
#' @param paramname the name of the parameter
#' @param paramval the value of the parameter
#' 
#' @examples \dontrun{
#' OpenFLUID.setModelGlobalParam(ofsim,"gvalue",37.2)
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getModelGlobalParam}}
OpenFLUID.setModelGlobalParam <- function(ofblob,paramname,paramval)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(paramname))
  
  .Call("SetModelGlobalParam", ofblob, paramname, as.character(paramval), PACKAGE="ROpenFLUID")  
  
  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Sets the simulation period begin date
#' 
#' @param ofblob the simulation definition blob
#' @param begindate the begin date as an ISO datetime string (\%Y-\%m-\%d \%H:\%M:\%S)
#' 
#' @examples \dontrun{
#' OpenFLUID.setPeriodBeginDate(ofsim,"1997-06-05 04:00:00")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getPeriodBeginDate}}
#' @seealso \code{\link{OpenFLUID.setPeriodEndDate}}
#' @seealso \code{\link{OpenFLUID.getPeriodEndDate}}
OpenFLUID.setPeriodBeginDate <- function(ofblob,begindate)
{
  stopifnot(!is.null(ofblob))  
  stopifnot(is.character(begindate))

  .Call("SetPeriod", ofblob, begindate, "", PACKAGE="ROpenFLUID")

  return(invisible(NULL))
}


# =====================================================================
# =====================================================================


#' Sets the simulation period end date
#' 
#' @param ofblob the simulation definition blob
#' @param enddate the end date as an ISO datetime string (\%Y-\%m-\%d \%H:\%M:\%S)
#' 
#' @examples \dontrun{
#' OpenFLUID.setPeriodEndDate(ofsim,"1997-06-05 16:07:17")
#' }
#' 
#' @seealso \code{\link{OpenFLUID.getPeriodEndDate}}
#' @seealso \code{\link{OpenFLUID.setPeriodBeginDate}}
#' @seealso \code{\link{OpenFLUID.getPeriodBeginDate}}
OpenFLUID.setPeriodEndDate <- function(ofblob,enddate)
{
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(enddate))

  .Call("SetPeriod", ofblob, "", enddate, PACKAGE="ROpenFLUID")

  return(invisible(NULL))
}

