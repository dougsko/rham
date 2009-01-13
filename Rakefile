#!/usr/bin/env ruby

require 'rake/rdoctask'
require 'rake/testtask'
require 'rake/gempackagetask'

# Define global vars
PROJECT = "Rham"
MY_NAME = "Doug Prostko"
MY_EMAIL = "dougtko@gmail.com"
PROJECT_SUMMARY = "libham wrapper"
UNIX_NAME = "rham"
WEBSITE_DIR = "."
RDOC_HTML_DIR = "#{WEBSITE_DIR}/rdoc"
DEPS = ""

# Find version info
REQUIRE_PATHS = ["."]
$LOAD_PATH.concat(REQUIRE_PATHS)
# This library file defines the MyProject::VERSION constant.
require_files = FileList["ext/*.so", "lib/*.rb"]
require_files.each do |file|
	require file
end
PROJECT_VERSION = eval("#{PROJECT}::VERSION")

# Options common to RDocTask AND Gem::Specification.
# The --main argument specifies which file appears on the index.html page
GENERAL_RDOC_OPTS = {
        "--title" => "#{PROJECT} Documentation",
        "--main" => "README",
}

# Extra RDOC files
RDOC_FILES = FileList["README", "LICENSE"]

# Filelist with Test::Unit test cases.
TEST_FILES = FileList["test/**/*.rb"]

# Executable scripts, all non-garbage files under bin/.
BIN_FILES = FileList["**/*.rb"]

# This filelist is used to create source packages.
# Include all Ruby and RDoc files.
DIST_FILES = FileList["**/*.rdoc", "README", "LICENSE"]
DIST_FILES.include("Rakefile")
DIST_FILES.include(BIN_FILES)
DIST_FILES.include("ext/*.so", "lib/*.rb", "lib/*.so")

# Run the tests if rake is invoked without arguments.
task "default" => ["test"]
test_task_name = "test"
Rake::TestTask.new(test_task_name) do |t|
        t.test_files = TEST_FILES
        t.libs = REQUIRE_PATHS
end

# The "rdoc" task generates API documentation.
Rake::RDocTask.new("rdoc") do |t|
        t.rdoc_files = RDOC_FILES + BIN_FILES
        t.title = GENERAL_RDOC_OPTS["--title"]
        t.main = GENERAL_RDOC_OPTS["--main"]
        t.rdoc_dir = RDOC_HTML_DIR
end

GEM_SPEC = Gem::Specification.new do |s|
        s.name = UNIX_NAME
        s.version = PROJECT_VERSION
        s.summary = PROJECT_SUMMARY
        s.author = MY_NAME
        s.email = MY_EMAIL
        s.files = DIST_FILES
        s.test_files = TEST_FILES
        s.has_rdoc = true
        s.extra_rdoc_files = RDOC_FILES
        s.rdoc_options = GENERAL_RDOC_OPTS.to_a.flatten
        s.add_dependency(DEPS)
end

# Now we can generate the package-related tasks.
Rake::GemPackageTask.new(GEM_SPEC) do |pkg|
        pkg.need_zip = true
        pkg.need_tar = true
end

# The "prepare-release" task makes sure your tests run, and then generates
# files for a new release.
desc "Run tests, generate RDoc and create packages."
task "prepare-release" => ["clobber"] do
        puts "Preparing release of #{PROJECT} version #{PROJECT_VERSION}"
        Rake::Task["test"].invoke
        Rake::Task["rdoc"].invoke
        Rake::Task["package"].invoke
end
