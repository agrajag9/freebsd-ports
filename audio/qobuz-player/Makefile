PORTNAME=	qobuz-player
DISTVERSIONPREFIX=	v
DISTVERSION=	0.6.5
CATEGORIES=	audio

MAINTAINER=	agrajag9@a9development.com
COMMENT=	High resolution audio player backed by Qobuz
WWW=		https://github.com/SofusA/qobuz-player

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libasound.so:audio/alsa-lib

USES=		cargo \
		gstreamer \
		sqlite \
		ssl
USE_GITHUB=	yes
GH_ACCOUNT=	SofusA
CARGO_INSTALL=	no

PLIST_FILES=	bin/${PORTNAME}

do-install:
	${INSTALL_PROGRAM} ${WRKDIR}/target/release/${PORTNAME} ${STAGEDIR}${PREFIX}/bin/

.include <Makefile.crates>
.include <bsd.port.mk>
