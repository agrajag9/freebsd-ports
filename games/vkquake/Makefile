PORTNAME=	vkquake
DISTVERSION=	1.32.2
CATEGORIES=	games

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Vulkan Quake port based on QuakeSpasm
WWW=		https://github.com/Novum/vkQuake

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	glslangValidator:graphics/glslang \
		vulkan-headers>0:graphics/vulkan-headers
LIB_DEPENDS=	libvulkan.so:graphics/vulkan-loader

USES=		desktop-file-utils meson pkgconfig sdl

USE_GITHUB=	yes
GH_ACCOUNT=	Novum
GH_PROJECT=	vkQuake
USE_SDL=	sdl2

.include "${.CURDIR}/../quake-data/Makefile.include"

CFLAGS+=	-DDATADIR='\"${Q1DIR}\"' -Wno-error=atomic-alignment

OPTIONS_DEFINE=			DEBUG FLAC OPUS USERDIRS VORBIS WAVE
OPTIONS_DEFAULT=		FLAC MP3 OPUS USERDIRS VORBIS WAVE
OPTIONS_RADIO=			MP3LIBRARY
OPTIONS_RADIO_MP3LIBRARY=	MAD MP3

MP3LIBRARY_DESC=	MP3 audio library
USERDIRS_DESC=		Support loading game data from user directories (~/.vkquake)
WAVE_DESC=		Wave audio support

DEBUG_MESON_ON=		--buildtype=debug --optimization=0
DEBUG_MESON_OFF=	--buildtype=plain --optimization=2
FLAC_LIB_DEPENDS=	libFLAC.so:audio/flac
FLAC_MESON_ENABLED=	use_codec_flac
MAD_LIB_DEPENDS=	libmad.so:audio/libmad
MAD_MESON_ARGS=		-Duse_codec_mp3=enabled
MAD_MESON_ON=		-Dmp3_lib=mad
MP3_LIB_DEPENDS=	libmpg123.so:audio/mpg123
MP3_MESON_ARGS=		-Duse_codec_mp3=enabled
MP3_MESON_ON=		-Dmp3_lib=mpg123
OPUS_LIB_DEPENDS=	libopus.so:audio/opus \
			libopusfile.so:audio/opusfile
OPUS_MESON_ENABLED=	use_codec_opus
USERDIRS_MESON_ENABLED=	do_userdirs
VORBIS_LIB_DEPENDS=	libogg.so:audio/libogg \
			libvorbis.so:audio/libvorbis \
			libvorbisfile.so:audio/libvorbis
VORBIS_MESON_ENABLED=	use_codec_vorbis
WAVE_MESON_ENABLED=	use_codec_wave

post-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${MESON_BUILD_DIR}/${PORTNAME} \
		${STAGEDIR}${PREFIX}/bin
	${MKDIR} ${STAGEDIR}${Q1DIR}
	${INSTALL_DATA} ${WRKSRC}/Quake/vkquake.pak \
		${STAGEDIR}${Q1DIR}
	${MKDIR} ${STAGEDIR}${PREFIX}/share/icons/hicolor/256x256/apps
	${INSTALL_DATA} ${FILESDIR}/vkquake.png \
		${STAGEDIR}${PREFIX}/share/icons/hicolor/256x256/apps/vkquake.png
	${INSTALL_DATA} ${FILESDIR}/vkquake.desktop \
		${STAGEDIR}${PREFIX}/share/applications

.include <bsd.port.mk>
