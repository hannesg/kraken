#!/usr/bin/env ruby
require "set"


class Hitman

  SourceLocation = Struct.new(:file, :line)

  class RecursiveFileEnumerator
    include Enumerable
    def initialize(dir)
      @dir = dir
    end

    def each(&block)
      Dir.new(@dir).each do |fn|
        next if fn =~ /\.{1,2}$/
        n = File.join(@dir,fn)
        if File.directory? n
          RecursiveFileEnumerator.new(n).each &block
        else
          block.call( n )
        end
      end
    end

  end

  class DependencySet

    include Enumerable

    def initialize()
      @deps = Hash.new{|hsh,key| hsh[key] = [] }
    end

    def require(what, file = '(unknown)', at = '-1' )
      @deps[what] << SourceLocation.new(file,at)
      return self
    end

    def <<(other)
      other.deps.each do |k,v|
        @deps[k].push(*v)
      end
      return self
    end

    def each(&block)
      @deps.each_key(&block)
    end

    def deps
      return @deps
    end

  end

  def cpp?(what)
    @srcdirs.any?{|d| File.exists?(d+'/'+what+'.cpp') }
  end

  def h?(what)
    @srcdirs.any?{|d| File.exists?(d+'/'+what+'.h') }
  end

  def h(what)
    @srcdirs.each do |d|
      return d+'/'+what+'.h' if File.exists?(d+'/'+what+'.h')
    end
    raise "Unable to find the .h file for #{what}. Searched in: #{@srcdir.join(', ')}"
  end

  def cpp(what)
    @srcdirs.each do |d|
      return d+'/'+what+'.cpp' if File.exists?(d+'/'+what+'.cpp')
    end
    raise "Unable to find the .cpp file for #{what}. Searched in: #{@srcdir.join(', ')}"
  end

  def o(what)
    File.join(@build_dir,what+'.o')
  end

  def bin(what)
    File.join(@bin_dir,what)
  end

  def executable?(what)
    cpp?(what) and @executables.include?(cpp(what))
  end

  def initialize(&block)
    @srcdirs = []
    @executables = []
    @build_dir = 'build'
    @bin_dir = '.'
    instance_eval(&block)
  end


  def srcdir(*args)
    @srcdirs.push(*args)
  end

  def executable(*args)
    args.each do |arg|
      @executables.push(*Dir[arg])
    end
  end

  def load!
    @dependencies = Hash.new{|hsh,key| hsh[key] = DependencySet.new }
    @srcdirs.each do |srcdir|
      RecursiveFileEnumerator.new(srcdir).each do |srcfile|
        next unless srcfile =~ /\.(h|cpp)$/
        file = srcfile[srcdir.length+1..-1]
        m = /^(.*)\.([^\.]+)$/.match(file)
        @dependencies[m[1]] << read_deps!(srcfile)
      end
    end
  end

  def read_deps!(srcfile)
    deps = DependencySet.new
    File.read(srcfile).each_line.each_with_index do |line,i|
      if line =~ /^#include "([^"]+)\.h"/
        deps.require( $1, srcfile , i )
      end
    end
    return deps
  end

  def cxx_args
    [' -pthread -Wall -std=c++0x' ]
  end

  def cxx_cargs
    ( cxx_args + [ *@srcdirs.map{|d| "-I#{d}"} ] ).join(' ')
  end

  def cxx_ld
    ( cxx_args ).join(' ')
  end

  def echo!
    buf = []
    @dependencies.each do |name,deps|
      if cpp? name
        buf << o(name) << ': ' << [ cpp(name), *deps.map{|n| h(n) if h?(n) }.compact].join(' ') << "\n"
        buf << "\tg++ -c " << cxx_cargs << ' ' << cpp(name) << ' -o ' << o(name) << "\n"
        if executable? name
          buf << bin(name) << ': ' << [ expand(name).map{|n| cpp?(n) ? o(n) : h(n) } ].join(' ') << "\n"
          buf << "\tg++ " << cxx_ld << ' ' << expand(name).select{|n| cpp?(n) }.map{|n| o(n) }.join(' ') << ' ' << ' -o ' << File.basename(name) << "\n"
        end
      end
    end
    buf << 'all: ' << executables.join(' ') << "\n"
    buf << 'clean: ' << "\n"
    buf << "\trm -rf " << ( executables + objects ).join(' ') << "\n"
    buf << 'Makefile: configure.rb src/* tests/*' << "\n"
    buf << "\truby configure.rb > Makefile\n"
    buf << ".PHONY: all clean\n"

    puts buf.join
  end

  def objects
    return @dependencies.select{|d,_| cpp?(d) and not executable?(d) }.map{|d,_| o(d) }
  end

  def executables
    return @executables.map{|e| bin(entity_name(e)) }
  end

  def entity_name(file)
    @srcdirs.each{|d| return file[d.length..-5] if file[0...d.length] == d }
  end

  def print_deps!
    @dependencies.each do |name,deps|
      puts name
      deps.deps.each do |name, locations|
        puts "\t" + name
        locations.each do |loc|
          puts "\t\t" + loc.inspect
        end
        puts expand(name).inspect
      end
    end
  end

  def expand!
  end

  def expand(dep)
    d = @dependencies[dep]
    missing = d.each.to_a
    result = Set[dep, *missing]
    until missing.none?
      still_missing = []
      missing.each do |m|
        @dependencies[m].each do |dd|
          if not result.include? dd
            still_missing << dd
            result << dd
          end
        end
      end
      missing = still_missing
    end
    return result.to_a
  end

end


h = Hitman.new do

  srcdir 'src'
  srcdir 'tests'

  executable 'tests/test_*.cpp'

end

h.load!
h.expand!
h.echo!
#h.print_deps!
#puts deps.inspect
