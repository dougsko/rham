require 'mkmf'

hamlibsrc = ENV["PWD"] + "/hamlib-1.2.8/src"

$CFLAGS = "-Wall -I./hamlib-1.2.8/include -I#{hamlibsrc} -L/usr/local/lib"

#srcs = ["rham.c", "#{hamlibsrc}/rig.c" ]
srcs = ["rham.c"]

have_library("hamlib", "rig_allocate")

$objs = srcs.collect { |f| f.sub(".c", ".o") }

create_makefile("rham")


