# $FreeBSD: tags/RELEASE_10_3_0/devel/gumbo/Makefile 385521 2015-05-06 15:16:53Z mat $

PORTNAME=	gumbo
PORTVERSION=	0.9.3
DISTVERSIONPREFIX=	v
CATEGORIES=	devel textproc

MAINTAINER=	bdrewery@FreeBSD.org
COMMENT=	Pure-C HTML5 parser

LICENSE=	APACHE20

USE_GITHUB=	yes
GH_ACCOUNT=	google
GH_PROJECT=	gumbo-parser

USES=		autoreconf gmake pathfix libtool
INSTALL_TARGET=	install-strip
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes
PATHFIX_MAKEFILEIN=Makefile.am

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libgumbo.so.1.0.0

.include <bsd.port.mk>
