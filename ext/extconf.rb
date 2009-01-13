require 'mkmf'

$CFLAGS = "-Wall"
srcs = ["rham.c"]
have_library("hamlib", "rig_init")
create_makefile("rham")
