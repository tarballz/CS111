# Created by: Timothy Beyer <beyert@cs.ucr.edu>
# $FreeBSD: tags/RELEASE_10_3_0/japanese/tegaki-recognize/Makefile 371202 2014-10-19 17:45:13Z mva $

PORTNAME=	tegaki
PORTVERSION=	0.3.1.2
CATEGORIES=	japanese python
MASTER_SITES=	http://www.tegaki.org/releases/${PORTVERSION:.2=}/
PKGNAMESUFFIX=	-recognize
DISTNAME=	${PORTNAME}${PKGNAMESUFFIX}-${PORTVERSION}

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Open-Source Chinese and Japanese Handwriting Recognition

LICENSE=	GPLv2

LIB_DEPENDS=	libzinnia.so:${PORTSDIR}/japanese/zinnia
RUN_DEPENDS=	${PYTHON_SITELIBDIR}/tegakigtk/recognizer.py:${PORTSDIR}/japanese/py-tegaki-gtk

OPTIONS_DEFINE=	DOCS

USES=		python:2
USE_PYTHON=	distutils
PYDISTUTILS_PKGNAME=	${PORTNAME}_recognize

post-install:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/AUTHORS ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/COPYING ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/COPYRIGHT ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${STAGEDIR}${DOCSDIR}

post-patch:
	@${REINPLACE_CMD} \
		-e 's,distutils\.command\.install ,setuptools\.command\.install ,' \
		${WRKSRC}/setup.py

.include <bsd.port.mk>
