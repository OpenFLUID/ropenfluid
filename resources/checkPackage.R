args <- commandArgs(TRUE)

if (as.character(args) %in% rownames(installed.packages()))
{
  quit(status=1)
}

quit(status=0)