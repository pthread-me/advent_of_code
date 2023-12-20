set width 0
set height 0
set verbose off
start  # runs to main, so shared libraries are loaded
       # after you reach main, GDB should have libc symbols, "puts" among them
break puts
commands 1
backtrace
continue
end
