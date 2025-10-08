set debuginfod enabled off
set pagination off
file range
set args -100 100 3
set $counter = 0
break range.c:32
commands 1
silent
set $counter = $counter + 1
if $counter >= 28 && $counter <= 35
echo @@@\n
printf "iter=%d, start=%ld, end=%ld, step=%ld, current=%ld\n", $counter, start, end, step, current
end
continue
end
set inferior-tty /dev/null
run
