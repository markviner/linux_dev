set debuginfod enabled off
set pagination off
file range
set args 1 12
break range.c:32
commands 1
silent
if current % 5 == 0
echo @@@\n
printf "start=%ld, end=%ld, step=%ld, current=%ld\n", start, end, step, current
end
continue
end
set inferior-tty /dev/null
run
