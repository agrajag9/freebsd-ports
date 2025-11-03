PORTNAME=	arrpc
DISTVERSION=	3.6.0
CATEGORIES=	net-im

MAINTAINER=	agrajag9@a9development.com
COMMENT=	Open implementation of Discord's local RPC servers

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		node

USE_NODE=	npm:build

USE_GITHUB=	yes
GH_ACCOUNT=	OpenAsar
GH_PROJECT=	arrpc

do-build:
		cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${NPM_CMD} install

.include <bsd.port.mk>
