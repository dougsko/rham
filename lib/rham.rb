#!/usr/bin/ev ruby
#
#
# Ruby methods for the Rham class
#
require 'rham.so'

class Rham
    # Sets up a new rig object.  You must first define variable, $model,
    # to a supported rig.
    #
    #   $model = "dummy"
    #   rig = Rham.new
    #
    def initialize
    end

    # Returns a hash containing the frequency and mode that the rig is
    # set to.
    #
    #   rig.stats    #=> {"freq" => "20000.0000", "mode" => "wide" }
    #
	def stats
		stats = {}
		stats["freq"] = rig_get_freq
		stats["mode"] = rig_get_mode
		stats
	end
end
