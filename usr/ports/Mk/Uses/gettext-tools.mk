# $FreeBSD: tags/RELEASE_10_3_0/Mk/Uses/gettext-tools.mk 399326 2015-10-15 07:36:38Z bapt $
#
# Handle dependency on the gettext-tools port
#
# Feature:	gettext-tools
# Usage:	USES=gettext-tools or USES=gettext-tools:ARGS
# Valid ARGS:	build (default), run
#
# MAINTAINER:	portmgr@FreeBSD.org

.if !defined(_INCLUDE_USES_GETTEXT_TOOLS_MK)
_INCLUDE_USES_GETTEXT_TOOLS_MK=	yes

.if empty(gettext-tools_ARGS)
gettext-tools_ARGS=	build
.endif

.if ${gettext-tools_ARGS:Mbuild}
BUILD_DEPENDS+=	msgfmt:${PORTSDIR}/devel/gettext-tools
.endif
.if ${gettext-tools_ARGS:Mrun}
RUN_DEPENDS+=	msgfmt:${PORTSDIR}/devel/gettext-tools
.endif

.endif
