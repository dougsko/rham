#!/usr/bin/ev ruby
#
#
# Ruby methods for the Rham class
#
class Rham
	def stats
		stats = {}
		stats["freq"] = rig_get_freq
		stats["strength"] = rig_get_strength
		stats["mode"] = rig_get_mode
		stats
	end
end
