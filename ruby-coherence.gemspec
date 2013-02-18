# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{ruby-coherence}
  s.version = "0.0.1"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Flinn"]
  s.date = %q{2013-02-17}
  s.email = %q{flinn@actsasflinn.com}
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = ["README.rdoc"]
  s.files = ["COPYING", "Rakefile", "README.rdoc", "ext/coherence.c", "ext/coherence.h", "ext/extconf.rb"]
  s.homepage = %q{http://github.com/actsasflinn/ruby-coherence/}
  s.require_paths = ["ext"]
  s.rubygems_version = %q{1.3.7}
  s.summary = %q{A Ruby binding for Oracle Coherence}
  s.test_files = ["spec/spec.rb"]

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
    else
    end
  else
  end
end
