lib = File.expand_path("../lib", __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)

Gem::Specification.new do |s|
  s.name    = "barcode"
  s.version = "0.1.0"
  s.summary = "barcode binding for Ruby"
  s.author  = "Julien Boulnois"

  s.files = Dir["{lib,ext}/**/*",
    "Rakefile",
    "README"]

  s.extensions << "ext/barcode/extconf.rb"
  s.require_paths = ["lib", "ext"]

  s.add_development_dependency 'rake-compiler', '~> 1.0'

end
