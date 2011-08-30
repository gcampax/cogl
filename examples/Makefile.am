include $(top_srcdir)/build/autotools/Makefile.am.silent

INCLUDES = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/clutter/cogl \
	-I$(top_builddir)/clutter/cogl

AM_CFLAGS = \
	$(COGL_DEP_CFLAGS) \
	$(COGL_EXTRA_CFLAGS) \
	-DCOGL_ENABLE_EXPERIMENTAL_2_0_API \
	-DCOGL_EXAMPLES_DATA=\""$(abs_top_srcdir)/examples/"\"

AM_CPPFLAGS = \
	-DG_DISABLE_SINGLE_INCLUDES \
	-DCOGL_DISABLE_DEPRECATED


common_ldadd = \
	$(COGL_DEP_LIBS) \
	$(top_builddir)/cogl/libcogl.la

noinst_PROGRAMS = 

if HAVE_GDK_EXAMPLE
noinst_PROGRAMS += gdk-cogl

gdk_cogl_SOURCES = gdk-cogl.c
gdk_cogl_CFLAGS = $(GDK_CFLAGS) $(AM_CFLAGS) $(AM_CPPFLAGS)
gdk_cogl_LDADD = $(GDK_LIBS) $(common_ldadd)
endif

if BUILD_COGL_PANGO
if HAVE_EGL_EXAMPLE
noinst_PROGRAMS += crate
crate_SOURCES = crate.c
crate_LDADD = $(common_ldadd) $(top_builddir)/cogl-pango/libcogl-pango.la
crate_CFLAGS = $(AM_CFLAGS) $(COGL_PANGO_DEP_CFLAGS)
endif
endif

if X11_TESTS
noinst_PROGRAMS += x11-foreign x11-tfp
x11_foreign_SOURCES = x11-foreign.c
x11_foreign_LDADD = $(common_ldadd)
x11_tfp_SOURCES = x11-tfp.c
x11_tfp_LDADD = $(common_ldadd)
endif

if SUPPORT_WAYLAND_EGL_SERVER
noinst_PROGRAMS += cogland
cogland_SOURCES = cogland.c
cogland_LDADD = $(common_ldadd)
endif

EXTRA_DIST = \
	crate.jpg \
	android/hello/AndroidManifest.xml \
	android/hello/jni/Application.mk \
	android/hello/jni/Android.mk \
	android/hello/jni/main.c \
	android/hello/res/values \
	android/hello/res/values/strings.xml \
	android/hello/.gitignore \
	android/hello/build.xml

