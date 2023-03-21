#!/bin/bash
read QEMU_PIDFILE < <(xxd -p -l 4 /dev/urandom)
read QEMU_PTY \
    < <(qemu-system-aarch64 -M raspi3b -kernel $1 -daemonize --pidfile $QEMU_PIDFILE -display none -serial null -serial pty -initrd $3 -dtb $4 \
    | sed 's/ /\n/g' | grep '/dev')
echo "QEMU serial port is attached to $QEMU_PTY"

tmux new \; \
     splitw -h \; \
     splitw -v \; \
     selectp -t 0 \; \
     send "screen $QEMU_PTY 115200" C-m \; \
     selectp -t 2 \; \
     send 'clear' C-m \; \
     selectp -t 1 \; \
     send 'bash' C-m "clear; while true; do read -p 'Press enter to load kernel ...'; ./$2 $QEMU_PTY; done" C-m

read QEMU_DAEMON < <(cat $QEMU_PIDFILE)
rm -f $QEMU_PIDFILE

kill -9 $QEMU_DAEMON
echo "QEMU daemon is killed (pid: $QEMU_DAEMON)"