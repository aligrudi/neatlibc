format ELF

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

errno	dd	0
public errno

public _exit
_exit:
	mov	eax, 1
	jmp	__syscall

public fork
fork:
	mov	eax, 2
	jmp	__syscall

public read
read:
	mov	eax, 3
	jmp	__syscall

public write
write:
	mov	eax, 4
	jmp	__syscall

public open
open:
	mov	eax, 5
	jmp	__syscall

public close
close:
	mov	eax, 6
	jmp	__syscall

public waitpid
waitpid:
	mov	eax, 7
	jmp	__syscall

public creat
creat:
	mov	eax, 8
	jmp	__syscall

public link
link:
	mov	eax, 9
	jmp	__syscall

public unlink
unlink:
	mov	eax, 10
	jmp	__syscall

public execve
execve:
	mov	eax, 11
	jmp	__syscall

public chdir
chdir:
	mov	eax, 12
	jmp	__syscall

public time
time:
	mov	eax, 13
	jmp	__syscall

public mknod
mknod:
	mov	eax, 14
	jmp	__syscall

public chmod
chmod:
	mov	eax, 15
	jmp	__syscall

public lseek
lseek:
	mov	eax, 19
	jmp	__syscall

public getpid
getpid:
	mov	eax, 20
	jmp	__syscall

public mount
mount:
	mov	eax, 21
	jmp	__syscall

public umount
umount:
	mov	eax, 22
	jmp	__syscall

public setuid
setuid:
	mov	eax, 23
	jmp	__syscall

public getuid
getuid:
	mov	eax, 24
	jmp	__syscall

public sync
sync:
	mov	eax, 36
	jmp	__syscall

public kill
kill:
	mov	eax, 37
	jmp	__syscall

public mkdir
mkdir:
	mov	eax, 39
	jmp	__syscall

public rmdir
rmdir:
	mov	eax, 40
	jmp	__syscall

public __dup as 'dup'
__dup:
	mov	eax, 41
	jmp	__syscall

public pipe
pipe:
	mov	eax, 42
	jmp	__syscall

public brk
brk:
	mov	eax, 45
	jmp	__syscall

public setgid
setgid:
	mov	eax, 46
	jmp	__syscall

public getgid
getgid:
	mov	eax, 47
	jmp	__syscall

public signal
signal:
	mov	eax, 48
	jmp	__syscall

public geteuid
geteuid:
	mov	eax, 49
	jmp	__syscall

public getegid
getegid:
	mov	eax, 50
	jmp	__syscall

public ioctl
ioctl:
	mov	eax, 54
	jmp	__syscall

public fcntl
fcntl:
	mov	eax, 55
	jmp	__syscall

public dup2
dup2:
	mov	eax, 62
	jmp	__syscall

public getppid
getppid:
	mov	eax, 64
	jmp	__syscall

public setsid
setsid:
	mov	eax, 66
	jmp	__syscall

public gettimeofday
gettimeofday:
	mov	eax, 78
	jmp	__syscall

public settimeofday
settimeofday:
	mov	eax, 79
	jmp	__syscall

public mmap
mmap:
	mov	eax, 192
	jmp	__syscall

public munmap
munmap:
	mov	eax, 91
	jmp	__syscall

public stat
stat:
	mov	eax, 106
	jmp	__syscall

public lstat
lstat:
	mov	eax, 107
	jmp	__syscall

public fstat
fstat:
	mov	eax, 108
	jmp	__syscall

public clone
clone:
	mov	eax, 120
	jmp	__syscall

public uname
uname:
	mov	eax, 122
	jmp	__syscall

public fchdir
fchdir:
	mov	eax, 133
	jmp	__syscall

public nanosleep
nanosleep:
	mov	eax, 162
	jmp	__syscall

public poll
poll:
	mov	eax, 168
	jmp	__syscall

public chown
chown:
	mov	eax, 182
	jmp	__syscall

public getcwd
getcwd:
	mov	eax, 183
	jmp	__syscall
