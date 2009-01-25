#!/usr/bin/env ruby
#
#
require 'lib/rham'

a = Rham.new()
a.rig_open

a.rig_set_mode("AM", "normal")
a.rig_set_freq(20000)

a.stats.each do |k,v|
	puts "#{k} = #{v}"
end
