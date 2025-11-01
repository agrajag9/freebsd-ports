PORTNAME=	arrpc
DISTVERSION=	3.6.0
CATEGORIES=	net-im

MAINTAINER=	agrajag9@a9development.com
COMMENT=	Open implementation of Discord's local RPC servers

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		electron:37,build

USE_ELECTRON=	npm:npm prefetch extract rebuild:electron build:forge

USE_GITHUB=	yes
GH_ACCOUNT=	OpenAsar
GH_PROJECT=	arrpc

.include <bsd.port.mk>
