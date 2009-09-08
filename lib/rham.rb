#!/usr/bin/ev ruby
#
#
# Ruby methods for the Rham class
#
require 'rham.so'

class Rham
	def stats
		stats = {}
		stats["freq"] = rig_get_freq
		stats["mode"] = rig_get_mode
		stats
	end
end
