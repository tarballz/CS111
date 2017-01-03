# $FreeBSD: tags/RELEASE_10_3_0/Mk/Uses/libedit.mk 399326 2015-10-15 07:36:38Z bapt $
#
# handle dependency on the libedit port
#
# Feature:	libedit
# Usage:	USES=libedit
# Valid ARGS:	none
#
# MAINTAINER:	portmgr@FreeBSD.org

.if !defined(_INCLUDE_USES_LIBEDIT_MK)
_INCLUDE_USES_LIBEDIT_MK=	yes
.include "${USESDIR}/localbase.mk"

LIB_DEPENDS+=	libedit.so.0:${PORTSDIR}/devel/libedit
.endif
