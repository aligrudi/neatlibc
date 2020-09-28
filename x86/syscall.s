
global errno
errno	dd	0

__syscall:
	push	ebp
	mov	ebp, esp

	push	ebx
	push	edi
	push	esi

	mov	ebx, [ebp+8]
	mov	ecx, [ebp+12]
	mov	edx, [ebp+16]
	mov	esi, [ebp+20]
	mov	edi, [ebp+24]
	mov	ebp, [ebp+28]

	int	0x80

	cmp	eax, -125
	jb	done
	neg	eax
	mov	[errno], eax
	mov	eax, -1
done:
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret

global _exit
_exit:
	mov	eax, 1
	jmp	__syscall

global fork
fork:
	mov	eax, 2
	jmp	__syscall

global read
read:
	mov	eax, 3
	jmp	__syscall

global write
write:
	mov	eax, 4
	jmp	__syscall

global open
open:
	mov	eax, 5
	jmp	__syscall

global close
close:
	mov	eax, 6
	jmp	__syscall

global waitpid
waitpid:
	mov	eax, 7
	jmp	__syscall

global creat
creat:
	mov	eax, 8
	jmp	__syscall

global link
link:
	mov	eax, 9
	jmp	__syscall

global unlink
unlink:
	mov	eax, 10
	jmp	__syscall

global execve
execve:
	mov	eax, 11
	jmp	__syscall

global chdir
chdir:
	mov	eax, 12
	jmp	__syscall

global time
time:
	mov	eax, 13
	jmp	__syscall

global mknod
mknod:
	mov	eax, 14
	jmp	__syscall

global chmod
chmod:
	mov	eax, 15
	jmp	__syscall

global lseek
lseek:
	mov	eax, 19
	jmp	__syscall

global getpid
getpid:
	mov	eax, 20
	jmp	__syscall

global mount
mount:
	mov	eax, 21
	jmp	__syscall

global umount
umount:
	mov	eax, 22
	jmp	__syscall

global setuid
setuid:
	mov	eax, 23
	jmp	__syscall

global getuid
getuid:
	mov	eax, 24
	jmp	__syscall

global utime
utime:
	mov	eax, 30
	jmp	__syscall

global access
access:
	mov	eax, 33
	jmp	__syscall

global sync
sync:
	mov	eax, 36
	jmp	__syscall

global kill
kill:
	mov	eax, 37
	jmp	__syscall

global mkdir
mkdir:
	mov	eax, 39
	jmp	__syscall

global rmdir
rmdir:
	mov	eax, 40
	jmp	__syscall

global __dup
global dup
dup:
__dup:
	mov	eax, 41
	jmp	__syscall

global pipe
pipe:
	mov	eax, 42
	jmp	__syscall

global brk
brk:
	mov	eax, 45
	jmp	__syscall

global setgid
setgid:
	mov	eax, 46
	jmp	__syscall

global getgid
getgid:
	mov	eax, 47
	jmp	__syscall

global signal
signal:
	mov	eax, 48
	jmp	__syscall

global geteuid
geteuid:
	mov	eax, 49
	jmp	__syscall

global getegid
getegid:
	mov	eax, 50
	jmp	__syscall

global ioctl
ioctl:
	mov	eax, 54
	jmp	__syscall

global fcntl
fcntl:
	mov	eax, 55
	jmp	__syscall

global dup2
dup2:
	mov	eax, 63
	jmp	__syscall

global getppid
getppid:
	mov	eax, 64
	jmp	__syscall

global setsid
setsid:
	mov	eax, 66
	jmp	__syscall

global gettimeofday
gettimeofday:
	mov	eax, 78
	jmp	__syscall

global settimeofday
settimeofday:
	mov	eax, 79
	jmp	__syscall

global mmap
mmap:
	mov	eax, 192
	jmp	__syscall

global munmap
munmap:
	mov	eax, 91
	jmp	__syscall

global stat
stat:
	mov	eax, 106
	jmp	__syscall

global lstat
lstat:
	mov	eax, 107
	jmp	__syscall

global fstat
fstat:
	mov	eax, 108
	jmp	__syscall

global clone
clone:
	mov	eax, 120
	jmp	__syscall

global uname
uname:
	mov	eax, 122
	jmp	__syscall

global fchdir
fchdir:
	mov	eax, 133
	jmp	__syscall

global getdents
getdents:
	mov	eax, 141
	jmp	__syscall

global nanosleep
nanosleep:
	mov	eax, 162
	jmp	__syscall

global poll
poll:
	mov	eax, 168
	jmp	__syscall

global chown
chown:
	mov	eax, 182
	jmp	__syscall

global getcwd
getcwd:
	mov	eax, 183
	jmp	__syscall

global sigaction
sigaction:
	mov	eax, 67
	jmp	__syscall

global sigreturn
sigreturn:
	mov	eax, 119
	jmp	__syscall

global fsync
fsync:
	mov	eax, 118
	jmp	__syscall

global fdatasync
fdatasync:
	mov	eax, 148
	jmp	__syscall

global truncate
truncate:
	mov	eax, 92
	jmp	__syscall

global ftruncate
ftruncate:
	mov	eax, 93
	jmp	__syscall
