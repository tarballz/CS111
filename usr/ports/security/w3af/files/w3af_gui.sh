#!/bin/sh
#
# $FreeBSD: tags/RELEASE_10_3_0/security/w3af/files/w3af_gui.sh 340872 2014-01-24 00:14:07Z mat $
#

cd %%PATH%%
exec %%PYTHON_CMD%% -O w3af_gui.py
