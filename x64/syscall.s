
extern errno

__syscall:
	mov	r10, rcx
	syscall

	cmp	rax, 0
	jge	done
	cmp	rax, -4095
	jb	done
	neg	rax
	mov	[errno], eax
	mov	rax, -1
done:
	ret

global _exit
_exit:
	mov	rax, 60
	jmp	__syscall

global fork
fork:
	mov	eax, 57
	jmp	__syscall

global read
read:
	mov	eax, 0
	jmp	__syscall

global write
write:
	mov	eax, 1
	jmp	__syscall

global open
open:
	mov	eax, 2
	jmp	__syscall

global close
close:
	mov	eax, 3
	jmp	__syscall

global waitpid
waitpid:
	xor	rcx, rcx
	mov	eax, 61
	jmp	__syscall

global creat
creat:
	mov	eax, 85
	jmp	__syscall

global link
link:
	mov	eax, 86
	jmp	__syscall

global unlink
unlink:
	mov	eax, 87
	jmp	__syscall

global execve
execve:
	mov	eax, 59
	jmp	__syscall

global chdir
chdir:
	mov	eax, 80
	jmp	__syscall

global time
time:
	mov	eax, 201
	jmp	__syscall

global mknod
mknod:
	mov	eax, 133
	jmp	__syscall

global chmod
chmod:
	mov	eax, 90
	jmp	__syscall

global lseek
lseek:
	mov	eax, 8
	jmp	__syscall

global getpid
getpid:
	mov	eax, 39
	jmp	__syscall

global mount
mount:
	mov	eax, 165
	jmp	__syscall

global umount
umount:
	xor	rsi, rsi
	mov	eax, 166
	jmp	__syscall

global setuid
setuid:
	mov	eax, 105
	jmp	__syscall

global getuid
getuid:
	mov	eax, 104
	jmp	__syscall

global utime
utime:
	mov	eax, 132
	jmp	__syscall

global access
access:
	mov	eax, 21
	jmp	__syscall

global sync
sync:
	mov	eax, 162
	jmp	__syscall

global kill
kill:
	mov	eax, 62
	jmp	__syscall

global mkdir
mkdir:
	mov	eax, 83
	jmp	__syscall

global rmdir
rmdir:
	mov	eax, 83
	jmp	__syscall

global __dup
global dup
__dup:
dup:
	mov	eax, 32
	jmp	__syscall

global pipe
pipe:
	mov	eax, 22
	jmp	__syscall

global brk
brk:
	mov	eax, 12
	jmp	__syscall

global setgid
setgid:
	mov	eax, 106
	jmp	__syscall

global getgid
getgid:
	mov	eax, 104
	jmp	__syscall

global geteuid
geteuid:
	mov	eax, 107
	jmp	__syscall

global getegid
getegid:
	mov	eax, 108
	jmp	__syscall

global ioctl
ioctl:
	mov	eax, 16
	jmp	__syscall

global fcntl
fcntl:
	mov	eax, 72
	jmp	__syscall

global dup2
dup2:
	mov	eax, 33
	jmp	__syscall

global getppid
getppid:
	mov	eax, 110
	jmp	__syscall

global setsid
setsid:
	mov	eax, 112
	jmp	__syscall

global gettimeofday
gettimeofday:
	mov	eax, 96
	jmp	__syscall

global settimeofday
settimeofday:
	mov	eax, 164
	jmp	__syscall

global mmap
mmap:
	mov	eax, 9
	jmp	__syscall

global munmap
munmap:
	mov	eax, 11
	jmp	__syscall

global stat
stat:
	mov	eax, 4
	jmp	__syscall

global lstat
lstat:
	mov	eax, 6
	jmp	__syscall

global fstat
fstat:
	mov	eax, 5
	jmp	__syscall

global clone
clone:
	mov	eax, 56
	jmp	__syscall

global uname
uname:
	mov	eax, 63
	jmp	__syscall

global fchdir
fchdir:
	mov	eax, 81
	jmp	__syscall

global getdents
getdents:
	mov	eax, 78
	jmp	__syscall

global nanosleep
nanosleep:
	mov	eax, 35
	jmp	__syscall

global poll
poll:
	mov	eax, 7
	jmp	__syscall

global chown
chown:
	mov	eax, 92
	jmp	__syscall

global getcwd
getcwd:
	mov	eax, 79
	jmp	__syscall

global sigaction
sigaction:
	mov	eax, 13
	jmp	__syscall

global sigreturn
sigreturn:
	mov	eax, 15
	jmp	__syscall

global fsync
fsync:
	mov	eax, 74
	jmp	__syscall

global fdatasync
fdatasync:
	mov	eax, 75
	jmp	__syscall

global truncate
truncate:
	mov	eax, 76
	jmp	__syscall

global ftruncate
ftruncate:
	mov	eax, 77
	jmp	__syscall
