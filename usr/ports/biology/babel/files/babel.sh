#!/bin/sh
# $FreeBSD: tags/RELEASE_10_3_0/biology/babel/files/babel.sh 340851 2014-01-23 19:55:14Z mat $

export BABEL_DIR=${BABEL_DIR-@PREFIX@/share/babel}

exec @PREFIX@/libexec/babel "$@"
