#! /bin/sh
# $FreeBSD: tags/RELEASE_10_3_0/sysutils/jdiskreport/files/jdiskreport.sh 340872 2014-01-24 00:14:07Z mat $
JDISKDIR="%%JDISKDIR%%"
JAVAVM="%%JAVAVM%%"
PORTVERSION="%%PORTVERSION%%"

$JAVAVM -jar "$JDISKDIR/jdiskreport-$PORTVERSION.jar"
