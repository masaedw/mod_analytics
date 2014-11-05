mod_analytics.la: mod_analytics.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_analytics.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_analytics.la
