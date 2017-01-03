/*
 * $FreeBSD: tags/RELEASE_10_3_0/devel/qmake/files/qconfig.cpp 340872 2014-01-24 00:14:07Z mat $
 * Hand-crafted...
 * The default prefix (/ usr / local) is dynamicly replaced
 * at configure time.
 */
const char *qInstallPath()             { return "/usr/local"; }
const char *qInstallPathDocs()         { return "/usr/local/share/doc/qt"; }
const char *qInstallPathHeaders()      { return "/usr/local/include"; }
const char *qInstallPathLibs()         { return "/usr/local/lib"; }
const char *qInstallPathBins()         { return "/usr/local/bin"; }
const char *qInstallPathPlugins()      { return "/usr/local/plugins"; }
const char *qInstallPathData()         { return "/usr/local/share/qt"; }
const char *qInstallPathTranslations() { return "/usr/local/translations"; }
const char *qInstallPathSysconf()      { return "/usr/local/etc"; }
