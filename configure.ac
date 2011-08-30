AC_INIT([ROpenFLUID],[1.6.2],[fabrejc@supagro.inra.fr])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi



CC=`"${R_HOME}/bin/R" CMD config CC`
CPP=`"${R_HOME}/bin/R" CMD config CPP`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`


AC_PROG_CC
AC_PROG_CPP

OF_CPPFLAGS="`pkg-config --cflags openfluid` `pkg-config --cflags libxml-2.0` `pkg-config --cflags glibmm-2.4`"
OF_LIBS="`pkg-config --libs openfluid` `pkg-config --libs libxml-2.0` `pkg-config --libs glibmm-2.4`"

OF_PKG_CPPFLAGS="${PKG_CPPFLAGS} ${OF_CPPFLAGS}"
OF_PKG_LIBS="${PKG_LIBS} ${OF_LIBS} -L/usr/lib -lboost_system -lboost_filesystem"

AC_SUBST(OF_PKG_CPPFLAGS)
AC_SUBST(OF_PKG_LIBS)

AC_CONFIG_FILES([src/Makevars])

AC_OUTPUT

