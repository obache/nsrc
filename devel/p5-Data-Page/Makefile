# $NetBSD: Makefile,v 1.20 2021/05/24 19:50:26 wiz Exp $

DISTNAME=	Data-Page-2.03
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	3
CATEGORIES=	databases perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Data/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://metacpan.org/release/Data-Page
COMMENT=	Pager utility for Class::DBI
LICENSE=	${PERL5_LICENSE}

DEPENDS+=	p5-Class-Accessor-Chained>=0:../../devel/p5-Class-Accessor-Chained
BUILD_DEPENDS+=	p5-Test-Exception>=0:../../devel/p5-Test-Exception

USE_LANGUAGES=		# empty
PERL5_PACKLIST=		auto/Data/Page/.packlist

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
