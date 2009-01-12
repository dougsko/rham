require 'mkmf'

hamlibsrc = ENV["PWD"] + "/hamlib-1.2.8/src"

$CFLAGS = "-Wall -I/usr/local/include/hamlib"

#srcs = ["rham.c", "#{hamlibsrc}/rig.c" ]
srcs = ["rham.c"]

have_library("hamlib", "rig_init")

$objs = srcs.collect { |f| f.sub(".c", ".o") }

create_makefile("rham")


