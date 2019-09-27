# frozen_string_literal: true

require 'bundler/gem_tasks'
require 'rspec/core/rake_task'
require 'rake/extensiontask'
require 'fileutils'

RSpec::Core::RakeTask.new(:spec)

gemspec = Gem::Specification.load('bsm.gemspec')
Rake::ExtensionTask.new do |ext|
  ext.name = 'internal'
  ext.ext_dir = 'ext/bsm/internal'
  ext.lib_dir = 'lib/bsm/bsm_parse'
  ext.gem_spec = gemspec
  ext.source_pattern = '*.{c,cpp}'
end

task :regen_parser do
  sh %(cd ext/bsm/internal && NO_PRESETS=true ruco bsm.ruco)
end

task default: [:test]
task test: %i[regen_parser compile spec]
