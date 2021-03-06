#--
# Copyright (C)2007 Tony Arcieri
# You can redistribute this under the terms of the Ruby license
# See file LICENSE for details
#++

module Rev
  # The AsyncWatcher lets you signal another thread to wake up.  Its
  # intended use is notifying another thread of events.
  class AsyncWatcher < IOWatcher
    def initialize
      @reader, @writer = ::IO.pipe
      super(@reader)
    end

    # Signal the async watcher.  This call is thread safe.
    def signal
      # Write a byte to the pipe.  What we write is meaningless, it
      # merely signals an event has occurred for each byte written.
      @writer.write "\0"
    end
    
    # Called whenever a signal is received
    def on_signal; end
    event_callback :on_signal

    #########
    protected
    #########

    def on_readable
      # Read a byte from the pipe.  This clears readability, unless
      # another signal is pending
      @reader.read 1
      on_signal
    end
  end
end
