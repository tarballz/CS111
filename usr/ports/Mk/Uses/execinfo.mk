# $FreeBSD: tags/RELEASE_10_3_0/Mk/Uses/execinfo.mk 399326 2015-10-15 07:36:38Z bapt $
#
# handle dependency on libexecinfo
#
# Feature:	execinfo
# Usage:	USES=execinfo
#
# Takes no arguments
#
# Exported variables:
#
# EXECINFO_CPPFLAGS - preprocessor flags needed to correctly use
#                     execinfo library
# EXECINFO_LDFLAGS  - linker flags needed to correctly use
#                     execinfo library
#

.if !defined(_INCLUDE_USES_EXECINFO_MK)
_INCLUDE_USES_EXECINFO_MK=	yes

.if !exists(/usr/lib/libexecinfo.so)
LIB_DEPENDS+=	libexecinfo.so:${PORTSDIR}/devel/libexecinfo
EXECINFO_CPPFLAGS=	-I${LOCALBASE}/include
EXECINFO_LDFLAGS=	-L${LOCALBASE}/lib
.endif

.endif
