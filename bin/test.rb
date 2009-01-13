#!/usr/bin/env ruby
#
#
require 'lib/rham'
require 'ext/rham'

a = Rham.new
a.rig_open

puts a.rig_get_info

a.rig_set_mode("AM", "normal")
a.rig_set_freq(20000)

a.stats.each do |k,v|
	puts "#{k} = #{v}"
end
