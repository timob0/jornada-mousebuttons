################################################################################
#
# JORNADA_MOUSEBUTTONS
#
################################################################################

# Commit ID from Github

JORNADA_MOUSEBUTTONS_VERSION = 1.0.0
JORNADA_MOUSEBUTTONS_SITE_METHOD = git
JORNADA_MOUSEBUTTONS_SITE = https://github.com/timob0/jornada-mousebuttons.git

JORNADA_MOUSEBUTTONS_CFLAGS = $(TARGET_CFLAGS)
JORNADA_MOUSEBUTTONS_LICENSE = GPL
JORNADA_MOUSEBUTTONS_LICENSE_FILES = COPYING

# Options for building with libnl
JORNADA_MOUSEBUTTONS_CFLAGS = -I$(STAGING_DIR)/usr/include/libevdev-1.0 -levdev

define JORNADA_MOUSEBUTTONS_BUILD_CMDS
	$(TARGET_MAKE_ENV) CFLAGS="$(JORNADA_MOUSEBUTTONS_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" LIBS="$(JORNADA_MOUSEBUTTONS_LIBS)" \
		$(MAKE) CC="$(TARGET_CC)" -C $(@D)/$(JORNADA_MOUSEBUTTONS_SUBDIR)
endef

define JORNADA_MOUSEBUTTONS_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 -D $(@D)/$(JORNADA_MOUSEBUTTONS_SUBDIR)/out/evdev-rce \
		$(TARGET_DIR)/usr/bin/evdev-rce
endef

$(eval $(generic-package))
