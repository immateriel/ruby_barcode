spec = Gem::Specification.load("barcode.gemspec")

task :clean do
  sh "cd ext && make clean; echo"
end

task :default => [:compile]

task :extconf => [:clean] do
  sh "cd ext && ruby extconf.rb"
end

task :compile => [:extconf] do
  sh "cd ext && make"
end