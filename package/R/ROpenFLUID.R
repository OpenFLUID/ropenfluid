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



.onLoad <- function(lib, pkg) {
  library.dynam("ROpenFLUID", pkg, lib)
}



# General ##############################


#' Returns the OpenFLUID version
#'
#' @return the OpenFLUID version number
#'
#' @examples \dontrun{
#' v = OpenFLUID.getVersion()
#' }
OpenFLUID.getVersion <- function() {
  .Call("GetVersion", PACKAGE = "ROpenFLUID")
}



# Paths ########################################


#' Returns all the paths to search for simulators
#'
#' @return a vector of paths
#'
#' @examples \dontrun{
#' paths = OpenFLUID.getSimulatorsPaths()
#' }
#'
#' @seealso \code{\link{OpenFLUID.addExtraSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.getExtraSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.resetExtraSimulatorsPaths}}
OpenFLUID.getSimulatorsPaths <- function() {
  .Call("GetSimulatorsPaths", PACKAGE = "ROpenFLUID")
}


#' Adds paths to search for simulators
#'
#' @param paths the colon separated paths to add
#'
#' @examples \dontrun{
#' OpenFLUID.addExtraSimulatorsPaths("/first/path")
#' OpenFLUID.addExtraSimulatorsPaths("/second/path:/third/path")  # Unix
#' OpenFLUID.addExtraSimulatorsPaths("/second/path;/third/path")  # Windows
#' OpenFLUID.addExtraSimulatorsPaths(c("/fourth/path","/fifth/path"))
#' }
#'
#' @seealso \code{\link{OpenFLUID.getSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.getExtraSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.resetExtraSimulatorsPaths}}
OpenFLUID.addExtraSimulatorsPaths <- function(paths) {
  stopifnot(is.character(paths) | is.vector(paths, mode = "character"))

  if (is.vector(paths, mode = "character"))
    .Call(
      "AddExtraSimulatorsPaths",
      paste(unique(paths), collapse = .Platform$path.sep),
      PACKAGE = "ROpenFLUID"
    )
  else
    .Call("AddExtraSimulatorsPaths", paths, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Returns the added paths to search for simulators
#'
#' @return a vector of paths
#'
#' @examples \dontrun{
#' paths = OpenFLUID.getExtraSimulatorsPaths()
#' }
#'
#' @seealso \code{\link{OpenFLUID.addExtraSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.getSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.resetExtraSimulatorsPaths}}
OpenFLUID.getExtraSimulatorsPaths <- function() {
  .Call("GetExtraSimulatorsPaths", PACKAGE = "ROpenFLUID")
}


#' Resets list of added paths to search for simulators
#'
#' @examples \dontrun{
#' OpenFLUID.resetExtraSimulatorsPaths()
#' }
#'
#' @seealso \code{\link{OpenFLUID.addExtraSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.getSimulatorsPaths}}
#' @seealso \code{\link{OpenFLUID.getExtraSimulatorsPaths}}
OpenFLUID.resetExtraSimulatorsPaths <- function() {
  .Call("ResetExtraSimulatorsPaths", PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Returns all the paths to search for observers
#'
#' @return a vector of paths
#'
#' @examples \dontrun{
#' paths = OpenFLUID.getObserversPaths()
#' }
#'
#' @seealso \code{\link{OpenFLUID.addExtraObserversPaths}}
#' @seealso \code{\link{OpenFLUID.getExtraObserversPaths}}
#' @seealso \code{\link{OpenFLUID.resetExtraObserversPaths}}
OpenFLUID.getObserversPaths <- function() {
  .Call("GetObserversPaths", PACKAGE = "ROpenFLUID")
}


#' Adds paths to search for observers
#'
#' @param paths the colon separated paths to add
#'
#' @examples \dontrun{
#' OpenFLUID.addExtraObserversPaths("/first/path")
#' OpenFLUID.addExtraObserversPaths("/second/path:/third/path")  # Unix
#' OpenFLUID.addExtraObserversPaths("/second/path;/third/path")  # Windows
#' OpenFLUID.addExtraObserversPaths(c("/fourth/path","/fifth/path"))
#' }
#'
#' @seealso \code{\link{OpenFLUID.getObserversPaths}}
#' @seealso \code{\link{OpenFLUID.getExtraObserversPaths}}
#' @seealso \code{\link{OpenFLUID.resetExtraObserversPaths}}
OpenFLUID.addExtraObserversPaths <- function(paths) {
  stopifnot(is.character(paths) | is.vector(paths, mode = "character"))

  if (is.vector(paths, mode = "character"))
    .Call(
      "AddExtraObserversPaths",
      paste(unique(paths), collapse = .Platform$path.sep),
      PACKAGE = "ROpenFLUID"
    )
  else
    .Call("AddExtraObserversPaths", paths, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Returns the added paths to search for observers
#'
#' @return a vector of paths
#'
#' @examples \dontrun{
#' paths = OpenFLUID.getExtraObserversPaths()
#' }
#'
#' @seealso \code{\link{OpenFLUID.addExtraObserversPaths}}
#' @seealso \code{\link{OpenFLUID.getObserversPaths}}
#' @seealso \code{\link{OpenFLUID.resetExtraObserversPaths}}
OpenFLUID.getExtraObserversPaths <- function() {
  .Call("GetExtraObserversPaths", PACKAGE = "ROpenFLUID")
}


#' Resets list of added paths to search for observers
#'
#' @examples \dontrun{
#' OpenFLUID.resetExtraObserversPaths()
#' }
#'
#' @seealso \code{\link{OpenFLUID.addExtraObserversPaths}}
#' @seealso \code{\link{OpenFLUID.getObserversPaths}}
#' @seealso \code{\link{OpenFLUID.getExtraObserversPaths}}
OpenFLUID.resetExtraObserversPaths <- function() {
  .Call("ResetExtraObserversPaths", PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Sets the current output directory for simulations
#'
#' @param path the output directory path
#'
#' @examples \dontrun{
#' OpenFLUID.setCurrentOutputDir("/path/to/output")
#' }
OpenFLUID.setCurrentOutputDir <- function(path) {
  stopifnot(is.character(path))

  .Call("SetCurrentOutputDir", path, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}



# Datasets and projects ##############################


#OpenFLUID.newProject <- function()
#{
#  ret <- .Call("NewProject", PACKAGE = "ROpenFLUID")
#
#  stopifnot(!is.null(ret))
#
#  return(ret)
#}


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
OpenFLUID.openDataset <- function(path) {
  stopifnot(is.character(path))

  ret <- .Call("OpenDataset", path, PACKAGE = "ROpenFLUID")

  stopifnot(!is.null(ret))

  return(ret)
}


#' Writes a dataset on disk from a simulation definition blob
#'
#' @param ofblob the simulation definition blob
#' @param path the full path where the datset is written
#'
#' @examples \dontrun{
#' OpenFLUID.writeDataset(ofsim ,"/path/to/dataset")
#' }
#'
#' @seealso \code{\link{OpenFLUID.openDataset}}
OpenFLUID.writeDataset <- function(ofblob, path) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(path))

  .Call("WriteDataset", ofblob, path, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


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
OpenFLUID.openProject <- function(path) {
  stopifnot(is.character(path))

  ret <- .Call("OpenProject", path, PACKAGE = "ROpenFLUID")

  stopifnot(!is.null(ret))

  return(ret)
}



# Model ##############################


#' Returns the value of a simulator parameter
#'
#' @param ofblob the simulation definition blob
#' @param simid the simulator ID
#' @param paramname the name of the parameter
#' @return the parameter value
#'
#' @examples \dontrun{
#' val = OpenFLUID.getSimulatorParam(ofsim, "my.simulator","coeff")
#' }
#'
#' @seealso \code{\link{OpenFLUID.setSimulatorParam}}
#' @seealso \code{\link{OpenFLUID.removeSimulatorParam}}
OpenFLUID.getSimulatorParam <- function(ofblob, simid, paramname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(simid))
  stopifnot(is.character(paramname))

  .Call("GetSimulatorParam", ofblob, simid, paramname, PACKAGE = "ROpenFLUID")
}


#' Returns the values of simulator parameters
#'
#' @param ofblob the simulation definition blob
#' @param simid the simulator ID
#' @param paramnames names of the parameters
#' @return the parameter values
#'
#' @examples \dontrun{
#' vals = OpenFLUID.getSimulatorParams(ofsim, "my.simulator",c("coeff","coeff"))
#' }
#'
#' @seealso \code{\link{OpenFLUID.getObserverParams}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParams}}
OpenFLUID.getSimulatorParams <- function(ofblob, simid, paramnames) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(simid))
  if (is.null(paramnames) || (length(paramnames) == 0)) {
    return(NULL)
  }
  stopifnot(is.vector(paramnames, mode = "character"))

  if (length(paramnames) == 1) {
    ret <- data.frame(
             stringsAsFactors = FALSE,
             x = .Call(
                   "GetSimulatorParam",
                   ofblob, simid, paramnames[1],
                   PACKAGE = "ROpenFLUID"
                 )
           )
    colnames(ret) <- paramnames
  } else {
    ret <- as.data.frame(
             stringsAsFactors = FALSE,
             x = t(
                   sapply(
                     paramnames,
                     function(paramname) .Call(
                       "GetSimulatorParam",
                       ofblob, simid, paramname,
                       PACKAGE = "ROpenFLUID"
                     )
                   )
                 )
           )
  }
  rownames(ret) <- c(simid)

  return(ret)
}


#' Returns all the parameters names of a simulator
#'
#' @param ofblob the simulation definition blob
#' @param simid the simulator ID
#' @return a vector of parameters names
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getSimulatorParamNames(ofsim, simid)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParamNames}}
#' @seealso \code{\link{OpenFLUID.getGeneratorParamNames}}
#' @seealso \code{\link{OpenFLUID.getObserverParamNames}}
OpenFLUID.getSimulatorParamNames <- function(ofblob, simid) {
  stopifnot(!is.null(ofblob))

  ret <- .Call("GetSimulatorParamNames", ofblob, simid, PACKAGE = "ROpenFLUID")

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])
}


#' Sets a value of a simulator parameter
#'
#' @param ofblob the simulation definition blob
#' @param simid the simulation simulator id
#' @param paramname the name of the parameter
#' @param paramval the parameter value
#'
#' @examples \dontrun{
#' OpenFLUID.setSimulatorParam(ofsim, "my.simulator","coeff",3)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getSimulatorParam}}
#' @seealso \code{\link{OpenFLUID.removeSimulatorParam}}
OpenFLUID.setSimulatorParam <- function(ofblob, simid, paramname, paramval) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(simid))
  stopifnot(is.character(paramname))

  .Call(
    "SetSimulatorParam",
    ofblob, simid, paramname, as.character(paramval),
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}


#' Sets values of a simulator parameters
#'
#' @param ofblob the simulation definition blob
#' @param simid the simulation simulator id
#' @param paramvals the values of the parameters in a data.frame,
#' with parameters names as columns names
#' @examples \dontrun{
#' OpenFLUID.setSimulatorParams(
#'   ofsim,
#'   "my.simulator",data.frame("coeffA"=3, "coeffB"=3.3)
#' )
#' }
#'
#' @seealso \code{\link{OpenFLUID.setModelGlobalParams}}
#' @seealso \code{\link{OpenFLUID.setGeneratorParams}}
#' @seealso \code{\link{OpenFLUID.setObserverParams}}
OpenFLUID.setSimulatorParams <- function(ofblob, simid, paramvals) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(simid))
  stopifnot(is.data.frame(paramvals))

  for (paramname in colnames(paramvals)) {
    .Call(
      "SetSimulatorParam",
      ofblob, simid, paramname, as.character(paramvals[paramname][1]),
      PACKAGE = "ROpenFLUID"
    )
  }

  return(invisible(NULL))
}


#' Removes a simulator parameter
#'
#' @param ofblob the simulation definition blob
#' @param simid the simulation simulator id
#' @param paramname the name of the parameter
#'
#' @examples \dontrun{
#' OpenFLUID.removeSimulatorParam(ofsim, "my.simulator","coeff")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getSimulatorParam}}
#' @seealso \code{\link{OpenFLUID.setSimulatorParam}}
OpenFLUID.removeSimulatorParam <- function(ofblob, simid, paramname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(simid))
  stopifnot(is.character(paramname))

  .Call(
    "RemoveSimulatorParam",
    ofblob, simid, paramname,
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}


#' Returns a the value of a generator parameter
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class to which the generator is applied
#' @param varname the variable name to which the generator is applied
#' @param paramname the name of the parameter
#' @return the parameter value
#'
#' @examples \dontrun{
#' val = OpenFLUID.getGeneratorParam(ofsim, "SU","var.flux","fixedvalue")
#' }
#'
#' @seealso \code{\link{OpenFLUID.setGeneratorParam}}
OpenFLUID.getGeneratorParam <- function(ofblob, unitsclass, varname, paramname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.character(varname))
  stopifnot(is.character(paramname))

  .Call(
    "GetGeneratorParam",
    ofblob, unitsclass, varname, paramname,
    PACKAGE = "ROpenFLUID"
  )
}


#' Returns the values of generator parameters
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class to which the generator is applied
#' @param varname the variable name to which the generator is applied
#' @param paramnames the names of the parameters
#' @return the parameter values
#'
#' @examples \dontrun{
#' val = OpenFLUID.getGeneratorParams(ofsim, "SU","var.flux",c("min","max"))
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParams}}
#' @seealso \code{\link{OpenFLUID.getObserverParams}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParams}}
OpenFLUID.getGeneratorParams <- function(ofblob,
                                         unitsclass, varname, paramnames) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.character(varname))
  if (is.null(paramnames) || (length(paramnames) == 0)) {
    return(NULL)
  }
  stopifnot(is.vector(paramnames, mode = "character"))

  if (length(paramnames) == 1) {
    ret <- data.frame(
             stringsAsFactors = FALSE,
             x = .Call(
                   "GetGeneratorParam",
                   ofblob, unitsclass, varname, paramnames[1],
                   PACKAGE = "ROpenFLUID"
                 )
           )
    colnames(ret) <- paramnames
  } else {
    ret <- as.data.frame(
             stringsAsFactors = FALSE,
             x = t(
                   sapply(
                     paramnames,
                     function(paramname) .Call(
                       "GetGeneratorParam",
                       ofblob, unitsclass, varname, paramname,
                       PACKAGE = "ROpenFLUID"
                     )
                   )
                 )
          )
  }
  rownames(ret) <- c(varname)

  return(ret)
}


#' Returns all parameters names of a generator
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the name of the variable generated
#' @param varname the name of the variable generated
#' @return a vector of parameters names
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getGeneratorParamNames(ofsim, "SU","var1")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParamNames}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParamNames}}
#' @seealso \code{\link{OpenFLUID.getObserverParamNames}}
OpenFLUID.getGeneratorParamNames <- function(ofblob, unitsclass, varname) {
  stopifnot(!is.null(ofblob))

  ret <- .Call(
           "GetGeneratorParamNames",
           ofblob, unitsclass, varname,
           PACKAGE = "ROpenFLUID")

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])

}


#' Sets a value for a generator parameter
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class to which the generator is applied
#' @param varname the variable name to which the generator is applied
#' @param paramname the name of the parameter
#' @param paramval the value of the parameter
#'
#' @examples \dontrun{
#' OpenFLUID.setGeneratorParam(ofsim, "SU","var.flux","fixedvalue",12.3)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getGeneratorParam}}
OpenFLUID.setGeneratorParam <- function(ofblob,
                                        unitsclass, varname,
                                        paramname, paramval) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.character(varname))
  stopifnot(is.character(paramname))

  .Call(
    "SetGeneratorParam",
    ofblob, unitsclass, varname,
    paramname, as.character(paramval),
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}


#' Sets values of generator parameters
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class to which the generator is applied
#' @param varname the variable name to which the generator is applied
#' @param paramvals the value of the parameters in a data.frame,
#' with parameters names as columns names
#'
#' @examples \dontrun{
#' OpenFLUID.setGeneratorParams(
#'   ofsim,
#'   "SU", "var.flux",
#'   data.frame("min"=0.0, "max"=1.0)
#' )
#' }
#'
#' @seealso \code{\link{OpenFLUID.setModelGlobalParams}}
#' @seealso \code{\link{OpenFLUID.setObserverParams}}
#' @seealso \code{\link{OpenFLUID.setSimulatorParams}}
OpenFLUID.setGeneratorParams <- function(ofblob,
                                         unitsclass, varname, paramvals) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.character(varname))
  stopifnot(is.data.frame(paramvals))

  for (paramname in colnames(paramvals)) {
    .Call(
      "SetGeneratorParam",
      ofblob, unitsclass, varname,
      paramname, as.character(paramvals[paramname][1]),
      PACKAGE = "ROpenFLUID"
    )
  }

  return(invisible(NULL))
}


#' Returns the value of a global parameter of the model
#'
#' @param ofblob the simulation definition blob
#' @param paramname the name of the parameter
#' @return the parameter value
#'
#' @examples \dontrun{
#' val = OpenFLUID.getModelGlobalParam(ofsim, "gvalue")
#' }
#'
#' @seealso \code{\link{OpenFLUID.setModelGlobalParam}}
#' @seealso \code{\link{OpenFLUID.removeModelGlobalParam}}
OpenFLUID.getModelGlobalParam <- function(ofblob, paramname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(paramname))

  .Call("GetModelGlobalParam", ofblob, paramname, PACKAGE = "ROpenFLUID")
}


#' Returns the values of global parameters of the model
#'
#' @param ofblob the simulation definition blob
#' @param paramnames names of the parameters
#' @return the parameter values
#'
#' @examples \dontrun{
#' vals = OpenFLUID.getModelGlobalParams(ofsim, c("gvalueA","gvalueB"))
#' }
#'
#' @seealso \code{\link{OpenFLUID.getGeneratorParams}}
#' @seealso \code{\link{OpenFLUID.getObserverParams}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParams}}
OpenFLUID.getModelGlobalParams <- function(ofblob, paramnames) {
  stopifnot(!is.null(ofblob))
  if (is.null(paramnames) || (length(paramnames) == 0)) {
    return(NULL)
  }
  stopifnot(is.vector(paramnames, mode = "character"))

  if (length(paramnames) == 1) {

    ret <- data.frame(
             stringsAsFactors = FALSE,
             x = .Call(
                   "GetModelGlobalParam",
                   ofblob, paramnames[1],
                   PACKAGE = "ROpenFLUID"
                 )
           )
    colnames(ret) <- paramnames
  } else {
    ret <- as.data.frame(
             stringsAsFactors = FALSE,
             x = t(
                   sapply(
                     paramnames,
                     function(paramname) .Call(
                       "GetModelGlobalParam",
                       ofblob, paramname,
                       PACKAGE = "ROpenFLUID"
                     )
                   )
                 )
           )
  }
  rownames(ret) <- c("global")

  return(ret)
}


#' Returns all the variables names generated by generators
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the units class
#' @return a vector of variables names
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getGeneratorsVarNames(ofsim, "SU")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getSimulatorsIDs}}
#' @seealso \code{\link{OpenFLUID.getObserversIDs}}
OpenFLUID.getGeneratorsVarNames <- function(ofblob, unitsclass) {
  stopifnot(!is.null(ofblob))

  ret <- .Call(
           "GetGeneratorsVarNames",
           ofblob, unitsclass,
           PACKAGE = "ROpenFLUID"
         )

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])

}


#' Returns all the global parameters names
#'
#' @param ofblob the simulation definition blob
#' @return a vector of parameters names
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getModelGlobalParamNames(ofsim)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getGeneratorParamNames}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParamNames}}
#' @seealso \code{\link{OpenFLUID.getObserverParamNames}}
OpenFLUID.getModelGlobalParamNames <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  ret <- .Call("GetModelGlobalParamNames", ofblob, PACKAGE = "ROpenFLUID")

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])

}


#' Sets a model global parameter value
#'
#' @param ofblob the simulation definition blob
#' @param paramname the name of the parameter
#' @param paramval the value of the parameter
#'
#' @examples \dontrun{
#' OpenFLUID.setModelGlobalParam(ofsim, "gvalue",37.2)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParam}}
#' @seealso \code{\link{OpenFLUID.removeModelGlobalParam}}
OpenFLUID.setModelGlobalParam <- function(ofblob, paramname, paramval) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(paramname))

  .Call(
    "SetModelGlobalParam",
    ofblob, paramname, as.character(paramval),
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}


#' Sets a value of a global parameter of the model
#'
#' @param ofblob the simulation definition blob
#' @param paramvals the values of the parameters in a data.frame,
#' with parameters names as columns names
#'
#' @examples \dontrun{
#' OpenFLUID.setModelGlobalParams(
#'   ofsim,
#'   data.frame("gvalue1"=37.2, "gvalue2"=14.6)
#' )
#' }
#'
#' @seealso \code{\link{OpenFLUID.setModelGlobalParams}}
#' @seealso \code{\link{OpenFLUID.setSimulatorParams}}
#' @seealso \code{\link{OpenFLUID.setObserverParams}}
OpenFLUID.setModelGlobalParams <- function(ofblob, paramvals) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.data.frame(paramvals))

  for (paramname in colnames(paramvals)) {
    .Call(
      "SetModelGlobalParam",
      ofblob, paramname, as.character(paramvals[paramname][1]),
      PACKAGE = "ROpenFLUID"
    )
  }

  return(invisible(NULL))
}


#' Removes a global parameter of the model
#'
#' @param ofblob the simulation definition blob
#' @param paramname the name of the parameter
#'
#' @examples \dontrun{
#' OpenFLUID.removeModelGlobalParam(ofsim, "gvalue")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParam}}
#' @seealso \code{\link{OpenFLUID.setModelGlobalParam}}
OpenFLUID.removeModelGlobalParam <- function(ofblob, paramname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(paramname))

  .Call("RemoveModelGlobalParam", ofblob, paramname, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Returns all the simulators IDs used by the model
#'
#' @param ofblob the simulation definition blob
#' @return a vector of simulators IDs
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getSimulatorsIDs(ofsim)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getGeneratorsVarNames}}
#' @seealso \code{\link{OpenFLUID.getObserversIDs}}
OpenFLUID.getSimulatorsIDs <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  ret <- .Call("GetSimulatorsIDs", ofblob, PACKAGE = "ROpenFLUID")

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])
}



# Spatial structure ##############################


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
OpenFLUID.getUnitsClasses <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  .Call("GetUnitsClasses", ofblob, PACKAGE = "ROpenFLUID")
}


#' Returns the existing units IDs for a given units class
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the units class
#' @return a vector of units IDs
#'
#' @examples \dontrun{
#' ids = OpenFLUID.getUnitsIDs(ofsim, "SU")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getUnitsClasses}}
OpenFLUID.getUnitsIDs <- function(ofblob, unitsclass) {
  stopifnot(!is.null(ofblob))

  .Call("GetUnitsIDs", ofblob, unitsclass, PACKAGE = "ROpenFLUID")
}



# Spatial attributes ##############################


#' Creates an attribute for all spatial units of a class,
#' initialized with a default value
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class
#' @param attrname the attribute name
#' @param attrval the default attribute value for alla units
#'
#' @examples \dontrun{
#' OpenFLUID.createAttribute(ofsim, "SU","area",1.0)
#' OpenFLUID.createAttribute(ofsim, "SU","code","NONE")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getAttribute}}
#' @seealso \code{\link{OpenFLUID.setAttribute}}
#' @seealso \code{\link{OpenFLUID.removeAttribute}}
OpenFLUID.createAttribute <- function(ofblob, unitsclass, attrname, attrval) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.character(attrname))

  .Call(
    "CreateAttribute",
    ofblob, unitsclass, attrname, as.character(attrval),
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}


#' Returns an attribute value for a given spatial unit
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class
#' @param unitid the unit ID
#' @param attrname the name of the attribute
#' @return the attribute value
#'
#' @examples \dontrun{
#' val = OpenFLUID.getAttribute(ofsim, "SU",18, "length")
#' }
#'
#' @seealso \code{\link{OpenFLUID.createAttribute}}
#' @seealso \code{\link{OpenFLUID.setAttribute}}
#' @seealso \code{\link{OpenFLUID.removeAttribute}}
OpenFLUID.getAttribute <- function(ofblob, unitsclass, unitid, attrname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.numeric(unitid))
  stopifnot(is.character(attrname))

  ret <- .Call(
           "GetAttribute",
           ofblob, unitsclass, as.integer(unitid), attrname,
           PACKAGE = "ROpenFLUID"
         )

  stopifnot(!is.null(ret))

  return(ret)
}


#' Returns the attributes values for given spatial units and attributes names
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class
#' @param unitids the vector of unit IDs
#' @param attrnames the vector of names of the attributes
#' @param unitidsAsRownames if TRUE rename row as unitids,
#' if FALSE add a column of unitids
#' @return a data.frame (unitids x attrnames) of the attribute values
#'
#' @examples \dontrun{
#' valdf = OpenFLUID.getAttributes(ofsim, "SU",c(18, 23), c("length","width"))
#' }
#'
#' @seealso \code{\link{OpenFLUID.setAttributes}}
OpenFLUID.getAttributes <- function(ofblob,
                                    unitsclass, unitids, attrnames,
                                    unitidsAsRownames = TRUE) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  if (is.null(unitids) || (length(unitids) == 0)) {
    return(NULL)
  }
  stopifnot(is.vector(unitids, mode = "numeric"))
  if (is.null(attrnames) || (length(attrnames) == 0)) {
    return(NULL)
  }
  stopifnot(is.vector(attrnames, mode = "character"))

  if (length(unitids) == 1) {
    if (length(attrnames) == 1) {
      ret <- data.frame(
               stringsAsFactors = FALSE,
               x = .Call(
                     "GetAttribute",
                     ofblob, unitsclass, as.integer(unitids[1]), attrnames[1],
                     PACKAGE = "ROpenFLUID"
                   )
             )
      colnames(ret) <- attrnames
    } else {
      ret <- as.data.frame(
               stringsAsFactors = FALSE,
               x = t(
                     sapply(
                       attrnames,
                       function(attrname) .Call(
                         "GetAttribute",
                         ofblob, unitsclass,
                         as.integer(unitids[1]), attrname,
                         PACKAGE = "ROpenFLUID"
                       )
                     )
                   )
             )
    }
  } else {
    ret <- as.data.frame(
             stringsAsFactors = FALSE,
             x = sapply(
                   attrnames,
                   function(attrname) sapply(
                     unitids,
                     function(unitid) .Call(
                       "GetAttribute",
                       ofblob, unitsclass, as.integer(unitid), attrname,
                       PACKAGE = "ROpenFLUID"
                     )
                   )
                 )
           )
  }

  unitidNames <- paste(unitsclass, unitids, sep = "#")

  if (unitidsAsRownames)
    rownames(ret) <- unitidNames
  else {
    ret <- cbind(
             data.frame(
               "unitid" = unitidNames,
               stringsAsFactors = FALSE),
             ret
           )
  }

  stopifnot(!is.null(ret))

  return(ret)
}


#' Returns all the attributes names of an units class
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the class unit
#' @return a vector of attributes names
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getAttributesNames(ofsim, unitsclass)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParamNames}}
#' @seealso \code{\link{OpenFLUID.getGeneratorParamNames}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParamNames}}
#' @seealso \code{\link{OpenFLUID.getObserverParamNames}}
OpenFLUID.getAttributesNames <- function(ofblob, unitsclass) {
  stopifnot(!is.null(ofblob))

  ret <- .Call("GetAttributesNames", ofblob, unitsclass, PACKAGE = "ROpenFLUID")

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])

}


#' Sets an attribute value for a given spatial unit
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class
#' @param unitid the unit ID
#' @param attrname the name of the attribute
#' @param attrval the value of the attribute
#'
#' @examples \dontrun{
#' OpenFLUID.setAttribute(ofsim, "SU",18, "length",12.3)
#' OpenFLUID.setAttribute(ofsim, "SU",18, "CODE","ABC")
#' }
#'
#' @seealso \code{\link{OpenFLUID.createAttribute}}
#' @seealso \code{\link{OpenFLUID.getAttribute}}
#' @seealso \code{\link{OpenFLUID.removeAttribute}}
OpenFLUID.setAttribute <- function(ofblob,
                                   unitsclass, unitid,
                                   attrname, attrval) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.numeric(unitid))
  stopifnot(is.character(attrname))

  .Call(
    "SetAttribute",
    ofblob, unitsclass, as.integer(unitid), attrname,
    as.character(attrval),
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}


#' Sets attributes values for given spatial units and attributes names
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class
#' @param attrvals the data.frame of values (unit id x attribute name)
#'
#' @examples \dontrun{
#' OpenFLUID.setAttributes(
#'   ofsim,
#'   "SU",
#'   data.frame(
#'     "length"=c(1, 2),
#'     "width"=c(3.2, 7.8),
#'     "unitid"=c("SU#18","SU#23")
#'   )
#' )
#' }
#'
#' @seealso \code{\link{OpenFLUID.getAttributes}}
OpenFLUID.setAttributes <- function(ofblob, unitsclass, attrvals) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.data.frame(attrvals))

  if ("unitid" %in% rownames(attrvals)) {
    unitids <- as.integer(gsub(
                            paste(unitsclass, "#", sep = ""),
                            "",
                            attrvals$unitid
                          )
               )
  }
  else {
    unitids <- as.integer(gsub(
                            paste(unitsclass, "#", sep = ""),
                            "",
                            rownames(attrvals)
                          )
               )
  }
  attrnames <- colnames(attrvals)

  for (i in seq(length(unitids))) {
    for (j in seq(length(attrnames))) {
      .Call(
        "SetAttribute",
        ofblob, unitsclass, unitids[i],
        attrnames[j], as.character(attrvals[i, j]),
        PACKAGE = "ROpenFLUID"
      )
    }
  }
  return(invisible(NULL))
}


#' Removes an attribute for a given spatial units class
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class
#' @param attrname the name of the attribute
#'
#' @examples \dontrun{
#' OpenFLUID.removeAttribute(ofsim, "SU","length")
#' }
#'
#' @seealso \code{\link{OpenFLUID.createAttribute}}
#' @seealso \code{\link{OpenFLUID.getAttribute}}
#' @seealso \code{\link{OpenFLUID.setAttribute}}
OpenFLUID.removeAttribute <- function(ofblob, unitsclass, attrname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.character(attrname))

  .Call("RemoveAttribute", ofblob, unitsclass, attrname, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}



# Monitoring ##############################


#' Returns the value of an observer parameter
#'
#' @param ofblob the simulation definition blob
#' @param obsid the observer ID
#' @param paramname the name of the parameter
#' @return the parameter value
#'
#' @examples \dontrun{
#' val = OpenFLUID.getObserverParam(ofsim, "my.observer","value")
#' }
#'
#' @seealso \code{\link{OpenFLUID.setObserverParam}}
#' @seealso \code{\link{OpenFLUID.removeObserverParam}}
OpenFLUID.getObserverParam <- function(ofblob, obsid, paramname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(obsid))
  stopifnot(is.character(paramname))

  .Call("GetObserverParam", ofblob, obsid, paramname, PACKAGE = "ROpenFLUID")
}


#' Returns the values of observer parameters
#'
#' @param ofblob the simulation definition blob
#' @param obsid the observer ID
#' @param paramnames names of the parameters
#' @return the parameter values
#'
#' @examples \dontrun{
#' vals = OpenFLUID.getObserverParams(ofsim, "my.observer",c("valueA","valueB"))
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParams}}
#' @seealso \code{\link{OpenFLUID.getGeneratorParams}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParams}}
OpenFLUID.getObserverParams <- function(ofblob, obsid, paramnames) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(obsid))
  if (is.null(paramnames) || (length(paramnames) == 0)) {
    return(NULL)
  }
  stopifnot(is.vector(paramnames, mode = "character"))

  if (length(paramnames) == 1) {
    ret <- data.frame(
             stringsAsFactors = FALSE,
             x = .Call(
                   "GetObserverParam",
                   ofblob, obsid, paramnames[1],
                   PACKAGE = "ROpenFLUID"
                  )
           )
    colnames(ret) <- paramnames
  } else {
    ret <- as.data.frame(
             stringsAsFactors = FALSE,
             x = t(
                   sapply(
                     paramnames,
                     function(paramname) .Call(
                       "GetObserverParam",
                       ofblob, obsid, paramnames[1],
                       PACKAGE = "ROpenFLUID"
                     )
                   )
                 )
           )
  }
  rownames(ret) <- c(obsid)

  return(ret)
}


#' Returns all parameters names of an observer
#'
#' @param ofblob the simulation definition blob
#' @param obsid the observer ID
#' @return a vector of parameters names
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getObserverParamNames(ofsim, obsid)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getModelGlobalParamNames}}
#' @seealso \code{\link{OpenFLUID.getGeneratorParamNames}}
#' @seealso \code{\link{OpenFLUID.getSimulatorParamNames}}
OpenFLUID.getObserverParamNames <- function(ofblob, obsid) {
  stopifnot(!is.null(ofblob))

  ret <- .Call("GetObserverParamNames", ofblob, obsid, PACKAGE = "ROpenFLUID")

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])

}


#' Sets a value for an observer parameter
#'
#' @param ofblob the simulation definition blob
#' @param obsid the simulation observer id
#' @param paramname the name of the parameter
#' @param paramval the parameter value
#'
#' @examples \dontrun{
#' OpenFLUID.setObserverParam(ofsim, "my.observer","value",3)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getObserverParam}}
#' @seealso \code{\link{OpenFLUID.removeObserverParam}}
OpenFLUID.setObserverParam <- function(ofblob, obsid, paramname, paramval) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(obsid))
  stopifnot(is.character(paramname))


  .Call(
    "SetObserverParam",ofblob, obsid, paramname,
    as.character(paramval),
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}


#' Sets values for observer parameters
#'
#' @param ofblob the simulation definition blob
#' @param obsid the simulation observer id
#' @param paramvals the values of the parameters in a data.frame,
#' with parameters names as column names
#'
#' @examples \dontrun{
#' OpenFLUID.setObserverParams(
#'   ofsim,
#'   "my.observer",data.frame("valueA"=3, "valueB"=6.7))
#' }
#'
#' @seealso \code{\link{OpenFLUID.setModelGlobalParams}}
#' @seealso \code{\link{OpenFLUID.setGeneratorParams}}
#' @seealso \code{\link{OpenFLUID.setSimulatorParams}}
OpenFLUID.setObserverParams <- function(ofblob, obsid, paramvals) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(obsid))
  stopifnot(is.data.frame(paramvals))

  for (paramname in colnames(paramvals)) {
    .Call(
      "SetObserverParam",
      ofblob, obsid, paramname, as.character(paramvals[paramname][1]),
      PACKAGE = "ROpenFLUID"
    )
  }

  return(invisible(NULL))
}


#' Removes an observer parameter
#'
#' @param ofblob the simulation definition blob
#' @param obsid the simulation observer id
#' @param paramname the name of the parameter
#'
#' @examples \dontrun{
#' OpenFLUID.removeObserverParam(ofsim, "my.observer","value")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getObserverParam}}
#' @seealso \code{\link{OpenFLUID.setObserverParam}}
OpenFLUID.removeObserverParam <- function(ofblob, obsid, paramname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(obsid))
  stopifnot(is.character(paramname))

  .Call("RemoveObserverParam", ofblob, obsid, paramname, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Returns all observers IDs used for the monitoring
#'
#' @param ofblob the simulation definition blob
#' @return a vector of observers IDs
#'
#' @examples \dontrun{
#' varnames = OpenFLUID.getObserversIDs(ofsim)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getGeneratorsVarNames}}
#' @seealso \code{\link{OpenFLUID.getSimulatorsIDs}}
OpenFLUID.getObserversIDs <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  ret <- .Call("GetObserversIDs", ofblob, PACKAGE = "ROpenFLUID")

  if (ret == "")
    return(NULL)

  return(strsplit(ret, split = ";")[[1]])
}


#' Adds export of simulation variables as CSV files for a given units class
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the units class to add for simulation variables export
#' @param unitid the unit ID (optional)
#' @param varname the name of the variable(s) (optional)
#' @param precision the number of digits of the variables (optional)
#'
#' @examples \dontrun{
#' OpenFLUID.addVariablesExportAsCSV(ofsim, "TU")
#' OpenFLUID.addVariablesExportAsCSV(ofsim, "TU",1, "var1",precision = 14)
#' OpenFLUID.addVariablesExportAsCSV(ofsim, "TU",2, "var1;var2")
#' OpenFLUID.addVariablesExportAsCSV(ofsim, "TU",2, c("var1","var2"))
#' OpenFLUID.addVariablesExportAsCSV(ofsim, "TU",c(3, 5), c("var1","var2"))
#' OpenFLUID.addVariablesExportAsCSV(ofsim, "TU",1, "*")
#' }
#'
#' @seealso \code{\link{OpenFLUID.loadResult}}
OpenFLUID.addVariablesExportAsCSV <- function(ofblob,
                                              unitsclass,
                                              unitid = NULL,
                                              varname = "*", precision = 0) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(
    is.numeric(unitid) |
    is.vector(unitid, mode = "numeric") |
    is.null(unitid)
  )
  stopifnot(is.character(varname) | is.vector(varname, mode = "character"))
  stopifnot(is.numeric(precision))

  if (is.vector(varname, mode = "character"))
    varnames <- paste(unique(varname), collapse = ";")
  else
    varnames <- varname

  if (is.null(unitid))
    unitids <- "*"
  else {
    if (is.vector(unitid, mode = "numeric"))
      unitids <- paste(as.character(unique(unitid)), collapse = ";")
    else
      unitids <- as.character(unitid)
  }

  .Call(
    "AddVariablesExportAsCSV",
    ofblob, unitsclass, unitids, varnames, as.integer(precision),
    PACKAGE = "ROpenFLUID"
  )

  return(invisible(NULL))
}



# Simulation configuration ##############################


#' Returns the default time step of the simulation
#'
#' @param ofblob the simulation definition blob
#' @return the time step value in seconds
#'
#' @examples \dontrun{
#' deltat = OpenFLUID.getDefaultDeltaT(ofsim)
#' }
#'
#' @seealso \code{\link{OpenFLUID.setDefaultDeltaT}}
OpenFLUID.getDefaultDeltaT <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  ret <- .Call("GetDefaultDeltaT", ofblob, PACKAGE = "ROpenFLUID")

  stopifnot(!is.null(ret))

  return(ret)
}


#' Sets the default time step for the simulation
#'
#' @param ofblob the simulation definition blob
#' @param deltat the time step value in seconds
#'
#' @examples \dontrun{
#' OpenFLUID.setDefaultDeltaT(60)
#' OpenFLUID.setDefaultDeltaT(86400)
#' }
#'
#' @seealso \code{\link{OpenFLUID.getDefaultDeltaT}}
OpenFLUID.setDefaultDeltaT <- function(ofblob, deltat) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.numeric(deltat))
  stopifnot(deltat > 0)

  .Call("SetDefaultDeltaT", ofblob, as.integer(deltat), PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Returns the begin date of the simulation period
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
OpenFLUID.getPeriodBeginDate <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  .Call("GetPeriodBeginDate", ofblob, PACKAGE = "ROpenFLUID")
}


#' Returns the end date of the simulation period
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
OpenFLUID.getPeriodEndDate <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  .Call("GetPeriodEndDate", ofblob, PACKAGE = "ROpenFLUID")
}


#' Sets the begin date of the simulation period
#'
#' @param ofblob the simulation definition blob
#' @param begindate the begin date as an ISO datetime string
#' (\%Y-\%m-\%d \%H:\%M:\%S)
#'
#' @examples \dontrun{
#' OpenFLUID.setPeriodBeginDate(ofsim, "1997-06-05 04:00:00")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getPeriodBeginDate}}
#' @seealso \code{\link{OpenFLUID.setPeriodEndDate}}
#' @seealso \code{\link{OpenFLUID.getPeriodEndDate}}
OpenFLUID.setPeriodBeginDate <- function(ofblob, begindate) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(begindate))

  .Call("SetPeriod", ofblob, begindate, "", PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Sets the end date of the simulation period
#'
#' @param ofblob the simulation definition blob
#' @param enddate the end date as an ISO datetime string
#' (\%Y-\%m-\%d \%H:\%M:\%S)
#'
#' @examples \dontrun{
#' OpenFLUID.setPeriodEndDate(ofsim, "1997-06-05 16:07:17")
#' }
#'
#' @seealso \code{\link{OpenFLUID.getPeriodEndDate}}
#' @seealso \code{\link{OpenFLUID.setPeriodBeginDate}}
#' @seealso \code{\link{OpenFLUID.getPeriodBeginDate}}
OpenFLUID.setPeriodEndDate <- function(ofblob, enddate) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(enddate))

  .Call("SetPeriod", ofblob, "", enddate, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Prints informations to screen about the simulation definition blob
#'
#' @param ofblob the simulation definition blob
#'
#' @examples \dontrun{
#' OpenFLUID.printSimulationInfo(ofsim)
#' }
OpenFLUID.printSimulationInfo <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  .Call("PrintSimulationInfo", ofblob, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Delete simulation blob
#'
#' @param ofblob the simulation definition blob
#'
#' @examples \dontrun{
#' OpenFLUID.deleteSimulationBlob(ofsim)
#' }
OpenFLUID.deleteSimulationBlob <- function(ofblob) {
  stopifnot(!is.null(ofblob))

  .Call("DeleteBlob", ofblob, PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


# Simulation execution ##############################


#' Runs a project and returns a simulation definition blob
#'
#' @param path the full path of the dataset to open
#' @param verbose enable/disable verbose mode
#'
#' @examples \dontrun{
#' ofsim = OpenFLUID.runProject("/path/to/dataset")
#' ofsim = OpenFLUID.runProject("/path/to/dataset",verbose = TRUE)
#' }
#'
#' @seealso \code{\link{OpenFLUID.runSimulation}}
#' @seealso \code{\link{OpenFLUID.openProject}}
OpenFLUID.runProject <- function(path, verbose = FALSE) {
  stopifnot(is.character(path))

  ofdata <- OpenFLUID.openProject(path)

  OpenFLUID.runSimulation(ofdata, verbose)
  
  OpenFLUID.deleteSimulationBlob(ofdata)
  
  return(invisible(NULL))
}


#' Runs a simulation from a simulation definition blob
#'
#' @param ofblob the simulation definition blob
#' @param verbose enable/disable verbose mode
#'
#' @examples \dontrun{
#' OpenFLUID.runSimulation(ofsim)
#' OpenFLUID.runSimulation(ofsim, verbose = TRUE)
#' }
#'
#' @seealso \code{\link{OpenFLUID.runProject}}
#' @seealso \code{\link{OpenFLUID.openProject}}
#' @seealso \code{\link{OpenFLUID.openDataset}}
OpenFLUID.runSimulation <- function(ofblob, verbose = FALSE) {
  stopifnot(!is.null(ofblob))

  .Call("RunSimulation", ofblob, as.integer(verbose), PACKAGE = "ROpenFLUID")

  return(invisible(NULL))
}


#' Runs a simulation from a simulation definition blob
#' as an external independent process
#'
#' @param ofblob the simulation definition blob
#' @param workpath a workspace for simulation files.
#' Inside this path, an IN directory will be created to store
#' the input dataset, and an out directory will be created for output data.
#' If this workpath is not provided or is NULL, a temporary path
#' will be automatically generated
#' @param verbose the verbose mode for the run. Possible values are similar
#' than the R system2 built-in function, e.g. FALSE for quiet mode, "" for
#' console output, a path string for file log.
#'
#' @examples \dontrun{
#' OpenFLUID.runSimulationAsExternalProcess(ofsim)
#' OpenFLUID.runSimulationAsExternalProcess(ofsim, workpath = "/path/to/work")
#' }
#'
#' @seealso \code{\link{OpenFLUID.runSimulation}}
OpenFLUID.runSimulationAsExternalProcess <- function(ofblob, workpath = NULL, verbose = FALSE) {
  stopifnot(!is.null(ofblob))

  if (is.null(workpath)) {
    workpath <- tempdir()
  }

  inpath <- paste(workpath, "IN", sep = "/")
  outpath <- paste(workpath, "OUT", sep = "/")

  OpenFLUID.writeDataset(ofblob, inpath)

  command <- "openfluid"
  args <- c("run", inpath, outpath)
  ret <- system2(command, args, wait = TRUE,
                 stdout = verbose, stderr = verbose, input = NULL)

  return(ret)
}



# Results ##############################


#' Loads results as a dataframe, giving dataset informations
#'
#' @param ofblob the simulation definition blob
#' @param unitsclass the unit class
#' @param unitid the unit ID
#' @param varname the variable name
#' @return a dataframe containing the simulation results
#'
#' @examples \dontrun{
#' resSU18 = OpenFLUID.loadResult(ofsim, "SU",18, "runoff")
#' resRS1 = OpenFLUID.loadResult(ofsim, "RS",1, "waterlevel")
#' }
#'
#' @seealso \code{\link{OpenFLUID.loadResultFile}}
OpenFLUID.loadResult <- function(ofblob, unitsclass, unitid, varname) {
  stopifnot(!is.null(ofblob))
  stopifnot(is.character(unitsclass))
  stopifnot(is.numeric(unitid))
  stopifnot(is.character(varname))

  filename <- .Call("GetSimulationOutputDir", ofblob, PACKAGE = "ROpenFLUID")

  filename <- paste(filename, "ropenfluid", sep = "/")
  filename <- paste(filename, unitsclass, sep = "")
  filename <- paste(filename, unitsclass, sep = "_")
  filename <- paste(filename, as.integer(unitid), sep = "")
  filename <- paste(filename, varname, sep = "_")
  filename <- paste(filename, ".csv", sep = "")

  return(OpenFLUID.loadResultFile(filename))
}


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
OpenFLUID.loadResultFile <- function(filepath) {
  stopifnot(is.character(filepath))

  data <- read.csv(file = filepath, header = TRUE, sep = " ",
                   stringsAsFactors = F)
  data$datetime <- as.POSIXct(data$datetime,
                              format = "%Y%m%d-%H%M%S", tz = "UTC")

  return(data)
}
