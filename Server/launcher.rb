#!/usr/bin/env ruby

require "serialport"
require "pry-byebug"
require "airborne"
require "json"

# Basic server that will make some API calls and change the LED mode.

class Launcher
  def initialize
    @KEY  = ENV["BitBucketKey"]

    @port = "/dev/ttyACM0"
    @baud = 57600
    @data = 8
    @stop = 1
    @parity = SerialPort::NONE

    puts("Getting latest commit...")    
    get_latest_commit

    puts("Connecting to serial port...")
    @serial_port   = SerialPort.new(@port, @baud, @data, @stop, @parity)
    sleep(5)

    puts("Setting default hue...")
    @serial_port.putc("h")
    @serial_port.putc("1")
    @serial_port.putc("1")
    @serial_port.putc("5")

    sleep(5)

    puts("Setting default mode...")
    @serial_port.putc("m")
    @serial_port.putc("4")
    @serial_port.putc("0")
  end

  def get_latest_commit
    cmd = "curl -s --user cditchfield:#{@KEY} https://api.bitbucket.org/2.0/repositories/neadwerx/xerp"
    result = `#{cmd}`

    @latest_commit = JSON.parse(result)["updated_on"]
	
    puts("Latest commit: #{@latest_commit}")
  end

  def run_loading_bar
    puts("----------------------")
    puts(" ")
    puts("Running loading bar...")
    puts(" ")
    puts("----------------------")
    @serial_port.putc("m")
    @serial_port.putc("3")
    @serial_port.putc("9")  
  end 

  def exec
    current_commit = @latest_commit
    get_latest_commit

    if current_commit != @latest_commit
      run_loading_bar
      latest_commit = current_commit 
    end    
  end
end

launcher = Launcher.new

loop do
  sleep(10)
  launcher.exec
end
