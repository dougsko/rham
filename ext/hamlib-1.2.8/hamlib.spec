%define ver 1.2.8
%define prefix	/usr

Summary: Run-time library to control radio transcievers and receivers.
Name: hamlib
Version: %ver
Release: 1
Copyright: LGPL
Group: Ham/Libraries
Packager: Stephane Fillod <fillods@users.sourceforge.net>
Source: http://prdownloads.sourceforge.net/hamlib/hamlib-%{ver}.tar.gz
BuildRoot: /tmp/hamlib-%{ver}-buildroot
URL: http://hamlib.sourceforge.net
BuildRequires: binutils >= 2.9.4, gcc >= 2.95, glibc-devel >= 2.1
BuildRequires: /bin/sh, fileutils, findutils, flex
BuildRequires: gzip, make >= 3.77, patch >= 2.5, rpm >= 3.0, sed
BuildRequires: textutils
BuildRequires: /bin/sh, automake >= 1.4, libtool >= 1.4, fileutils, findutils

%changelog

* Tue Sep 26 2004 Stephane Fillod
- New backends: skanti, racal, wj, tuner
- New command 'rigswr'

* Tue Jan 20 2004 Tomi Manninen
- Fix for 1.1.5pre2
- Better use of rpm macros
- Disable all bindings

* Tue Oct 08 2003 Joop Stakenborg
- Fix 'make rpm' again by disabling c++ bindings.
- rotclass.h and rigclass.h go into the devel package for now (FIXME)

* Wed Jan 15 2003 Joop Stakenborg
- Fix the spec file for 1.1.4CVS
- 'make rpm' should work now

* Thu Jun 17 2002 Stephane Fillod
- Added rotator support
- Added RPC daemon, hamlib.m4
- Upstream version 1.1.3

* Mon Jul 18 2001 Stephane Fillod
- Made initial "working" SPEC file


%description
 Most recent amateur radio transceivers allow external control of their
 functions through a computer interface. Unfortunately, control commands are
 not always consistent across a manufacturer's product line and each
 manufacturer's product line differs greatly from its competitors.
 .
 This library addresses that issue by providing a standardised programming
 interface that applications can talk to and translating that into the
 appropriate commands required by the radio in use.
 .
 This package provides the run-time form of the library. If you wish to
 develop software using this library you need the 'hamlib-devel' package.
 .
 Also included in the package is a simple radio control program 'rigctl',
 which let one control a radio transceiver or receiver, either from
 command line interface or in a text-oriented interactive interface.

%package devel
Summary: Development library to control radio transcievers and receivers.
Group: Development/Libraries
Requires: hamlib

%description devel
 Most recent amateur radio transceivers allow external control of their
 functions through a computer interface. Unfortunately, control commands are
 not always consistent across a manufacturer's product line and each
 manufacturer's product line differs greatly from its competitors.
 .
 This library addresses that issue by providing a standardised programming
 interface that applications can talk to and translating that into the
 appropriate commands required by the radio in use.
 .
 This package provides the development library. If you wish to run applications
 developed using this library you'll need the 'hamlib' package.

#%package c++
#Summary: Hamlib radio control library C++ binding
#Group: Development/Libraries
#Requires: hamlib

#%description c++
#C++ Binding.

#%package c++-devel
#Summary: Hamlib radio control library C++ binding headers and static libs
#Group: Development/Libraries
#Requires: hamlib, hamlib-devel

#%description c++-devel
#This package contains all of the headers and the static libraries 
#for C++ binding of Hamlib.

#You'll only need this package if you are doing development.

#%package perl
#Summary: Hamlib radio control library Perl binding
#Group: Development/Libraries
#Requires: hamlib
#
#%description perl
#Perl Binding.

%prep
%setup
%build

%configure --without-cxx-binding   \
	   --without-perl-binding  \
	   --without-kylix-binding \
	   --without-tcl-binding   \
	   --without-python-binding
make CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" all

%install
rm -rf $RPM_BUILD_ROOT
(umask 077 && mkdir -p $RPM_BUILD_ROOT)
chmod go= $RPM_BUILD_ROOT
%makeinstall

chmod 644 $RPM_BUILD_ROOT%{prefix}/lib/*.la
#strip $RPM_BUILD_ROOT%{prefix}/lib/*-%{version}.so


%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(644, root, root, 755)
%doc COPYING

#%doc doc/*.html
#%doc doc/*.sgml
#%doc doc/*.txt

%defattr(755, root, root, 755)
%{_libdir}/libhamlib-%{ver}.so.2
%{_libdir}/libhamlib-%{ver}.so.2.0.4
%{_libdir}/libhamlib.la
%{_libdir}/hamlib-alinco.so
%{_libdir}/hamlib-alinco.la
%{_libdir}/hamlib-aor.so
%{_libdir}/hamlib-aor.la
%{_libdir}/hamlib-drake.so
%{_libdir}/hamlib-drake.la
%{_libdir}/hamlib-dummy.so
%{_libdir}/hamlib-dummy.la
%{_libdir}/hamlib-easycomm.so
%{_libdir}/hamlib-easycomm.la
%{_libdir}/hamlib-flexradio.so
%{_libdir}/hamlib-flexradio.la
%{_libdir}/hamlib-fodtrack.so
%{_libdir}/hamlib-fodtrack.la
%{_libdir}/hamlib-icom.so
%{_libdir}/hamlib-icom.la
%{_libdir}/hamlib-jrc.so
%{_libdir}/hamlib-jrc.la
%{_libdir}/hamlib-kachina.so
%{_libdir}/hamlib-kachina.la
%{_libdir}/hamlib-kenwood.so
%{_libdir}/hamlib-kenwood.la
%{_libdir}/hamlib-kit.so
%{_libdir}/hamlib-kit.la
%{_libdir}/hamlib-lowe.so
%{_libdir}/hamlib-lowe.la
%{_libdir}/hamlib-microtune.so
%{_libdir}/hamlib-microtune.la
%{_libdir}/hamlib-pcr.so
%{_libdir}/hamlib-pcr.la
%{_libdir}/hamlib-racal.so
%{_libdir}/hamlib-racal.la
%{_libdir}/hamlib-rft.so
%{_libdir}/hamlib-rft.la
%{_libdir}/hamlib-rotorez.so
%{_libdir}/hamlib-rotorez.la
%{_libdir}/hamlib-rpcrig.so
%{_libdir}/hamlib-rpcrig.la
%{_libdir}/hamlib-rpcrot.so
%{_libdir}/hamlib-rpcrot.la
%{_libdir}/hamlib-sartek.so
%{_libdir}/hamlib-sartek.la
%{_libdir}/hamlib-skanti.so
%{_libdir}/hamlib-skanti.la
%{_libdir}/hamlib-tapr.so
%{_libdir}/hamlib-tapr.la
%{_libdir}/hamlib-tentec.so
%{_libdir}/hamlib-tentec.la
%{_libdir}/hamlib-tuner.so
%{_libdir}/hamlib-tuner.la
%{_libdir}/hamlib-uniden.so
%{_libdir}/hamlib-uniden.la
%{_libdir}/hamlib-winradio.so
%{_libdir}/hamlib-winradio.la
%{_libdir}/hamlib-wj.so
%{_libdir}/hamlib-wj.la
%{_libdir}/hamlib-yaesu.so
%{_libdir}/hamlib-yaesu.la
%{_bindir}/rigctl
%{_sbindir}/rpc.rigd
%{_mandir}/man1/rigctl.1.gz
%{_mandir}/man8/rpc.rigd.8.gz
%{_bindir}/rotctl
%{_sbindir}/rpc.rotd
%{_mandir}/man1/rotctl.1.gz
%{_mandir}/man8/rpc.rotd.8.gz
%{_bindir}/rigmem
%{_mandir}/man1/rigmem.1.gz
%{_bindir}/rigswr
%{_mandir}/man1/rigswr.1.gz

%files devel
%defattr(644, root, root, 755)

%{_includedir}/hamlib/rig.h
%{_includedir}/hamlib/rigclass.h
%{_includedir}/hamlib/rotclass.h
%{_includedir}/hamlib/rig_dll.h
%{_includedir}/hamlib/riglist.h
%{_includedir}/hamlib/rotator.h
%{_includedir}/hamlib/rotlist.h
%{_datadir}/aclocal/hamlib.m4
%{_libdir}/pkgconfig/hamlib.pc
%{_libdir}/libhamlib.a
%{_libdir}/libhamlib.so
%{_libdir}/hamlib-alinco.a
%{_libdir}/hamlib-aor.a
%{_libdir}/hamlib-drake.a
%{_libdir}/hamlib-dummy.a
%{_libdir}/hamlib-easycomm.a
%{_libdir}/hamlib-flexradio.a
%{_libdir}/hamlib-fodtrack.a
%{_libdir}/hamlib-icom.a
%{_libdir}/hamlib-jrc.a
%{_libdir}/hamlib-kachina.a
%{_libdir}/hamlib-kenwood.a
%{_libdir}/hamlib-kit.a
%{_libdir}/hamlib-lowe.a
%{_libdir}/hamlib-microtune.a
%{_libdir}/hamlib-pcr.a
%{_libdir}/hamlib-racal.a
%{_libdir}/hamlib-rft.a
%{_libdir}/hamlib-rotorez.a
%{_libdir}/hamlib-rpcrig.a
%{_libdir}/hamlib-rpcrot.a
%{_libdir}/hamlib-sartek.a
%{_libdir}/hamlib-skanti.a
%{_libdir}/hamlib-tapr.a
%{_libdir}/hamlib-tentec.a
%{_libdir}/hamlib-tuner.a
%{_libdir}/hamlib-uniden.a
%{_libdir}/hamlib-winradio.a
%{_libdir}/hamlib-wj.a
%{_libdir}/hamlib-yaesu.a

#%files c++
#%defattr(755, root, root, 755)
#%{_libdir}/libhamlib++-%{version}.so


#%files c++-devel
#%defattr(644, root, root, 755)

#%{_includedir}/hamlib/rigclass.h
#%{_includedir}/hamlib/rotclass.h

#%{_datadir}/aclocal/hamlib++.m4
#%{_libdir}/libhamlib++.a
#%{_libdir}/libhamlib++.la

#%files perl
#%defattr(755, root, root, 755)
#/usr/local/lib/perl/5.6.1/Hamlib.pm
#%dir /usr/local/lib/perl/5.6.1/auto/Hamlib
#%doc /usr/local/man/man3/Hamlib.3pm

