#!/usr/bin/env ruby
#
#

require 'drb'

$model = "dummy"

#DRb.start_service
a = DRbObject.new nil, ARGV.shift
a.rig_open

a.rig_set_mode("AM", "normal")
a.rig_set_freq(20000)

a.stats.each do |k,v|
	puts "#{k} = #{v}"
end
