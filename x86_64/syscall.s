format ELF64

__syscall:
	mov	r10, rcx
	syscall

	cmp	rax, 0
	jge	done
	cmp	rax, -4095
	jb	done
	neg	rax
	mov	[errno], rax
	mov	rax, -1
done:
	ret

errno	dq	0
public errno

public _exit
_exit:
	mov	rax, 60
	jmp	__syscall

public fork
fork:
	mov	eax, 57
	jmp	__syscall

public read
read:
	mov	eax, 0
	jmp	__syscall

public write
write:
	mov	eax, 1
	jmp	__syscall

public open
open:
	mov	eax, 2
	jmp	__syscall

public close
close:
	mov	eax, 3
	jmp	__syscall

public waitpid
waitpid:
	xor	rcx, rcx
	mov	eax, 61
	jmp	__syscall

public creat
creat:
	mov	eax, 85
	jmp	__syscall

public link
link:
	mov	eax, 86
	jmp	__syscall

public unlink
unlink:
	mov	eax, 87
	jmp	__syscall

public execve
execve:
	mov	eax, 59
	jmp	__syscall

public chdir
chdir:
	mov	eax, 80
	jmp	__syscall

public time
time:
	mov	eax, 201
	jmp	__syscall

public mknod
mknod:
	mov	eax, 133
	jmp	__syscall

public chmod
chmod:
	mov	eax, 90
	jmp	__syscall

public lseek
lseek:
	mov	eax, 8
	jmp	__syscall

public getpid
getpid:
	mov	eax, 39
	jmp	__syscall

public mount
mount:
	mov	eax, 165
	jmp	__syscall

public umount
umount:
	xor	rsi, rsi
	mov	eax, 166
	jmp	__syscall

public setuid
setuid:
	mov	eax, 105
	jmp	__syscall

public getuid
getuid:
	mov	eax, 104
	jmp	__syscall

public utime
utime:
	mov	eax, 132
	jmp	__syscall

public access
access:
	mov	eax, 21
	jmp	__syscall

public sync
sync:
	mov	eax, 162
	jmp	__syscall

public kill
kill:
	mov	eax, 62
	jmp	__syscall

public mkdir
mkdir:
	mov	eax, 83
	jmp	__syscall

public rmdir
rmdir:
	mov	eax, 83
	jmp	__syscall

public __dup as 'dup'
__dup:
	mov	eax, 32
	jmp	__syscall

public pipe
pipe:
	mov	eax, 22
	jmp	__syscall

public brk
brk:
	mov	eax, 12
	jmp	__syscall

public setgid
setgid:
	mov	eax, 106
	jmp	__syscall

public getgid
getgid:
	mov	eax, 104
	jmp	__syscall

public geteuid
geteuid:
	mov	eax, 107
	jmp	__syscall

public getegid
getegid:
	mov	eax, 108
	jmp	__syscall

public ioctl
ioctl:
	mov	eax, 16
	jmp	__syscall

public fcntl
fcntl:
	mov	eax, 72
	jmp	__syscall

public dup2
dup2:
	mov	eax, 33
	jmp	__syscall

public getppid
getppid:
	mov	eax, 110
	jmp	__syscall

public setsid
setsid:
	mov	eax, 112
	jmp	__syscall

public gettimeofday
gettimeofday:
	mov	eax, 96
	jmp	__syscall

public settimeofday
settimeofday:
	mov	eax, 164
	jmp	__syscall

public mmap
mmap:
	mov	eax, 9
	jmp	__syscall

public munmap
munmap:
	mov	eax, 11
	jmp	__syscall

public stat
stat:
	mov	eax, 4
	jmp	__syscall

public lstat
lstat:
	mov	eax, 6
	jmp	__syscall

public fstat
fstat:
	mov	eax, 5
	jmp	__syscall

public clone
clone:
	mov	eax, 56
	jmp	__syscall

public uname
uname:
	mov	eax, 63
	jmp	__syscall

public fchdir
fchdir:
	mov	eax, 81
	jmp	__syscall

public nanosleep
nanosleep:
	mov	eax, 35
	jmp	__syscall

public poll
poll:
	mov	eax, 7
	jmp	__syscall

public chown
chown:
	mov	eax, 92
	jmp	__syscall

public getcwd
getcwd:
	mov	eax, 79
	jmp	__syscall

public sigaction
sigaction:
	mov	eax, 13
	jmp	__syscall

public sigreturn
sigreturn:
	mov	eax, 15
	jmp	__syscall
