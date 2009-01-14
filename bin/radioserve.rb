#!/usr/bin/env ruby 
#
#
# serves a rig object for a remote client to work with
#

require 'lib/rham'
require 'drb'
require 'drb/acl'

acl = ACL.new(%w(deny all
                 allow localhost
                 allow igotinternets.net))
DRb.install_acl(acl)

DRb.start_service("druby://192.168.0.6:7176", Rham.new)
puts DRb.uri

DRb.thread.join
