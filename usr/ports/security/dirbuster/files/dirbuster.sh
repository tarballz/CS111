#!/bin/sh
#
# $FreeBSD: tags/RELEASE_10_3_0/security/dirbuster/files/dirbuster.sh 340872 2014-01-24 00:14:07Z mat $
#

cd %%PATH%%
exec %%JAVA_CMD%% -jar -Xmx256m %%DIRBUSTER%% "$@"
