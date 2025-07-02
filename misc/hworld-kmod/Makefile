PORTNAME=	hworld-kmod
DISTVERSIONPREFIX=	v
DISTVERSION=	0.0.1
CATEGORIES=	misc

MAINTAINER=	agrajag9@a9development.com
COMMENT=	FreeBSD hello world kmod
WWW=		https://github.com/agrajag9/hworld-kmod/

LICENSE=	BSD2CLAUSE

USES=		kmod
USE_GITHUB=	yes
GH_ACCOUNT=	agrajag9

PLIST_FILES=	${KMODDIR}/hworld_kmod.ko

do-install:
	${INSTALL_KLD} ${WRKSRC}/hworld-kmod.ko ${STAGEDIR}${KMODDIR}

.include <bsd.port.mk>
