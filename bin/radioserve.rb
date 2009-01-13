#!/usr/bin/env ruby 
#
#
# serves a rig object for a remote client to work with
#

require 'lib/rham'
require 'drb'

DRb.start_service nil, Rham.new
puts DRb.uri

DRb.thread.join
