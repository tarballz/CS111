# $FreeBSD: tags/RELEASE_10_3_0/Mk/Uses/makeinfo.mk 399326 2015-10-15 07:36:38Z bapt $
#
# handle dependency on the makeinfo port
#
# Feature:	makeinfo
# Usage:	USES=makeinfo
# Valid ARGS:	build (default, implicit), run, both
#
# MAINTAINER: portmgr@FreeBSD.org

.if !defined(_INCLUDE_USES_MAKEINFO_MK)
_INCLUDE_USES_MAKEINFO_MK=	yes

.if !empty(makeinfo_ARGS)
IGNORE=	USES=makeinfo - expects no arguments
.endif

.if !exists(/usr/bin/makeinfo)
BUILD_DEPENDS+=	makeinfo:${PORTSDIR}/print/texinfo
.endif

.endif
