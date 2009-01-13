#!/usr/bin/env ruby
#
#
require 'rham.so'

a = Rham.new
a.rig_open
a.rig_get_info
puts a.rig_get_freq
a.rig_get_vfo
puts a.rig_get_powerstat
