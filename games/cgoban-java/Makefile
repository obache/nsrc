# $NetBSD: Makefile,v 1.54 2020/12/02 08:50:24 ast Exp $
#

DISTNAME=	cgoban-java-3.5.23
CATEGORIES=	games java
MASTER_SITES=	${MASTER_SITE_LOCAL}
# Mirrored from http://files.gokgs.com/javaBin/cgoban.jar
EXTRACT_SUFX=	.jar

MAINTAINER=	ast@NetBSD.org
HOMEPAGE=	https://www.gokgs.com/
COMMENT=	Client for the KGS Go Server and SGF viewer/editor
LICENSE=	generic-nonlicense

WRKSRC=		${WRKDIR}
USE_JAVA=	run
USE_JAVA2=	yes
USE_TOOLS+=	printf

INSTALLATION_DIRS=	bin lib/java

do-build:
	printf "#! ${SH}\\nexec ${JAVA_BINPREFIX}-java -jar ${PREFIX}/lib/java/${DISTNAME}.jar \"\$$@\"\\n" > ${WRKSRC}/cgoban-java.sh

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/cgoban-java.sh \
		${DESTDIR}${PREFIX}/bin/cgoban-java
	${INSTALL_DATA} ${WRKSRC}/${DISTNAME}.jar \
		${DESTDIR}${PREFIX}/lib/java/${DISTNAME}.jar

.include "../../mk/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
