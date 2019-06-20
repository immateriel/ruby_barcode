# somewhere in your Rakefile, define your gem spec
spec = Gem::Specification.new do |s|
  s.name    = "barcode"
  s.version = "0.1.0"
  s.summary = "barcode binding for Ruby"
  s.author  = "Julien Boulnois"

  s.extensions = "ext/extconf.rb"

  s.files = Dir.glob("ext/*.{c,h,rb}") +
            Dir.glob("lib/*.{rb,so}")
end
