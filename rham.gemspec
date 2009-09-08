# Generated by jeweler
# DO NOT EDIT THIS FILE
# Instead, edit Jeweler::Tasks in Rakefile, and run `rake gemspec`
# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{rham}
  s.version = "0.0.1"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["dougsko"]
  s.date = %q{2009-09-07}
  s.description = %q{ruby wrapper for libham}
  s.email = %q{dougtko@gmail.com}
  s.executables = ["radio.rhtml", "radioserve.rb", "radioclient.rb"]
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = [
    "LICENSE",
     "README.rdoc"
  ]
  s.files = [
    "LICENSE",
     "README.rdoc",
     "Rakefile",
     "VERSION",
     "bin/radio.rhtml",
     "bin/radioclient.rb",
     "bin/radioserve.rb",
     "ext/extconf.rb",
     "ext/rham.c",
     "lib/rham.rb",
     "spec/rham_spec.rb",
     "spec/spec_helper.rb"
  ]
  s.homepage = %q{http://github.com/dougsko/rham}
  s.rdoc_options = ["--charset=UTF-8"]
  s.require_paths = ["lib"]
  s.rubygems_version = %q{1.3.5}
  s.summary = %q{A ruby wrapper for libham}
  s.test_files = [
    "spec/spec_helper.rb",
     "spec/rham_spec.rb"
  ]

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 3

    if Gem::Version.new(Gem::RubyGemsVersion) >= Gem::Version.new('1.2.0') then
      s.add_development_dependency(%q<rspec>, [">= 0"])
    else
      s.add_dependency(%q<rspec>, [">= 0"])
    end
  else
    s.add_dependency(%q<rspec>, [">= 0"])
  end
end
