#!/bin/sh
# $FreeBSD: tags/RELEASE_10_3_0/net/dgd/files/dgd.sh 340872 2014-01-24 00:14:07Z mat $

DGD_CONF=%%PREFIX%%/etc/dgd/kernel.dgd
DGD_USER=mud
DGD=%%PREFIX%%/sbin/dgd
DGD_LOG=%%DATADIR%%/kernel.log
DGD_PID=/var/run/dgd.pid

case "$1" in
	start)
		if [ -x "${DGD}" ]; then
			su ${DGD_USER} -c "${DGD} ${DGD_CONF}" >> "${DGD_LOG}" 2>&1 &
			echo $(($!+2)) > "${DGD_PID}"
			echo -n ' dgd'
		fi
		;;
	stop)
		kill -TERM `cat "${DGD_PID}"` && rm -f "${DGD_PID}"
		;;
	*)
		echo ""
		echo "Usage: `basename $0` { start | stop }"
		echo ""
		exit 64
		;;
esac
