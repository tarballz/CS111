import os

iteration = 1

for i in range(iteration):
	os.system("""echo '' > /var/log/debug.log &&
	           stress-ng --vm 14 --vm-bytes=256m -t 3m &&
	           cp /var/log/debug.log ./{}_debug.log &&
	           chmod 777 *.log && sleep 60""".format(i))

