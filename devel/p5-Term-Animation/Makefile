# $NetBSD: Makefile,v 1.14 2021/05/24 19:51:37 wiz Exp $
#

DISTNAME=	Term-Animation-2.6
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	10
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=../../authors/id/K/KB/KBAUCOM/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://metacpan.org/release/Term-Animation
COMMENT=	ASCII sprite animation package
LICENSE=	${PERL5_LICENSE}

DEPENDS+=	p5-Curses>=1.06:../../devel/p5-Curses

PERL5_PACKLIST=	auto/Term/Animation/.packlist
USE_LANGUAGES=	# none

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
